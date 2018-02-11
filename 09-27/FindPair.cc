/*
 FindPair.cc
 Author: Andrea Bisbano
 Date: 19/11/17
 Problem: http://codeforces.com/problemset/problem/160/C?locale=en
 Solution:
 Time ost:
 Space cost:

*/

#include <iostream>
#include <cassert>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
std::pair<T,T> findPair( std::vector<T> &Vec, int K) {
  std::sort(Vec.begin(), Vec.end());


  int Size = Vec.size();
  for (int i = 0; i < Size; ++i) {
    for (int j = 0; j < Size; ++j) {
      std::cout << "(" << Vec[i] << "," << Vec[j] << ")\t";
    }
    std::cout << std::endl;
  }

  K--; // We decrease value K to have a 0-based value.
  std::cout << "Index " << (K/Size) << " " << (K%Size) << std::endl;

  return std::pair<T,T> (Vec[K/Size], Vec[K%Size]);

}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  
  int Size;
  int K;
  std::vector<long> Vec;
  long Value;

  std::cin >> Size;
  assert(Size >= 1 && Size <= 10000);
  Vec.reserve(Size);
  std::cin >> K;
  assert(K >= 1 && K <= Size*Size);
  for (int i = 0; i < Size; ++i) {
    std::cin >> Value;
    assert(Value >= -1000000000 && Value <= 1000000000);
    Vec.push_back(Value);
  }

  auto Result = findPair(Vec, K);

  std::cout << Result.first << " " << Result.second << std::endl;


}
