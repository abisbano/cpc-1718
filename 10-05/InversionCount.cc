/*
 InversionCount.cc
 Author: Andrea Bisbano
 Date: 28/12/17
 Problem: http://www.spoj.com/problems/INVCNT/
 Solution:
 Time cost:
 Space cost:
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


// Merge
template <typename T>
int mergeCount(std::vector<T> &vec, int l, int middle, int r) {
  int i = l;
  int j = middle + 1;
  std::vector<T> B((r-l)+1);
  int k = 0;
  int inv = 0;

  while (i <= middle && j <= r) {
    if (vec[i] < vec[j]) {
//      B.push_back(Vec[i]);
//      ++i;
      B[k++] = vec[i++];
    } else {
//      B.push_back(Vec[j]);
//      ++j;
      B[k++] = vec[j++];
      inv += middle - i + 1;
    }
//    ++k;
  }

  while (i <= middle) {
    B[k] = vec[i];
    ++k;
//    B.push_back(Vec[i]);
    ++i;
  }

  while (j <= r) {
    B[k] = vec[j];
    ++k;
//    B.push_back(Vec[j]);
    ++j;
  }

  std::copy(B.begin(), B.end(), vec.begin() + l);

  return inv;
}

// Merge Sort
template <typename T>
int sortCount(std::vector<T> &vec, size_t l, size_t r) {
  if (l >= r)
    return 0;
  int middle = (l + r) / 2;
  int leftInv = sortCount(vec, l, middle);
  int rightInv = sortCount(vec, middle + 1, r);
  return leftInv + rightInv + mergeCount(vec, l, middle, r);
}

int main() {

  int testCases;
  std::vector<uint64_t> vec;
  size_t n;
  size_t value;
  std::string blank;

  std::cin >> testCases;
  std::getline(std::cin, blank);

  for (int i = 0; i < testCases; ++i) {
    std::cin >> n;
    vec.reserve(n);
    for (int j = 0; j < n; ++j) {
      std::cin >> value;
      vec.push_back(value);
    }
    std::getline(std::cin, blank);
    std::cout << sortCount(vec, 0, n-1) << std::endl;
    vec.clear();
  }

  return 0;
}
