#pragma once

#include <iostream>

class PlayingBoard;
class computerPlayer;
class humanPlayer;

class GameLogic
{
private:
	const int m_GameWinningScore = 3;
	const int m_winRoundPoint = 1;
	int m_NumbOfRounds = 1;

public:
	static const char TIE = 'T'; //Game is tie
	static const char NOONE = 'N'; //No one has won the game yet

	bool isMoveLegal(PlayingBoard& playingBoard, int move);
	bool isGameOver(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer);

	bool decideFirstTurn(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer);
	bool isComputerInPlay();
	bool isGameTie(PlayingBoard& playingBoard);
	bool isRoundOver(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, PlayingBoard& playingBoard);


	char findWinner(PlayingBoard& playingBoard);
	char decideTurn(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, char gamePiece);
	char initializeFirstTurn();


	void allocateGamePieces(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, bool firstTurn);
	void game(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard);
	void gameRound(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard);

	void announceRoundWinner(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard, char winner);
	void announceGameWinner(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer);
	void scoreManagement(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, char winner);
	void printScores(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer);
	void printRound();
	void incrementRoundNumb();
};

