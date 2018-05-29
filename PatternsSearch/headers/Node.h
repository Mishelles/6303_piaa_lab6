#ifndef NODE_H
#define NODE_H

#include <map>

struct Node {

    Node(const char& sym, const int& parentLink = -1);

    std::map<char, int> nextNodes;
    std::map<char, int> moves;
    int patternNum;
    int suffixLink;
    int correctSuffixLink;
    int parentLink;
    bool isEndOfPattern;
    char sym;

};

#endif
