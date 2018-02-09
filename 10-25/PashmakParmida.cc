/*
  PashmakParmida.cc

  author: Andrea Bisbano
  date: 14/01/18
  problem: http://codeforces.com/problemset/problem/459/D?locale=en

  solution description:

*/

#include <iostream>
#include <cassert>
#include <vector>
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

  size_t n = vec.size();
  size_t c = remap<uint64_t>(vec);

  fenwickTree<uint64_t> ft(n);
  std::vector<uint64_t> counter(c);
  std::vector<uint64_t> suffixCounter(n);

  for (int i = n-1; i >= 0; --i) {
    ++counter[vec[i]];
    suffixCounter[i] = counter[vec[i]];
    ft.add(counter[vec[i]], 1);
  }

  std::fill(counter.begin(), counter.end(), 0);
  uint64_t result = 0;
  for (int i = 0; i < n; ++i) {
    ft.add(suffixCounter[i], -1);
    ++counter[vec[i]];
    result += ft.sum(counter[vec[i]]-1);
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
