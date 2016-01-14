#pragma once

#include <iostream>
#include <string>

class PlayingBoard
{
private:
	char m_playingBoard[]; // The playing board

public:
	PlayingBoard();
	static const int NUMBER_OF_SQUARES = 9;
	static const char EMPTY = ' '; //Empty game piece
	static const char X = 'X'; //Game piece: 'X'
	static const char O = 'O'; //Game piece: 'O'

	void initialize();
	const void display();
	const char getBoard(int i);
	void addGamePiece(int movePosition, char gamePiece);
	void removeGamePiece(int movePosition);
	void clear();

};

