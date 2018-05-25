#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

struct BohrVertex {

    BohrVertex(const char& sym, const int& parentLink = -1);

    // Номер вершины, в которую мы попадём по символу
    std::map<char, int> nextVertices;

    // Запоминание перехода автомата
    std::map<char, int> moves;

    // Номер строки-образца
    int patternNum;

    int suffixLink;

    int correctSuffixLink;

    // Родительская вершина в дереве
    int parentLink;

    bool isEndOfPattern;

    // Символ на ребре
    char sym;

};

typedef std::pair<int, int> result;

struct BohrTree {

    BohrTree();

    // Добавление строки в дерево
    void addString(const std::string&, const int&);

    // Получение перехода автомата
    int getAutoMove(const int&, const char&);

    // Получение суффиксальной ссылки
    int getSuffixLink(const int&);

    // Получение "хорошей" суффиксальной ссылки
    int getCorrectSuffixLink(const int&);

    // Проверка
    void check(const int&, const int&, const std::vector<std::string>&, std::vector<result>&);

    // Поиск
    std::vector<result> find(const std::string&, const std::vector<std::string>&);


    // Данные
    std::vector<BohrVertex> bohrTree;
};

class AhoCorasick {

public:
       AhoCorasick();
      ~AhoCorasick();

      void init(const std::string&, const std::vector<std::string>&, const unsigned int&);
      std::vector<result> solve();
      void reset();
      static bool _sortComparator(const result&, const result&);

private:

      std::string _text;
      std::vector<std::string> _patterns;

      BohrTree* _bohr;

};

int main() {

    std::string text;
    unsigned int numOfPatterns;

    std::cin >> text;
    std::cin >> numOfPatterns;
    std::vector<std::string> patterns(numOfPatterns);

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        std::cin >> patterns[i];
    }

    AhoCorasick ahoCor;

    ahoCor.init(text, patterns, numOfPatterns);
    std::vector<result> results = ahoCor.solve();

    for (auto result : results) {
        std::cout << result.first << " " << result.second << std::endl;
    }

    return 0;
}

BohrVertex::BohrVertex(const char& sym, const int& parentLink)
    : sym(sym)
    , parentLink(parentLink)
    , isEndOfPattern(false)
    , suffixLink(-1)
    , correctSuffixLink(-1)
{
    moves[sym] = -1;
    nextVertices[sym] = -1;
}

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

AhoCorasick::AhoCorasick() {
  _bohr = NULL;
}

AhoCorasick::~AhoCorasick() {
  reset();
}

void AhoCorasick::init(const std::string& text, const std::vector<std::string>& patterns, const unsigned int& numOfPatterns) {
    _text = text;
    _patterns = patterns;

    _bohr = new BohrTree;

    for (unsigned int i = 0; i < numOfPatterns; i++) {
        _bohr->addString(_patterns[i], i);
    }
}

std::vector<result> AhoCorasick::solve() {
    std::vector<result> res;

    if (!_bohr) return res;

    res = _bohr->find(_text, _patterns);
    std::sort(res.begin(), res.end(), _sortComparator);

    return res;
}

void AhoCorasick::reset() {
    if (_bohr) delete _bohr;
    _patterns.clear();
    _text.clear();
}

bool AhoCorasick::_sortComparator(const result& a, const result& b) {
    return (a.first == b.first) ? (a.second < b.second) : (a.first < b.first);
}
