#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <fstream>
#include "Poco/RegularExpression.h"
#include "Poco/String.h"

using namespace std;
using Poco::RegularExpression;

namespace POCO_TEXTNORM {
  typedef pair<unique_ptr<RegularExpression>, string> RegExpPtr_Str_Pair;
  // read rules into a map
  void read_rules(const string& input_file_a, map<string, string>& rules_a);
  // complie rules for future use
  void compile_rules(const map<string, string>& rules_a, map<string,
   RegExpPtr_Str_Pair> &compiled_rules_a);
  // normlaize the input text based on rules
  
  void text_normalize(const string& input_str_a, string& output_a,
    const map<string, RegExpPtr_Str_Pair> &compiled_rules_a);
  

  void read_rules(const string& input_file_a, map<string, string>& rules_a) {
 
    ifstream infile(input_file_a);
    string pattern, rule;
    while (infile >> pattern >> rule) {
      pattern = Poco::toLower(pattern);
      if (rules_a.count(pattern) == 0) {
        rules_a[pattern] = rule;
      }
      else {
        cout << "Warning: replicated pattern!" << endl;
      }
    }
  	return;
  }

  void compile_rules(const map<string, string>& rules_a, map<string,
   RegExpPtr_Str_Pair>&compiled_rules_a) {
    for (const auto& k : rules_a) {
      unique_ptr<RegularExpression> re(new RegularExpression(k.first));
      compiled_rules_a[k.first].first = std::move(re);
      compiled_rules_a[k.first].second = k.second;
    }
    return;
  }

  void text_normalize(const string& input_str_a, string& output_a,
   const map<string, RegExpPtr_Str_Pair> &compiled_rules_a) {
    output_a = input_str_a;
    for (const auto& k : compiled_rules_a) {
      k.second.first->subst(output_a, k.second.second);

    }
    return;
  }
}
// simple test
int main(int argc, char** argv) {
  map<string, string> rules;
  string input_str = "`⁽‐Who’s vs. Who's";
  string output = "";
  map<string, POCO_TEXTNORM::RegExpPtr_Str_Pair> compiled_rules;
  POCO_TEXTNORM::read_rules("rules.txt", rules);
  POCO_TEXTNORM::compile_rules(rules, compiled_rules);
  POCO_TEXTNORM::text_normalize(input_str, output, compiled_rules);
  cout << input_str << " --> " << output << endl;
  return 0;
}
