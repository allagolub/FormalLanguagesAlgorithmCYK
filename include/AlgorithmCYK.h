#ifndef FORMALLANGUAGE
#define FORMALLANGUAGE
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <stack>
#include <utility>
#include <queue>

struct GrammarRules {
  char left_part_;
  std::string right_part_;
  GrammarRules(const char left_part, const std::string& right_part) {
    left_part_ = left_part;
    right_part_ = right_part;
  }
  GrammarRules() = default;
};
class Grammar {
 public:
  void AddRule(const std::string& rule);
  Grammar(const std::unordered_map<char, std::vector<std::string>>& rules) : rules_(std::move(rules)) {};
  Grammar() = default;
  std::unordered_map<char, std::vector<std::string>> rules_;
  void GrammarToChomsky();

 protected:
  std::vector<bool> used_symbols_ = std::vector<bool>(34, false);
  std::vector<char> used_terminals_ = std::vector<char>(34, '1');
  int first_available_symbol = 0;
  std::set<char> epsilon_left_part;
  std::set<char> new_epsilon_left_part;
  void InsertRule(char left_part, std::string right_part);
  bool IsTerminal(char symbol);
  void DeleteLongRules();
  bool CheckChainRules(char symbol);
  void DeleteChainRules();
  void DeleteMultipleTerminals();
  void DeleteEpsilon();
  void FindEpsilon();
};

class GrammarChomsky {
 public:
  GrammarChomsky(Grammar &grammar) : rules_(std::move(grammar.rules_)) {
    for (auto& it : rules_) {
      non_terminals_.insert(it.first);
    }
  };
  GrammarChomsky(const std::set<char>& non_terminals, const std::unordered_map<char, std::vector<std::string>>& rules)
      : non_terminals_(non_terminals), rules_(std::move(rules)) {};

  std::set<char> non_terminals_;
  std::unordered_map<char, std::vector<std::string>> rules_;
  GrammarChomsky() = default;

 protected:
  bool IsTerminal(char symbol);
};

class AlgorithmCYK : public GrammarChomsky {
 public:
  bool ResultCYK(const std::string& word);
  AlgorithmCYK(GrammarChomsky &grammar) : GrammarChomsky(grammar.non_terminals_, grammar.rules_) {};
  AlgorithmCYK() = default;

 protected:
  std::map<char, std::vector<std::vector<bool>>> dp_;
  std::string word_;
  bool CYK();
};
#endif //FORMALLANGUAGE