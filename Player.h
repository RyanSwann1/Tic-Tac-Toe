#pragma once
#include <iostream>
class Player
{
private:
	char m_GamePiece = ' ';
	int m_Score = 0;
	bool m_firstTurn;

public:

	const void setGamePiece(char piece);
	const char getGamePiece();
	void addScore(int score);
	int getScore();
};

