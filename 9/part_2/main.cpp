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

#define FILENAME "example.txt"

struct FileData {
    int id;
    int length;
};

std::vector<int> drive;
std::vector<FileData> decoded;
std::vector<FileData> compressed;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::vector<int> linemap;
        std::stringstream linestream(line);
        std::string word;

        for ( char c : line ) {
            linemap.push_back((int) c - '0');
        }

        drive = linemap;
    }
}

void print() {
    for(auto c : drive) {
        std::cout << c;
    }
    std::cout << std::endl;
}

void decode() {
    int id=0;
    for (int i = 0; i < drive.size(); i++) {
        if (i % 2 == 0) {
            decoded.push_back({ id, drive[i] });
        }else {
            decoded.push_back({ -1, drive[i] });
        }

        if (i % 2 == 0) {
            id++;
        }
    }

    return;
}

void printDecoded() {
    for(auto f : decoded) {
        if (f.id != -1) {
            for (int i = 0; i < f.length; i++) {
                std::cout << f.id;
            }
        }else {
            for (int i = 0; i < f.length; i++) {
                std::cout << ".";
            }
        }
    }
    std::cout << std::endl;
}

void printCompressed() {
    for(auto f : compressed) {
        if (f.id != -1) {
            for (int i = 0; i < f.length; i++) {
                std::cout << f.id;
            }
        }else {
            for (int i = 0; i < f.length; i++) {
                std::cout << ".";
            }
        }
    }
    std::cout << std::endl;
}

int filefits(int size, int index) {
    return decoded[index].length >= size;
}

int findNextFittingFile(int idcounter, int size) {
    for (int i = 0; i < idcounter; i++) {
        if (decoded[i].id == -1 && filefits(size, i)) {
            return i;
        }
    }

    return -1;
}



void compress() {
    int idCounter = 0;
    for (int i = decoded.size() - 1; i > 0; i--) {
        if (decoded[i].id != -1) {
            int j = findNextFittingFile(i, decoded[i].length);
            decoded[j].length -= decoded[i].length;
            decoded.insert(decoded.begin() + j, { decoded[i].id, decoded[i].length });
        }
        printDecoded();
    }
}

long long checksum() {
    long long sum = 0;
    int id=0;

    for (int i = 0; i < compressed.size(); i++) {
        for (int k = 0; k < compressed[i].length; k++) {
            auto c = compressed[i];
            sum += compressed[i].id * id;

            id++;
        }
    }

    return sum;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    std::cout << "Decoding" << std::endl;
    decode();

    std::cout << "Compressing" << std::endl;
    compress();


    std::cout << "Calculating checksum" << std::endl;
    long long chs = checksum();
    std::cout << "Result: " << chs << std::endl;

    return 0;
}