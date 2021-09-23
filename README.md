# simple-csv-reader
Comma separated value file reader, that can do so simple cell arithmetics.

Example of how input file should be structured:

>*//First column is rows names, represented as any word or letter. First cell is empty*  
>,A,B,Cell  
>1,9,1,3  
>2,=A1+B1,0 *//Cell with arithmetics will start with '=', followed by \<ROW1\>\<CLMN1\>+-\*/\<ROW2\>\<CLMN2\>.So, the result of B2 cell should be 10*  
>30,-2,=B2-A30,4  
>*//First row is column numbers, represented as unsigned integers*  

Input file should be called file.csv and located in src folder  
  
Build instructions. Tested only on linux.  
cd ./build  
cmake ..  
cmake --build .  
./csvreader file.csv  
