/*
 PashmakParmida.cc
 Author: Andrea Bisbano
 Date: 14/01/18
 Problem: http://codeforces.com/problemset/problem/459/D?locale=en
 Solution description:
  This algorithm computes two support vectors L and R, where L[i] = f(1, i, a_i) and
  R[i] = f(i, n, a_i). Then it creates a segment tree of size equal to the maximum element of R
  and initially filled with 0. The generic leaf T[i] of the tree represent the number of times
  the function f(j, n, a_j) was equal to i.
  Then the algorithm updates the tree starting from the last index and after that in queries
  the tree for the segment (1~(L[i]-1)). The sum of all queries' result is the solution.
 Time cost: O(NlogN) is the cost to compute L and R arrays. Each query costs O(logn).
 Space cost: O(N) to store the segment tree.
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
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

  T sumQuery(Range query, Range segment, int pos) {
    if (query.left <= segment.left && query.right >= segment.right) {
      return tree[pos];
    }
    if (query.left > segment.right || query.right < segment.left) {
      return 0;
    }
    int mid = (segment.left + segment.right) / 2;
    return sumQuery(query, Range{segment.left, mid}, LEFT(pos)) +
            sumQuery(query, Range{mid+1, segment.right}, RIGHT(pos));
  }
};

uint64_t PashmakParmida(std::vector<uint64_t> &vec) {

  int n = vec.size();

  std::map<int, int> m;
  std::vector<int> L(n);
  std::vector<int> R(n);;
  for (int i = 0; i < n; ++i) {
    L[i] = ++m[vec[i]];
  }
  m.clear();
  for (int i = n - 1; i >= 0; --i) {
    R[i] = ++m[vec[i]];
  }

  int maxElem = *std::max_element(R.begin(), R.end());
  int size = int(1) << static_cast<int>(ceil(std::log2(maxElem)));
  SegmentTree<int> tree(2 * size - 1);

  uint64_t answer = 0;

  for (int i = n-1; i > 0; --i) {
    tree.singleUpdate(R[i], Range{1, size-1}, 0);
    if (L[i-1] != 1)
      answer += tree.sumQuery(Range{1, L[i-1]-1}, Range{1, size-1}, 0);
  }
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n;
  int value;
  std::vector<uint64_t> vec;

  std::cin >> n;
  assert(n >= 1 && n <= 1000000);
  vec.reserve(n);

  for (int i = 0; i < n; ++i) {
    std::cin >> value;
    assert(value >= 1 && value <= 1000000000);
    vec.push_back(value);
  }

  std::cout << PashmakParmida(vec) << "\n";
  return 0;
}
