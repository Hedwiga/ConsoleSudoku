#ifndef SUDOKU_H_
#define SUDOKU_H_
#include <string>
#include <iostream>
#define ASCII_DIFF 48
#define JUMP_IN_CONSOLE(VAR) for(int i = 0; i < (VAR); ++i) std::cout << std::endl;
#define SUDOKU_AMOUNT_EASY 5
#define SUDOKU_AMOUNT_MEDIUM 1
#define SUDOKU_AMOUNT_HARD 1
#define EMPTY 0
#define SIZE_ 3
#define SIZE_D 9 
#define SOLVED 1
#define UNSOLVED 0

typedef int SolveStatus;
class Grid
{
private:
	int grid[SIZE_D][SIZE_D];
	int users_grid[SIZE_D][SIZE_D];
	int num_of_sudoku;
	bool backtracking();
	bool block_is_safe(int num, int row, int col) const;
	bool row_is_safe(int num, int row) const;
	bool col_is_safe(int num, int col) const;
protected:
	SolveStatus status;
	enum Mode{ Easy, Medium, Hard };
	Mode mode;
	bool find_empty_box() const;
	bool find_empty_box(int & row, int & col) const;
	bool box_is_safe(int num, int row = 0, int col = 0) const;
	bool box_is_empty(int row, int col) const;
	bool fill_box(int num, int row, int col);
	void show_grid(int row = -1, int col = -1) const; 
	void show_available_numbers(int row, int col) const;
	void set_status(SolveStatus state); // SOLVED = 1 or UNSOLVED = 0
public:
	Grid(Mode difficulty = Easy);
	bool read_grid();
	bool create_grid();
	bool solve_sudoku();
	bool write_solution();
	
};
class Game : private Grid
{
private:
	std::string nickname;
	
public: 
	Game(std::string nickname = "Lovely Player", Mode difficulty = Easy);
	bool start_game();
	bool check_input(int & var);
};
int random(int min, int max);


#endif
