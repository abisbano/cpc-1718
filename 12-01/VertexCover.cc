/*
  VertexCover.cc

  author: Andrea Bisbano
  date: 26/01/18
  problem: http://www.spoj.com/problems/PT07X/

  solution description:

 FIXME: Clean code and write description of solution

 */

#include<vector>
#include<iostream>
#include<cassert>
#include<algorithm>

class tree {

  struct node {
    std::vector<uint64_t> adj;
    uint64_t cover;

    node() : cover(0) {}
  };

  std::vector<node> nodes;
  size_t size;

public:
  tree(size_t n) : size(n) {
    nodes = std::vector<node>(n);
  }

  void addEdge(size_t u, size_t v) {
    nodes[u].adj.push_back(v);
//    nodes[v].adj.push_back(u);
  }

  uint64_t vertexCover(size_t root, int64_t dad) {
//    printf("start node: %zu, cover: %llu, adj: %zu\n", root, nodes[root].cover, nodes[root].adj.size());
//    std::cout << "start node " << root << "\n";
    if (nodes[root].cover != 0 || nodes[root].adj.empty()){
//      printf("finished %zu\n", root);
      return nodes[root].cover;
    }

    size_t sons = nodes[root].adj.size();

    uint64_t sizeIncluded = 1;
    for (size_t i = 0; i < sons; ++i) {
      if (nodes[root].adj[i] == dad) continue;
      sizeIncluded += vertexCover(nodes[root].adj[i], root);
    }

    uint64_t sizeExcluded = 0;
    for (size_t i = 0; i < sons; ++i) {
      if (nodes[root].adj[i] == dad) continue;
      ++sizeExcluded;
      size_t nephews = nodes[nodes[root].adj[i]].adj.size();
      for (size_t j = 0; j < nephews; ++j) {
        if (nodes[nodes[root].adj[i]].adj[j] == root) continue;
        sizeExcluded += vertexCover(nodes[nodes[root].adj[i]].adj[j], nodes[root].adj[i]);
      }
    }
//    printf("n: %zu, ex: %llu, inc: %llu\n",root, sizeIncluded, sizeExcluded);
    nodes[root].cover = std::min(sizeExcluded, sizeIncluded);
    return  nodes[root].cover;

  }

  uint64_t minVertexCover() {
    if (size == 0) return 0;
    uint64_t result = 1000000;
    for (size_t i = 0; i < size; ++i) {
      if (nodes[i].cover == 0) {
        vertexCover(i, -1);
      }
      if (nodes[i].cover > 0 && nodes[i].cover < result) {
        result = nodes[i].cover;
      }
    }
    return result;
  }

};

//uint64_t vertexCover(std::vector<node> &tree, size_t root, int father) {
////  std::cout << root << "\n";
//
//  if (tree[root].cover != 0)
//    return tree[root].cover;
//
//  if (tree[root].adj.empty()) {
//    return 0;
//  }
//
//  size_t sons = tree[root].adj.size();
//
//  uint64_t sizeIncluded = 1;
//  for (size_t i = 0; i < sons; ++i) {
//    if (tree[root].adj[i] != father) {
//      sizeIncluded += vertexCover(tree, tree[root].adj[i], root);
//    }
//  }
//
//  uint64_t sizeExcluded = sons;
//  for (size_t i = 0; i < sons; ++i) {
//    if (tree[root].adj[i] != father) {
//      size_t nephews = tree[tree[root].adj[i]].adj.size();
//      for (size_t j = 0; j < nephews; ++j) {
//        if (tree[i].adj[j] != root) {
//          sizeExcluded += vertexCover(tree, tree[i].adj[j], i);
//        }
//      }
//    }
//  }
//
//  tree[root].cover = std::min(sizeExcluded, sizeIncluded);
//  return tree[root].cover;
//}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int64_t N;
  size_t u, v;

  std::cin >> N;
  assert(N >= 0 && N <= 100000);
  tree graph(N);

  for (int64_t i = 0; i < N-1; ++i) {
    std::cin >> u >> v;
    assert(u >= 1 && u <= N);
    assert(v >= 1 && v <= N);

    graph.addEdge(u-1,v-1);
  }

  std::cout << graph.minVertexCover() << "\n";
  return 0;
}
