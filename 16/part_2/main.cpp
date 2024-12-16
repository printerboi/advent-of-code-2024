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
std::pair<int, int> start;
std::pair<int, int> end;

const std::pair<int, int> UP = {-1, 0};
const std::pair<int, int> DOWN = {1, 0};
const std::pair<int, int> LEFT = {0, -1};
const std::pair<int, int> RIGHT = {0, 1};


struct Node {
    int x;
    int y;
    long steps;
    long distance;
    std::pair<int, int> orientation;
};

struct CompareNode {
    bool operator()(const Node& a, const Node& b) const {
        return a.steps > b.steps;
    }
};

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;
    std::vector<char> row;

    int j = 0;
    while (getline(file, line)) {
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

void enqNode(int y, int x, std::pair<int, int> orientation, long stepsUpdate, long distanceUpdate, std::priority_queue<Node, std::vector<Node>, CompareNode> &queue) {
    queue.push({
        x,
        y,
        stepsUpdate,
        distanceUpdate,
        orientation,
        }
    );
}

std::pair<int, int> r90(std::pair<int, int> v) {
    if (v.first == 1 && v.second == 0) {
        return { 0, -1 };
    }

    if (v.first == 0 && v.second == -1) {
         return { -1, 0 };
    }

    if (v.first == -1 && v.second == 0) {
         return { 0, 1 };
    }

    if (v.first == 0 && v.second == 1) {
         return { 1, 0 };
    }
}
std::pair<int, int> r180(std::pair<int, int> v) {
    return r90(r90(v));
}

std::pair<int, int> r90c(std::pair<int, int> v) {
    if (v.first == 1 && v.second == 0) {
         return { 0, 1 };
    }

    if (v.first == 0 && v.second == 1) {
         return { -1, 0 };
    }

    if (v.first == -1 && v.second == 0) {
         return { 0, -1 };
    }

    if (v.first == 0 && v.second == -1) {
         return { 1, 0 };
    }
}


std::vector<std::vector<std::pair<long, std::pair<int, int>>>> findShortestIterativPath() {
    std::priority_queue<
        Node, // Type of elements
        std::vector<Node>, // Container
        CompareNode // Min-Heap (smallest priority first)
    > queue;
    std::vector<std::vector<std::pair<long, std::pair<int, int>>>> distance(map.size(), std::vector<std::pair<long, std::pair<int, int>>>(map.size(), { LONG_MAX, { 0, 1 } }));
    distance[start.first][start.second] = {0, {0, 1} };

    queue.push({
        start.second, start.first, 0, 0, RIGHT
    });

    while (!queue.empty()) {
        Node node = queue.top();
        queue.pop();
        long currdistance = node.distance;
        long currsteps = node.steps;

        if (map[node.y][node.x] == '#') {
            continue;
        }

        if (map[node.y][node.x] == 'E') {
            continue;
        }

        //std::cout << "Node: (" << node.x << ", " << node.y << ") Distance: " << currdistance << "\n";

        if (currdistance + 1 < distance[node.y + node.orientation.first][node.x + node.orientation.second].first) {
            distance[node.y + node.orientation.first][node.x + node.orientation.second] = { currdistance + 1, node.orientation };
            enqNode(node.y + node.orientation.first, node.x + node.orientation.second, node.orientation, currsteps + 1, currdistance + 1,  queue);
        }

        auto ori90 = r90(node.orientation);
        if (currdistance + 1001 < distance[node.y + ori90.first][node.x + ori90.second].first) {
            distance[node.y + ori90.first][node.x + ori90.second] = { currdistance + 1001, ori90 };
            enqNode(node.y + ori90.first, node.x + ori90.second, ori90, currsteps + 1, currdistance + 1001, queue);
        }

        auto ori90c = r90c(node.orientation);
        if (currdistance + 1001 < distance[node.y + ori90c.first][node.x + ori90c.second].first) {
            distance[node.y + ori90c.first][node.x + ori90c.second] = { currdistance + 1001, ori90c };
            enqNode(node.y + ori90c.first, node.x + ori90c.second, ori90c, currsteps + 1, currdistance + 1001, queue);
        }
    }

    return distance;
}

long tracePaths(std::vector<std::vector<std::pair<long, std::pair<int, int>>>> distances) {
    std::vector<std::vector<char>> traces(map.size(), std::vector<char>(map.size(), '.'));
    long count = 0;

    std::priority_queue<
        Node, // Type of elements
        std::vector<Node>, // Container
        CompareNode // Min-Heap (smallest priority first)
    > queue;

    /*if (distances[end.first - 1][end.second].first < distances[end.first][end.second-1].first) {
        queue.push({
            end.second, end.first, 0, distances[end.first][end.second].first, DOWN
        });
    }else {
        queue.push({
            end.second, end.first, 0, distances[end.first][end.second].first, LEFT
        });
    }*/

    queue.push({
        end.second, end.first, 0, distances[end.first][end.second].first, DOWN
    });

    while (!queue.empty()) {
        Node node = queue.top();
        queue.pop();

        long currdistance = node.distance;
        long currsteps = node.steps;
        int i = 0;

        if (map[node.y][node.x] == '#') {
            continue;
        }

        if (map[node.y][node.x] == 'S') {
            continue;
        }

        std::cout << "Node: (" << node.x << ", " << node.y << ") Distance: " << currdistance << " Dir: " << node.orientation.first << ", " << node.orientation.second << "\n";

        if (currdistance - 1 == distances[node.y + node.orientation.first][node.x + node.orientation.second].first) {
            traces[node.y + node.orientation.first][node.x + node.orientation.second] = 'O';
            enqNode(node.y + node.orientation.first, node.x + node.orientation.second, node.orientation, currsteps + 1, currdistance - 1,  queue);
        }

        if ( currdistance - 1001 == distances[node.y + node.orientation.first][node.x + node.orientation.second].first) {
            auto ori90 = r90c(node.orientation);
            traces[node.y + node.orientation.first][node.x + node.orientation.second] = 'O';
            enqNode(node.y + node.orientation.first, node.x + node.orientation.second, ori90, currsteps + 1, currdistance - 1001, queue);
        }

        /*if ( currdistance + 999 == distances[node.y + r90(node.orientation).first][node.x + r90(node.orientation).second].first) {
            auto ori90 = r90(node.orientation);
            traces[node.y + r90(node.orientation).first][node.x + r90(node.orientation).second] = 'O';
            enqNode(node.y + r90(node.orientation).first, node.x + r90(node.orientation).second, ori90, currsteps + 1, currdistance + 999, queue);
        }*/

        if (currdistance - 1001 == distances[node.y + node.orientation.first][node.x + node.orientation.second].first) {
            auto ori90c = r90(node.orientation);
            traces[node.y + node.orientation.first][node.x + node.orientation.second] = 'O';
            enqNode(node.y + node.orientation.first, node.x + node.orientation.second, ori90c, currsteps + 1, currdistance - 1001, queue);
        }

        /*if ( currdistance + 999 == distances[node.y + r90c(node.orientation).first][node.x + r90c(node.orientation).second].first) {
            auto oric90 = r90c(node.orientation);
            traces[node.y + r90c(node.orientation).first][node.x + r90c(node.orientation).second] = 'O';
            enqNode(node.y + r90c(node.orientation).first, node.x + r90c(node.orientation).second, oric90, currsteps + 1, currdistance + 999, queue);
        }*/

        i++;
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map.size(); j++) {
            if (map[i][j] == '#') {
                std::cout << "#";
            }else if (traces[i][j] == 'O') {
                count++;
                std::cout << traces[i][j];
            }else {
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }

    return count;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    printMap(map);
    printStartPos();
    printEndPos();
    auto mindist = findShortestIterativPath();
    auto paths = tracePaths(mindist);

    std::cout << "SP with sum: " << paths+1  << std::endl;

    return 0;
}