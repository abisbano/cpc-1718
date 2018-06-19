/*
 InversionCount.cc
 Author: Andrea Bisbano
 Date: 28/12/17
 Problem: http://www.spoj.com/problems/INVCNT/
 Solution:
  The idea uses the merge sort algorithm to count the number of inversions. The total number of
  inversions is the sum of the inversion of the two subarrays and the inversions during the merge step.
  Given two indices i and j belonging respectively to the left and the right subarray, if
  a[i] > a[j] then there are (mid - i) inversions.
  This is true because the remaining values of the left subarray (with index greater than i) are
  also greater than a[j] because both subarrays are sorted.
  Exploiting this fact the algorithm counts the number or inversions.
 Time cost: O(nlogn) which is the cost of the merge sort.
 Space cost: O(1)
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>


// Merge operation
template <typename T>
uint64_t mergeCount(std::vector<T> &vec, std::vector<T> &tmp, size_t l, size_t middle, size_t r) {
  size_t i = l;
  size_t j = middle;
  size_t k = l;
  uint64_t inv = 0;

  while (i <= middle -1 && j <= r) {
    if (vec[i] <= vec[j]) {
      tmp[k++] = vec[i++];
    } else {
      tmp[k++] = vec[j++];
      inv += middle - i;
    }
  }
  // copy the rest of the array to tmp
  while (i <= middle - 1)
    tmp[k++] = vec[i++];

  while (j <= r)
    tmp[k++] = vec[j++];
  // update the original array.
  for (i=l; i <= r; i++)
    vec[i] = tmp[i];

  return inv;
}

// Merge Sort
template <typename T>
uint64_t sortCount(std::vector<T> &vec, std::vector<T> &tmp, size_t l, size_t r) {
  if (l >= r)
    return 0;
  size_t middle = (l + r) / 2;
  uint64_t leftInv = sortCount(vec, tmp, l, middle);
  uint64_t rightInv = sortCount(vec, tmp, middle + 1, r);
  return leftInv + rightInv + mergeCount(vec, tmp, l, middle+1, r);
}

int main() {

  size_t testCases;
  std::vector<uint64_t> vec;
  size_t n;
  size_t value;
  std::string blank;

  std::cin >> testCases;
  std::getline(std::cin, blank);

  for (size_t i = 0; i < testCases; ++i) {
    std::cin >> n;
    vec.reserve(n);
    std::vector<uint64_t> tmp(n,0);
    for (size_t j = 0; j < n; ++j) {
      std::cin >> value;
      vec.push_back(value);
    }
    std::getline(std::cin, blank);
    std::cout << sortCount(vec, tmp, 0, n-1) << std::endl;
    vec.clear();
  }

  return 0;
}
