#ifndef BOARD_H
#define BOARD_H

#include<string>
using namespace std;

class Board
{
public:
	Board(int size, int lenght);//Constructer of the function has been implemented.
	~Board();//Destructer of the function has been implemented.
	void print_board();//This function is used to print content of the board.
	bool put_piece(char character, int column);//This function is used to put a piece on the board
	void turn_board_clockwise();//This function is used to turn the board clockwise.
	char get_game_status();//This function is used to get game status. Wýn - Draw - Continue
private:
	char** mbBoard = NULL;
	int size; //size of the board
	int N;	  //given N value
	bool is_piece_win(char piece);//This function is used to understand whether given piece win.

};
#endif