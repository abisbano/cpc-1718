/*
 ShiftString
 Author: Andrea Bisbano
 Date: 29/06/18
 Problem: https://www.codechef.com/problems/TASHIFT
 Solution:
  This algorithm implements a variant of KMP algorithm. At first, it creates the failure table
  to store the number of charaters that the algorithm can skip if there's a mismatch.
  Then it compares the two strings keeping count of the LCP: every time it increse the algorithm
  computes the number of shift operation performed.
  Instead of using modular operation, this implementation concatenates the second string to itself
  to have all the possible shifting.
 Time cost: O(N)
 Space cost: O(N)
*/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

std::vector<size_t> failure(std::string &str) {
  size_t len = str.size();
  std::vector<size_t> fails(len+1, 0);
  size_t k = 0;

  for (size_t i = 2; i <= len; ++i) {
    while (k != 0 && str[i-1] != str[k]) {
      k = fails[k];
    }
    if (str[i-1] == str[k]) {
      k++;
    }
    fails[i] = k;
  }

  return fails;
}

size_t shiftString(const std::string &str1, const std::string &str2,
             const std::vector<size_t> &fails) {

  size_t k = 0;
  size_t maxLength = 0;
  size_t result = 0;

  for (size_t i = 1, len = str2.size(); i < len; ++i) {
    while (k != 0 && str1[k] != str2[i-1]) {
      k = fails[k];
    }
    if (str1[k] == str2[i-1]) {
      k++;
    }
    if (k > maxLength) {
      maxLength = k;
      result = i - k;
    }
  }

  return result;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t N;
  std::string str1, str2;

  std::cin >> N >> str1 >> str2;
  assert(N <= 1000000);
  str2 += str2;
  auto fails = failure(str1);
  std::cout << shiftString(str1, str2, fails) << "\n";
}
