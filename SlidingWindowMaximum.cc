/*
  SlidingWindowMaximum.cc

  author: Andrea Bisbano
  date: 27/10/17
  problem: http://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0
 
  solution description:
 Given an array A on n elements, a window (of size k), we want to use a Double-Ended Queue Q to store the
   ordered positions of the elements of A in the current window. By doing so the head of Q will always
   contain the maximum element.
 The starting window is in the range (-n, -1) and we repeat the following steps n times:
   1. Slide the window of one position right
   2. Remove the head of Q if it's no longer in the window.
   3. Add the new element from the tail and remove all the elements above which are smaller than the current.
   4. Report the head as the maximum of the current window (if the whole window is within A)
 Thanks to step 3 we have the guarantee that at every step if there's an element no longer in the
   window is the one in the head (and so step 2 makes sense).

 The cost in time of the algorithm is O(n), since the main loop performs at most n pop and n push operation.
 The cost in space is O(k) since the deque is at most of the same size of the window.

*/

#include <iostream>
#include <vector>
#include <cassert>
#include <deque>

void slidingWindowMaximum(const std::vector<int> &Vec, std::vector<int> &Result, int Size) {
  std::deque<int> Positions;

  for (int i = 0; i < Vec.size(); ++i) {

    // Step 2
    if ((!Positions.empty()) && Positions.front() <= i - Size)
      Positions.pop_front();
    // Step 3
    while ((!Positions.empty()) && Vec[Positions.back()] <= Vec[i])
      Positions.pop_back();
    Positions.push_back(i);
    // Step 4
    if (i >= Size - 1)
      Result.push_back(Vec[Positions.front()]);
  }
}

int main() {

  int TestCases = 0;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 200);

  std::vector<int> Vec;
  std::vector<int> Result;
  int VecSize = 0;
  int WindowSize = 0;
  int Value = 0;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> VecSize;
    assert(VecSize > 0 && VecSize <= 100);
    std::cin >> WindowSize;
    assert(WindowSize > 0 && WindowSize <= VecSize);
    Vec.reserve(VecSize);
    Result.reserve(VecSize - WindowSize + 1);

    for (int j = 0; j < VecSize; ++j) {
      std::cin >> Value;
      assert(Value >= 0 && Value <= 1000);
      Vec.push_back(Value);
    }
    slidingWindowMaximum(Vec, Result, WindowSize);
    for (int k : Result) {
      std::cout << k << " ";
    }
    std::cout << std::endl;
    Vec.clear();
    Result.clear();
  }
}
