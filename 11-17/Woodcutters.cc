/*
 Woodcutters.cc
 Author: Andrea Bisbano
 Date: 10/10/17
 Problem: http://codeforces.com/contest/545/problem/C
 Solution:
  This algorithm starts cutting from left to right and chooses greedly the side to cut, always choosing
  left side if it's possible. It counts always the first and the last tree, because they can always be
  cut (the first to the left and the last to the right).
 Time cost: O(n) to scan the input array one time.
 Space cost: O(1)
 */

#include<vector>
#include<iostream>
#include<cassert>

struct Tree {
  int32_t begin;
  int32_t end;
  int32_t height;

  Tree(int32_t pos, int32_t h) : begin(pos), end(pos), height(h) {}
  void cutLeft() {
    begin -= height;
  }
  void cutRight() {
    end += height;
  }
};

uint32_t woodcutters(std::vector<Tree> &trees) {
  uint32_t result = 1; // First tree is always cut.

  for (auto it = trees.begin() + 1, end = trees.end();
       it != end; ++it) {
    if ((it->begin - it->height) > ((it-1)->end)) {
      // It can be cut to the left
      it->cutLeft();
      ++result;
    } else if (((it+1) == end) ||
               (it->begin + it->height < (it+1)->begin)) {
      // It can be cut to the right
      it->cutRight();
      ++result;
    }
  }
  return result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t treeNumber;
  std::vector<Tree> trees;

  std::cin >> treeNumber;
  trees.reserve(treeNumber);

  int32_t pos = 0;
  int32_t height = 0;

  for (size_t i = 0; i < treeNumber; ++i) {
    std::cin >> pos >> height;
    trees.emplace_back(pos, height);
  }

  std::cout << woodcutters(trees) << "\n";
}
