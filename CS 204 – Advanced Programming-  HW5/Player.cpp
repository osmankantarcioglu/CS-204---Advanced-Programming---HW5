#include"Player.h"
#include"Board.h"
#include<iostream>

using namespace std;

//Constructer of the player class have been implemented in header file. 

/******************************************************************************
The function should return true if the piece is placed successfully on the game
board; otherwise, it should return false.
******************************************************************************/
bool Player::put(int column)
{
	return board.put_piece(piece, column);
}
/******************************************************************************
It turns the board clockwise.
******************************************************************************/
void Player::turn_board()
{
	board.turn_board_clockwise();
}
/******************************************************************************
It will return true if the player has won the game; it returns false otherwise.
******************************************************************************/
bool Player::is_winner()
{
	return(board.get_game_status() == piece);
}
/******************************************************************************
This function is used to return the player’s game piece character.
******************************************************************************/
char Player::get_symbol()
{
	return piece;
}