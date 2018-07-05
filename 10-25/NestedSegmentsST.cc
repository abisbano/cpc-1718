/*
 NestedSegments.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/problemset/problem/652/D?locale=en
 Solution:
  This algorithm uses a Segment Tree initialized with only 0 to keep track of the number of
  segment that end in any segment. The input queries are sorted in decresing order of the left
  end, so when the algorithm replies to any query, all the segments counted in the tree are
  inside the range. For each query if first computes the sum of ending segments, then it updates
  the tree with the right end of the current segment.
  The nodes of the tree are updated by computing the sum of the subtrees of each node.
 Time cost: O(nlogn) is the cost of sort. The cost of a single query is O(logn).
 Space cost: O(n) to store the segment tree.
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>

#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2
#define PARENT(i) (i - 1) / 2

struct Range {
  int left, right;
};

template <typename T>
class SegmentTree {
  int N;
  std::vector<T> tree;

public:
  SegmentTree(int n) : N(n) {
    tree = std::vector<T>(N, T());
  }

  int size() {
    return N;
  }

  void singleUpdate(int index, Range segment, int pos) {
    if (index > segment.right || index < segment.left) {
      return;
    }
    if (segment.left == segment.right) {
      ++tree[pos];
      return;
    }

    int mid = (segment.left + segment.right) / 2;
    singleUpdate(index, Range{segment.left, mid}, LEFT(pos));
    singleUpdate(index, Range{mid+1, segment.right}, RIGHT(pos));
    tree[pos] = tree[LEFT(pos)] + tree[RIGHT(pos)];
  }

  T nestedSegment(Range query, Range segment, int pos) {
    if (query.left <= segment.left && query.right >= segment.right) {
      return tree[pos];
    }
    if (query.left > segment.right || query.right < segment.left) {
      return 0;
    }
    int mid = (segment.left + segment.right) / 2;
    return nestedSegment(query, Range{segment.left, mid}, LEFT(pos)) +
            nestedSegment(query, Range{mid+1, segment.right}, RIGHT(pos));
  }

};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  uint64_t n;
  int l, r;

  std::vector<std::pair<Range, int>> queries;
  std::vector<int> elements;

  std::cin >> n;
  assert(n >= 1 && n <= 200000);

  queries.reserve(n);
  elements.reserve(2*n);

  for (int i = 0; i < n; ++i) {
    std::cin >> l >> r;
    elements.push_back(l);
    elements.push_back(r);
    queries.emplace_back(Range{l, r}, i);
  }

  // Scale and shift position from 0 to n.
  std::sort(elements.begin(), elements.end());
  for (int i = 0; i < n; ++i) {
    queries[i].first.left = (int) (std::lower_bound(elements.begin(), elements.end(),
                                                       queries[i].first.left)
                                     - elements.begin());
    queries[i].first.right = (int) (std::lower_bound(elements.begin(), elements.end(),
                                                        queries[i].first.right)
                                     - elements.begin());
  }

  std::sort(queries.begin(), queries.end(), [](const std::pair<Range, int> &a,
                                               const std::pair<Range, int> &b){
    return a.first.left > b.first.left;
  });

  int m = int(1) << static_cast<int>(ceil(std::log2(2 * n)));
  SegmentTree<int> tree(2 * m - 1);

  std::vector<int> result(n);

  for (auto q : queries) {
    result[q.second] = tree.nestedSegment(q.first, Range{0, 2*n-1}, 0);
    tree.singleUpdate(q.first.right, Range{0, 2*n-1}, 0);
  }

  for (auto i : result) {
    std::cout << i << "\n";
  }

}
