#include "stdafx.h"
#include "Player.h"


const void Player::setGamePiece(char piece)
{
	m_GamePiece = piece;
}

const char Player::getGamePiece()
{
	return m_GamePiece;
}

void Player::addScore(int score)
{
	m_Score += score;
}

int Player::getScore()
{
	return m_Score;
}



