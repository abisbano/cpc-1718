/*
  ChatRoom.cc

  author: Andrea Bisbano
  date: 18/01/18
  problem: http://codeforces.com/problemset/problem/58/A?locale=en

  solution description:
  TO BE WRITTEN

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
