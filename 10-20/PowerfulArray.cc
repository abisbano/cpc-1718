/*
  PowerfulArray.cc

  author: Andrea Bisbano
  date: 14/01/18
  problem: http://codeforces.com/contest/86/problem/D

  solution description:
 

*/

#include <iostream>
#include <cassert>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

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

void remove(uint64_t &S, uint64_t &c, uint64_t v) {
  S = S - c*c*v + (c-1)*(c-1)*v;
  --c;
}

void add(uint64_t &S, uint64_t &c, uint64_t v) {
  S = S - c*c*v + (c+1)*(c+1)*v;
  ++c;
}

std::vector<uint64_t> powerfulArray(std::vector<uint64_t> &vec,
                                    std::vector<std::tuple<uint64_t, uint64_t, size_t>> &queries) {

  size_t n = vec.size();
  // remap and scale the original array and save the true values.
  auto values = remap(vec);
  size_t size = values.size();

  size_t bucketNumber = (size_t) sqrt(n);
  std::vector<std::vector<std::tuple<uint64_t, uint64_t, size_t>>> buckets(bucketNumber);
  std::vector<uint64_t> counter(size+1,0);
  std::vector<uint64_t> result(queries.size());

  std::sort(queries.begin(), queries.end(), [bucketNumber] (std::tuple<uint64_t, uint64_t, size_t> &a,
                                              std::tuple<uint64_t, uint64_t, size_t> &b) {
    if (std::get<0>(a)/bucketNumber != std::get<0>(b)/bucketNumber) {
      return std::get<0>(a)/bucketNumber < std::get<0>(b)/bucketNumber;
    }
    return std::get<1>(a) < std::get<1>(b);
  });

  size_t currentL = 0, currentR = 0;
  uint64_t sum = values[vec[0]];
  counter[vec[0]] = 1;

  for (auto q : queries) {
    size_t l = std::get<0>(q)-1;
    size_t r = std::get<1>(q)-1;
    while (currentL > l) {
      --currentL;
      add(sum, counter[vec[currentL]], values[vec[currentL]]);
    }
    while (currentR < r) {
      ++currentR;
      add(sum, counter[vec[currentR]], values[vec[currentR]]);
    }
    while (currentL < l) {
      remove(sum, counter[vec[currentL]], values[vec[currentL]]);
      ++currentL;
    }
    while (currentR > r) {
      remove(sum, counter[vec[currentR]], values[vec[currentR]]);
      --currentR;
    }
    result[std::get<2>(q)] = sum;
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
  std::vector<std::tuple<uint64_t, uint64_t, size_t>> queries;

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
    queries.push_back(std::tuple<uint64_t, uint64_t, size_t>(l, r, i));
  }

  auto result = powerfulArray(vec, queries);
  for (auto i : result) {
    std::cout << i << "\n";
  }

  return 0;
}
