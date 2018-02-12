/*
 MagicNumbers.cc
 Author: Andrea Bisbano
 Date: 18/01/18
 Problem: http://codeforces.com/problemset/problem/320/A?locale=en
 Solution:
  The idea is to search the numbers composing a magic number with a greedy approch. We look every
  digit of the input number looking if it can be part of a magic number. When we find an impossible
  concatenation the algorithm terminates with false response, true otherwise.
 Time cost: O(N) where N is the number of digits of the input number.
 Space cost: O(1)
 */

#include <iostream>
#include <cassert>
#include <string>

bool isMagic(const std::string &number) {
  char last = '\0';
  char last2 = '\0';
  for (const char &c : number) {
    if (c == '1') {
      last2 = last;
      last = c;
      continue;
    }
    if (c == '4') {
      if (last == '1' || (last == '4' && last2 == '1')) {
        last2 = last;
        last = c;
        continue;
      }
    }
    return false;
  }
  return true;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string number;
  std::cin >> number;
  assert(number.length() >= 1 && number.length() <= 10);

  std::cout << (isMagic(number) ? "YES" : "NO") << "\n";
  return 0;
}
