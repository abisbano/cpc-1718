/*
 AlternativeThinking.cc
 Author: Andrea Bisbano
 Date: 18/01/18
 Problem: http://codeforces.com/problemset/problem/603/A?locale=en
 Solution:
  This algorithm counts the number of characters that are different from its predecessor and add
  to that result 2 because a flipping can increse the length of the subsequence of ad most 2.
  The only case when don't increse the subsequence length by 2 is when the subsequence in the
  whole sequence. So after the computation we choose the minimum between this value and the length
  of the input string.
 Time cost: O(N) because we need to read the whole string one time.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>

uint64_t countAlternative(const std::string &str, uint64_t n) {
  uint64_t count = 2;
  char last = '\0';
  for (const char &c : str) {
    if (c != last) {
      ++count;
      last = c;
    }
  }
  return std::min(count, n);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n;
  std::string str;

  std::cin >> n;
  std::cin >> str;

  std::cout << countAlternative(str, n) << "\n";
  return 0;

}
