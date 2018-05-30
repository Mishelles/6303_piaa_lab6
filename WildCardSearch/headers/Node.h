#ifndef NODE_H
#define NODE_H

#include <map>
#include <vector>

struct Node {

    Node(const wchar_t& sym, const int& parentLink = -1);

    std::map<wchar_t, int> nextNodes;
    std::map<wchar_t, int> moves;

    std::vector<int> patternNum;

    bool isEndOfPattern;
    wchar_t sym;
    int parentLink;
    int suffixLink;
    int correctSuffixLink;
};

#endif
