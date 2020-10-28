#include "sudoku.h"
#include <fstream>

sudoku::sudoku(): empty(true){

}

sudoku::sudoku(int puzzle_in[9][9]): empty(false){
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            puzzle[row][col]=puzzle_in[row][col];
        }
    }
}

sudoku::~sudoku(){

}

void sudoku::set(int puzzle_in[9][9]){
    this->empty=false;
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            puzzle[row][col]=puzzle_in[row][col];
        }
    }
}

bool sudoku::check_state(const int& ridx, const int& cidx, const int& num){
    //Check if desired location is empty
    if(puzzle[ridx][cidx] !=0 ){
        return false;
    }
    //check col for duplicates
    for(int row=0; row<9; row++){
        if(puzzle[row][cidx] == num){
            return false;
        }
    }
    //check row for duplicates
    for(int col=0; col<9; col++){
        if(puzzle[ridx][col]== num){
            return false;
        }
    }
    //check the 3x3 neighborhood
    for(int row=0; row<3; row++){
        for(int col=0; col<3; col++){
            if(puzzle[row+ridx-ridx%3][col+cidx-cidx%3]==num){
                return false;
            }
        }
    }
    return true;
}

bool sudoku::solve_helper(){
    int ridx=0;
    int cidx=0;
    //find first available position
    while(puzzle[ridx][cidx] !=0){
        cidx++;
        if(cidx>8){
            cidx=0;
            ridx++;
        }
        if(ridx>8){
            return true;
        }
    }

    for(int number=1; number<10; number++){
        if(check_state(ridx,cidx,number)){
          //place number
          puzzle[ridx][cidx]=number;
          if(solve_helper()){
              return true;
          }
          else{
              //undo placed number
              puzzle[ridx][cidx]=0;
          }
        }
    }
    return false;
}

void sudoku::solve(){
    if(this->empty){
        return;
    }
    solve_helper();
}


void sudoku::save(const char* fname){
    std::ofstream puzzle_out;
    puzzle_out.open(fname);
    for(int row=0; row<9; row++){
        for(int col=0; col<9; col++){
            puzzle_out<<puzzle[row][col];
            if(col+1 != 9){
                puzzle_out<<" ";
            }
        }
        puzzle_out<<std::endl;
    }
}
