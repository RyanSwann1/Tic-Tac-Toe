#pragma once
#include "Player.h"
#include <vector>


class PlayingBoard;
class GameLogic;
class humanPlayer;

class computerPlayer :
	public Player
{
private:
	bool m_InPlay;

public:

	void setInPlay(bool play);
	bool isInPlay();
	void move(PlayingBoard& playingBoard, GameLogic& gameLogic, humanPlayer& player1);
	int getMovePosition(PlayingBoard& playingBoard, GameLogic& gameLogic, humanPlayer& player1);
	void winNextTurn(PlayingBoard& playingBoard, GameLogic& gameLogic, int& move, bool& found);
	void blockNextTurn(PlayingBoard& playingBoard, GameLogic& gameLogic, humanPlayer& player1, int& move, bool& found);
	void bestNextPosition(PlayingBoard& playingBoard, GameLogic& gameLogic, int& move, bool& found);

};

