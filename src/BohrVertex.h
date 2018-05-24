#ifndef BOHR_VERTEX_H
#define BOHR_VERTEX_H

#include <map>

struct BohrVertex {

    BohrVertex(const char& sym, const int& parentLink = -1);

    // Номер вершины, в которую мы попадём по символу
    std::map<char, int> nextVertices;

    // Запоминание перехода автомата
    std::map<char, int> moves;

    // Номер строки-образца
    int patternNum;

    int suffixLink;

    int correctSuffixLink;

    // Родительская вершина в дереве
    int parentLink;

    bool isEndOfPattern;

    // Символ на ребре
    char sym;

};

#endif
