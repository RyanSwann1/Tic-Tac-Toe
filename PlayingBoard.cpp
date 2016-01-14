#include "stdafx.h"
#include "PlayingBoard.h"


PlayingBoard::PlayingBoard()
{
	m_playingBoard[NUMBER_OF_SQUARES];
	initialize();
}


void PlayingBoard::initialize()
{

	int addToBoard = 0;
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
	{
		m_playingBoard[addToBoard] = EMPTY;
		addToBoard++;
	}
}

const void PlayingBoard::display()
{
	int numb = 0;
	const int newRow = 3;
	std::cout << "---------------------" << "\n";
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
	{
		std::cout << " | " << m_playingBoard[i] << " | ";
		numb++;

		//Makes new row in board
		if (numb % newRow == 0)
		{
			std::cout << "\n";
			std::cout << "---------------------";
			std::cout << "\n";
		}
	}
}

const char PlayingBoard::getBoard(int i)
{
	return m_playingBoard[i];
}

void PlayingBoard::addGamePiece(int movePosition, char gamePiece)
{
	m_playingBoard[movePosition] = gamePiece;
}

void PlayingBoard::removeGamePiece(int movePosition)
{
	m_playingBoard[movePosition] = EMPTY;
}


void PlayingBoard::clear()
{
	int elementNumb = 0; //Element number that it is going through
	for (int i = 0; i < NUMBER_OF_SQUARES; i++)
	{
		m_playingBoard[elementNumb] = EMPTY;
		elementNumb++;
	}
}

