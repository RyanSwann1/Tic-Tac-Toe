#include "stdafx.h"
#include "computerPlayer.h"
#include "PlayingBoard.h"
#include "GameLogic.h"
#include "humanPlayer.h"

void computerPlayer::setInPlay(bool play)
{
	m_InPlay = play;
}

bool computerPlayer::isInPlay()
{
	return m_InPlay;
}

int computerPlayer::getMovePosition(PlayingBoard & playingBoard, GameLogic& gameLogic, humanPlayer& player1)
{
	int movePosition = 0;
	bool found = false; //Found position to move
	
	while (!found)
	{
		winNextTurn(playingBoard, gameLogic, movePosition, found);
		blockNextTurn(playingBoard, gameLogic, player1, movePosition, found);
	    bestNextPosition(playingBoard, gameLogic, movePosition, found);
	}

	//movePosition = 4;
	return movePosition;
}

void computerPlayer::winNextTurn(PlayingBoard& playingBoard, GameLogic& gameLogic, int& move, bool& found)
{
	if (!found)
	{
		move = 0; // Reset movement
		while (move < PlayingBoard::NUMBER_OF_SQUARES && !found)
		{
			if (gameLogic.isMoveLegal(playingBoard, playingBoard.getBoard(move)))
			{
				playingBoard.addGamePiece(move, getGamePiece());
				found = gameLogic.findWinner(playingBoard) == getGamePiece();
				playingBoard.removeGamePiece(move);
			}

			else
			{
				move++;
			}
		}
	}

	else
	{
		return;
	}
}

void computerPlayer::blockNextTurn(PlayingBoard& playingBoard, GameLogic& gameLogic, humanPlayer& player1, int& move, bool& found)
{
	if (!found)
	{
		move = 0; // Reset movement position
		while (move < PlayingBoard::NUMBER_OF_SQUARES && !found)
		{
			if (gameLogic.isMoveLegal(playingBoard, playingBoard.getBoard(move)))
			{
				playingBoard.addGamePiece(move, player1.getGamePiece());
				found = gameLogic.findWinner(playingBoard) == player1.getGamePiece();
				playingBoard.removeGamePiece(move);
			}

			else
			{
				move++;
			}
		}
	}

	else
	{
		return;
	}
}

void computerPlayer::bestNextPosition(PlayingBoard& playingBoard, GameLogic& gameLogic, int& move, bool& found)
{
	if (!found)
	{
		/*
		0, 1, 2
		3, 4, 5
		6, 7, 8
		*/
		int i = 0;
		move = 0;
		std::vector<int> bestMoves = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		
		while (!found && i < bestMoves.size())
		{
			move = bestMoves[i];
			if (gameLogic.isMoveLegal(playingBoard, bestMoves[i]))
			{
				found = true;
			}

			else
			{
				i++;
			}
		}

	}

	else
	{
		return;
	}
}

void computerPlayer::move(PlayingBoard& playingBoard, GameLogic& gameLogic, humanPlayer& player1)
{
	int movePosition = getMovePosition(playingBoard, gameLogic, player1);

	playingBoard.addGamePiece(movePosition, getGamePiece());
}
