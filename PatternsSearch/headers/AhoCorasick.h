#include "Bohr.h"

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

      Bohr* _bohr;

};
