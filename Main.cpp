// Tic Tac Toe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PlayingBoard.h"
#include "GameLogic.h"
#include "computerPlayer.h"
#include "humanPlayer.h"



int main()
{
	computerPlayer computer;
	humanPlayer player1, player2;
	GameLogic gameLogic;
	PlayingBoard playingBoard;

	//The game
	gameLogic.game(player1, player2, computer, gameLogic, playingBoard);


	std::string barn;
	std::cin >> barn;

	return 0;
}



