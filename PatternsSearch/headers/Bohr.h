#ifndef BOHR_H
#define BOHR_H

#include "Node.h"
#include <vector>

typedef std::pair<int, int> result;

struct Bohr {

    Bohr();

    // Добавление строки в дерево
    void addString(const std::wstring&, const int&);

    // Получение перехода автомата
    int getAutoMove(const int&, const wchar_t&);

    // Получение суффиксальной ссылки
    int getSuffixLink(const int&);

    // Получение "хорошей" суффиксальной ссылки
    int getCorrectSuffixLink(const int&);

    // Проверка
    void check(const int&, const int&, const std::vector<std::wstring>&, std::vector<result>&);

    // Поиск
    std::vector<result> find(const std::wstring&, const std::vector<std::wstring>&);


    // Данные
    std::vector<Node> bohr;
};

#endif
