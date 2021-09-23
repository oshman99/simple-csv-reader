#include <csvMapClass.h>

void CsvMap::readFile(std::ifstream& file)
{
    /*проходя по файлу, эта функция записывает данные в двумерную map*/

    std::string line, row_cell, cell;
    std::getline(file, line);

    if(line.find_first_of(".|;:@#$%^&*()_")!=std::string::npos)
    {
        std::cerr << "FORIGN CHARACTERS FOUND IN:" << line << std::endl;
        exit(-3);
    }
    
    std::stringstream ss(line);
    //пропуск первой ячейки(пустая)
    std::getline(ss, cell, ',');
    //заполняем внешнюю map номерами столбцов
    while(std::getline(ss, cell, ','))
        table[cell];

    //заполняем внутреннюю map номерами строк и ячейками
    while(getline(file, line))
    {
        std::stringstream ss(line);
        //первое значение до запятой - номер строки
        std::getline(ss, row_cell, ',');

        if(row_cell.find_first_of("0123456789") == std::string::npos)
        {
            std::cerr << "CLMN NUMBER CONTAINS NO DIGITS, SHOULD BE INTEGER:" << row_cell << std::endl;
            exit(-3);
        }

        /*NOTE::
        Альтернативы:
         for(iterator iter = table.begin(), itr!=table.end(), itr++);

         iterator iter = table.begin();
         while(iter != table.end())
            iter++;


        Типы итераторов по map:
        Для доступа к внешней map:    std::map<std::string, std::map<std::string, std::string> >::iterator;
        Для доступа к внутренней map: std::map<std::string, std::string>::iterator;
        for-range loop, который написан ниже гораздо легче читается и будет хорошим решением в C++17.
        Но такое решение подходит не всегда, в выводе таблицы было гораздо проще использовать while-loop
        */
        //для каждого столбца во внешней map...
        for (auto& [key ,value]: table)
        {
            //считываем ячейки
            std::getline(ss, cell, ',');
            value[row_cell] = cell;
        }
    }
}


void CsvMap::printTable(int depth)
{
    //пустая ячейка
    std::cout << ',';

    //итератор-указатель на последний столбец
    auto end_row = --table.cend();
    for(const auto& [key, value]: table)
    {
        //если это последний элемент в строке - вывести переход на другую строку вместо запятой 
        if(key == end_row->first)
        {
            std::cout << key << std::endl;
            break;
        }
        std::cout << key << ',';
    }

    //итератор по строкам
    auto clmn_itr = table.begin()->second.begin();

    while(clmn_itr!=table.begin()->second.end())
    {
        std::cout << clmn_itr->first << ',';
        //итератор по столбцам
        auto row_ptr = table.begin();

            while(row_ptr != table.end())
            {
                std::cout <<  calcCell(table[row_ptr->first][clmn_itr->first], depth);
                //в конце строки запятая не нужна
                if(row_ptr != end_row)
                    std::cout << ',';
                row_ptr++;
            }

        std::cout << std::endl;
        clmn_itr++;
    }
}

//функция решает выражение в клетке если есть '=', иначе возвращает значение в клетке
int CsvMap::calcCell(std::string cell, int depth)
{
    int first_val, second_val;

    if(!depth)
    {
        std::cerr << "REACHED MAX CELL REFERENCE DEPTH" << std::endl;
        exit(-2);
    }

    if(cell.find_first_of('=') == 0)
    {
        std::size_t cell_operator = cell.find_first_of("+-*/");
        if(cell_operator != std::string::npos)
        {
            first_val  = findCell(cell.substr(1, cell_operator-1), depth);
            second_val = findCell(cell.substr(cell_operator + 1,cell.length()), depth);
            depth--;
        }
        
        switch(cell[cell_operator])
        {
            case '+':
                return first_val + second_val;
            case '-':
                return first_val - second_val;
            case '*':
                return first_val * second_val;
            case '/':
            {

                if(second_val == 0)
                {
                    std::cerr << "DIVISION BY ZERO: CELL" << cell << std::endl;
                    exit(-2);
                }

                return first_val / second_val;  
            }

            default:
            {
                std::cerr << "INVALID ARITHMETICS OPERATOR: CELL " << cell << std::endl;
                exit(-1);
            }

        }
    }

    else if(cell.find_first_of('=') != std::string::npos)
    {
        std::cerr << "INVALID '=' USAGE CELL " << cell << std::endl;
        exit(-1);
    }

    //условие выхода из рекурсии - клетка просто содержит значение
    else
        return std::stoi(cell);
}

//распознать номер ячейки и вызвать calcCell
int CsvMap::findCell(std::string cell_link, int depth)
{
    //тк известен формат ссылок:столбец-строка, и строки всегда целые числа, то ищем первую цифру
    std::size_t found = cell_link.find_first_of("0123456789");

    if(found == std::string::npos)
    {
        std::cerr << "INVALID CELL LINK, NO CLMN NUMBER: CELL " << cell_link << std::endl;
        exit(-1);
    }
    else if(found == 0)
    {
        std::cerr << "INVALID CELL LINK, CLMN NUMBER SHOULD GO AFTER ROW: CELL " << cell_link << std::endl;
        exit(-1);
    }

    std::string row = cell_link.substr(0, found);
    std::string clmn = cell_link.substr(found, cell_link.length());
    if(table.find(row) != table.cend())
        if(table[row].find(clmn) != table[row].cend())
            return calcCell(table[row][clmn], depth);

    else
    {
        std::cerr << "INVALID CELL LINK, NO SUCH CELL EXISTS: CELL " << cell_link << std::endl;
        exit(-1);
        
    }

    //что бы не ругался
    return -1;
}