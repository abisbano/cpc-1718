/*
 01Knapsack.cc
 Author: Andrea Bisbano
 Date: 24/01/18
 Problem: https://practice.geeksforgeeks.org/problems/0-1-knapsack-problem/0
 Solution:
  This algorithm creats a table where each row represent an item and each column the maximum weight.
  The element T[i][j] contains the partial solution, considering the first i elements that have a maximum
  weight of j. If the item i doesn't fit in the knapsack, then T[i][j] = T[i-1][j]. Otherwise
  T[i][j] is the maximum between T[i-1][j] (i.e it's chosen to not bring item i)
  and T[i-1][j-w(i)]+v(i) (it's chosen to bring the item i).
 Time cost: O(Wn) where W is the capacity of the knapsack.
 Space cost: O(Wn) to store the table.
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
