#include "Bohr.h"

class AhoCorasick {

public:
       AhoCorasick();
      ~AhoCorasick();

      void init(const std::wstring&, const std::vector<std::wstring>&, const unsigned int&);
      std::vector<result> solve();
      void reset();
      static bool _sortComparator(const result&, const result&);

private:

      std::wstring _text;
      std::vector<std::wstring> _patterns;

      Bohr* _bohr;

};
