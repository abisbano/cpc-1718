/*
 ChatRoom.cc
 Author: Andrea Bisbano
 Date: 18/01/18
 Problem: http://codeforces.com/problemset/problem/58/A?locale=en
 Solution:
  The idea is to search the letter composing the word `hello' with a greedy approach: the algorithm scans
  the input string looking for one letter per time and when it's found it starts looking for the next one.
  If and when the whole word is found it terminates, otherwise it returns a negative response after
  scanning the whole string.
 Time cost: O(N) in worst case because it needs to scan the whole input string.
 Space cost: O(1)
*/

#include<iostream>
#include<cassert>
#include<string>

bool isHello(std::string word) {
  std::string hello = "hello";
  uint64_t index = 0;

  for (char c : word) {
    if (c ==  hello[index]) {
      ++index;
      if (index >= 5)
        return true;
    }
  }
  return false;

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string word;
  std::cin >> word;
  assert(word.length() >= 1 && word.length() <= 100);

  std::cout << (isHello(word) ? "YES" : "NO") << "\n";

}
