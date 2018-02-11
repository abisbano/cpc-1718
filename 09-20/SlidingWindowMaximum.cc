/*
 SlidingWindowMaximum.cc
 Author: Andrea Bisbano
 Date: 27/10/17
 Problem: http://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0
 Solution:
  Given an array A on n elements, a window (of size k), we want to use a Double-Ended Queue Q to store the
  ordered positions of the elements of A in the current window. By doing so the head of Q will always
  contain the maximum element.
  The starting window is in the range (-n, -1) and we repeat the following steps n times:
  1. Slide the window of one position right
  2. Remove the head of Q if it's no longer in the window.
  3. Add the new element from the tail and remove all elements above which are smaller than the current.
  4. Report the head as the maximum of the current window (if the whole window is within A)
  Thanks to step 3 we have the guarantee that at every step if there's an element no longer in the
  window is the one in the head (and so step 2 makes sense).
 Time cost: O(n) beacuse the main loop performs at most n pop and n push operations.
 Space cost: O(k) because the deque is at most of the same size of the window.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

void slidingWindowMaximum(const std::vector<int32_t> &vec, std::vector<int32_t> &result, int32_t K) {
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
  std::vector<int32_t> vec;
  std::vector<int32_t> result;
  int32_t N, K;
  int32_t val;

  std::cin >> T;
  assert(T > 0 && T <= 200);

  for (size_t i = 0; i < T; ++i) {
    std::cin >> N;
    assert(N > 0 && N <= 100);
    std::cin >> K;
    assert(K > 0 && K <= N);
    vec.reserve(N);
    result.reserve(N - K + 1);

    for (size_t j = 0; j < N; ++j) {
      std::cin >> val;
      assert(val >= 0 && val <= 1000);
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
