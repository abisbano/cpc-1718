/*
 FoxNames.cc
 Author: Andrea Bisbano
 Date: 12/02/18
 Problem: http://codeforces.com/problemset/problem/510/C?locale=en
 Solution:
  This algorithm creates a graph where each node represent an alphabet letter. Then is computes
  the input strings adding an edge (u, v) if the letter u preceeds letter v in the solution's order.
  Then it performs a DFS to check if the graph is acyclic and in that case its topological sort
  is the solution. Otherwise, if the graph has a cycle there isn't a solution.
 Time cost: O(N+M) where N is 26 (the letter of the alphabet) and M is the number of dependencies
            (1 less than the number of strings).
 Space cost: O(1)
*/


#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

#define OFFSET 97

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

bool visitDfs(std::string &result, std::vector<node> &G, uint64_t i) {
//  std::cout << "Visit " << i << "\n";
  G[i].setColor(1);
  auto adj = G[i].getAdjacent();
  for (uint64_t n : adj) {
    if (G[n].getColor() == 0 && visitDfs(result, G, n)) {
      return true;
    } else if (G[n].getColor() == 1) {
      return true;
    }
  }
  G[i].setColor(2);
  result.push_back(i+OFFSET);
  return false;
}

std::string foxNames(std::vector<node> &G, const std::vector<uint32_t> &order) {

  std::string result;
  size_t n = order.size();

  for (size_t i = 0; i < n; ++i) {
    if (G[order[i]].getColor() == 0) {
      if (visitDfs(result, G, order[i]))
        return "Impossible";
    }
  }

  for (int i = 25; i >= 0; --i) {
    if (G[i].getColor() == 0) {
      result.push_back(i+OFFSET);
    }
  }

  std::reverse(result.begin(), result.end());
  return result;
}

bool addEdges(std::vector<node> &G, std::vector<uint32_t> &order,
              std::string &succ, std::string &pred) {
  size_t lenghtSucc = succ.length();
  size_t lengthPred = pred.length();
  size_t i = 0;
  while(succ[i] == pred[i]) {
    ++i;
  }
  if (i == lenghtSucc && lengthPred > lenghtSucc) {
    return true;
  }
  if (i < lengthPred && i < lenghtSucc) {
    G[pred[i]-OFFSET].addEdge(succ[i]-OFFSET);
    order.push_back(pred[i]-OFFSET);
  }
  return false;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;

  std::vector<node> graph(26);
  std::vector<uint32_t> order;
  order.reserve(26);
  std::string sOld;
  std::string sNew;

  std::cin >> n;
  assert(n >= 1 && n <= 100);

  std::cin >> sOld;
  for (size_t i = 1; i < n; ++i) {
    std::cin >> sNew;
    if (addEdges(graph, order, sNew, sOld)) {
      std::cout << "Impossible\n";
      return 0;
    }
    sOld = sNew;
  }

  std::cout << foxNames(graph, order) << "\n";
}
