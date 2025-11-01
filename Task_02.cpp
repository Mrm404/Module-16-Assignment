#include <bits/stdc++.h>
using namespace std;

void printCanvas(vector<string> &canvas) {
    for (string &row : canvas)
        cout << row << "\n";
}

void drawTree(vector<string> &canvas, int x, int y, int length, int depth) {
    if (depth == 0 || length == 0) return;
    for (int i = 0; i < length; i++)
        if (y - i >= 0)
            canvas[y - i][x] = '|';
    int newY = y - length;
    if (newY >= 0) {
        if (x - length/2 >= 0)
            canvas[newY][x - length/2] = '/';
        if (x + length/2 < (int)canvas[0].size())
            canvas[newY][x + length/2] = '\\';
    }
    drawTree(canvas, x - length/2, newY - 1, length / 2, depth - 1);
    drawTree(canvas, x + length/2, newY - 1, length / 2, depth - 1);
}

void drawSierpinski(vector<string> &canvas, int x, int y, int size, int depth) {
    if (depth == 0) {
        for (int i = 0; i < size; i++) {
            int start = x - i, end = x + i;
            if (y + i < (int)canvas.size())
                for (int j = start; j <= end; j++)
                    if (j >= 0 && j < (int)canvas[0].size())
                        canvas[y + i][j] = '*';
        }
        return;
    }
    drawSierpinski(canvas, x, y, size / 2, depth - 1);
    drawSierpinski(canvas, x - size / 2, y + size / 2, size / 2, depth - 1);
    drawSierpinski(canvas, x + size / 2, y + size / 2, size / 2, depth - 1);
}

void drawKoch(vector<pair<double, double>> &points, double x1, double y1, double x2, double y2, int depth) {
    if (depth == 0) {
        points.push_back({x2, y2});
        return;
    }
    double dx = (x2 - x1) / 3;
    double dy = (y2 - y1) / 3;
    double x3 = x1 + dx, y3 = y1 + dy;
    double x4 = x1 + 2 * dx, y4 = y1 + 2 * dy;
    double angle = M_PI / 3;
    double x5 = x3 + (dx * cos(angle) - dy * sin(angle));
    double y5 = y3 + (dx * sin(angle) + dy * cos(angle));
    drawKoch(points, x1, y1, x3, y3, depth - 1);
    drawKoch(points, x3, y3, x5, y5, depth - 1);
    drawKoch(points, x5, y5, x4, y4, depth - 1);
    drawKoch(points, x4, y4, x2, y2, depth - 1);
}

void printKochSnowflakeASCII(int depth) {
    const int width = 100, height = 40;
    vector<string> canvas(height, string(width, ' '));
    vector<pair<double, double>> points;

    drawKoch(points, 10, height/2, width-10, height/2, depth);
    for (auto &p : points) {
        int x = round(p.first);
        int y = round(p.second);
        if (x >= 0 && x < width && y >= 0 && y < height)
            canvas[y][x] = '*';
    }
    printCanvas(canvas);
}

int main() {
    int width = 80, height = 30;
    vector<string> canvas(height, string(width, ' '));
    cout << "Choose Fractal Type:\n";
    cout << "1. Recursive Tree\n2. Sierpinski Triangle\n3. Koch Snowflake\n";
    int choice; cin >> choice;

    switch(choice) {
        case 1:
            drawTree(canvas, width/2, height-1, 8, 4);
            printCanvas(canvas);
            break;
        case 2:
            drawSierpinski(canvas, width/2, 0, 16, 3);
            printCanvas(canvas);
            break;
        case 3:
            printKochSnowflakeASCII(3);
            break;
        default:
            cout << "Invalid choice.\n";
    }
    return 0;
}
