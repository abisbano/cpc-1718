/*
 TreeAndQueries.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/contest/375/problem/D
 Solution:

 Time cost:
 Space cost:
 

*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

struct node {
  std::vector<size_t> adj;
  uint32_t color;
  uint32_t start;
  uint32_t finish;
  uint32_t visitState;
  node(uint32_t c) : color(c), start(0), finish(0), visitState(0) {
    adj = std::vector<size_t>();
  }
};

struct query {
  size_t left;
  size_t right;
  uint32_t times;
  size_t index;

  query(size_t l, size_t r, uint32_t t, uint32_t i)
    : left(l), right(r), times(t), index(i) {}
};

void dfs(std::vector<node> &tree, size_t u, uint32_t &time,
         std::vector<uint32_t> &colors, std::vector<size_t> &times) {
  tree[u].visitState = 1;
  tree[u].start = time;
  times[time] = u;
  colors.push_back(tree[u].color);
  for(auto w : tree[u].adj){
    if (tree[w].visitState == 0)
      time++;
      dfs(tree, w, time, colors, times);
  }
  tree[u].finish = time;
}

size_t remap(std::vector<node> &tree, std::vector<uint32_t> &vec) {
  std::sort(vec.begin(), vec.end());
  size_t size = std::distance(vec.begin(), std::unique(vec.begin(), vec.end()));
  for (auto &n : tree) {
    n.color = std::distance(vec.begin(), std::lower_bound(vec.begin(), vec.begin() + size, n.color));
  }
  return size;
}

size_t createTree(std::vector<node> &tree, std::vector<size_t> &times) {
  uint32_t time = 0;
  std::vector<uint32_t> colors;
  dfs(tree, 0, time, colors, times);
  return remap(tree, colors);
}

void remove(std::vector<uint32_t> &counter, uint32_t c,
            std::vector<uint32_t> &answers) {
  --answers[counter[c]];
  --counter[c];
}

void add(std::vector<uint32_t> &counter, uint32_t c,
         std::vector<uint32_t> &answers) {
  ++counter[c];
  ++answers[counter[c]];
}

std::vector<uint32_t> treeAndQueries(std::vector<node> &tree,
                                     std::vector<query> &queries,
                                     size_t colors,
                                     const std::vector<size_t> &times) {
  size_t n = queries.size();
  std::vector<uint32_t> result(n,0);
  std::vector<uint32_t> counter(colors,0);
  size_t buckets = (size_t) sqrt(tree.size()) + 1;

  std::sort(queries.begin(), queries.end(), [buckets] (const query &a, const query &b) {
    if (a.left/buckets != b.left/buckets) {
      return a.left/buckets < b.left/buckets;
    }
    return a.right < b.right;
  });

  size_t currL = 0;
  size_t currR = 1;
  std::vector<uint32_t> answers(tree.size() + 1, 0);
  add(counter, tree[0].color, answers);

  for (auto q : queries) {
    if (q.times > tree.size()) {
      result[q.index] = 0;
      continue;
    }
    size_t l = q.left;
    size_t r = q.right;
    while (currR <= r) {
      add(counter, tree[times[currR]].color, answers);
      ++currR;
    }
    while (currL > l) {
      add(counter, tree[times[currL-1]].color, answers);
      --currL;
    }
    while (currR > r+1) {
      remove(counter, tree[times[currR-1]].color, answers);
      --currR;
    }
    while (currL < l) {
      remove(counter, tree[times[currL]].color, answers);
      ++currL;
    }

    result[q.index] = answers[q.times];
  }

  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n, m;
  uint32_t color;
  std::vector<node> tree;
  size_t a, b;
  std::vector<query> queries;

  std::cin >> n >> m;
  assert(n <= 100000);
  assert(m <= 100000);
  tree.reserve(n);
  queries.reserve(m);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> color;
    assert(color <= 100000);
    tree.emplace_back(color);
  }
  for (size_t i = 0; i < n-1; ++i) {
    std::cin >> a >> b;
    if (a < b)
      tree[a-1].adj.push_back(b-1);
    else
      tree[b-1].adj.push_back(a-1);
  }

  std::vector<size_t> times(n, 0);
  size_t colors = createTree(tree, times);

  for (size_t i = 0; i < m; ++i) {
    std::cin >> a >> b;
    queries.emplace_back(tree[a-1].start, tree[a-1].finish, b, i);
  }

  auto result = treeAndQueries(tree, queries, colors, times);
  for (auto i : result) {
    std::cout << i << "\n";
  }

  return 0;
}
