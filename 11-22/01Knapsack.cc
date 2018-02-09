/*
  01Knapsack.cc

  author: Andrea Bisbano
  date: 24/01/18
  problem: https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0

  solution description:

 FIXME: Clean code and write description of solution

 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

uint64_t knapsack(const std::vector<std::pair<uint64_t, uint64_t>> &items, uint64_t W) {

  size_t n = items.size();

  std::vector<std::vector<uint64_t>> T(n+1, std::vector<uint64_t>(W+1, 0));

  for (size_t i = 1; i <= n; ++i) {
    for (size_t j = 1; j <= W; ++j) {
      if (items[i-1].second <= j) { // The item fits
        T[i][j] = std::max(T[i-1][j], T[i-1][j-items[i-1].second] + items[i-1].first);
      } else {
        T[i][j] = T[i-1][j];
      }
    }
  }

  return T[n][W];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  uint64_t N, W;
  uint64_t w, v;
  std::vector<std::pair<uint64_t, uint64_t>> items; // <value,weight>

  std::cin >> T;
  assert(T >= 1 && T <= 100);
  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N >= 1 && N <= 100);
    items.resize(N);
    std::cin >> W;
    assert(W >= 1 && W <= 100);
    for (size_t i = 0; i < N; ++i) {
      std::cin >> v;
      assert(v >= 1 && v <= 100);
      items[i].first = v;
    }
    for (size_t i = 0; i < N; ++i) {
      std::cin >> w;
      assert(w >= 1 && w <= 100);
      items[i].second = w;
    }

    std::cout << knapsack(items, W) << "\n";
    items.clear();
  }
  return 0;
}
