#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include"Board.h"
#include<iostream>
using namespace std;

class Player
{
public:
	Player(Board & givenBoard, char givenPiece) //constructer for the player class.
		: board(givenBoard), piece(givenPiece){} // corresponding private data members are initialized. 
	bool put(int column); //The function should return true if the piece is placed successfully on the game board; otherwise, it should return false.
	void turn_board(); // It turns the board clockwise.
	bool is_winner(); // It will return true if the player has won the game; it returns false otherwise.
	char get_symbol(); //returns the player’s game piece character.
private:
	Board& board;
	char piece;
};
#endif