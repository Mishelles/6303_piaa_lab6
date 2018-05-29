#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>

struct Node {

    Node(const char& sym, const int& parentLink = -1);

    std::map<char, int> nextNodes;
    std::map<char, int> moves;

    std::vector<int> patternNum;

    bool isEndOfPattern;
    char sym;
    int parentLink;
    int suffixLink;
    int correctSuffixLink;
};

#endif
