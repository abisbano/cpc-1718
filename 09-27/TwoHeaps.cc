/*
  TwoHeaps.cc

  author: Andrea Bisbano
  date: 20/12/17
  problem: http://codeforces.com/problemset/problem/353/B?locale=en

  solution description:

 The idea of this solution it to divide the values in two sets: the first containing
  only the values that appears at most 2 times and the second with the others.
 After that, we divide the values in the first set among the two heaps in an even way,
  with the caution of inserting the values that appears two times in both heaps.
 The values of the second set are inserted at random to fill the two heaps.
 By doing that the number of possible combination is the maximum possible.

 In the implementation we sort the values in increasing order, saving the original
  position. After that we scan the sorted array and for each value we have tree possibilities:
 1. is the first time we find a value
 2. is the second time we find a value
 3. we already found the value more than two times.
 In cases 1 and 2 we add the current value to one of the two heaps. To guarantee that
  the heaps are balanced and the repeated values are in both of them, two consecutive
  values are putted in different heaps (this is true for every value, not only the
  repeated one)
 In the third case, we store the value for later processing and after scanning the
  whole array we insert the values at random in both heaps to fill them.

 The cost in time of this algorithm is O(nlogn) because of the sorting and we don't
  need addition space to perform the operations.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

class Element {
  int Position;
  int Value;

public:
  Element(int P, int V) : Position(P), Value(V) { }

  int getPosition() {
    return Position;
  }

  int getValue() {
    return Value;
  }

  friend bool operator<(const Element& lhs, const Element& rhs) {
    return lhs.Value < rhs.Value;
  }

};

int twoHeaps(std::vector<Element> &Vec, std::vector<int> &Result) {

  std::sort(Vec.begin(), Vec.end());

  int Distinct = 0;
  int Current = 0;
  int Heap = 1;
  bool MoreThanTwo = false;

  std::vector<int> Duplicates;

  for (auto E : Vec) {

    if (E.getValue() != Current || !MoreThanTwo) {
      MoreThanTwo = false;
      Result[E.getPosition()] = Heap;
      Heap = (Heap == 1) ? 2 : 1;
      ++Distinct;
    } else {
      Duplicates.push_back(E.getPosition());
    }
    if (E.getValue() == Current) {
      MoreThanTwo = true;
    } else {
      Current = E.getValue();
    }
  }


  //  TODO: This could be written in a cleaner way...
  int i = 0;
  for (; i < Duplicates.size() / 2 ; ++i) {
    Result[Duplicates[i]] = 1;
  }
  for (; i < Duplicates.size(); ++i) {
    Result[Duplicates[i]] = 2;
  }

  return (Distinct/2 * (Distinct - Distinct/2));
}


int main() {
  int Size;
  int K;
  std::vector<Element> Vec;
  long Value;

  std::cin >> Size;
  assert(Size >= 1 && Size <= 100);

  for (int i = 0; i < Size*2; ++i) {
    std::cin >> Value;
    assert(Value >= 10 && Value <= 99);
    Vec.emplace_back(i, Value);
  }

  std::vector<int> Result(Size*2, 0);
  auto Distinct = twoHeaps(Vec, Result);

  std::cout << Distinct << std::endl;
  for (auto i : Result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;


}
