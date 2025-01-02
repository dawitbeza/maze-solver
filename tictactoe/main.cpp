#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

// Position structure
struct Pos {
    int row, col;
    Pos(int row, int col) : row(row), col(col) {}
    Pos() = default;
    bool operator==(const Pos& pos) {
        return pos.col == col && pos.row == row;
   }
};

bool validMove(std::vector<std::vector<int>>& maze, const Pos& currentCell, char direction) {
    if (direction == 'U')
        if (currentCell.row - 1 >= 0 && maze[currentCell.row - 1][currentCell.col] != 1)
            return true;
    if (direction == 'D')
        if (currentCell.row + 1 <= maze.size() - 1 && maze[currentCell.row + 1][currentCell.col] != 1)
            return true;
    if (direction == 'L')
        if (currentCell.col - 1 >= 0 && maze[currentCell.row][currentCell.col - 1] != 1)
            return true;
    if (direction == 'R')
        if (currentCell.col + 1 <= maze[0].size() - 1 && maze[currentCell.row][currentCell.col + 1] != 1)
            return true;

    return false;
}


void printSolvedMaze(const std::vector<std::vector<int>>& maze,  std::vector<Pos>& moves) {
    int moveTracker = 0;
    for (int row = 0; row < maze.size(); row++) {
        for (int col = 0; col < maze[0].size(); col++) {
            if ( moveTracker < moves.size() && moves[moveTracker] == Pos{row, col}) {
                std::cout << maze[row][col] << "-   ";
                moveTracker++;
            }
            else std::cout << maze[row][col] << "    ";
        }
        std::cout << std::endl << std::endl;
    }
    std::cout << std::endl << std::endl;
}

bool solveSudoku(std::vector<std::vector<int>> maze, const Pos& startPos, std::vector<Pos>& moves, int& attempt) {
    if (maze[startPos.row][startPos.col] == 2) {
        return true;
    }

    for (const auto& ch : { 'U', 'D', 'R', 'L' }) {
        attempt++;
        if (validMove(maze, startPos, ch)) {
            moves.push_back({startPos.row, startPos.col});
            maze[startPos.row][startPos.col] = 1;
            if (ch == 'U')
                if (solveSudoku(maze, { startPos.row - 1, startPos.col },  moves, attempt))
                    return true;
            if (ch == 'D')
                if (solveSudoku(maze, { startPos.row + 1, startPos.col }, moves, attempt))
                    return true;
            if (ch == 'R')
                if (solveSudoku(maze, { startPos.row, startPos.col + 1 }, moves, attempt))
                    return true;
            if (ch == 'L')
                if (solveSudoku(maze, { startPos.row, startPos.col - 1}, moves, attempt))
                    return true;
            maze[startPos.row][startPos.col] = 0;
        }
    }
    return false;
}

//for sorting the our move vector based on the row and column
bool comparePos(const Pos& a, const Pos& b) {
    if (a.row == b.row) {
        return a.col < b.col; 
    }
    return a.row < b.row; 
}
int main() {
    // Maze representation (0 = path, 1 = wall, 2 = goal)
#include <vector>

    std::vector<std::vector<int>> maze = {
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    };


    int attempt = 0;
    std::vector<Pos> moves;
    solveSudoku(maze, { 0, 0 }, moves, attempt);
    //this sorting helps us to mark cells found in the left or up of a given cell
    std::sort(moves.begin(), moves.end(), comparePos);
    printSolvedMaze(maze, moves);
    std::cout << attempt;
    return 0;
}
