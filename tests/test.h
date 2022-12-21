#ifndef FORMALLANGUAGE_PRACTIE_TEST_TEST_H_
#define FORMALLANGUAGE_PRACTIE_TEST_TEST_H_
#include <gtest/gtest.h>
#include "../include/AlgorithmCYK.cpp"
class TestAlgorithmCYK : public AlgorithmCYK {
 public:
  TestAlgorithmCYK() : AlgorithmCYK () {};
  explicit TestAlgorithmCYK(GrammarChomsky& grammar) : AlgorithmCYK(grammar) {}
  int64_t GetQuantityRules() {
    return rules_.size();
  }
  std::unordered_map<char, std::vector<std::string>> GetRules() {
    return rules_;
  }
  bool GetResultCYK(const std::string& word) {
    return ResultCYK(word);
  }
  void SetWord(const std::string & word) {
    word_ = word;
  }
};
#endif //FORMALLANGUAGE_PRACTIE_TEST_TEST_H_
