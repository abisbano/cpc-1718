/*

 LearningLanguages.cc

 author: Andrea Bisbano
 date: 16/01/18
 problem: http://codeforces.com/contest/277/problem/A

 solution description:
  TO BE WRITTEN
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
