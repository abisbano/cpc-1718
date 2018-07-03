/*
 PowerfulArray.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/contest/86/problem/D
 Solution:
  This solution is an implementation of the MO's algorithm. The queries are logically divided in sqrt(n)
  buckets, where n is the length of input array and the bucket i contains the queries with the
  left end l < sqrt(n) * i. After the queries are sorted, the algorithm procedes computing the solution
  using the last computed solution, moving the left and right ends of the previous query.
  Thanks to the order of the queries, the number of operation performed is the least possible.
 Time cost: O(Nsqrt(N))
 Space cost: O(N) to keep a counter for each different element in the input array.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

struct query {
  size_t left;
  size_t right;
  size_t index;
  query(size_t l, size_t r, size_t i) : left(l), right(r), index(i) {}
};

std::vector<uint64_t> remap(std::vector<uint64_t> &vec) {
  std::vector<uint64_t> tmp(vec.size());
  std::copy(vec.begin(), vec.end(), tmp.begin());
  std::sort(tmp.begin(), tmp.end());
  size_t size = std::distance(tmp.begin(), std::unique(tmp.begin(), tmp.end()));
  std::vector<uint64_t> values(size);
  tmp.resize(size);
  for (auto &e : vec) {
    auto value = e;
    e = std::distance(tmp.begin(), std::lower_bound(tmp.begin(), tmp.end(), e));
    values[e] = value;
  }
  return values;
}

inline void remove(uint64_t &S, uint64_t &c, uint64_t v) {
  S = S - c*c*v + (c-1)*(c-1)*v;
  --c;
}

inline void add(uint64_t &S, uint64_t &c, uint64_t v) {
  S = S - c*c*v + (c+1)*(c+1)*v;
  ++c;
}

std::vector<uint64_t> powerfulArray(std::vector<uint64_t> &vec,
                   std::vector<query> &queries) {

  // remap and scale the original array and keep the old values.
  auto values = remap(vec);
  std::vector<uint64_t> counter(vec.size() + 1, 0);
  size_t buckets = (size_t) sqrt(vec.size());
  std::vector<uint64_t> result(queries.size());

  std::sort(queries.begin(), queries.end(), [buckets] (query &a, query &b) {
    if (a.left/buckets != b.left/buckets) {
      return a.left/buckets < b.left/buckets;
    }
    return a.right < b.right;
  });

  size_t currentL = 0, currentR = 0;
  uint64_t sum = values[vec[0]];
  counter[vec[0]] = 1;

  for (auto q : queries) {
    size_t l = q.left - 1;
    size_t r = q.right - 1;
    while(currentL < l) {
      remove(sum, counter[vec[currentL]], values[vec[currentL]]);
      ++currentL;
    }
    while (currentL > l) {
      --currentL;
      add(sum, counter[vec[currentL]], values[vec[currentL]]);
    }
    while (currentR < r) {
      ++currentR;
      add(sum, counter[vec[currentR]], values[vec[currentR]]);
    }
    while (currentR > r) {
      remove(sum, counter[vec[currentR]], values[vec[currentR]]);
      --currentR;
    }
    result[q.index] = sum;
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n, t;
  uint64_t elem;
  std::vector<uint64_t> vec;
  size_t l, r;
  std::vector<query> queries;

  std::cin >> n >> t;
  assert(n >= 1 && n <= 200000);
  assert(t >= 1 && t <= 200000);
  vec.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> elem;
    assert(elem >= 1 && elem <= 1000000);
    vec.push_back(elem);
  }
  for (size_t i = 0; i < t; ++i) {
    std::cin >> l >> r;
    assert(l >= 1 && l <= r && r <= n);
    queries.emplace_back(l, r, i);
  }

  auto result = powerfulArray(vec, queries);

  for (auto i : result) {
    std::cout << i << "\n";
  }

  return 0;
}
