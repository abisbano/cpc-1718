/*
  LexicographicallyMaximumSubsequence.cc

  author: Andrea Bisbano
  date: 10/10/17
  problem: http://codeforces.com/problemset/problem/196/A?locale=en

  solution description:
  F

 */

#include<algorithm>
#include<iostream>
#include<cassert>
#include<string>

std::string maxSubsequence(const std::string &str) {
  std::string result = "";
  char max = '\0';

  for (int i = str.length(); i >= 0; --i) {
    if (str[i] >= max) {
      max = str[i];
      result += str[i];
    }
  }
  std::reverse(result.begin(), result.end());
  result.pop_back();
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string str;

  std::cin >>str;

  std::cout << maxSubsequence(str) << std::endl;

}
