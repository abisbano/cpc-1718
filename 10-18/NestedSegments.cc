/*
 NestedSegments.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/problemset/problem/652/D?locale=en
 Solution:
  The idea of this solution is to use a BIT B to keep track of right ends of the processed segments.
  We order the segments in decreasing order of the left end and for each couple <l,r> we first compute
  sum(r) and after that we add 1 in position r of the BIT.
  We use this ordering so we can just ignore the segments we still have to process because their left
  end is outside of the current range.
 Time cost: O(nlogn) because the cost os sorting id dominating the costs of other operations (O(logn)).
 Space cost: O(n) to store the BIT.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>

template <typename T>
class fenwickTree {
private:
  size_t size;
  std::vector<T> vec;

  size_t parent(size_t index) {
    return index - (index & (-1 * index));
  }

  size_t sibilling(size_t index) {
    return index + (index & (-1 * index));
  }

public:
  fenwickTree(size_t s) : size(s) {
    vec = std::vector<T>(s + 1, T());
  }

  T sum(size_t index) {
    T result = T();
    while (index != 0) {
      result += vec[index];
      index = parent(index);
    }
    return result;
  }

  void add(size_t index, const T &value) {
    while (index <= size) {
      vec[index] += value;
      index = sibilling(index);
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n;
  int64_t l, r;

  std::vector<std::tuple<int64_t, int64_t, uint64_t>> vec;
  std::vector<int64_t> elements;

  std::cin >> n;
  assert(n >= 1 && n <= 200000);

  vec.reserve(n);
  elements.reserve(2*n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> l >> r;
    elements.push_back(l);
    elements.push_back(r);
    vec.push_back(std::tuple<int64_t, int64_t, uint64_t>(l,r,i));
  }

  // Scale and shift position from 1 to n+1.
  std::sort(elements.begin(), elements.end());
  for (size_t i = 0; i < n; ++i) {
    std::get<0>(vec[i]) = (int64_t) (std::lower_bound(elements.begin(), elements.end(), std::get<0>(vec[i]))
                                     - elements.begin()) + 1;
    std::get<1>(vec[i]) = (int64_t) (std::lower_bound(elements.begin(), elements.end(), std::get<1>(vec[i]))
                                     - elements.begin()) + 1;
  }

  std::sort(vec.begin(), vec.end(), [](const std::tuple<int64_t, int64_t, uint64_t> &a,
                                       const std::tuple<int64_t, int64_t, uint64_t> &b){
    return std::get<0>(a) > std::get<0>(b);
  });

  fenwickTree<uint64_t> ft(2*n);
  std::vector<uint64_t> result(n);

  for (auto t : vec) {
    result[std::get<2>(t)] = ft.sum(std::get<1>(t));
    ft.add(std::get<1>(t), 1);
  }

  for (auto i : result) {
    std::cout << i << "\n";
  }

}
