/*
 LexicographicallyMaximumSubsequence.cc
 Author: Andrea Bisbano
 Date: 10/10/17
 Problem: http://codeforces.com/problemset/problem/196/A?locale=en
 Solution:
  This algorithms uses a greedy approach and starts processing the input string from the end and
  add any character only if it's lexicographically larger or equal to the last added.
  The solution is then the reverse of the string computed previously.
 Time cost: O(n) to read the whole string one time.
 Space cost: O(1)
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
  std::cin >> str;

  std::cout << maxSubsequence(str) << std::endl;
}
