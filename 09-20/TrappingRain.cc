/*
  TrappingRain.cc

  author: Andrea Bisbano
  date: 27/10/17
  problem: http://practice.geeksforgeeks.org/problems/trapping-rain-water/0

  solution description:
   The idea of this solution is to precompute and store in an array of the same
   size of the input data the value of the maximum element in the left subarray
   of each element.
   After that we scan the original array in reverse order, keeping track of the
   maximum value so far. For each element, the water trapped is the difference
   between the current value and the minimun between the maximum to the right
   and to the left.

   The cost in time for this algorithm in O(n), since we only need to scan the
   whole array 2 times. And the cost in space in also O(n) since we need to
   store a new array of the same size of the original problem.
 */

#include<vector>
#include<iostream>
#include<cassert>

int trappingRain(const std::vector<int> &Vec) {
  int Result = 0;
  std::vector<int> LeftMax;
  LeftMax.reserve(Vec.size());
  int CurrentMax = -1; // We use a dummy value for the first element,
                       // since it hasn't a left subarray.

  for (auto It = Vec.begin(), End = Vec.end(); It != End; ++It) {
    LeftMax.push_back(CurrentMax);
    if (*It > CurrentMax) {
      CurrentMax = *It;
    }
  }

  CurrentMax = -1; // We use the same variable for the maximum of the right subarray

  auto It2 = LeftMax.rbegin();
  for (auto It1 = Vec.rbegin(), End = Vec.rend(); It1 != End; ++It1, ++It2) {
    if (*It1 > CurrentMax) {
      CurrentMax = *It1;
    } else {
      if (*It1 < *It2) {
        Result += (std::min(CurrentMax, *It2) - *It1);
      }
    }
  }
  return Result;
}

int main() {

  int TestCases;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 100);

  std::vector<int> Vec;
  int Size;
  int Element;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> Size;
    assert(Size > 2 && Size <= 100);

    Vec.reserve(Size);

    for (int j = 0; j < Size; ++j) {
      std::cin >> Element;
      assert(Element >= 0 && Element < 10);
      Vec.push_back(Element);
    }

    std::cout << trappingRain(Vec) << std::endl;
    Vec.clear();
  }
}
