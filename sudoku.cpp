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

bool sudoku::solve_helper(){
    bool solved;
    int ridx=0;
    int cidx=0;
    int nridx;
    int ncidx;
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
    //calculate neighborhood of number
    if(ridx>-1 && ridx<3){
        nridx=0;
    }
    else if(ridx>2 && ridx<6){
        nridx=3;
    }
    else if(ridx>5 && ridx<9){
        nridx=6;
    }
    if(cidx>-1 && cidx<3){
        ncidx=0;
    }
    else if(cidx>2 && cidx<6){
        ncidx=3;
    }
    else if(cidx>5 && cidx<9){
        ncidx=6;
    }
    for(int number=1; number<10; number++){
        solved=true;
        //place number
        puzzle[ridx][cidx]=number;
        //check if state is valid
        //check col for duplicates
        for(int row=0; row<9; row++){
            if(row == ridx){
                continue;
            }
            if(puzzle[row][cidx] == number){
                solved=false;
                break;
            }
        }
        //check row for duplicates
        for(int col=0; col<9; col++){
            if(col == cidx){
                continue;
            }
            if(puzzle[ridx][col]== number){
                solved=false;
                break;
            }
        }
        //check neighborhoods
        for(int row=nridx; row<nridx+3; row++){
            for(int col=ncidx; col<ncidx+3; col++){
                if(col == cidx && row == ridx){
                    continue;
                }
                if(puzzle[row][col]==number){
                    solved= false;
                }
            }
        }
        if(solved == false){
            continue;
        }
        else{
            solved=solve_helper();
           if(solved){
               return true;
           }
        }
    }
     //undo placed number
    puzzle[ridx][cidx]=0;
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
