#pragma once
#include "Player.h"
class PlayingBoard;
class GameLogic;

class humanPlayer :
	public Player
{
public:

	int getMovePosition(PlayingBoard& playingBoard, GameLogic& gameLogic);
	void move(PlayingBoard& playingBoard, GameLogic& gameLogic);
};

