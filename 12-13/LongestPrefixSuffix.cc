/*

 LongestPrefixSuffix.cc
 https://practice.geeksforgeeks.org/problems/longest-prefix-suffix/0

 Solution description:


 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>


int computePrefixFunction(const std::string& Text, const int N) {

  std::vector<int> Pie(N,0);
//  Pie.reserve(N);

//  Pie.push_back(0);
  int K = 0;
  char cache;

  for (int q = 1;  q < N; ++q) {
    cache = Text.at(q);
    while (K > 0 && Text.at(K) != cache)
      K = Pie[K];
    if (Text.at(K) == cache) {
      ++K;
    }
    Pie[q] = K;
//    Pie.push_back(K);

  }

  return Pie[N-1];
}

int main() {

  int TestCases;

  std::cin >> TestCases;
  assert(TestCases >= 1 && TestCases <= 100);

  std::cin.clear();
  std::cin.ignore(100000,'\n');

  std::string Text;

  for (int i = 0; i < TestCases; ++i) {
    std::getline(std::cin, Text);

    std::cout << computePrefixFunction(Text, Text.length()) << std::endl;
  }
  return 0;
}

