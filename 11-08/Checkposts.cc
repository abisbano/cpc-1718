/*
 Checkposts.cc
 Author: Andrea Bisbano
 Date: 16/01/18
 Problem: http://codeforces.com/problemset/problem/427/C?locale=en
 Solution:
  The idea is that this problem is equivalent to Strongly Connected Components. To solve that, we
  compute two times DFS, the second time considering the vertex in decreasing order of finishing
  time. Then, for each SCC we select the minimium cost node computing it while doing the second DFS.
 Time cost: O(N+M), the cost of the DFS.
 Space cost: O(N) to store the finishing time for each node.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
#include <algorithm>

struct node {
  std::vector<uint64_t> adjacent;
  std::vector<uint64_t> adjacentInv;
  uint64_t cost;
  uint64_t color;

  node(uint64_t c) : cost(c), color(0) {}
};

void visitDfs(std::vector<node> &G,
              std::vector<std::pair<uint64_t, uint64_t>> &finish,
              uint64_t i, uint64_t &time) {
  G[i].color = 1;
  for (uint64_t n : G[i].adjacent) {
    if (G[n].color == 0)
      visitDfs(G, finish, n, time);
  }
  G[i].color = 2;
  finish[i].second = time++;
}

void visitDfsInv(std::vector<node> &G, uint64_t i, uint64_t &min, uint64_t &rep) {
  G[i].color = 1;
  if (G[i].cost == min) {
    ++rep;
  }
  if (G[i].cost < min) {
    min = G[i].cost;
    rep = 1;
  }

  for (uint64_t n : G[i].adjacentInv) {
    if (G[n].color == 2)
      visitDfsInv(G, n, min, rep);
  }
  G[i].color = 0;
}

std::pair<uint64_t, uint64_t> checkposts(std::vector<node> &G,
                                         std::vector<std::pair<uint64_t, uint64_t>> &finish) {
  uint64_t minimumCost = 0;
  uint64_t possibilities = 1;
  uint64_t time = 0;
  size_t n = G.size();
  uint64_t min = ULLONG_MAX;
  uint64_t rep = 0;

//  First DFS
  for (size_t i = 0; i < n; ++i) {
    if (G[i].color == 0) {
      visitDfs(G, finish, i, time);
    }
  }

// Sorting for finishing time
  std::sort(finish.begin(), finish.end(),
            [] (std::pair<uint64_t, uint64_t> &a, std::pair<uint64_t, uint64_t> &b){
              return a.second > b.second;
            });

//  Second DFS
  //  note: we use color with inverted meaning.
  for (size_t i = 0; i < n; ++i) {
    if (G[finish[i].first].color == 2) {
      min = ULLONG_MAX;
      rep = 0;
      visitDfsInv(G, finish[i].first, min, rep);
      minimumCost += min;
      possibilities = (possibilities * rep) % 1000000007;
    }
  }

  return std::make_pair(minimumCost, possibilities);
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n, m;
  size_t l, r;
  uint64_t edge;
  uint64_t cost;

  std::cin >> n;
  assert(n >= 1 && n <= 100000);

  std::vector<node> graph;
  std::vector<std::pair<uint64_t, uint64_t>> finish; // pair <index, finishTime>
  graph.reserve(n);
  finish.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> cost;
    assert(true);
    graph.emplace_back(cost);
    finish.emplace_back(i, 0);
  }

  std::cin >> m;
  assert(true);

  for (size_t i = 0; i < m; ++i) {
    std::cin >> l >> r;
    assert(true);
    graph[l-1].adjacent.push_back(r-1);
    graph[r-1].adjacentInv.push_back(l-1);
  }

  auto result = checkposts(graph, finish);

  std::cout << result.first << " " << result.second << "\n";

}
