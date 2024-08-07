/******************************************************************************
Sabanci  University CS204 Advanced Programming
Homework 5 – A modified Connect Four game with object sharing
Coded by: Osman Kantarcioglu    -   30891   - Section:B2
Date: 13.05.2024
******************************************************************************/
#include"Board.h"
#include<iostream>

using namespace std;

/******************************************************************************
Constructer of the function has been implemented.
New board has been initialized.
******************************************************************************/
Board::Board(int boardSize, int lenght) : size(boardSize), N(lenght)
{
	mbBoard = new char* [size];
	for (int idx = 0; idx < size; idx++)
	{
		mbBoard[idx] = new char[size];
		for (int idx2 = 0; idx2 < size; idx2++)
		{
			mbBoard[idx][idx2] = '-';
		}
	}
}
/******************************************************************************
Destructer of the function has been implemented.
Free dynamically allocated memory
******************************************************************************/
Board::~Board()
{
	for (int idx = 0; idx < size; idx++)
	{
		delete[] mbBoard[idx];//Free dynamically allocated memory
	}
	delete[] mbBoard;//Free dynamically allocated memory
}

/******************************************************************************
This function is used to print content of the board
******************************************************************************/
void Board::print_board()
{
	cout << endl;
	for (int idx1 = 0; idx1 < size; idx1++)//iterate over the board
	{
		for (int idx2 = 0; idx2 < size; idx2++)
		{
			cout << mbBoard[idx1][idx2];//print content of the board
		}
		cout << endl;
	}
	cout << endl;
}
/******************************************************************************
This function is used to put a piece on the board
******************************************************************************/
bool Board::put_piece(char character, int column)
{
	if (column < 0 || column >= size)
	{
		return false;//checks whether index is out of range 
	}
	else
	{
		if (mbBoard[0][column] != '-')
		{
			return false; //checks whether column is full
		}
		else //if column is not full and index is valid
		{
			//now it is time to put the peice on the board
			//first we need to find lowest EMPTY ýndex
			int empty_row = size - 1;
			do
			{
				if (mbBoard[empty_row][column] == '-')//if the current place for the piece is empty
				{
					mbBoard[empty_row][column] = character;//put the piece
					return true;
				}
				empty_row = empty_row - 1;//else (if not empty), go upword
			} while (empty_row >= 0);//don not move off the board when moving up.
		}
	}
	return false;
}
/******************************************************************************
This function is used to turn the board clockwise
******************************************************************************/
void Board::turn_board_clockwise()
{
	Board temp(size, N); //temp board has been created by using previously defined constructer to rotate the board

	//board have been roated but original board has not changed yet
	for (int idx = 0; idx < size; idx++)
	{
		for (int idx2 = 0; idx2 < size; idx2++)
		{
			temp.mbBoard[idx2][size - idx - 1] = mbBoard[idx][idx2];
		}
	}

	//gravity force is going to be applied
	//start iterating for each column from the bottom to top, when non empty cell has been found. Apply gravity for it
	for (int column = 0; column < size; column++) {
		int insertRow = size - 1; // initialize insertRow to the bottom of the column
		// iterate from bottom to top
		for (int row = size - 1; row >= 0; row--) {
			if (temp.mbBoard[row][column] != '-') {
				// move the non-empty cell to the bottommost available empty cell
				if (row != insertRow) {
					temp.mbBoard[insertRow][column] = temp.mbBoard[row][column];
					temp.mbBoard[row][column] = '-';
				}
				insertRow--; // move to the next empty cell upwards
			}
		}
	}

	//it is time to change original board
	for (int idx = 0; idx < size; idx++)
	{
		for (int idx2 = 0; idx2 < size; idx2++)
		{
			mbBoard[idx][idx2] = temp.mbBoard[idx][idx2];
		}
	}
	//destructer of the temp board will be called automatically when it program goes out of this scope
	//therefore, we do not need to free the memory manually
}

/******************************************************************************
This function is used to get game status
Firstly, it seach for all x and find whether x wins
Secondly, it search for all 0 and find whether 0 wins
LASTLY, set of conditions applied:
1) if board is full but neither x nor y won winner is D
2)if both x and y wons --> winner is D and the status is drawn
3) if only x wons --> winner is x
4) if only y wons --> winner is y
5) else continue game
******************************************************************************/
char Board::get_game_status() {
	bool xWins = is_piece_win('X');//checks X won or not
	bool oWins = is_piece_win('O');//checks O won or not

	bool boardFull = true;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (mbBoard[i][j] == '-') {//if at lest one of the cell is '-' (empty), movement still exists
				boardFull = false;//if board is not full, flag becomes false
			}
		}
	}

	if (boardFull == true && xWins == false && oWins == false) //1) if board is full but neither x nor y won winner is D
	{
		return 'D';
	}
	if (xWins == true && oWins == true)//2)if both x and y wons-- > winner is D and the status is drawn
	{
		return 'D';
	}
	else if (xWins)//3) if only x wons --> winner is x
	{
		return 'X';
	}
	else if (oWins)//4) if only y wons-- > winner is y
	{
		return 'O';
	}
	else//5) else continue game
	{
		return '-';
	}
}
/******************************************************************************
This function is used to understand whether given piece win.
******************************************************************************/
bool Board::is_piece_win(char piece)
{
	bool pieceWins = false;
	for (int idx1 = 0; idx1 < size && !pieceWins; idx1++) {
		for (int idx2 = 0; idx2 < size && !pieceWins; idx2++) {//iterate over all cells of the board
			if (mbBoard[idx1][idx2] == piece) {
				//if cell involves given piece, it checks whether given piece won
				/*
					The logic of horizontal and vertical win are very similar. However, it is a little bir tricky for left and right diagonal win
					1)For vertical win, idx1 + itr is less than size and mbBoard[idx1 + itr][idx2] equal to piece for N times, it wins.
					2)For horizontal win, again when idx2 + itr less than size and mbBoard[idx1][idx2 + itr] equal to piece for N times, it wins.
				*/
				//vertical win
				bool win = true;
				for (int itr = 1; itr < N && win; itr++) {
					if (idx1 + itr >= size || mbBoard[idx1 + itr][idx2] != piece) {
						win = false;
					}
				}
				if (win)
				{
					pieceWins = true;
				}
				//horizontal win
				win = true;
				for (int itr = 1; itr < N && win; itr++) {
					if (idx2 + itr >= size || mbBoard[idx1][idx2 + itr] != piece) {
						win = false;
					}
				}
				if (win)
				{
					pieceWins = true;
				}
				/*
					Now it is time to tricky part.
					1) idx1 + itr shold not exceed size as always, sice we iterate towards left idx2 - itr should not be less than zero
						it means that it should not exceed the leftmost boundary. For these two condition mbBoard[idx1 + itr][idx2 - itr]
						must be equal to given piece. If one of these condition is not satisfied. Right to left diagonal return false for win.
					2) similar to right to left, left to right also have three condition that need to be satisfied. As always idx1 + itr should
						not exceed size. idx2 + itr also should not exceed size when iterate towards rightmost boundary. In addition to these conditions,
						mbBoard[idx1 + itr][idx2 + itr] should be equal to given piece N times.
				*/
				//diagonal win(from right to left)
				win = true;
				for (int itr = 1; itr < N && win; itr++) {
					if (idx1 + itr >= size || idx2 - itr < 0 || mbBoard[idx1 + itr][idx2 - itr] != piece) {
						win = false;
					}
				}
				if (win)
				{
					pieceWins = true;
				}
				//diagonal win(from left to right)
				win = true;
				for (int itr = 1; itr < N && win; itr++) {
					if (idx1 + itr >= size || idx2 + itr >= size || mbBoard[idx1 + itr][idx2 + itr] != piece) {
						win = false;
					}
				}
				if (win)
				{
					pieceWins = true;
				}
			}
		}
	}
	return pieceWins;
}