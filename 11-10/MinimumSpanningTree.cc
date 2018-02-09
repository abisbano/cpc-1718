/*

 MinimumSpanningTree.cc

 author: Andrea Bisbano
 date: 17/01/18
 problem: http://www.spoj.com/problems/MST/

 solution description:
  TO BE WRITTEN
 */


#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

struct node {
  uint64_t father;
  uint64_t rank;
  node (uint64_t f) : father(f), rank(0) { }
};

struct edge {
  uint64_t first;
  uint64_t second;
  uint64_t weight;
  edge(uint64_t u, uint64_t v, uint64_t w) : first(u), second(v), weight(w) { }
};

uint64_t findSet(std::vector<node> &nodes, uint64_t x) {
  if (x != nodes[x].father)
    nodes[x].father = findSet(nodes, nodes[x].father);
  return nodes[x].father;
}

void link(std::vector<node> &nodes, uint64_t u, uint64_t v) {
  if (nodes[u].rank > nodes[v].rank) {
    nodes[v].father = u;
  } else {
    nodes[u].father = v;
    if (nodes[u].rank == nodes[v].rank) {
      ++nodes[v].rank;
    }
  }
}

void unionSet(std::vector<node> &nodes, uint64_t u, uint64_t v) {
  link(nodes, findSet(nodes, u), findSet(nodes, v));
}

uint64_t MST(std::vector<edge> &edges, size_t N) {
  std::vector<node> nodes;
  nodes.reserve(N);

  uint64_t result = 0;
  uint64_t counter = 0;

  for (size_t i = 0; i < N; ++i) {
    nodes.emplace_back(i);
  }

  std::sort(edges.begin(), edges.end(),
            [] (edge &a, edge &b) {
              return a.weight < b.weight;
            });

  for (auto e : edges) {
    if (findSet(nodes, e.first) != findSet(nodes, e.second)) {
      result += e.weight;
      ++counter;
      if (counter == N-1) {
        return result;
      }
      unionSet(nodes, e.first, e.second);
    }
  }
  return 0;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t N, M;
  uint64_t u, v, w;
  std::vector<edge> edges;

  std::cin >> N >> M;
  assert(N >= 1 && N <= 10000);
  assert(M >= 1 && M <= 100000);
  edges.reserve(M);
  for (size_t i = 0; i < M; ++i) {
    std::cin >> u >> v >> w;
    assert(u >= 1 && u <= N);
    assert(v >= 1 && v <= N);
    assert(w >= 0 && w <= 1000000);
    edges.emplace_back(u-1,v-1,w);
  }

  std::cout << MST(edges, N) << "\n";
  return 0;
}
