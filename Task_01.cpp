#include <bits/stdc++.h>
using namespace std;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

vector<vector<char>> maze;
vector<vector<bool>> visited;
vector<pair<int, int>> shortestPath;
vector<vector<pair<int, int>>> allPaths;

int rows, cols;

bool isValid(int r, int c) {
    return r >= 0 && r < rows && c >= 0 && c < cols && 
           maze[r][c] != '1' && !visited[r][c];
}

void backtrack(int r, int c, vector<pair<int, int>> &path) {
    if (maze[r][c] == 'E') {
        allPaths.push_back(path);
        if (shortestPath.empty() || path.size() < shortestPath.size())
            shortestPath = path;
        return;
    }

    visited[r][c] = true;

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc)) {
            path.push_back({nr, nc});
            backtrack(nr, nc, path);
            path.pop_back();
        }
    }

    visited[r][c] = false;
}

void solveMaze() {
    int startR = -1, startC = -1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (maze[i][j] == 'S') {
                startR = i;
                startC = j;
                break;
            }

    vector<pair<int, int>> path = {{startR, startC}};
    backtrack(startR, startC, path);
}

void printPath(const vector<pair<int, int>> &path) {
    for (auto [r, c] : path)
        cout << "(" << r << "," << c << ") ";
    cout << "\n";
}

int main() {
    maze = {
        {'S', '0', '1', '0', '0'},
        {'0', '1', '0', '1', '0'},
        {'0', '0', '0', '1', '0'},
        {'1', '1', '0', '0', 'E'}
    };

    rows = maze.size();
    cols = maze[0].size();
    visited.assign(rows, vector<bool>(cols, false));

    solveMaze();

    if (allPaths.empty()) {
        cout << "No path found.\n";
        return 0;
    }

    cout << "All possible paths:\n";
    for (auto &p : allPaths)
        printPath(p);

    cout << "\nShortest Path:\n";
    printPath(shortestPath);
    cout << "Length: " << shortestPath.size() << "\n";

    return 0;
}
