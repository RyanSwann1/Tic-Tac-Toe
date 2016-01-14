#include "stdafx.h"
#include "humanPlayer.h"
#include "PlayingBoard.h"
#include "GameLogic.h"


int humanPlayer::getMovePosition(PlayingBoard& playingBoard, GameLogic& gameLogic)
{
	int low = 0,
		high = PlayingBoard::NUMBER_OF_SQUARES - 1,
		movePosition = 0;
	bool moveAllowed = false;
	do
	{
		std::cout << "Enter a number between " << low << " and " << high << ".\n";
		std::cin >> movePosition;

		if (gameLogic.isMoveLegal(playingBoard, movePosition))
			moveAllowed = true;
		else
			std::cout << "Square already occupied." << "\n";

	} while (!moveAllowed);

	return movePosition;
}

void humanPlayer::move(PlayingBoard& playingBoard, GameLogic& gameLogic)
{
	int move = getMovePosition(playingBoard, gameLogic);

	playingBoard.addGamePiece(move, getGamePiece());
}
