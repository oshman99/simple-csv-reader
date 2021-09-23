#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include <csvMapClass.h>

bool init(int argc, char *argv[], std::ifstream& file);
void print_file(std::istream& file);

int main(int argc, char *argv[])
{
    std::ifstream in_file; 

    if(!init(argc, argv, in_file)){
        std::cerr << "Failed to init \n";
        return -1;
    }
    CsvMap table;
    table.readFile(in_file);
    table.printTable(5);
    return 0;
}



bool init(const int argc, char *argv[], std::ifstream& file)
{
    //input arguments management
    if (argc == 1){
        std::cerr << "No parameter given \n \n";
        return false;
    }

    else if (argc == 2){
        std::cerr << argv[1] << ": \n \n";
        file.open(argv[1]);
    }

    else{
        std::cerr << "Only 1 parameter needed, using first one \n \n";
        file.open(argv[1]);
    }

    if(!file){
        std::cerr << "Failed to open file! \n \n";
        return false;
    }
    return true;
}
