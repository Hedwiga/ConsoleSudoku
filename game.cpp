
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "sudoku.h"

Game::Game(std::string nickname, Mode difficulty) : Grid(difficulty)
{
	using std::cout;
	using std::endl;
	using std::cin;
	cout << "WELCOME TO SUDOKU!\n";
	cout << "Hello, " << nickname << "!" << endl;
	cout << "Enter your nickname: ";
	cin >> nickname;
	cout << nickname << ", please, enter difficulty: \n0 - Easy, 1 - Medium, 2 - Hard, Any other number - Default\n";
	int temp;
	while(!(cin >> temp))
	{
		cin.clear();
		while(cin.get() != '\n')
			continue;
		cout << "\aNumber is incorrect.\n0 - Easy, 1 - Medium, 2 - Hard, Any other number - Default\n.";
	}
	Grid::mode = (Mode)temp;
}
bool Game::start_game() 
{
	using std::cout;
	using std::endl;
	using std::cin;

	if(!create_grid()) return false;
	int row = 0, col = 0, num = 0;
	cout << "'Q' to quit\n";
	while(find_empty_box())
	{
		JUMP_IN_CONSOLE(20);
		show_grid();
		while(true)
		{
			cout << "Enter row and col to fill in: \n";
			cout << "Row: _\b";
			if(!check_input(row)) return false;
			cout << "Col: _\b";
			if(!check_input(col)) return false;
			--row;
			--col;
			if(box_is_empty(row, col))
				break;
			cout << "Box is already filled!Try again\n";
		}
		show_grid(row, col);
		fill_box(0, row, col);
		while(true)
		{
			cout << "Enter number to fill *:\n ";
			show_available_numbers(row, col);
			cout << "Number: _\b";
			if(!check_input(num)) return false;
			if(!(box_is_safe(num, row, col) && box_is_empty(row, col)))
			{
				cout << "Number isn't available!'\n";
				continue;
			}
			else break;
		}
		fill_box(num, row, col);
	}
	set_status(SOLVED);
	show_grid();
	cout << "You won!!!\n";
	return true;
}
bool Game::check_input(int & var)
{
	using std::cin;
	using std::cout;
	using std::endl;
	char temp;
	while((cin >> temp))
	{ 
		cin.clear();
		if(temp == 'q' || temp == 'Q') return false;
		else if(((int)temp - ASCII_DIFF < 1) || ((int)temp - ASCII_DIFF > SIZE_D))
		{
			while(cin.get() != '\n')
				continue;
			cout << "Incorrect value! Choose number in range 1-9: _\b";
		}
		else break;
	}
	var = (int)temp - ASCII_DIFF;
	return true;
}
