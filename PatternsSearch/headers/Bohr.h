#ifndef BOHR_H
#define BOHR_H

#include "Node.h"
#include <vector>

typedef std::pair<int, int> result;

struct Bohr {

    Bohr();

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
    std::vector<Node> bohr;
};

#endif
