#ifndef CSVMAP_H
#define CSVMAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>

class CsvMap
{
    public:
        void readFile(std::ifstream& file);
        //максимальная "глубина" ссылок в ячейках
        void printTable(int depth);
        //двумерная map[string][string] = cell
        std::map<std::string, std::map<std::string, std::string>> table;
    private:
        //пара функций рекурсивно вызывающие друг друга
        int calcCell(std::string cell, int depth);
        int findCell(std::string cell, int depth);
};


#endif