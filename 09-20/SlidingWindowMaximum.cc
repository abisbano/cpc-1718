/*
 SlidingWindowMaximum.cc
 Author: Andrea Bisbano
 Date: 27/10/17
 Problem: http://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0
 Solution:
  Given an array A of n elements and a integer k (the size of the window),
  we want to create a double-ended queue Q (of size up to k) to store the
  elements of A currently in the window, ordered in a way that the head
  will always contain the maximum element of the window.
  We start with a window in the range [-k, -1] and repeat the following steps n times:
  1. slide the window of one position right
  2. if the head of Q is no longer in the window, we remove it
  3. add the new element behind and remove all above elements which are smaller
  4. report the head as the current maximum (if the window has a valid range)
  Thanks to step 3 we have the guarantee that at every step if there's an element no longer in the
  window is the one in the head (and so step 2 makes sense).
 Time cost: O(n) beacuse the main loop performs at most n pop and n push operations.
 Space cost: O(k) because the deque is at most of the same size of the window.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

void slidingWindowMaximum(const std::vector<uint32_t> &vec, std::vector<uint32_t> &result, int32_t K) {
  std::deque<int32_t> positions;

  for (int32_t i = 0; i < vec.size(); ++i) {
    // Step 2
    if ((!positions.empty()) && positions.front() <= i - K)
      positions.pop_front();
    // Step 3
    while ((!positions.empty()) && vec[positions.back()] <= vec[i])
      positions.pop_back();
    positions.push_back(i);
    // Step 4
    if (i >= K - 1)
      result.push_back(vec[positions.front()]);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t T;
  std::vector<uint32_t> vec;
  std::vector<uint32_t> result;
  size_t N, K;
  uint32_t val;

  std::cin >> T;
  assert(T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N <= 100);
    std::cin >> K;
    assert(K <= N);
    vec.reserve(N);
    result.reserve(N - K + 1);

    for (size_t j = 0; j < N; ++j) {
      std::cin >> val;
      assert(val <= 1000);
      vec.push_back(val);
    }
    slidingWindowMaximum(vec, result, K);
    for (auto k : result) {
      std::cout << k << " ";
    }
    std::cout << "\n";
    vec.clear();
    result.clear();
  }
}
