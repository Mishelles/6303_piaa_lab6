#include "../headers/Bohr.h"

Bohr::Bohr(const int& size) {
    bohr.push_back(Node(-1));
    back = std::vector<int>(size, 0);
}

void Bohr::addString(const std::wstring& pattern, const int& numOfPattern) {
    int nodeNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {

        if (bohr[nodeNum].nextNodes.find(pattern[i]) == bohr[nodeNum].nextNodes.end()) {
            bohr.push_back(Node(pattern[i], nodeNum));
            bohr[nodeNum].nextNodes[pattern[i]] = bohr.size() - 1;
        }

        nodeNum = bohr[nodeNum].nextNodes[pattern[i]];
    }

    bohr[nodeNum].patternNum.push_back(numOfPattern);
    bohr[nodeNum].isEndOfPattern = true;
}

int Bohr::getAutoMove(const int& nodeNum, const wchar_t& sym) {

    if (bohr[nodeNum].moves.find(sym) == bohr[nodeNum].moves.end()) {
  		  if (bohr[nodeNum].nextNodes.find(sym) != bohr[nodeNum].nextNodes.end()) {
            bohr[nodeNum].moves[sym] = bohr[nodeNum].nextNodes[sym];
  		  } else {
  			     if (!nodeNum) {
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
            bohr[nodeNum].suffixLink = getAutoMove(getSuffixLink(bohr[nodeNum].parentLink), bohr[nodeNum].sym);
        }
  	}

  	return bohr[nodeNum].suffixLink;
}

int Bohr::getCorrectSuffixLink(const int& nodeNum) {
    if (bohr[nodeNum].correctSuffixLink == -1) {
		    int temp = getSuffixLink(nodeNum);
		    if (temp == 0) {
            bohr[nodeNum].correctSuffixLink = 0;
        } else {
			       if (bohr[temp].isEndOfPattern == true) {
                bohr[nodeNum].correctSuffixLink = temp;
             } else {
                bohr[nodeNum].correctSuffixLink = getCorrectSuffixLink(temp);
             }
		    }
	  }

	  return bohr[nodeNum].correctSuffixLink;
}

void Bohr::check(const int& nodeNum, const int& curPos, std::vector<result>& results) {
    for (int next = nodeNum; next != 0; next = getCorrectSuffixLink(next)) {
  	     if (bohr[next].isEndOfPattern) {
            results.push_back({ curPos - (int)patterns[bohr[next].patternNum.back()].size() + 1,
                                bohr[next].patternNum.back() + 1 });
         }
  	}
}

void Bohr::checkJoker(const int& nodeNum, const int& curPos, const unsigned int& jokerLen) {
    for (int next = nodeNum; next != 0; next = getCorrectSuffixLink(next)) {
  	     if (bohr[next].isEndOfPattern) {
  			      for (unsigned int m = 0; m < bohr[next].patternNum.size(); m++) {
  				        if ((curPos - (int)len[bohr[next].patternNum[m]]) >= 0) {
  	                  if ((++back[curPos - len[bohr[next].patternNum[m]]]) == (int)len.size()) {
  						            if (back.size() - (curPos - len[bohr[next].patternNum[m]]) >= jokerLen) {
  							              results.push_back(curPos - len[bohr[next].patternNum[m]] + 1);
                          }
  					          }
                  }
  			      }
  		   }
  	}
}

std::vector<unsigned int> Bohr::parseJoker(const std::wstring& jokerPattern, const wchar_t& joker) {
    std::vector <unsigned int> len;
  	std::wstring temp;

  	for (unsigned int i = 0; i < jokerPattern.size(); i++) {
  		  if (jokerPattern[i] == joker) {
  			    if (temp.size() > 0) {
  				      len.push_back(i);
  				      addString(temp, (int)(len.size() - 1));
  				      temp.clear();
  			    }
  			    continue;
  		  }
  		  else {
            temp.push_back(jokerPattern[i]);
        }

  		  if ((i == (jokerPattern.size() - 1)) && temp.size()) {
  	        len.push_back(i + 1);
  			    addString(temp, (int)(len.size() - 1));
  		  }
  	}

  	return len;
}

std::vector<result> Bohr::search(const std::wstring& text) {
    for (size_t i = 0; i<patterns.size(); i++) {
        addString(patterns[i], i);
    }

  	std::vector <result> results;

  	int nodeNum = 0;

  	for (unsigned int i = 0; i < text.size(); i++) {
  		  nodeNum = getAutoMove(nodeNum, text[i]);
  		  check(nodeNum, i + 1, results);
  	}

  	return results;
}

std::vector<int> Bohr::searchJocker(const std::wstring& text, const std::wstring& joker, const wchar_t& jokerSym) {
    len = parseJoker(joker, jokerSym);
  	int nodeNum = 0;

  	for (unsigned int i = 0; i < text.size(); i++) {
  		  nodeNum = getAutoMove(nodeNum, text[i]);
  		  checkJoker(nodeNum, i + 1, joker.size());
  	}

  	return results;
}
