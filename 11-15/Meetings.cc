/*
 Meetings.cc
 Author: Andrea Bisbano
 Date: 18/01/18
 Problem: https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0
 Solution:
  The idea is to sort the meeting in increasing order of finishing time, then we choose with a
  greedy approach the first meeting which its starting time is after the finishing time of the
  preovious one and so on.
 Time cost: O(NlogN) because we need to sort the input data.
 Space cost: O(1)
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

struct meeting {
  uint64_t index;
  uint64_t start;
  uint64_t finish;
};

void meetingsInOneRoom(std::vector<uint64_t> &result, std::vector<meeting> &meetings) {
  uint64_t lastFinish = 0;
  std::sort(meetings.begin(), meetings.end(), [] (meeting &a, meeting &b) {
    return a.finish < b.finish;
  });
  for (auto m : meetings) {
    if (m.start > lastFinish) {
      lastFinish = m.finish;
      result.push_back(m.index);
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t testCases;
  size_t n;
  uint64_t time;
  std::vector<uint64_t> result;

  std::cin >> testCases;
  assert(testCases >= 1 && testCases <= 70);

  for (size_t i = 0; i < testCases; ++i) {
    std::cin >> n;
    assert(n >= 1 && n <= 100);
    std::vector<meeting> meetings(n);
    for (size_t j = 0; j < n; ++j) {
      std::cin >> time;
      meetings[j].index = j+1;
      meetings[j].start = time;
    }
    for (size_t j = 0; j < n; ++j) {
      std::cin >> time;
      meetings[j].finish = time;
    }

    result.clear();
    meetingsInOneRoom(result, meetings);
    for (auto r : result) {
      std::cout << r << " ";
    }
    std::cout << "\n";
  }
}
