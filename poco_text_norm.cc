#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include "Poco/RegularExpression.h"

using namespace std;
using Poco::RegularExpression;

class RegWrapper {
public:
  //string key;
  RegularExpression *re;

}; 
// map<string, string> rules;


// read rules into a map
void read_rules(const string& input_file_a, map<string, string>& rules_a);
// complie rules for future use
void compile_rules(const map<string, string>& rules_a, map<string,
 unique_ptr<RegularExpression>> &compiled_rules_a);
// normlaize the input text based on rules
void text_normalize(const string& input_str_a, string& output_a,
 const map<string, string>& rules_a,
  const map<string, unique_ptr<RegularExpression>> &compiled_rules_a);


void read_rules(const string& input_file_a, map<string, string>& rules_a) {
  rules_a["\xE2\x80\x99"] = "'";

	return;
}

void compile_rules(const map<string, string>& rules_a, map<string,
 unique_ptr<RegularExpression>> &compiled_rules_a) {
  //vector<RegWrapper> rw;
  //map<string, RegularExpression*> rw;
  for (const auto& k : rules_a) {
    // RegularExpression *re = new RegularExpression(k.first);
    unique_ptr<RegularExpression> re(new RegularExpression(k.first));
    //compiled_rules_a[k.first] = &re;
    compiled_rules_a[k.first] = std::move(re);
  }
  return;
}

void text_normalize(const string& input_str_a, string& output_a,
 const map<string, string>& rules_a,
 const map<string, unique_ptr<RegularExpression>> &compiled_rules_a) {
  string s = "Who’s amir is 20 abc Who's ";
  for (const auto& k : compiled_rules_a) {
    //RegularExpression *re = k.second;
    k.second->subst(s, "'");
    std::cout<<s<<std::endl;
  }
  return;
}

int main(int argc, char** argv) {
  map<string, string> rules;
  string input_str = "";
  string output = "";
  map<string, unique_ptr<RegularExpression>> compiled_rules;
  read_rules("", rules);
  for (auto & k : rules) {
    cout << k.first << " " << k.second << endl;
  }
  compile_rules(rules, compiled_rules);
  text_normalize(input_str, output, rules, compiled_rules);
  return 0;
}
