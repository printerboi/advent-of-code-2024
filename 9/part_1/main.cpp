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

#define FILENAME "input.txt"

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

void compress() {
    while (decoded.size() > 1) {
        //printDecoded();

        if (decoded[0].id != -1) {
            compressed.push_back(decoded[0]);
            decoded.erase(decoded.begin());
        } else {
            FileData nextToInsert = decoded[decoded.size() - 1];
            while (nextToInsert.id == -1) {
                decoded.pop_back();
                nextToInsert = decoded[decoded.size() - 1];
            }

            int howMuchToInsert = decoded[0].length;
            if (howMuchToInsert >= nextToInsert.length) {
                compressed.push_back(nextToInsert);
                decoded.erase(decoded.end() - 1);
                decoded[0].length -= nextToInsert.length;
            }else {
                compressed.push_back({nextToInsert.id, howMuchToInsert});
                decoded[decoded.size() - 1].length -= howMuchToInsert;
                decoded[0].length = 0;
            }

            if (decoded[0].length == 0) {
                decoded.erase(decoded.begin());
            }
        }

        //printCompressed();
    }

    if (decoded.size() == 1) {
        if (decoded[0].id != -1) {
            compressed.push_back(decoded[0]);
        }else {
            decoded.clear();
        }
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