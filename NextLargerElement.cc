/*
  NextLargerElement.cc

  author: Andrea Bisbano
  date: 10/11/17
  problem: http://practice.geeksforgeeks.org/problems/next-larger-element/0
 
  solution description:
 The idea of this solution is to use a stack to store, in increasing order, the position of the elements
   for which we still have to find the next larger element.
 At each step of the loop we remove from the head (pop) all the elements smaller than the current one
   and we set that one as the next larger element for the previously removed elements.
 After that we add the element to the top of the stack and we know that the remaingn elements are larger
   than that.

 The cost in time is O(n), because for each element we perform just one push operation and at most one
   pop operation (if it has a next larger element); also the cost in space is O(n) because in the worst case
   we need a stack of the same size of the input array (i.e all elements are sorted in decreasing
   order and none has a next larger element).

*/

#include <iostream>
#include <vector>
#include <cassert>
#include <stack>

void nextLargerElement(const std::vector<int> &Vec, std::vector<int> &Result) {
  std::stack<int> S;

  for (int i = 0; i < Vec.size(); ++i) {
    while ((!S.empty()) && Vec[S.top()] <= Vec[i]) {
      Result[S.top()] = Vec[i];
      S.pop();
    }
    S.push(i);
  }

}

int main() {

  int TestCases = 0;
  std::cin >> TestCases;
  assert(TestCases > 0 && TestCases <= 200);

  std::vector<int> Vec;
  std::vector<int> Result;
  int VecSize = 0;
  int Value = 0;

  for (int i = 0; i < TestCases; ++i) {
    std::cin >> VecSize;
    assert(VecSize > 0 && VecSize <= 1000);
    Vec.reserve(VecSize);
    Result = std::vector<int>(VecSize, -1);

    for (int j = 0; j < VecSize; ++j) {
      std::cin >> Value;
      // This assertion is commented out because it invalidates the test case on geeksforgeek,
      // even if the problem states that each element is in [1, 1000].
      //assert(Value > 0 && Value <= 1000);
      Vec.push_back(Value);
    }
    nextLargerElement(Vec, Result);
    for (int k : Result) {
      std::cout << k << " ";
    }
    std::cout << std::endl;
    Vec.clear();
    Result.clear();
  }
}
