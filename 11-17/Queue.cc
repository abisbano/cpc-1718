/*
  Queue.cc

  author: Andrea Bisbano
  date: 22/01/18
  problem: http://codeforces.com/problemset/problem/141/C?locale=en

  solution description:

 FIXME: Clean code and write description of solution

 */

#include <vector>
#include <iostream>
#include <cassert>
#include <string>

struct person {
  std::string name;
  uint64_t higher;

  person(std::string n, uint64_t h) : name(n), higher(h) {}
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;
  std::vector<person> queue;
  std::string name;
  uint64_t height;

  std::cin >> n;
  assert(n >= 1 && n <= 3000);
  queue.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> name >> height;
    assert(true);
    queue.emplace_back(name, height);
  }

}



