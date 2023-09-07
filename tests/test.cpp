#include "test.h"

TEST(Test, TestResult) {
  Grammar grammar;
  grammar.AddRule("S->A");
  grammar.AddRule("A->e");
  grammar.AddRule("A->BB");
  grammar.AddRule("A->CD");
  grammar.AddRule("B->BB");
  grammar.AddRule("B->CD");
  grammar.AddRule("C->(");
  grammar.AddRule("D->BE");
  grammar.AddRule("D->)");
  grammar.AddRule("E->)");
  GrammarChomsky grammar_chomsky(grammar);
  TestAlgorithmCYK test_algorithm_cyk(grammar_chomsky);
  EXPECT_TRUE(test_algorithm_cyk.ResultCYK("()"));
  EXPECT_FALSE(test_algorithm_cyk.ResultCYK("(()("));
  EXPECT_FALSE(test_algorithm_cyk.ResultCYK("(((()"));
  EXPECT_TRUE(test_algorithm_cyk.ResultCYK("()(())"));
}
TEST(Test, TestGrammarToChomsky) {
  Grammar grammar;
  grammar.AddRule("S->aXbX");
  grammar.AddRule("S->aZ");
  grammar.AddRule("X->aY");
  grammar.AddRule("X->bY");
  grammar.AddRule("X->e");
  grammar.AddRule("Y->X");
  grammar.AddRule("Y->cc");
  grammar.AddRule("Z->ZX");
  grammar.GrammarToChomsky();
  GrammarChomsky grammar_chomsky(grammar);
  TestAlgorithmCYK test_algorithm_cyk(grammar_chomsky);
  EXPECT_FALSE(test_algorithm_cyk.ResultCYK("acc"));
}
TEST(Test, TestDeleteMultipleTerminals) {
  Grammar grammar;
  grammar.AddRule("S->aX");
  grammar.AddRule("S->ab");
  grammar.GrammarToChomsky();
  GrammarChomsky grammar_chomsky(grammar);
  TestAlgorithmCYK test_algorithm_cyk(grammar_chomsky);
  EXPECT_TRUE(test_algorithm_cyk.GetRules()['B'][0] == "b");
  EXPECT_TRUE(test_algorithm_cyk.GetRules()['A'][0] == "a");
  EXPECT_TRUE(test_algorithm_cyk.GetRules()['S'][0] == "AX");
  EXPECT_TRUE(test_algorithm_cyk.GetRules()['S'][1] == "AB");
}
TEST(Test, TestGrammar) {
  Grammar grammar;
  grammar.AddRule("S->a");
  grammar.AddRule("S->BB");
  grammar.GrammarToChomsky();
  GrammarChomsky grammar_chomsky(grammar);
  TestAlgorithmCYK test_algorithm_cyk(grammar_chomsky);
  EXPECT_TRUE(test_algorithm_cyk.GetRules()['S'].size() == 2);
}