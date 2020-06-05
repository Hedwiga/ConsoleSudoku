#include <iostream> 
#include <windows.h>
#include <cctype>
#include "sudoku.h"


int main()
{
	using std::cout;
	using std::cin;
	using std::endl;
	char launcher;
	char restart_status;
	bool flag = false;
	cout << "'S' - start the game\n'Q' - quit the program\n";
	while(cin >> launcher)
	{
		switch(launcher)
		{
		case 'q':
		case 'Q': 
			cout << "Bye!";
			return 0;
		case 's':
		case 'S': 
			flag = true;
			break;
		default: 
			cin.clear();
			while(cin.get() != '\n')
				continue;
			cout << "Incorrect character!\n'S' - start the game\n'Q' - quit the program\n";		
		}
		if(flag) 
		{
			Game new_game;
			if(!new_game.start_game()) 
			{
				cout << "Bye!\n";
				return -1;
			}
			cout << "Again?\n'S' - again\n'Q' - quit the program\n";
		}
	}
	return 0;
}

