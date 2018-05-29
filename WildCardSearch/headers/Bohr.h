#ifndef BOHR_H
#define BOHR_H

#include "Node.h"

typedef std::pair<int, int> result;

struct Bohr {

      Bohr(const int& size);

      void addString(const std::string& pattern, const int& numOfPattern);
      int getAutoMove(const int& vertexNum, const char& sym);
      int getSuffixLink(const int& vertexNum);
      int getCorrectSuffixLink(const int& vertexNum);

      void check(const int& vertexNum, const int& curPos, std::vector<result>& results);
      void checkJoker(const int& vertexNum, const int& curPos, const unsigned int& jokerLen);

      std::vector<unsigned int> parseJoker(const std::string& jokerPattern, const char& joker);

      std::vector<int> searchJocker(const std::string& text, const std::string& joker, const char& jokerSym);
      std::vector<result> search(const std::string& text);

      // Данные

      std::vector<Node> bohr;
      std::vector<int> results;
      std::vector<int> back;
      std::vector<unsigned int> len;
      std::vector<std::string> patterns;
};

#endif
