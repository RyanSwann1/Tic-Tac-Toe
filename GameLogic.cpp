#include "stdafx.h"

#include "GameLogic.h"
#include "PlayingBoard.h"
#include "computerPlayer.h"
#include "humanPlayer.h"



bool GameLogic::decideFirstTurn(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer)
{
	bool firstTurn;
	char responce = ' ';

	do
	{
		std::cout << "Would you like to go first? 'y' - Yes. 'n' - No." << "\n";
		std::cin >> responce;
		switch (responce)
		{
		case 'y':
			firstTurn = true;
			break;

		case 'n':
			firstTurn = false;
			break;

		default:
			std::cout << "Please enter valid data." << "\n";
		}
	} while (responce != 'y' && responce != 'n');

	allocateGamePieces(player1, player2, computer, firstTurn);

	if (firstTurn)
		return true;
	else
		return false;

}

void GameLogic::allocateGamePieces(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, bool firstTurn)
{
	if (computer.isInPlay())
	{
		if (firstTurn)
		{
			player1.setGamePiece(PlayingBoard::X);
			computer.setGamePiece(PlayingBoard::O);
		}

		else
		{
			computer.setGamePiece(PlayingBoard::X);
			player1.setGamePiece(PlayingBoard::O);
		}
	}

	else
	{
		if (firstTurn)
		{
			player1.setGamePiece(PlayingBoard::X);
			player2.setGamePiece(PlayingBoard::O);
		}

		else
		{
			player2.setGamePiece(PlayingBoard::X);
			player1.setGamePiece(PlayingBoard::O);
		}
	}
}

bool GameLogic::isComputerInPlay()
{
	char responce = ' ';
	std::cout << "Would you like to face a human or computer. 'h' Human. 'c' Computer.";
	std::cin >> responce;

	switch (responce)
	{
	case 'h':
		return false;
		break;

	case 'c':
		return true;
		break;

	default:
		std::cout << "Please enter valid data." << "\n";
	}
}

char GameLogic::findWinner(PlayingBoard& playingBoard)
{
	//All combination of winnngRows
	const int winningRows[8][3] = {
		//Horizontal 
		{ 0, 1, 2 },
		{ 3, 4, 5 },
		{ 6, 7, 8 },
		//Vertical
		{ 0, 3, 6 },
		{ 1, 4, 7 },
		{ 2, 5, 8 },
		//Diagonal
		{ 0, 4, 8 },
		{ 2, 4, 6 }
	};


	const int totalRows = 8; //Amount of rows there are to search through

	//playingBoard.getBoard(winningRows[row][0]);
	for (int row = 0; row < totalRows; row++)
	{
		if ((playingBoard.getBoard(winningRows[row][0]) != PlayingBoard::EMPTY) &&
			(playingBoard.getBoard(winningRows[row][0]) == playingBoard.getBoard(winningRows[row][1])) &&
			(playingBoard.getBoard(winningRows[row][1]) == playingBoard.getBoard(winningRows[row][2])))
		{
			return playingBoard.getBoard(winningRows[row][0]);
		}

	}

	if (isGameTie(playingBoard))
	{
		return TIE;
	}

	return NOONE;
}

bool GameLogic::isGameTie(PlayingBoard& playingBoard)
{
	int i = 0;
	for (int i = 0; i < PlayingBoard::NUMBER_OF_SQUARES; i++)
	{
		if (playingBoard.getBoard(i) == PlayingBoard::EMPTY)
		{
			return false;
		}
	}

	return true;
}

bool GameLogic::isRoundOver(humanPlayer & player1, humanPlayer & player2, computerPlayer& computer, PlayingBoard& playingBoard)
{
	return
		findWinner(playingBoard) == player1.getGamePiece() ||
		findWinner(playingBoard) == player2.getGamePiece() ||
		findWinner(playingBoard) == computer.getGamePiece();
}

bool GameLogic::isMoveLegal(PlayingBoard& playingBoard, int move)
{
	return playingBoard.getBoard(move) == PlayingBoard::EMPTY;
}

bool GameLogic::isGameOver(humanPlayer & player1, humanPlayer & player2, computerPlayer & computer)
{
	return
		player1.getScore() >= m_GameWinningScore ||
		player2.getScore() >= m_GameWinningScore ||
		computer.getScore() >= m_GameWinningScore;
}

char GameLogic::decideTurn(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, char gamePiece)
{
	if (computer.isInPlay())
	{
		if (gamePiece == player1.getGamePiece())
			return computer.getGamePiece();

		else
			return player1.getGamePiece();
	}

	else
	{
		if (gamePiece == player1.getGamePiece())
			return player2.getGamePiece();

		else
			return player1.getGamePiece();
	}
}

char GameLogic::initializeFirstTurn()
{
	return PlayingBoard::X;
}

void GameLogic::game(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard)
{
	computer.setInPlay(gameLogic.isComputerInPlay());

	while (!isGameOver(player1, player2, computer))
	{
		printRound();
		gameRound(player1, player2, computer, gameLogic, playingBoard);
	}

	announceGameWinner(player1, player2, computer);

	//announce game winner
}

void GameLogic::gameRound(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard)
{
	char turn = initializeFirstTurn();
	gameLogic.decideFirstTurn(player1, player2, computer);
	playingBoard.display();

	while (!isRoundOver(player1, player2, computer, playingBoard))
	{
		if (turn == player1.getGamePiece())
		{
			player1.move(playingBoard, gameLogic);
			turn = decideTurn(player1, player2, computer, player1.getGamePiece());
		}

		else if (turn == player2.getGamePiece())
		{
			player2.move(playingBoard, gameLogic);
			turn = decideTurn(player1, player2, computer, player2.getGamePiece());
		}

		else if (turn == computer.getGamePiece())
		{
			computer.move(playingBoard, gameLogic, player1);
			turn = decideTurn(player1, player2, computer, computer.getGamePiece());
		}
		//Display board
		playingBoard.display();
	}

	//After every round ends
	char winner = findWinner(playingBoard);
	announceRoundWinner(player1, player2, computer, gameLogic, playingBoard, winner);
	scoreManagement(player1, player2, computer, winner);
	playingBoard.clear();

	printScores(player1, player2, computer);

	incrementRoundNumb();

}

void GameLogic::announceRoundWinner(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer, GameLogic& gameLogic, PlayingBoard& playingBoard, char winner)
{
	if (winner == player1.getGamePiece())
	{
		std::cout << "Player 1 has wins the round." << "\n";
	}

	else if (winner == player2.getGamePiece())
	{
		std::cout << "Player 2 wins the round." << "\n";
	}

	else if (winner == computer.getGamePiece())
	{
		std::cout << "The Computer wins the round." << "\n";
	}
}

void GameLogic::scoreManagement(humanPlayer & player1, humanPlayer & player2, computerPlayer& computer, char winner)
{
	if (winner == player1.getGamePiece())
		player1.addScore(m_winRoundPoint);
	
	else if (winner == player2.getGamePiece())
		player2.addScore(m_winRoundPoint);

	else if (winner == computer.getGamePiece())
		computer.addScore(m_winRoundPoint);

}

void GameLogic::printScores(humanPlayer & player1, humanPlayer & player2, computerPlayer& computer)
{
	if (computer.isInPlay())
	{
		std::cout << "\nPlayer1 Score: " << player1.getScore() << "\n";
		std::cout << "Computer Score:" << computer.getScore() << "\n";
	}

	else
	{
		std::cout << "\nPlayer1 Score: " << player1.getScore() << "\n";
		std::cout << "Player2 Score: " << player2.getScore() << "\n\n";
	}

}

void GameLogic::incrementRoundNumb()
{
	m_NumbOfRounds++;
}

void GameLogic::announceGameWinner(humanPlayer& player1, humanPlayer& player2, computerPlayer& computer)
{
	if (computer.isInPlay())
	{
		if (player1.getScore() >= m_GameWinningScore)
			std::cout << "Player1 wins the game in " << m_NumbOfRounds << " rounds!" << "\n";

		if (computer.getScore() >= m_GameWinningScore)
			std::cout << "Computer wins the game in " << m_NumbOfRounds << " rounds!" << "\n";
	}

	else
	{
		if (player1.getScore() >= m_GameWinningScore)
			std::cout << "Player1 wins the game in " << m_NumbOfRounds << " rounds!" << "\n";

		if (player2.getScore() >= m_GameWinningScore)
			std::cout << "Player2 wins the game in " << m_NumbOfRounds << " rounds!" << "\n";
	}

}

void GameLogic::printRound()
{
	std::cout << "\nRound " << m_NumbOfRounds << "\n";
}
