/*
  Towers.cc

  author: Andrea Bisbano
  date: 18/10/17
  problem: http://codeforces.com/problemset/problem/37/A?locale=en
 
  solution description:
 The idea of this solution is to don't use comparison model, since we know that the maximum length of a bar
  is 1000 (we call it M). The idea consist in creating a support array of M+1 elements that is used to
  count the occurence of each possible length. So we need to scan the original array one time and for each
  value increase the corrisponding value of the support array. At each iteration we also compute the current
  maximum confronting the current counter with the maximum value so far; by doing this we avoid to scan
  the whole support array.
 The cost in time of this solution is O(N), but it has a cost in space of O(M).

 Another solution, using comparison model, consist in sorting the original array and the scanning it
  counting the different elements and the maximum value. This solution has a cost in time of O(nlogn)
  and don't use additional space.
 The choice of implementing the first solution is due to several running time experiment performed on both
  algorithms. As expected, these tests showed that the comparison model solution is better for smaller
  inputs (i.e. < 350 items).
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define MAX_VALUE 1000

void computeTowers(const std::vector<int> &Vec, int& MaxHeight, int& TowersNumber) {
  std::vector<int> Towers = std::vector<int>(MAX_VALUE + 1, 0);
  for (auto Value : Vec) {
    if (Towers[Value] == 0) {
      // That's a new tower, so we increase counting.
      ++TowersNumber;
    }
    ++Towers[Value];
    if (Towers[Value] > MaxHeight) {
      MaxHeight = Towers[Value];
    }
  }
}

int main() {
  int Size = 0;
  int Value = 0;
  std::vector<int> Vec;
  int MaxHeight = 0;
  int TowersNumber = 0;

  std::cin >> Size;
  assert(Size > 0 && Size <= 1000);
  Vec.reserve(Size);
  for (int j = 0; j < Size; ++j) {
    std::cin >> Value;
    assert(Value >= 0 && Value <= MAX_VALUE);
    Vec.push_back(Value);
  }
  computeTowers(Vec, MaxHeight, TowersNumber);
  std::cout << MaxHeight << " " << TowersNumber << std::endl;
}
