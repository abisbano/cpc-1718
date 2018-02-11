/*
 TwoHeaps.cc
 Author: Andrea Bisbano
 Date: 20/12/17
 Problem: http://codeforces.com/problemset/problem/353/B?locale=en
 Solution:
  The idea of this solution it to divide the values in two sets: the first containing
  only the values that appears at most 2 times and the second with the others.
  After that, we divide the values in the first set among the two heaps in an even way,
  with the caution of inserting the values that appears two times in both heaps.
  The values of the second set are inserted at random to fill the two heaps.
  By doing that the number of possible combination is the maximum possible.
 Time cost: O(nlogn) because we need to sort the elements.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

class element {
  uint32_t position;
  uint32_t value;

public:
  element(uint32_t p, uint32_t v) : position(p), value(v) { }

  uint32_t getPosition() const {
    return position;
  }

  uint32_t getValue() const {
    return value;
  }

};

uint32_t twoHeaps(std::vector<element> &vec, std::vector<uint32_t> &result) {

  std::sort(vec.begin(), vec.end(), [] (const element& lhs, const element& rhs) {
    return lhs.getValue() < rhs.getValue();
  });

  uint32_t distinct = 0;
  uint32_t current = 0;
  uint32_t heap = 1;
  bool moreThanTwo = false;
  std::vector<uint32_t> duplicates;

  for (auto el : vec) {
    if (el.getValue() != current || !moreThanTwo) {
      moreThanTwo = false;
      result[el.getPosition()] = heap;
      heap = (heap == 1) ? 2 : 1;
      ++distinct;
    } else {
      duplicates.push_back(el.getPosition());
    }
    if (el.getValue() == current) {
      moreThanTwo = true;
    } else {
      current = el.getValue();
    }
  }

  size_t i = 0;
  for (; i < duplicates.size() / 2 ; ++i) {
    result[duplicates[i]] = 1;
  }
  for (; i < duplicates.size(); ++i) {
    result[duplicates[i]] = 2;
  }

  return (distinct/2 * (distinct - distinct/2));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  size_t N;
  std::vector<element> vec;
  uint32_t value;

  std::cin >> N;
  assert(N >= 1 && N <= 100);

  for (size_t i = 0; i < N*2; ++i) {
    std::cin >> value;
    assert(value >= 10 && value <= 99);
    vec.emplace_back(i, value);
  }

  std::vector<uint32_t> result(N*2, 0);
  auto distinct = twoHeaps(vec, result);

  std::cout << distinct << std::endl;
  for (auto i : result) {
    std::cout << i << " ";
  }
  std::cout << "\n";
}
