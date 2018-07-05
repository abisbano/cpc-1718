/*
 StrangeFoodChain.cc
 Author: Andrea Bisbano
 Date: 17/01/18
 Problem: http://www.spoj.com/problems/CHAIN/
 Solution:
  This algorithm is an implementation of the following solution:
  https://www.quora.com/How-do-I-solve-the-strange-food-chain-question-on-SPOJ
 Time cost:
 Space cost:
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

int find(std::vector<int> &root,
         std::vector<int> &d, int v) {
  if (v == root[v]) {
    return v;
  }
  int tmp = root[v];
  root[v] = find(root, d, root[v]);
  d[v] += d[tmp];
  return root[v];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int T; // test cases
  int N, K;
  int f, x, y;
  int answer;
  std::vector<int> d;
  std::vector<int> root;

  std::cin >> T;
  for (int i = 0; i < T; ++i) {
    std::cin >> N >> K;
    assert(N >= 1 && N <= 50000);
    assert(K >= 1 && K <= 100000);
    root.resize(N+1);
    d.resize(N+1,0);
    for (int j = 0; j < N+1; ++j) {
      root[j] = j;
    }
    answer = 0;

    for (int j = 0; j < K; ++j) {
      std::cin >> f >> x >> y;
      // false case 1
      if (x > N || y > N) {
        ++answer;
        continue;
      }
      int px = find(root, d, x);
      int py = find(root, d, y);

      --f;

      if (px == py) {
        int tmp = (d[x] - d[y]) % 3;
        if (tmp < 0) tmp += 3;
        if (tmp != f) {
          ++answer;
        }
      } else {
        root[px] = py;
        int h = (d[x] - d[y] - f) % 3;
        d[px] = h < 0 ? -h : -h + 3;
      }
    }
    std::cout << answer << "\n";
    root.clear();
    d.clear();
  }
  return 0;
}
