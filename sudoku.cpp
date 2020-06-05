
#include <fstream>

#include <cstdlib>
#include <ctime>
#include "sudoku.h"
#include "grid_output.h"

Grid::Grid(Mode difficulty)
{
	using std::cout;
	switch(difficulty)
	{
	case Easy:
		mode = Easy;
		num_of_sudoku = random(0, SUDOKU_AMOUNT_EASY);
		break;
	case Medium:
		mode = Medium;
		num_of_sudoku = random(0, SUDOKU_AMOUNT_MEDIUM);
		break;
	case Hard:
		mode = Hard;
		num_of_sudoku = random(0, SUDOKU_AMOUNT_HARD);
		break;
	default:
		cout << "Incorrect difficulty!\nSet by Medium\n";
		mode = Medium;
	}
	for(int i = 0; i < SIZE_D; ++i)
		for(int j = 0; j < SIZE_D; ++j)
			users_grid[i][j] = grid[i][j] = 0;
}
bool Grid::backtracking()
{
	int row, col = 0;
	if(!find_empty_box(row, col)) return true;
	for(int num = 1; num <= SIZE_D; ++num)
	{
		if(box_is_safe(num, row, col) && users_grid[row][col] == EMPTY)
		{
			users_grid[row][col] = num;
			if(backtracking()) 
				return true;
			users_grid[row][col] = EMPTY;
		} 
	}
	return false;
		
}
bool Grid::find_empty_box(int & row, int & col) const// returns true if empty box is founded
{
	for(row = 0; row < SIZE_D; ++row)
		for(col = 0; col < SIZE_D; ++col)
			if(users_grid[row][col] == EMPTY) 
				return true;
	return false;
}
bool Grid::find_empty_box() const
{
	for(int row = 0; row < SIZE_D; ++row)
		for(int col = 0; col < SIZE_D; ++col)
			if(users_grid[row][col] == EMPTY) 
				return true;
	return false;
}
bool Grid::box_is_safe(int num, int row, int col) const
{
	return 
		row_is_safe(num, row) &&
		col_is_safe(num, col) &&
		block_is_safe(num, row, col);
}
bool Grid::box_is_empty(int row, int col) const
{
	return grid[row][col] == EMPTY;
} 
bool Grid::block_is_safe(int num, int row, int col) const // return false if founds number in a block
{
	int limit_row = 0, limit_col = 0;
	if(row < SIZE_) 
		limit_row = SIZE_;
	else if(row < SIZE_ * 2) 
		limit_row = SIZE_ * 2;
	else
		limit_row = SIZE_ * 3;
		
	if(col < SIZE_)
		limit_col = SIZE_;
	else if(col < SIZE_ * 2) 
		limit_col = SIZE_ * 2;
	else
		limit_col = SIZE_ * 3;

	for(row = limit_row - SIZE_; row < limit_row; ++row)
		for(col = limit_col - SIZE_; col < limit_col; ++col)
			if(users_grid[row][col] == num)
				return false;
	return true;
}

bool Grid::row_is_safe(int num, int row) const // return false if founds number in a row
{
	for(int j = 0; j < SIZE_D; ++j)
		if(users_grid[row][j] == num ) return false;
	return true;	
}

bool Grid::col_is_safe(int num, int col) const // return false if founds number in a col
{
	for(int j = 0; j < SIZE_D; ++j)
		if(users_grid[j][col] == num ) return false;
	return true;	
}

bool Grid::fill_box(int num, int row, int col)
{
	users_grid[row][col] = num;
}

bool Grid::create_grid()
{
	if(!read_grid()) return false;
	std::cout << "Number of sudoku: " << num_of_sudoku << std::endl;
	for(int i = 0; i < SIZE_D; ++i)
		for(int j = 0; j < SIZE_D; ++j)
			grid[i][j] = users_grid[i][j];
	if(!solve_sudoku()) return false;

	write_solution();
	for(int i = 0; i < SIZE_D; ++i)
		for(int j = 0; j < SIZE_D; ++j)
			users_grid[i][j] = grid[i][j];
	return true;
}
bool Grid::read_grid()
{
	using namespace std;
	string path; 
	switch(mode)
	{
	case Easy:
		path = "easy";
		break;
	case Medium:
		path = "medium";
		break;
	case Hard:
		path = "hard";
		break;
	}
	path = path + "\\sudoku_" +  std::to_string(num_of_sudoku) + "\\sudoku.txt";
	ifstream file;
	file.open(path.c_str());
	if(!file.is_open())
		return false;
	for(int i = 0; i < SIZE_D; ++i)
		for(int j = 0; j < SIZE_D; ++j)
			file >> users_grid[i][j];
	file.close();
	return true;	
}
bool Grid::solve_sudoku()
{
	return backtracking();
}
bool Grid::write_solution()
{
	using namespace std;
	string path; 
	switch(mode)
	{
	case Easy:
		path = "easy";
		break;
	case Medium:
		path = "medium";
		break;
	case Hard:
		path = "hard";
		break;
	}
	path = path + "\\sudoku_" +  to_string(num_of_sudoku) + "\\solution.txt";
	ofstream file;
	file.open(path.c_str());
	if(!file.is_open())
		return false;
	for(int i = 0; i < SIZE_D; ++i)
	{
		for(int j = 0; j < SIZE_D; ++j)
		{
			file << users_grid[i][j] << " ";
			if((j + 1) % SIZE_ == 0) file << " ";
		}
		if((i + 1) % SIZE_ == 0) file << endl;
		file << endl;
	}
	file.close();	
}
void Grid::set_status(SolveStatus state)
{
	status = state;
}
void Grid::show_grid(int row, int col) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	using std::cout;
	using std::endl;
	cout << "    ";
	for(int i = 1; i < SIZE_D + 1; ++i)
	{
		SetConsoleTextAttribute(hConsole, 240);
		cout << " " << i << " ";
		SetConsoleTextAttribute(hConsole, 15);
		cout << " ";
	}
	cout << endl;
	cout << "   ";
	for(int l = 0; l <= LENGHT_OF_BLOCK * SIZE_; ++l) // upper border
	{
		if(l == 0)
			cout << (char)LEFT_UP_COR;
		else if(l == LENGHT_OF_BLOCK  * SIZE_)
			 cout << (char)RIGHT_UP_COR;
		else if(l % LENGHT_OF_BLOCK  == 0)
			cout << (char)BORDER_UP_D;
		else if(l % (SIZE_ + 1) == 0)
			cout << (char)BORDER_UP;
		else cout << (char)BORDER_HORT ;
	}
	cout << endl;
	
	for(int i = 0; i < SIZE_D; ++i)
	{
		SetConsoleTextAttribute(hConsole, 240);
		cout << ' ' << i + 1 << ' ';
		SetConsoleTextAttribute(hConsole, 15);
		cout << (char)BORDER_VERT; // left border
		for(int j = 0; j < SIZE_D; ++j)
		{
			
			if((row >= 0) && (col >= 0) && row == i && col == j)
			{
				SetConsoleTextAttribute(hConsole, 11);
				cout <<  ' ' << '*' << ' ';	
				SetConsoleTextAttribute(hConsole, 15);
			}
			else if(grid[i][j] && status == UNSOLVED)
			{
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
				cout <<  ' ' << grid[i][j] << ' ';
				SetConsoleTextAttribute(hConsole, 15);
			}
			else
			{
				if(status == SOLVED)
					SetConsoleTextAttribute(hConsole, 223);
				else if(users_grid[i][j])
					SetConsoleTextAttribute(hConsole, 176);
				else
					SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
				cout <<  ' ' << users_grid[i][j] << ' ';
				SetConsoleTextAttribute(hConsole, 15);
			}	
			if((j + 1) % SIZE_ == 0 ) cout << (char)BORDER_VERT; // right border
			else cout << (char)VERT_LINE; // dividers(lines)
		}
		cout << endl;
		cout << "   ";
		for(int l = 0; l <= LENGHT_OF_BLOCK  * SIZE_; ++l) // inner lines(horizontal dividers)
		{
			if(((i + 1) % SIZE_ != 0))
			{
				if(l == 0)
					cout << (char)BORDER_LEFT;
				else if(l == LENGHT_OF_BLOCK  * SIZE_)
					 cout << (char)BORDER_RIGHT;
				else if(l % LENGHT_OF_BLOCK  == 0)
					cout << (char)GRID_HORT;
				else if(l % (SIZE_ + 1) == 0)
					cout << (char)GRID;
				else cout << (char)HORT_LINE ;	
			}
			else if(SIZE_D - i != 1)
			{	
			
				if(l == 0)
					cout << (char)BORDER_LEFT_D;
				else if(l == LENGHT_OF_BLOCK  * SIZE_ )
					 cout << (char)BORDER_RIGHT_D;
				else if(l % LENGHT_OF_BLOCK  == 0)
					cout << (char)BORDER_GRID;
				else if(l % (SIZE_ + 1) == 0)
					cout << (char)GRID_VERT;
				else cout << (char)BORDER_HORT;
			}	
			else
			{
				if(l == 0) cout << (char)LEFT_DOWN_COR;
				else if(l == LENGHT_OF_BLOCK  * SIZE_)
					 cout << (char)RIGHT_DOWN_COR;
				else if(l % LENGHT_OF_BLOCK  == 0)
					cout << (char)BORDER_DOWN_D;
				else if(l % (SIZE_ + 1) == 0)
					cout << (char)BORDER_DOWN;
				else cout << (char)BORDER_HORT ;
			}	
		}
		cout << endl;
	}
	cout << endl;
}
void Grid::show_available_numbers(int row, int col) const
{
	using std::cout;
	using std::endl;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "Numbers available:\n";
	SetConsoleTextAttribute(hConsole, 6);
	for(int num = 1; num <= SIZE_D; ++num)
	{
		if(row_is_safe(num, row) &&
		col_is_safe(num, col) &&
		block_is_safe(num, row, col)) 
			cout << ' ' << num << ' ';
	}
	SetConsoleTextAttribute(hConsole, 15);	
}

int random(int min, int max)
{
	srand(time(0));
	return (rand() % (max - min + 1)) + min;
}
