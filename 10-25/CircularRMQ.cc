/*
 CircularRMQ.cc
 Author: Andrea Bisbano
 Date: 02/07/18
 Problem: http://codeforces.com/problemset/problem/52/C
 Solution:
  This code provides an implementation of a Segment tree with lazy propagation to solve the RMQ problem.
  The segment tree is implemented using a class containing two arrays (one for the tree itself and the
  other for the lazy tree).
  The circular queries (L, R) with L > R are handled like two different queries,
  the first is (0, R) and the second (L, N), where N is the size of the input array.
 Time cost: O(mlogn) where M is the number of queries (both kind of queries require O(logn)).
 Space cost: O(logn) to store the Segment Tree.
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

#define LEFT(i)   2 * i + 1
#define RIGHT(i)  2 * i + 2
#define PARENT(i) (i - 1) / 2

struct range {
  size_t left;
  size_t right;
  range(size_t l, size_t r) : left(l), right(r) {}
};

template <typename T>
class SegmentTree {
  size_t N;
  std::vector<T> tree;
  std::vector<T> lazy;

public:
  SegmentTree(size_t n) : N(n) {
    tree = std::vector<T>(N, T());
    lazy = std::vector<T>(N, T());
  }

  size_t size() {
    return N;
  }

  void build(const std::vector<T> &vec,
             size_t low, size_t high, size_t pos) {
    if (low == high) {
      tree[pos] = vec[low];
      return;
    }
    size_t mid = (low + high) / 2;
    build(vec, low, mid, LEFT(pos));
    build(vec, mid + 1, high, RIGHT(pos));
    tree[pos] = std::min(tree[LEFT(pos)], tree[RIGHT(pos)]);
  }

  void update(range query, int64_t val, range segment, size_t pos) {
    // apply pending updates
    if (lazy[pos] != T()) {
      tree[pos] += lazy[pos];
      if (segment.left != segment.right) {
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
      }
      lazy[pos] = T();
    }

    // no overlap
    if (query.left > segment.right || query.right < segment.left) {
      return;
    }

    // total overlap
    if (query.left <= segment.left && query.right >= segment.right) {
      tree[pos] += val;
      if (segment.left != segment.right) {
        lazy[LEFT(pos)] += val;
        lazy[RIGHT(pos)] += val;
      }
      return;
    }

    size_t mid = (segment.left + segment.right) / 2;
    update(query, val, range(segment.left, mid), LEFT(pos));
    update(query, val, range(mid + 1, segment.right), RIGHT(pos));
    tree[pos] = std::min(tree[LEFT(pos)], tree[RIGHT(pos)]);
  }

  T rmq(range query, range segment, size_t pos) {
    if (lazy[pos] != T()) {
      tree[pos] += lazy[pos];
      if (segment.left != segment.right) {
        lazy[LEFT(pos)] += lazy[pos];
        lazy[RIGHT(pos)] += lazy[pos];
      }
      lazy[pos] = T();
    }

    if (query.left <= segment.left && query.right >= segment.right) {
      return tree[pos];
    }
    if (query.left> segment.right || query.right < segment.left) {
      return LLONG_MAX;
    }
    size_t mid = (segment.left + segment.right) / 2;
    return std::min(rmq(query, range(segment.left, mid), LEFT(pos)),
                    rmq(query, range(mid + 1, segment.right), RIGHT(pos)));
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  // input array
  size_t n;
  std::vector<int64_t> vec;
  int64_t v;

  std::cin >> n;
  vec.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> v;
    vec.push_back(v);
  }

  // Segment tree construction
  size_t m = size_t(1) << static_cast<size_t>(ceil(std::log2(n)));
  SegmentTree<int64_t> tree(2 * m - 1);
  tree.build(vec, 0, n-1, 0);

  // Input queries
  size_t q, l, r;
  std::cin >> q;
  char c[100];
  std::cin.ignore();
  for (size_t i = 0; i < q; ++i) {
    std::cin.getline(c,100);
    if (std::istringstream(c) >> l >> r >> v) {
      // update
      if (l <= r) {
        tree.update(range(l, r), v, range(0,n-1), 0);
      } else {
        tree.update(range(0, r), v, range(0,n-1), 0);
        tree.update(range(l, n-1), v, range(0,n-1), 0);
      }
    } else {
      // RMQ
      if (l <= r) {
        std::cout << tree.rmq(range(l, r), range(0, n-1), 0) << "\n";
      } else {
        int64_t q1 = tree.rmq(range(0, r), range(0, n-1), 0);
        int64_t q2 = tree.rmq(range(l, n-1), range(0, n-1), 0);
        std::cout << std::min(q1, q2) << "\n";
      }
    }
  }
}
