/*
  MinimumNumberOfJumps.cc

  author: Andrea Bisbano
  date: 25/01/18
  problem: https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0

  solution description:

 FIXME: Clean code and write description of solution

 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

int64_t minimumNumberOfJumps(const std::vector<uint64_t> &vec) {
  if (vec.empty()) {
    return -1;
  }
  size_t N = vec.size();
  std::vector<uint64_t> paths(N,1000);
  paths[0] = 0;

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = i + 1; j < N && j <= i + vec[i]; ++j) {
      paths[j] = std::min(paths[j], paths[i] + 1);
    }
  }
  return (paths[N-1] == 1000) ? -1 : paths[N-1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T, N;
  uint64_t value;
  std::vector<uint64_t> vec;

  std::cin >> T;
  assert(T >= 1 && T <= 40);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N >= 1 && N <= 100);
    vec.reserve(N);
    for (size_t i = 0; i < N; ++i) {
      std::cin >> value;
      assert(value >= 0 && value <= 100);
      vec.push_back(value);
    }

    std::cout << minimumNumberOfJumps(vec) << "\n";
    vec.clear();
  }
  return 0;
}
