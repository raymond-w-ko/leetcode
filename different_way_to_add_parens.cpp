#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
 public:
  bool is_op(char ch) {
    return (ch == '+' || ch == '-' || ch == '*');
  }
  vector<int> diffWaysToCompute(string input) {
    vector<int> results;
    
    bool just_num = true;
    for (int i = 0; i < input.size(); ++i) {
      char ch = input[i];
      if (is_op(ch)) {
        just_num = false;
        string l = input.substr(0, i);
        string r = input.substr(i + 1);
        auto lefts = diffWaysToCompute(l);
        auto rights = diffWaysToCompute(r);
        
        for (int left : lefts) {
          for (int right : rights) {
            int result = 0;
            switch (ch) {
              case '+': result = left + right; break;
              case '-': result = left - right; break;
              case '*': result = left * right; break;
            }
            results.push_back(result);
          }
        }
      }
    }
    
    if (just_num) {
      results.push_back(atoi(input.c_str()));
    }
    
    return results;
  }
};

int main() {
  Solution sol;
  auto nums = sol.diffWaysToCompute("2*3-4*5");
  for (auto num : nums) {
    cout << num << " ";
  }
  cout << "\n";
  return 0;
}
