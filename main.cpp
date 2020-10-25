#include "sudoku.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc,char** argv){
    if(argc !=3){
        std::cout<<"Usage: ./<program_name> <fnamein> <fnameout>\n";
        std::cout<<"<fnamein>: Input file name\n";
        std::cout<<"<fnameout>: Output file name\n";
        std::cout<<"Separate all numbers in grid with a single space with all empty slots being represented as a zero.\n";
        std::cout<<"Separate rows with new lines."<<std::endl;
        return 0;
    }
    std::fstream file_in;
    std::string temp_row;
    int ridx=0;
    int puzzle[9][9];
    file_in.open(argv[1]);
    while(std::getline(file_in,temp_row)){
        std::stringstream row(temp_row);
        int element;
        for(int col=0; col<9; col++){
            row>>element;
            puzzle[ridx][col]=element;
        }
        ridx++;
    }
    sudoku sudoku_puzzle(puzzle);
    sudoku_puzzle.solve();
    sudoku_puzzle.save(argv[2]);
}