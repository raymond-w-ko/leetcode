#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


class Solution {
  vector<string> EMPTY;
 public:
  Solution()
      : num_possible_boards_(0),
        num_solutions_(0)
  {
  }
  vector<vector<string>> solveNQueens(int n) {
    for (int i = 0; i < n; ++i) {
      EMPTY.emplace_back(n, '.');
    }
    
    vector<vector<string>> solutions;
    vector<char> col_occupied(n, 0);
    
    search(EMPTY, n, 0, col_occupied, solutions);
    return solutions;
  }
  
  void search(vector<string>& board, const int n, const int row,
              vector<char>& col_occupied,
              vector<vector<string>>& solutions) {
    if (row == n) {
      num_possible_boards_++;
      if (valid_queens(board, n)) {
        solutions.push_back(board);
        num_solutions_++;
      }
      return;
    }
    for (int i = 0; i < n; ++i) {
      int col = i;
      if (col_occupied[col])
        continue;
      board[row][col] = 'Q';
      col_occupied[col] = 1;
      search(board, n, row + 1, col_occupied, solutions);
      col_occupied[col] = 0;
      board[row][col] = '.';
    }
  }
  
  bool valid_queens(const vector<string>& board, const int n) {
    for (int r_ = 0; r_ < n; ++r_) {
      for (int c_ = 0; c_ < n; ++c_) {
        if (board[r_][c_] != 'Q')
          continue;
        for (int r = r_ - 1, c = c_ - 1;
             r >= 0 && c >= 0 && r < n && c < n;
             r -= 1, c -= 1)
        {
          if (board[r][c] == 'Q')
            return false;
        }
        
        for (int r = r_ - 1, c = c_ + 1;
             r >= 0 && c >= 0 && r < n && c < n;
             r -= 1, c += 1)
        {
          if (board[r][c] == 'Q')
            return false;
        }
        
        for (int r = r_ + 1, c = c_ + 1;
             r >= 0 && c >= 0 && r < n && c < n;
             r += 1, c += 1)
        {
          if (board[r][c] == 'Q')
            return false;
        }

        for (int r = r_ + 1, c = c_ - 1;
             r >= 0 && c >= 0 && r < n && c < n;
             r += 1, c -= 1)
        {
          if (board[r][c] == 'Q')
            return false;
        }
      }
    }
    return true;
  }
  
  void print_board(const vector<string>& board) {
    cout << "----------------------------------------\n";
    for (const auto& row : board) {
      cout << row << "\n";
    }
  }
  
  long long num_possible_boards_;
  long long num_solutions_;
};

int main() {
  Solution sol;
  auto boards = sol.solveNQueens(9);
  for (auto board : boards) {
    sol.print_board(board);
  }
  cout << "num possible boards: " << sol.num_possible_boards_ << "\n";
  cout << "num solutions: " << sol.num_solutions_ << "\n";
}
