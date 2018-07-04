/*
 VertexCover.cc
 Author: Andrea Bisbano
 Date: 26/01/18
 Problem: http://www.spoj.com/problems/PT07X/
 Solution:
  This algorithm implements a DP solution for the Vertex Cover problem on trees.
  The idea is that for each node there are two possibilities:
  1. The node belongs to the VC, so all the children belong to the cover. Then the solution is
    the sum of the VC of the children plus 1.
  2. The node doesn't belong to the VC. In that case all the children must belong to the VC,
    and thus the solution is the sum of the VC of the children.
  Exploiting this idea, the algorithm computes the VC for the root in both cases (it is part
  or it isn't part of the VC) and the minimum between those two values is the solution.
  To exploit the DP, the algorithm keeps the values of both partial VC for each node, so
  it doesn't have to compute the same value two times.
 Time cost: O(N) VC for each node is computed only two times.
 Space cost:  O(N) to keep the intermediate values.
 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

class tree {
  struct node {
    std::vector<uint64_t> adj;
    int32_t cover[2];

    node() {
      cover[0] = -1;
      cover[1] = -1;
    }
  };

  std::vector<node> nodes;
  size_t size;

public:
  tree(size_t n) : size(n) {
    nodes = std::vector<node>(n);
  }

  void addEdge(size_t u, size_t v) {
    nodes[u].adj.push_back(v);
    nodes[v].adj.push_back(u);
  }

  uint64_t vertexCover(size_t root, size_t taken, int32_t dad) {
    if (nodes[root].cover[taken] != -1) {
      return nodes[root].cover[taken];
    }

    size_t sons = nodes[root].adj.size();
    uint64_t cover = taken;

    for (size_t i = 0; i < sons; ++i) {
      size_t nextSon = nodes[root].adj[i];
      if (nextSon == dad) continue;
      if (taken) {
        cover += std::min(vertexCover(nextSon, 0, root),vertexCover(nextSon, 1, root));
      } else {
        cover += vertexCover(nextSon, 1, root);
      }
    }

    nodes[root].cover[taken] = cover;
    return cover;
  }

  uint64_t minVertexCover() {
    if (size == 0) return 0;
    return std::min(vertexCover(0, 0, -1), vertexCover(0,1,-1));
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t N;
  size_t u, v;

  std::cin >> N;
  assert(N <= 100000);
  tree graph(N);

  for (size_t i = 0; i < N-1; ++i) {
    std::cin >> u >> v;
    assert(u >= 1 && u <= N);
    assert(v >= 1 && v <= N);
    graph.addEdge(u-1,v-1);
  }

  std::cout << graph.minVertexCover() << "\n";
  return 0;
}
