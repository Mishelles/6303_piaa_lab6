#ifndef BOHR_H
#define BOHR_H

#include "Node.h"

typedef std::pair<int, int> result;

struct Bohr {

      Bohr(const int& size);

      void addString(const std::wstring& pattern, const int& numOfPattern);
      int getAutoMove(const int& vertexNum, const wchar_t& sym);
      int getSuffixLink(const int& vertexNum);
      int getCorrectSuffixLink(const int& vertexNum);

      void check(const int& vertexNum, const int& curPos, std::vector<result>& results);
      void checkJoker(const int& vertexNum, const int& curPos, const unsigned int& jokerLen);

      std::vector<unsigned int> parseJoker(const std::wstring& jokerPattern, const wchar_t& joker);

      std::vector<int> searchJocker(const std::wstring& text, const std::wstring& joker, const wchar_t& jokerSym);
      std::vector<result> search(const std::wstring& text);

      // Данные

      std::vector<Node> bohr;
      std::vector<int> results;
      std::vector<int> back;
      std::vector<unsigned int> len;
      std::vector<std::wstring> patterns;
};

#endif
