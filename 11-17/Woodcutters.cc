/*
  Woodcutters.cc

  author: Andrea Bisbano
  date: 10/10/17
  problem: http://codeforces.com/contest/545/problem/C

  solution description:

 FIXME: Clean code and write description of solution

 */

#include<vector>
#include<iostream>
#include<cassert>

class Tree {
  int Begin;
  int End;
  int Height;
public:
  Tree(int Pos, int H) : Begin(Pos), End(Pos), Height(H) {}

  void cutLeft() {
    Begin -= Height;
  }

  void cutRight() {
    End += Height;
  }

  int getBegin() {
    return Begin;
  }

  int getEnd() {
    return End;
  }

  int getHeight() {
    return Height;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int TreeNumber;
  std::vector<Tree> Trees;
  std::cin >> TreeNumber;
  Trees.reserve(TreeNumber);

  int Pos = 0;
  int Height = 0;

  for (int i = 0; i < TreeNumber; ++i) {
    std::cin >> Pos;
    std::cin >> Height;
    Trees.emplace_back(Pos, Height);
  }

  int Result = 1; // First tree is always cut.

  for (auto It = Trees.begin() + 1, End = Trees.end();
       It != End; ++It) {
    if ((It->getBegin() - It->getHeight()) > ((It-1)->getEnd())) {
        // It can be cut to the left
      It->cutLeft();
      ++Result;
    } else if (((It+1) == End) ||
               (It->getBegin() + It->getHeight()  < (It+1)->getBegin())) {
      // It can be cut to the right
      It->cutRight();
      ++Result;
    }
  }
  std::cout << Result << std::endl;
}



