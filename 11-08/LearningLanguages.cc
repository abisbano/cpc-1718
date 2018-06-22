/*
 LearningLanguages.cc
 Author: Andrea Bisbano
 Date: 16/01/18
 Problem: http://codeforces.com/contest/277/problem/A
 Solution:
  The idea is to create a graph where each node can represent an emplyee or a language and the edges
  can be only from one kind to the other and they represent the knowledge of a language.
  Then, from each employee node that wasn't find yet, the algorithm performs a DFS and the total cost
  is the number of DFS needed to reach every employee node.
  There is a special case when every employee know no language. In that case the cost is the number
  of emplyees.
 Time cost: O(N+M) because of the DFS.
 Space cost: O(1)
 */

#include <iostream>
#include <vector>
#include <cassert>

class node {
  std::vector<uint64_t> adjacent;
  uint64_t color;

public:
  void addEdge(uint64_t dest) {
    adjacent.push_back(dest);
  }

  const std::vector<uint64_t> &getAdjacent() {
    return adjacent;
  }

  uint64_t getColor() {
    return color;
  }

  void setColor(uint64_t c) {
    color = c;
  }

  node() : color(0) {}
};

void visitDfs(std::vector<node> &G, uint64_t i) {
  G[i].setColor(1);
  auto adj = G[i].getAdjacent();
  for (uint64_t n : adj) {
    if (G[n].getColor() == 0)
      visitDfs(G, n);
  }
  G[i].setColor(2);
}

uint64_t learningLanguages(std::vector<node> &G, size_t n) {
  uint64_t result = 0;

  for (size_t i = 0; i < n; ++i) {
    if (G[i].getColor() == 0) {
      ++result;
      visitDfs(G, i);
    }
  }

  return result-1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n, m;
  size_t l;
  uint64_t edge;
  bool aLanguage = false;

  std::cin >> n >> m;
  assert(n >= 2 && n <= 100);
  assert(m >= 2 && m <= 100);

  std::vector<node> graph(n+m);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> l;
    if (!aLanguage && l > 0)
      aLanguage = true;
    for (size_t j = 0; j < l; ++j) {
      std::cin >> edge;
      graph[i].addEdge(n+edge-1);
      graph[n+edge-1].addEdge(i);
    }
  }
  if (!aLanguage)
    std::cout << n << "\n";
  else
    std::cout << learningLanguages(graph, n) << "\n";
}
