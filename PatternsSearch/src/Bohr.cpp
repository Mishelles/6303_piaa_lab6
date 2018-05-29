#include "../headers/Bohr.h"


Bohr::Bohr() {
    bohr.push_back(Node('#'));
}

void Bohr::addString(const std::string& pattern, const int& numOfPatterns) {

    int nodeNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {
        char sym = pattern[i];

        if ((bohr[nodeNum].nextNodes.find(sym) == bohr[nodeNum].nextNodes.end())
            || (bohr[nodeNum].nextNodes[sym] == -1)) {

              bohr.push_back(Node(sym, nodeNum));
              bohr[nodeNum].nextNodes[sym] = bohr.size() - 1;
        }

        nodeNum = bohr[nodeNum].nextNodes[sym];
    }

    bohr[nodeNum].patternNum = numOfPatterns;
    bohr[nodeNum].isEndOfPattern = true;

}

int Bohr::getAutoMove(const int& nodeNum, const char& sym) {

    if (bohr[nodeNum].moves.find(sym) == bohr[nodeNum].moves.end()
        || bohr[nodeNum].moves[sym] == -1) {
  	     if (bohr[nodeNum].nextNodes.find(sym) != bohr[nodeNum].nextNodes.end()
              && bohr[nodeNum].nextNodes[sym] != -1) {
                  bohr[nodeNum].moves[sym] = bohr[nodeNum].nextNodes[sym];
        } else {
  			     if (nodeNum == 0) {
                bohr[nodeNum].moves[sym] = 0;
             } else {
                bohr[nodeNum].moves[sym] = getAutoMove(getSuffixLink(nodeNum), sym);
             }
  		}
  	}

  return bohr[nodeNum].moves[sym];
}

int Bohr::getSuffixLink(const int& nodeNum) {

    if (bohr[nodeNum].suffixLink == -1) {
        if (!nodeNum || !bohr[nodeNum].parentLink) {
            bohr[nodeNum].suffixLink = 0;
        } else {
          bohr[nodeNum].suffixLink = getAutoMove(getSuffixLink(
              bohr[nodeNum].parentLink), bohr[nodeNum].sym);
        }
    }

    return bohr[nodeNum].suffixLink;
}

int Bohr::getCorrectSuffixLink(const int& nodeNum) {

    if (bohr[nodeNum].correctSuffixLink == -1) {
        int temp = getSuffixLink(nodeNum);

        if (!temp) {
            bohr[nodeNum].correctSuffixLink = 0;
        } else {
            if (bohr[temp].isEndOfPattern) {
                bohr[nodeNum].correctSuffixLink = temp;
            } else {
                bohr[nodeNum].correctSuffixLink = getCorrectSuffixLink(temp);
            }
        }
    }

    return bohr[nodeNum].correctSuffixLink;
}

void Bohr::check(const int& nodeNum, const int& i
          ,  const std::vector<std::string>& patterns
          ,  std::vector<result> &results) {

    for (int next = nodeNum; next; next = getCorrectSuffixLink(next)) {
        if (bohr[next].isEndOfPattern) {
            result temp(i - patterns[bohr[next].patternNum].size() + 1,
                            bohr[next].patternNum + 1);
            results.push_back(temp);
        }
    }
}

std::vector<result> Bohr::find(const std::string& text, const std::vector<std::string>& patterns) {

    std::vector<result> res;

    int nodeNum = 0;
    for(unsigned i = 0; i < text.size(); i++) {
        nodeNum = getAutoMove(nodeNum, text[i]);
        check(nodeNum, i + 1, patterns, res);
    }

    return res;
}
