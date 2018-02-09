

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
    if (degrees[i] == 1) { // We can handle this node
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
