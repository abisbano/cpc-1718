/*
 Queue.cc
 Author: Andrea Bisbano
 Date: 22/01/18
 Problem: http://codeforces.com/problemset/problem/141/C?locale=en
 Solution:
  This algorithm sorts in non decreasing order the input array by the number of people higher in front of any
  person. If the value is higher than the index in the sorted array the solution is impossible and the returns
  -1. Then it assigns the initial height of each person as the difference between that value and the index in
  the sorted array. For each element, it compares its height with the height of the previous assigned and
  increments the ones that are smaller.
 Time cost: O(NlogN)
 Space cost: O(N) to store the heights.
*/

#include <vector>
#include <iostream>
#include <cassert>
#include <algorithm>

struct person {
  std::string name;
  uint64_t higher;
  uint64_t height;

  person(std::string n, uint64_t h) : name(n), higher(h), height(0) {}
};

bool computeQueue(std::vector<person> &queue) {
  size_t n = queue.size();
  std::sort(queue.begin(), queue.end(),
            [] (const person &a, const person &b) {
              return a.higher < b.higher;
            });
  for (size_t i = 0; i < n; ++i) {
    if (queue[i].higher > i) {
      return false;
    }
    queue[i].height = 150 + (i - queue[i].higher)*10;
    for (size_t k = 0; k < i; ++k) {
      if (queue[k].height >= queue[i].height) {
        queue[k].height += 10;
      }
    }
  }
  return true;
}

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

  if (computeQueue(queue)) {
    for (auto p : queue) {
      std::cout << p.name << " " << p.height << "\n";
    }
  } else {
    std::cout << "-1\n";
  }
  return 0;
}
