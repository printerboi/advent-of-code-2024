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


std::vector<std::pair<int, int>> directions = {UP, DOWN, LEFT, RIGHT};

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

std::vector<std::vector<std::vector<long>>> findShortestIterativPath() {
    std::priority_queue<
        Node, // Type of elements
        std::vector<Node>, // Container
        CompareNode // Min-Heap (smallest priority first)
    > queue;
    std::vector<std::vector<std::vector<long>>> distance(map.size(), std::vector<std::vector<long>>(map.size(), std::vector<long>(directions.size(), LONG_MAX)));
    distance[start.first][start.second] = {0, {} };

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

        std::cout << "Node: (" << node.x << ", " << node.y << ") Distance: " << currdistance << "\n";

        for (int i = 0; i < directions.size(); i++) {
            Node newNode = {
                node.x + directions[i].second,
                node.y + directions[i].first,
                node.steps + 1,
                node.distance + 1,
                directions[i],
            };

            if (node.orientation != directions[i]) {
                newNode.distance += 1000;
            }

            if (map[newNode.y][newNode.x] == '#') {
                continue;
            }

            if (newNode.distance < distance[newNode.y][newNode.x][i]) {
                distance[newNode.y][newNode.x][i] = newNode.distance;
                queue.push(newNode);
            }
        }

    }

    return distance;
}

long tracePaths(std::vector<std::vector<std::vector<long>>> distance) {
    std::vector<std::vector<char>> traces(map.size(), std::vector<char>(map.size(), '.'));
    long count = 0;

    std::priority_queue<
        Node, // Type of elements
        std::vector<Node>, // Container
        CompareNode // Min-Heap (smallest priority first)
    > queue;

    auto minval = std::min_element(distance[start.first][start.second].begin(), distance[start.first][start.second].end());
    long minIndex = std::distance(distance[start.first][start.second].begin(),  minval);

    queue.push({
        end.second, end.first, 0, distance[end.first][end.second][minIndex], directions[minIndex]
    });

    while (!queue.empty()) {
        Node node = queue.top();
        queue.pop();

        long currdistance = node.distance;
        long currsteps = node.steps;

        if (map[node.y][node.x] == '#') {
            continue;
        }

        if (map[node.y][node.x] == 'S') {
            continue;
        }

        std::cout << "Node: (" << node.x << ", " << node.y << ") Distance: " << currdistance << " Dir: " << node.orientation.first << ", " << node.orientation.second << "\n";

        for (int i = 0; i < directions.size(); i++) {
            long dist = node.distance - 1;

            if (node.orientation != directions[i]) {
                dist -= 1000;
            }

            Node newNode = {
                node.x + node.orientation.second * -1,
                node.y + node.orientation.first * -1,
                node.steps + 1,
                dist,
                directions[i]
            };

            if (map[newNode.y][newNode.x] == '#') {
                continue;
            }

            long minDist = distance[newNode.y][newNode.x][i];

            if (newNode.distance == minDist) {
                distance[newNode.y][newNode.x][i] = newNode.distance;
                traces[newNode.y][newNode.x] = 'O';
                queue.push(newNode);
            }
        }
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

    std::cout << "SP with sum: " << paths + 1  << std::endl;

    return 0;
}