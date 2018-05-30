#ifndef NODE_H
#define NODE_H

#include <map>

struct Node {

    Node(const wchar_t& sym, const int& parentLink = -1);

    std::map<wchar_t, int> nextNodes;
    std::map<wchar_t, int> moves;
    int patternNum;
    int suffixLink;
    int correctSuffixLink;
    int parentLink;
    bool isEndOfPattern;
    wchar_t sym;

};

#endif
