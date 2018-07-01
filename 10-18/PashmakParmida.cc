/*
 PashmakParmida.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/problemset/problem/459/D?locale=en
 Solution description:
  This algorithm starts by remapping the values of the input array A so that they range in [0,n-1].
  Then it computes suffixCounter array, such that suffixCounter[i] = f(i,n,A[i]) and while doing that
  it also computes a BIT B where B[i] is the number of entries in suffixCounter that are equal to i.
  Then in processes the input array from left to right and, for each value A[i], it computes the value
  k = f(1,i,A[i]) and then searches for values f(j,n,A[j]) < k.
  To do so, it decreases the entry suffixCounter[i] of B bt 1 at each steps and then computes sum(k-1)
  which is the values it is looking for.
  The sum for every i is the solution to the problem.
 Time cost: O(NlogN)
 Space cost: O(N)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

template <typename T>
class fenwickTree {
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

template <typename T>
size_t remap(std::vector<T> &vec) {
  std::vector<T> tmp(vec.size());
  std::copy(vec.begin(), vec.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end());
  size_t size = std::distance(tmp.begin(), std::unique(tmp.begin(), tmp.end()));
  tmp.resize(size);
  for (auto &e : vec) {
    e = std::distance(tmp.begin(), std::lower_bound(tmp.begin(), tmp.end(), e));
  }
  return size;
}

uint64_t PashmakParmida(std::vector<uint64_t> &vec) {
  uint64_t result = 0;
  size_t n = vec.size();
  size_t c = remap<uint64_t>(vec);

  fenwickTree<uint64_t> ft(n);
  std::vector<uint64_t> counter(c,0);
  std::vector<uint64_t> suffixCounter(n,0);
  for (int i = n-1; i >= 0; --i) {
    ++counter[vec[i]];
    suffixCounter[i] = counter[vec[i]];
    ft.add(counter[vec[i]],1);
  }

  std::fill(counter.begin(), counter.end(), 0);
  for (size_t i = 0; i < n; ++i) {
    ft.add(suffixCounter[i], -1);
    ++counter[vec[i]];
    result += ft.sum(counter[vec[i]] - 1);
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;
  uint64_t value;
  std::vector<uint64_t> vec;

  std::cin >> n;
  assert(n >= 1 && n <= 1000000);
  vec.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> value;
    assert(value >= 1 && value <= 1000000000);
    vec.push_back(value);
  }

  std::cout << PashmakParmida(vec) << "\n";
  return 0;
}
