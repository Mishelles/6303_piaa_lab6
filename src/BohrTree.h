#ifndef BOHR_TREE_H
#define BOHR_TREE_H

#include "BohrVertex.h"
#include <vector>

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

#endif
