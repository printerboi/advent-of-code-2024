#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <cmath>
#include <cassert>
#include <bits/stdc++.h>
#include <bitset>
#include <limits.h>
#include <queue>

#define FILENAME "input.txt"

std::vector<std::vector<char>> map;
std::vector<std::vector<bool>> predsmap;
std::vector<std::pair<int, int>> path;
std::pair<int, int> start;
std::pair<int, int> end;
long globmin = INT_MAX;

std::vector<std::vector<long>> distance;
std::vector<std::vector<bool>> visited;

enum class DIRECTION {
    LEFT,
    RIGHT,
    UP, DOWN, UNDEFINED
};

const std::pair<int, int> UP = {-1, 0};
const std::pair<int, int> DOWN = {1, 0};
const std::pair<int, int> LEFT = {0, -1};
const std::pair<int, int> RIGHT = {0, 1};


struct Node {
    int x;
    int y;
    int distance;
    DIRECTION direction;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.distance > b.distance; // Min-heap (smallest distance has highest priority)
    }
};

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;
    std::vector<char> row;

    int j = 0;
    while (getline(file, line)) {
        if (line == "") {
            break;
        }

        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
            if (line[i] == 'S') {
                start.first = j;
                start.second = i;
            }
            if (line[i] == 'E') {
                end.first = j;
                end.second = i;
            }
        }
        map.push_back(row);
        row.clear();
        j++;
    }

    predsmap.resize(map.size(), std::vector<bool>(map.size(), false));
}

void printMap(std::vector<std::vector<char>> map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printStartPos() {
    std::cout << "Start at: (" << start.first << ", " << start.second << ")" << std::endl;
}

void printEndPos() {
    std::cout << "End at: (" << end.first << ", " << end.second << ")" << std::endl;
}

long findShortestPath(std::pair<int, int> pos, DIRECTION dir, std::vector<std::vector<bool>> &preds, long steps) {
    if (map[pos.first][pos.second] == '#' || steps > globmin) {
        return 999999;
    }

    if (map[pos.first][pos.second] == 'E') {
        globmin = steps;
        std::cout << globmin << std::endl;
        return 1;
    }

    long up = 1001;
    long down = 1001;
    long left = 1001;
    long right = 1001;

    if (dir == DIRECTION::UP) {
        up = 1;
    }else if (dir == DIRECTION::DOWN) {
        down = 1;
    }else if (dir == DIRECTION::LEFT) {
        left = 1;
    }else{
        right = 1;
    }

    long goUp = 999999;
    long goDown = 999999;
    long goLeft = 999999;
    long goRight = 999999;

    if (!preds[pos.first-1][pos.second] && steps + up < globmin) {
        auto locmap = preds;
        locmap[pos.first-1][pos.second] = true;
        //printPath(locmap);
        goUp = up + findShortestPath({ pos.first-1, pos.second }, DIRECTION::UP, locmap, steps+up);
    }

    if (!preds[pos.first+1][pos.second] && steps + down < globmin) {
        auto locmap = preds;
        locmap[pos.first+1][pos.second] = true;
        //printPath(locmap);
        goDown = down + findShortestPath({ pos.first+1, pos.second }, DIRECTION::DOWN, locmap, steps+down);
    }

    if (!preds[pos.first][pos.second-1] && steps + left < globmin) {
        auto locmap = preds;
        locmap[pos.first][pos.second-1] = true;
        //printPath(locmap);
        goLeft = left + findShortestPath({ pos.first, pos.second-1 }, DIRECTION::LEFT, locmap, steps+left);
    }

    if (!preds[pos.first][pos.second+1] && steps + right < globmin) {
        auto locmap = preds;
        locmap[pos.first][pos.second+1] = true;
        //printPath(locmap);
        goRight = right + findShortestPath({ pos.first, pos.second+1 }, DIRECTION::RIGHT, locmap, steps+right);
    }

    long min = std::min(goUp, std::min(goDown, std::min(goLeft, goRight)));

    return min;
}

int findMinDist(std::vector<int> distance, std::vector<bool> visited) {
    int min = INT_MAX;
    int minIndex = 0;

    for (int i = 0; i < distance.size(); i++) {
        if (visited[distance[i]] && distance[i] < min) {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

std::vector<std::vector<int>>  findShortestIterativPath() {
    std::priority_queue<
        Node, // Type of elements
        std::vector<Node>, // Container
        CompareNode // Min-Heap (smallest priority first)
    > queue;
    std::vector<std::vector<int>> distance(map.size(), std::vector<int>(map.size(), INT_MAX));

    queue.push({
        start.second, start.first, 0, DIRECTION::RIGHT
    });

    while (!queue.empty()) {
        Node node = queue.top();
        queue.pop();
        int currdistance = node.distance;

        if (map[node.y][node.x] == '#') {
            continue;
        }

        if (map[node.y][node.x] == 'E') {
            continue;
        }

        if (currdistance > distance[node.y][node.x]) {
            continue;
        }

        if (node.direction == DIRECTION::RIGHT) {
            if (node.distance + 1 < distance[node.y][node.x+1]) {
                distance[node.y][node.x+1] = currdistance + 1;
                queue.push({
                        node.x+1,
                        node.y,
                        node.distance + 1,
                        node.direction,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y+1][node.x]) {
                distance[node.y+1][node.x] = currdistance + 1001;
                queue.push({
                        node.x,
                        node.y+1,
                        node.distance + 1001,
                        DIRECTION::DOWN,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y-1][node.x]) {
                distance[node.y-1][node.x] = currdistance + 1001;
                queue.push(
                    {
                        node.x,
                        node.y-1,
                        node.distance + 1001,
                        DIRECTION::UP,
                    }
                );
            }
        }

        if (node.direction == DIRECTION::LEFT) {
            if (node.distance + 1 < distance[node.y][node.x-1]) {
                distance[node.y][node.x-1] = currdistance + 1;
                queue.push(
                    {
                        node.x-1,
                        node.y,
                        node.distance + 1,
                        node.direction,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y+1][node.x]) {
                distance[node.y+1][node.x] = currdistance + 1001;
                queue.push(
                    {
                        node.x,
                        node.y+1,
                        node.distance + 1001,
                        DIRECTION::DOWN,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y-1][node.x]) {
                distance[node.y-1][node.x] = currdistance + 1001;
                queue.push(
                    {
                        node.x,
                        node.y-1,
                        node.distance + 1001,
                        DIRECTION::UP,
                    }
                );
            }
        }

        if (node.direction == DIRECTION::UP) {
            if (node.distance + 1 < distance[node.y-1][node.x]) {
                distance[node.y-1][node.x] = currdistance + 1;
                queue.push(
                    {
                        node.x,
                        node.y-1,
                        node.distance + 1,
                        node.direction,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y][node.x-1]) {
                distance[node.y][node.x-1] = currdistance + 1001;
                queue.push(
                    {
                        node.x-1,
                        node.y,
                        node.distance + 1001,
                        DIRECTION::LEFT,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y][node.x+1]) {
                distance[node.y][node.x+1] = currdistance + 1001;
                queue.push(
                    {
                        node.x+1,
                        node.y,
                        node.distance + 1001,
                        DIRECTION::RIGHT,
                    }
                );
            }
        }

        if (node.direction == DIRECTION::DOWN) {
            if (node.distance + 1 < distance[node.y+1][node.x]) {
                distance[node.y+1][node.x] = currdistance + 1;
                queue.push(
                    {
                        node.x,
                        node.y+1,
                        node.distance + 1,
                        node.direction,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y][node.x-1]) {
                distance[node.y][node.x-1] = currdistance + 1001;
                queue.push(
                    {
                        node.x-1,
                        node.y,
                        node.distance + 1001,
                        DIRECTION::LEFT,
                    }
                );
            }

            if (node.distance + 1001 < distance[node.y][node.x+1]) {
                queue.push(
                    {
                        node.x+1,
                        node.y,
                        node.distance + 1001,
                        DIRECTION::RIGHT,
                    }
                );
            }
        }
    }

    return distance;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    printMap(map);
    printStartPos();
    printEndPos();
    std::vector<std::pair<int, int>> nodes;
    auto mindist = findShortestIterativPath();

    std::cout << "SP with sum: " << mindist[end.first][end.second]  << std::endl;

    return 0;
}