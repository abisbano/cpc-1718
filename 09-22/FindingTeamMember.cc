/*
 FindingTeamMember.cc
 Author: Andrea Bisbano
 Date: 15/12/17
 Problem: http://codeforces.com/problemset/problem/579/B?locale=en
 Solution:
  For each member, we want to choose the highest possible strength among every value.
  So we create a set containing every possible team and its strength, we sort it
  in reverse order and then we scan the array and every team with both member still
  umpaired is the best team for those two members.
 Time cost: O(nlogn) that is the cost of the sorting operation, where n is the number of possibile teams.
 Space cost: O(1).
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define MAX_VALUE 1000000

class team {
  uint32_t first;
  uint32_t second;
  uint32_t strength;

public:
  uint32_t getFirst() {
    return first;
  }

  uint32_t getSecond() {
    return second;
  }

  team(uint32_t fst, uint32_t snd, uint32_t s) : first(fst), second(snd), strength(s) {}

  friend bool operator>(const team& lhs, const team& rhs) {
    return lhs.strength > rhs.strength;
  }
};

void findingTeamMember(std::vector<team> &vec, std::vector<uint32_t> &result) {
  // Sorting
  std::sort(vec.begin(), vec.end(),
            [](const team &lhs, const team &rhs) { return lhs > rhs; });

  for (auto T : vec) {
    if (result[T.getFirst()] == 0 && result[T.getSecond()] == 0) {
      result[T.getFirst()] = T.getSecond() + 1; // partecipants' numeration starts from 1.
      result[T.getSecond()] = T.getFirst() + 1;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  size_t N = 0; // Number of teams
  std::vector<team> teams; // Input vector
  uint32_t val;

  std::cin >> N;
  assert(N <= 400);
  teams.reserve((N*(N-1))/2);
  // Array of partecipants, initialized with 0 (special value that means `still umpaired').
  std::vector<uint32_t> result(2*N, 0);

  for (size_t i = 1; i < N*2; ++i) {
    for (size_t j = 0; j < i; ++j) {
      std::cin >> val;
      assert(val <= MAX_VALUE);
      teams.emplace_back(i, j, val);
    }
  }

  findingTeamMember(teams, result);
  for (auto j : result) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}
