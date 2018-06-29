/*
 MishaForest.cc
 Author: Andrea Bisbano
 Date: 06/11/17
 Problem: http://codeforces.com/problemset/problem/501/C?locale=en
 Solution:
  This algorithm starts from any node with degree 1. In that case the XOR sum of the node is equal to its
  only adjacent node. After a node is processed the algorithm updates the degree and the sum of both the node
  and its adjacent. If the adjacent after the update has degree 1 then it procedes with it, otherwise
  it continues searching for another node with degree 1.
  Since there aren't cycles in the graph there's always at least one node with degree equals to 1 and so
  the algorithm can find a solution.
 Time cost: O(N) to process the N nodes of the gra
 Space cost: O(N) to store the edges (these can't be more than the node)
 */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

void createEdge(size_t index, std::vector<uint32_t>& degrees,
                std::vector<uint32_t>& sums,
                std::vector<std::pair<uint32_t,uint32_t>>& edges) {
  uint32_t s = sums[index]; // This is the only remaining neighbor of this node.
  --degrees[index];
  --degrees[s];
  sums[index] ^= s;
  sums[s] ^= index;
  edges.push_back(std::make_pair(index, s));
  if (degrees[s] == 1) {
    createEdge(s, degrees, sums, edges);
  }
  return;
}

size_t mishaForest(std::vector<uint32_t>& degrees,
                   std::vector<uint32_t>& sums,
                   std::vector<std::pair<uint32_t,uint32_t>>& edges) {

  size_t n = degrees.size();

  for (size_t i = 0; i < n; ++i) {
    if (degrees[i] == 1) { // This node can be handled
      createEdge(i, degrees, sums, edges);
    }
  }

  return edges.size();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::vector<uint32_t> degrees;
  std::vector<uint32_t> sums;
  uint32_t n; // Number of nodes
  uint32_t deg; // Degree of the current node
  uint32_t s; // XOR sum of the current node

  std::vector<uint32_t> savedNodes;

  std::cin >> n;
  degrees.reserve(n);
  sums.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> deg >> s;
    degrees.push_back(deg);
    sums.push_back(s);
  }

  std::vector<std::pair<uint32_t,uint32_t>> result;

  std::cout << mishaForest(degrees, sums, result) << "\n";
  for (auto edge : result) {
    std::cout << edge.first << " " << edge.second << "\n";
  }

  return 0;
}
