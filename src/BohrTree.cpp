#include "BohrTree.h"


BohrTree::BohrTree() {
    bohrTree.push_back(BohrVertex('#'));
}

void BohrTree::addString(const std::string& pattern, const int& numOfPatterns) {

    int vertexNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {
        char sym = pattern[i];

        if ((bohrTree[vertexNum].nextVertices.find(sym) == bohrTree[vertexNum].nextVertices.end())
            || (bohrTree[vertexNum].nextVertices[sym] == -1)) {

              bohrTree.push_back(BohrVertex(sym, vertexNum));
              bohrTree[vertexNum].nextVertices[sym] = bohrTree.size() - 1;
        }

        vertexNum = bohrTree[vertexNum].nextVertices[sym];
    }

    bohrTree[vertexNum].patternNum = numOfPatterns;
    bohrTree[vertexNum].isEndOfPattern = true;

}

int BohrTree::getAutoMove(const int& vertexNum, const char& sym) {

    if (bohrTree[vertexNum].moves.find(sym) == bohrTree[vertexNum].moves.end()
        || bohrTree[vertexNum].moves[sym] == -1) {
  	     if (bohrTree[vertexNum].nextVertices.find(sym) != bohrTree[vertexNum].nextVertices.end()
              && bohrTree[vertexNum].nextVertices[sym] != -1) {
                  bohrTree[vertexNum].moves[sym] = bohrTree[vertexNum].nextVertices[sym];
        } else {
  			     if (vertexNum == 0) {
                bohrTree[vertexNum].moves[sym] = 0;
             } else {
                bohrTree[vertexNum].moves[sym] = getAutoMove(getSuffixLink(vertexNum), sym);
             }
  		}
  	}

  return bohrTree[vertexNum].moves[sym];
}

int BohrTree::getSuffixLink(const int& vertexNum) {

    if (bohrTree[vertexNum].suffixLink == -1) {
        if (!vertexNum || !bohrTree[vertexNum].parentLink) {
            bohrTree[vertexNum].suffixLink = 0;
        } else {
          bohrTree[vertexNum].suffixLink = getAutoMove(getSuffixLink(
              bohrTree[vertexNum].parentLink), bohrTree[vertexNum].sym);
        }
    }

    return bohrTree[vertexNum].suffixLink;
}

int BohrTree::getCorrectSuffixLink(const int& vertexNum) {

    if (bohrTree[vertexNum].correctSuffixLink == -1) {
        int temp = getSuffixLink(vertexNum);

        if (!temp) {
            bohrTree[vertexNum].correctSuffixLink = 0;
        } else {
            if (bohrTree[temp].isEndOfPattern) {
                bohrTree[vertexNum].correctSuffixLink = temp;
            } else {
                bohrTree[vertexNum].correctSuffixLink = getCorrectSuffixLink(temp);
            }
        }
    }

    return bohrTree[vertexNum].correctSuffixLink;
}

void BohrTree::check(const int& vertexNum, const int& i
          ,  const std::vector<std::string>& patterns
          ,  std::vector<result> &results) {

    for (int next = vertexNum; next; next = getCorrectSuffixLink(next)) {
        if (bohrTree[next].isEndOfPattern) {
            result temp(i - patterns[bohrTree[next].patternNum].size() + 1,
                            bohrTree[next].patternNum + 1);
            results.push_back(temp);
        }
    }
}

std::vector<result> BohrTree::find(const std::string& text, const std::vector<std::string>& patterns) {

    std::vector<result> res;

    int vertexNum = 0;
    for(unsigned i = 0; i < text.size(); i++) {
        vertexNum = getAutoMove(vertexNum, text[i]);
        check(vertexNum, i + 1, patterns, res);
    }

    return res;
}
