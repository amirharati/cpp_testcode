#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <fstream>
#include "Poco/RegularExpression.h"

using namespace std;
using Poco::RegularExpression;

/*class RegWrapper {
public:
  //string key;
  RegularExpression *re;

};
*/ 
// map<string, string> rules;
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
    // rules_a["\xE2\x80\x99"] = "'";
    ifstream infile(input_file_a);
    string pattern, rule;
    while (infile >> pattern >> rule) {
      // cout << pattern << "--->" << rule << endl;
      // only add this if pattern is 
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
    //vector<RegWrapper> rw;
    //map<string, RegularExpression*> rw;
    for (const auto& k : rules_a) {
      // RegularExpression *re = new RegularExpression(k.first);
      unique_ptr<RegularExpression> re(new RegularExpression(k.first));
      //compiled_rules_a[k.first] = &re;
      compiled_rules_a[k.first].first = std::move(re);
      compiled_rules_a[k.first].second = k.second;
    }
    return;
  }

  void text_normalize(const string& input_str_a, string& output_a,
   const map<string, RegExpPtr_Str_Pair> &compiled_rules_a) {
    // string s = "Who’s amir is 20 abc Who's ";
    output_a = input_str_a;
    for (const auto& k : compiled_rules_a) {
      //RegularExpression *re = k.second;
      k.second.first->subst(output_a, k.second.second);
      // std::cout<<s<<std::endl;
    }
    return;
  }
}
int main(int argc, char** argv) {
  map<string, string> rules;
  string input_str = "Who’s amir is 20 abc Who's";
  string output = "";
  map<string, POCO_TEXTNORM::RegExpPtr_Str_Pair> compiled_rules;
  POCO_TEXTNORM::read_rules("rules.txt", rules);
  /*for (auto & k : rules) {
    cout << k.first << " " << k.second << endl;
  }*/
  POCO_TEXTNORM::compile_rules(rules, compiled_rules);
  POCO_TEXTNORM::text_normalize(input_str, output, compiled_rules);
  cout << input_str << "-->" << output << endl;
  return 0;
}
