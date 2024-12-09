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

void compress() {
    for (int i = 0; i < decoded.size(); i++) {
        if (decoded[i].id == -1) {
            int blockcounter = 0;

            while (decoded[i].length > 0) {
                int k = decoded[i].length;

                int j = decoded.size() - 1;
                int found = -1;

                while (j > i && found == -1) {
                    //std::cout << "[" << decoded[j] << "] -> " << i  << std::endl;
                    if (decoded[j].id != -1) {
                        found = j;
                    }else{
                        j--;
                    }

                }
                auto d = decoded[i];
                auto e = decoded[found];
                if (found != -1) {
                    if (decoded[found].length <= decoded[i].length - k) {
                        compressed.push_back(decoded[found]);
                        k = k + decoded[found].length - 1;
                        decoded.erase(decoded.begin() + found);
                        blockcounter = k;
                    }else {
                        int used = k;
                        if (k < decoded[found].length) {
                            compressed.push_back({ decoded[found].id, k });
                            blockcounter = k;
                            decoded[i].length -= k;
                        }else {
                            compressed.push_back({ decoded[found].id, decoded[found].length });
                            blockcounter += decoded[found].length ;
                            decoded[i].length -= decoded[found].length;
                        }

                        decoded[found].length -= used;
                        if (decoded[found].length <= 0) {
                            decoded.erase(decoded.begin() + found);
                        }
                    }

                }
            }
        }else {
            compressed.push_back(decoded[i]);
        }

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
}

long long checksum() {
    long long sum = 0;
    int id=0;

    for (int i = 0; i < compressed.size(); i++) {
        for (int k = 0; k <= compressed[i].length; k++) {
            sum += compressed[i].id * id;

            id++;
        }
    }

    return sum;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    std::cout << "Length: " << drive.size() << std::endl;
    //calculate();
    print();
    std::cout << "Decoding" << std::endl;
    decode();
    std::cout << "Length: " << decoded.size() << std::endl;


    /*for(auto f : decoded) {
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
    std::cout << std::endl;*/

    std::cout << "Compressing" << std::endl;
    compress();
    std::cout << "Length: " << compressed.size() << std::endl;


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

    std::cout << "Calculating checksum" << std::endl;
    long long chs = checksum();
    std::cout << chs << std::endl;

    return 0;
}