#ifndef SUDOKU_H
#define SUDOKU_H

class sudoku{
    private:
        int puzzle[9][9];
        bool empty;
        bool solve_helper();
    public:
        sudoku();
        sudoku(int puzzle_in[9][9]);
        ~sudoku();
        void set(int puzzle_in[9][9]);
        void solve();
        void save(const char* fname);
};

#endif