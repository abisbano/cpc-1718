/*
 FindingTeamMember.cc
 Author: Andrea Bisbano
 Date: 15/12/17
 Problem: http://codeforces.com/problemset/problem/579/B?locale=en
 Solution:
  We want to choose, for each member, the highest possible strength among every value. To do se, we store
  a set containing the strenght of each couple and the members it's formed by. After that, we sort in
  reverse order the array, we scan the elements and we choose a value if the memebrs it's composed by are
  still umpaired.
 Time cost: O(nlogn) that is the cost of the sorting operation.
 Space cost: O(1).
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define MAX_VALUE 1000000

class team {
  int member1;
  int member2;
  int strength;

public:
  int getMember1() {
    return member1;
  }

  int getMember2() {
    return member2;
  }

  team(int m1, int m2, int S) : member1(m1), member2(m2), strength(S) {}

  friend bool operator>(const team& lhs, const team& rhs) {
    return lhs.strength > rhs.strength;
  }
};

void findingTeamMember(std::vector<team> &vec, std::vector<int> &result) {
  // Sorting
  std::sort(vec.begin(), vec.end(),
            [](const team &lhs, const team &rhs) { return lhs > rhs; });

  for (auto T : vec) {
    if (result[T.getMember1()] == 0 && result[T.getMember2()] == 0) {
      result[T.getMember1()] = T.getMember2() + 1; // partecipants' numeration starts from 1.
      result[T.getMember2()] = T.getMember1() + 1;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int N = 0; // Number of teams
  std::vector<team> teams; // Input vector
  int val;

  std::cin >> N;
  assert(N > 0 && N <= 400);
  teams.reserve((N*(N-1))/2);
  // Array of partecipants, initialized with 0 (special value that means `still umpaired').
  std::vector<int> result(2*N, 0);

  for (int i = 1; i < N*2; ++i) {
    for (int j = 0; j < i; ++j) {
      std::cin >> val;
      assert(val >= 0 && val <= MAX_VALUE);
      teams.emplace_back(i, j, val);
    }
  }

  findingTeamMember(teams, result);
  for (auto j : result) {
    std::cout << j << " ";
  }
  std::cout << "\n";
}
