#include "../headers/BohrTree.h"

BohrTree::BohrTree(const int& size) {
    bohrTree.push_back(BohrVertex(-1));
    back = std::vector<int>(size, 0);
}

void BohrTree::addString(const std::string& pattern, const int& numOfPattern) {
    int vertexNum = 0;

    for (unsigned int i = 0; i < pattern.size(); i++) {

        if (bohrTree[vertexNum].nextVertices.find(pattern[i]) == bohrTree[vertexNum].nextVertices.end()) {
            bohrTree.push_back(BohrVertex(pattern[i], vertexNum));
            bohrTree[vertexNum].nextVertices[pattern[i]] = bohrTree.size() - 1;
        }

        vertexNum = bohrTree[vertexNum].nextVertices[pattern[i]];
    }

    bohrTree[vertexNum].patternNum.push_back(numOfPattern);
    bohrTree[vertexNum].isEndOfPattern = true;
}

int BohrTree::getAutoMove(const int& vertexNum, const char& sym) {

    if (bohrTree[vertexNum].moves.find(sym) == bohrTree[vertexNum].moves.end()) {
  		  if (bohrTree[vertexNum].nextVertices.find(sym) != bohrTree[vertexNum].nextVertices.end()) {
            bohrTree[vertexNum].moves[sym] = bohrTree[vertexNum].nextVertices[sym];
  		  } else {
  			     if (!vertexNum) {
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
            bohrTree[vertexNum].suffixLink = getAutoMove(getSuffixLink(bohrTree[vertexNum].parentLink), bohrTree[vertexNum].sym);
        }
  	}

  	return bohrTree[vertexNum].suffixLink;
}

int BohrTree::getCorrectSuffixLink(const int& vertexNum) {
    if (bohrTree[vertexNum].correctSuffixLink == -1) {
		    int temp = getSuffixLink(vertexNum);
		    if (temp == 0) {
            bohrTree[vertexNum].correctSuffixLink = 0;
        } else {
			       if (bohrTree[temp].isEndOfPattern == true) {
                bohrTree[vertexNum].correctSuffixLink = temp;
             } else {
                bohrTree[vertexNum].correctSuffixLink = getCorrectSuffixLink(temp);
             }
		    }
	  }

	  return bohrTree[vertexNum].correctSuffixLink;
}

void BohrTree::check(const int& vertexNum, const int& curPos, std::vector<result>& results) {
    for (int next = vertexNum; next != 0; next = getCorrectSuffixLink(next)) {
  	     if (bohrTree[next].isEndOfPattern) {
            results.push_back({ curPos - (int)patterns[bohrTree[next].patternNum.back()].size() + 1,
                                bohrTree[next].patternNum.back() + 1 });
         }
  	}
}

void BohrTree::checkJoker(const int& vertexNum, const int& curPos, const unsigned int& jokerLen) {
    for (int next = vertexNum; next != 0; next = getCorrectSuffixLink(next)) {
  	     if (bohrTree[next].isEndOfPattern) {
  			      for (unsigned int m = 0; m < bohrTree[next].patternNum.size(); m++) {
  				        if ((curPos - (int)len[bohrTree[next].patternNum[m]]) >= 0) {
  	                  if ((++back[curPos - len[bohrTree[next].patternNum[m]]]) == (int)len.size()) {
  						            if (back.size() - (curPos - len[bohrTree[next].patternNum[m]]) >= jokerLen) {
  							              results.push_back(curPos - len[bohrTree[next].patternNum[m]] + 1);
                          }
  					          }
                  }
  			      }
  		   }
  	}
}

std::vector<unsigned int> BohrTree::parseJoker(const std::string& jokerPattern, const char& joker) {
    std::vector <unsigned int> len;
  	std::string temp;

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

std::vector<result> BohrTree::search(const std::string& text) {
    for (size_t i = 0; i<patterns.size(); i++) {
        addString(patterns[i], i);
    }

  	std::vector <result> results;

  	int vertexNum = 0;

  	for (unsigned int i = 0; i < text.size(); i++) {
  		  vertexNum = getAutoMove(vertexNum, text[i]);
  		  check(vertexNum, i + 1, results);
  	}

  	return results;
}

std::vector<int> BohrTree::searchJocker(const std::string& text, const std::string& joker, const char& jokerSym) {
    len = parseJoker(joker, jokerSym);
  	int vertexNum = 0;

  	for (unsigned int i = 0; i < text.size(); i++) {
  		  vertexNum = getAutoMove(vertexNum, text[i]);
  		  checkJoker(vertexNum, i + 1, joker.size());
  	}

  	return results;
}
