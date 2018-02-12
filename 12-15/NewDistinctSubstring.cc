/*
 NewDistinctSubstring.cc
 Author: Andrea Bisbano
 Date: 12/02/18
 Problem: http://www.spoj.com/problems/SUBST1/
 Solution:
  The idea is to use a suffix array and the longest common prefix. To do so, we first compute the
  suffix array and then we use the kasai's algorithm to compute the lcp starting from the previous
  result.
 Time cost: O(NlogNlogN) the cost is dominated by the computation of suffix array.
 Space cost: O(N) to store the suffix array and the lcp.
*/

#include <iostream>
#include <string>
#include <cassert>
#include <algorithm>
#include <vector>

#define OFFSET 65

struct suffix {
  size_t index;
  int32_t rank;
  int32_t nextRank;
};

int compare(const suffix &a, const suffix &b) {
  return (a.rank == b.rank ? a.nextRank < b.nextRank : a.rank < b.rank);
}

void buildSuffixArray(std::vector<int32_t> &suffixArray,
                      std::string str) {
  size_t n = str.length();

  suffixArray = std::vector<int32_t>(n,0);
  std::vector<suffix> suffixes(n);
  std::vector<size_t> indices(n,0);
  for (size_t i = 0; i < n; ++i) {
    suffixes[i].index = i;
    suffixes[i].rank = str[i] - OFFSET;
    suffixes[i].nextRank = ((i+1 < n) ? str[i+1] - OFFSET : -1);
  }

  std::sort(suffixes.begin(), suffixes.end(), compare);

  for (size_t k = 4; k < 2*n; k *= 2) {
    int32_t rank = 0;
    int32_t previousRank = suffixes[0].rank;
    suffixes[0].rank = rank;
    indices[suffixes[0].index] = 0;

    for (size_t i = 1; i < n; ++i) {
      if (suffixes[i].rank != previousRank ||
          suffixes[i].nextRank != suffixes[i-1].nextRank) {
        ++rank;
        previousRank = suffixes[i].rank;
      }
      suffixes[i].rank = rank;
      indices[suffixes[i].index] = i;
    }

    for (size_t i = 0; i < n; ++i) {
      int32_t nextIndex = suffixes[i].index + k/2;
      suffixes[i].nextRank = ((nextIndex < n) ?
                                 suffixes[indices[nextIndex]].rank
                                 : -1);
    }

    std::sort(suffixes.begin(), suffixes.end(), compare);

  }

  for (size_t i = 0; i < n; ++i) {
    suffixArray[i] = suffixes[i].index;
  }

}

void kasai (std::vector<int32_t> &lcp,
            const std::vector<int32_t> &suffixArray, std::string &str) {
  size_t n = suffixArray.size();

  lcp = std::vector<int32_t>(n,0);
  std::vector<int32_t> invSuff(n,0);

  for (size_t i = 0; i < n; ++i) {
    invSuff[suffixArray[i]] = i;
  }
  int32_t k = 0;

  for (size_t i = 0; i < n; ++i) {
    if (invSuff[i] == n-1) {
      k = 0;
      continue;
    }
    int32_t j = suffixArray[invSuff[i]+1];
    while ((i+k) < n && (j+k) < n && str[i+k] == str[j+k]) {
      ++k;
    }
    lcp[invSuff[i]] = k;
    if (k > 0) {
      --k;
    }
  }
}

int32_t newDistinctSubstring(std::string &str) {

  std::vector<int32_t> suffixArray;
  std::vector<int32_t> lcp;

  buildSuffixArray(suffixArray, str);
  kasai(lcp, suffixArray, str);

  size_t n = suffixArray.size();
  int32_t result = n - suffixArray[0];

  for (size_t i = 1; i < n; ++i) {
    result += (n-suffixArray[i]) - lcp[i-1];
  }
  return result;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t n;
  std::string str;

  std::cin >> n;
  assert(n >= 1 && n <= 20);

  for (size_t i = 0; i < n; ++i) {
    std::cin >> str;
    std::cout << newDistinctSubstring(str) << "\n";
  }
}

