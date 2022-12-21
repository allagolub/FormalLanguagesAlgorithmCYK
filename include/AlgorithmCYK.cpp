#include <iostream>
#include <cstring>
#include "AlgorithmCYK.h"

bool Grammar::IsTerminal(char symbol) {
  return std::islower(symbol);
}
void Grammar::InsertRule(char left_part, std::string right_part) {
  rules_[left_part].emplace_back(right_part);
}
void Grammar::AddRule(const std::string& rule) {
  char left_part = rule[0];
  std::string right_part;
  used_symbols_[int(left_part) - int('A')] = -1;
  right_part = rule.substr(3, rule.size());
  if (right_part == "e") {
    epsilon_left_part.insert(left_part);
    return;
  }
  InsertRule(left_part, right_part);
}
void Grammar::DeleteLongRules() {
  std::queue<std::pair<char, std::string>> queue;
  for (auto& rules : rules_) {
    for (auto right_part = rules.second.begin(); right_part  != rules.second.end(); ++right_part) {
      if ((*(right_part)).size() > 2) {
        while (used_symbols_[first_available_symbol]) {
          first_available_symbol++;
        }
        char new_left_part = (char(first_available_symbol + int('A')));
        std::string tmp = (*(right_part)).substr(1, (*(right_part)).size());
        queue.push(make_pair(new_left_part, tmp));
        std::string new_rule;
        new_rule.push_back((*right_part)[0]);
        used_symbols_[first_available_symbol] = true;
        new_rule.push_back(char(first_available_symbol + 'A'));
        (*right_part) = new_rule;
      }
    }
  }
  std::string right_part;
  char left_part;
  while (!queue.empty()) {
    left_part = queue.front().first;
    right_part = queue.front().second;
    queue.pop();
    if (right_part.size() > 2) {
      while (used_symbols_[first_available_symbol]) {
        first_available_symbol++;
      }
      char new_left_part = (char(first_available_symbol + int('A')));
      std::string tmp;
      tmp.push_back(right_part[0]);
      tmp.push_back(new_left_part);
      rules_[left_part].emplace_back(tmp);
      tmp = (right_part).substr(1, (right_part).size());
      used_symbols_[first_available_symbol] = true;
      queue.push(make_pair(new_left_part, tmp));
    } else {
      rules_[left_part].emplace_back(right_part);
    }
  }
}
void Grammar::FindEpsilon() {
  bool is_change = true;
  while (is_change) {
    is_change = false;
    for (auto &rules : rules_) {
      if ((epsilon_left_part.find(rules.first) != epsilon_left_part.end()) || (new_epsilon_left_part.find(rules.first) != new_epsilon_left_part.end())) {
        continue;
      }
      for (auto &right_part : rules_[rules.first]) {
        bool epsilon_find = true;
        for (auto &str : right_part) {
          if (epsilon_left_part.find(str) == epsilon_left_part.end()) {
            epsilon_find = false;
            break;
          }
        }
        if (epsilon_find) {
          new_epsilon_left_part.insert(rules.first);
          epsilon_left_part.insert(rules.first);
          is_change = true;
          break;
        }
      }
    }
  }
}
void Grammar::DeleteEpsilon() {
  FindEpsilon();
  for (auto &rules : rules_) {
    if ((epsilon_left_part.find(rules.first) != epsilon_left_part.end())
        && (new_epsilon_left_part.find(rules.first) == new_epsilon_left_part.end())) {
      continue;
    }
    auto it = rules_[rules.first].begin();
    for (auto &right_part : rules_[rules.first]) {
      if ((right_part.size() == 1) && (epsilon_left_part.find(right_part[0]) != epsilon_left_part.end())) {
        char old_rule = right_part[0];
        it = rules_[rules.first].erase(it);
        for (auto& elem : rules_[old_rule]) {
          rules_[rules.first].emplace_back(elem);
        }
      }
      if ((right_part.size() == 2) && (epsilon_left_part.find(right_part[1]) != epsilon_left_part.end())) {
        if (right_part[0] != rules.first) {
          std::string tmp;
          tmp.push_back(right_part[0]);
          rules_[rules.first].emplace_back(tmp);
        }
      }
      if ((right_part.size() == 2) && (epsilon_left_part.find(right_part[0]) != epsilon_left_part.end())) {
        if (right_part[1] != rules.first) {
          std::string tmp;
          tmp.push_back(right_part[1]);
          rules_[rules.first].emplace_back(tmp);
        }
      }
      it++;
    }
  }
}
void Grammar::DeleteChainRules() {
  for (auto& rules : rules_) {
    CheckChainRules(rules.first);
  }
}
bool Grammar::CheckChainRules(char symbol) {
  auto it = rules_[symbol].begin();
  for (auto& right_part : rules_[symbol]) {
    if ((right_part.size() == 1) && (!IsTerminal((right_part[0]))) && std::isalpha(right_part[0])) {
      CheckChainRules(right_part[0]);
      it = rules_[symbol].erase(it);
      for (auto& it : rules_[right_part[0]]) {
        rules_[symbol].emplace_back(it);
      }
    }
    ++it;
  }
}
void Grammar::DeleteMultipleTerminals() {
  for (auto& rules : rules_) {
    for (auto& right_part : rules_[rules.first]) {
      if ((right_part.size() == 2) && ((IsTerminal(right_part[0])) || (IsTerminal(right_part[1])) ||
          (!std::isalpha(right_part[0])) || (!std::isalpha(right_part[1])))) {
        if (IsTerminal(right_part[0]) || (!std::isalpha(right_part[0]))) {
          if (used_terminals_[int(right_part[0] - 'a')] != '1') {
            right_part[0] = used_terminals_[int(right_part[0] - 'a')];
          } else {
            while (used_symbols_[first_available_symbol]) {
              first_available_symbol++;
            }
            used_symbols_[first_available_symbol] = true;
            char new_symbol = (char(first_available_symbol + int('A')));
            used_terminals_[int(right_part[0] - 'a')] = new_symbol;
            std::string tmp;
            tmp.push_back(right_part[0]);
            rules_[new_symbol].emplace_back(tmp);
            right_part[0] = new_symbol;
          }
        }
        if (IsTerminal(right_part[1]) || (!std::isalpha(right_part[1]))) {
          if (used_terminals_[int(right_part[1] - 'a')] != '1') {
            right_part[1] = used_terminals_[int(right_part[1] - 'a')];
          } else {
            while (used_symbols_[first_available_symbol]) {
              first_available_symbol++;
            }
            used_symbols_[first_available_symbol] = true;
            char new_symbol = (char(first_available_symbol + int('A')));
            used_terminals_[int(right_part[1] - 'a')] = new_symbol;
            std::string tmp;
            tmp.push_back(right_part[1]);
            rules_[new_symbol].emplace_back(tmp);
            right_part[1] = new_symbol;
          }
        }
      }
    }
  }
}

bool AlgorithmCYK::CYK() {
  int size = word_.size();
  for (auto &it : non_terminals_) {
    dp_[it].resize(size, std::vector<bool>(size, false));
  }
  for (int i = 0; i < size; ++i) {
    for (auto &it_first : rules_) {
      for (auto &it_second : it_first.second) {
        if ((it_second.size() == 1) && (it_second[0] == word_[i])) {
          dp_[it_first.first][i][i] = true;
        }
      }
    }
  }
  for (int quantity = 1; quantity < size; ++quantity) {
    for (int j = 1; j < size; ++j) {
      for (int i = 0; i < j; ++i) {
        for (int k = i; k < j; ++k) {
          for (auto &rules : rules_) {
            for (auto &right_part : rules.second) {
              if ((right_part.size() == 2) && (dp_[right_part[0]][i][k]) && (dp_[right_part[1]][k + 1][j])) {
                dp_[rules.first][i][j] = true;
              }
            }
          }
        }
      }
    }
  }
  return dp_['A'][0][size - 1];
}
void Grammar::GrammarToChomsky() {
  DeleteLongRules();
  DeleteEpsilon();
  DeleteChainRules();
  DeleteMultipleTerminals();
}
bool AlgorithmCYK::ResultCYK(const std::string& word) {
  if (word == "e") {
    return (std::find(rules_['A'].begin(), rules_['A'].end(),"") != rules_['A'].end());
  } else {
    word_ = word;
  }
  return CYK();
}