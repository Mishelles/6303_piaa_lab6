#ifndef BOHR_VERTEX_H
#define BOHR_VERTEX_H

#include <map>
#include <vector>

struct BohrVertex {

    BohrVertex(const char& sym, const int& parentLink = -1);

    std::map<char, int> nextVertices;
    std::map<char, int> moves;

    std::vector<int> patternNum;

    bool isEndOfPattern;
    char sym;
    int parentLink;
    int suffixLink;
    int correctSuffixLink;
};

#endif
