/*
  FindingTeamMember.cc

  author: Andrea Bisbano
  date: 15/12/17
  problem: http://codeforces.com/problemset/problem/579/B?locale=en
 
  solution description:
    The idea of the solution is to choose, for each member, the highest possible strength among every value.
    To do so we use a data structure containing the numbers of two partecipants and the strength of the team
    formed by them. We store all the input value in an array and we sort it by decreasing order of the strength.
    After that, we simply scan the sorted array and we choose a value if the members composing it are still
    umpaired.
    The cost of this algorithm is O(nlogn) because of the sorting and n is the number of possible team.
*/

#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

#define MAX_VALUE 1000000

class Team {
  int Member1;
  int Member2;
  int Strength;

public:
  int getMember1() {
    return Member1;
  }

  int getMember2() {
    return Member2;
  }

  Team(int M1, int M2, int S) : Member1(M1), Member2(M2), Strength(S) {}

  friend bool operator>(const Team& lhs, const Team& rhs) {
    return lhs.Strength > rhs.Strength;
  }
};

void findingTeamMember(std::vector<Team> &Values, std::vector<int> &Result) {
  // Sorting
  std::sort(Values.begin(), Values.end(),
            [](const Team &lhs, const Team &rhs) { return lhs > rhs; });

  for (auto T : Values) {
    if (Result[T.getMember1()] == 0 && Result[T.getMember2()] == 0) {
      Result[T.getMember1()] = T.getMember2() + 1; // partecipants' numeration starts from 1.
      Result[T.getMember2()] = T.getMember1() + 1;
    }
  }
}

int main() {
  int N = 0; // Number of teams
  std::vector<Team> Teams; // Input vector
  int Value;

  std::cin >> N;
  assert(N > 0 && N <= 400);
  Teams.reserve((N*(N-1))/2);
  // Array of partecipants, initialized with 0 (special value that means `still umpaired').
  std::vector<int> Result(2*N, 0);

  for (int i = 1; i < N*2; ++i) {
    for (int j = 0; j < i; ++j) {
      std::cin >> Value;
      assert(Value >= 0 && Value <= MAX_VALUE);
      Teams.emplace_back(i, j, Value);
    }
  }

  findingTeamMember(Teams, Result);
  for (auto j : Result) {
    std::cout << j << " ";
  }
  std::cout << std::endl;
}
