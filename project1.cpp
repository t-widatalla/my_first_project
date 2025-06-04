#include <iostream>
#include <cstdlib>
using namespace std;

enum enGameChoice{ rock = 1, paper = 2, scissor = 3 };
enum enWinner{player1 = 1, computer = 2, draw = 3};

struct stRoundInfo
{
	short gameRounds;
	enGameChoice player1Choice;
	enGameChoice computerChoice;
	enWinner winnerName;
	string roundWinnerName;
};

struct stGameResults 
{
	short gameRounds;
	short player1WinTimes;
	short computerWinTimes;
	short drawTimes;
	enWinner gameWinner;
	string gameWinnerName;

};


string tabs(short numberOfTabs)
{
	string t = "";
	for (int i = 1; i <= numberOfTabs; i++)
	{
		t += "\t";
		cout << t;
	}
	return t;
}

int randomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}

enGameChoice readPlayerChoice()
{
	short choice = 1;
	do
	{
		cout << "enter your choice  1) rock, 2) paper, 3) scissor :" << endl;
		cin >> choice;

	} while (choice < 1 || choice > 3);

	return (enGameChoice)choice;
}

enGameChoice getComputerChoice()
{
	return (enGameChoice)randomNumber(1, 3);
}

int howManyRounds()
{
	int rounds = 1;
	do
	{
		cout << "enter how many rounds do you want to play 1 - 10\n";
		cin >> rounds;


	} while (rounds < 1 || rounds > 10);

	return rounds;
}

enWinner winner(stRoundInfo round)
{
	if (round.player1Choice == round.computerChoice) return enWinner::draw;

	switch (round.player1Choice)
	{
	case enGameChoice::paper:
	{
		if (round.computerChoice == enGameChoice::scissor)
			return enWinner::computer;
	}
	break;

	case enGameChoice::rock:
		if (round.computerChoice == enGameChoice::paper)
			return enWinner::computer;
		break;

	case enGameChoice::scissor:
		if (round.computerChoice == enGameChoice::rock) return enWinner::computer;
		break;

	}

	return enWinner::player1;

}

string winnerName(stRoundInfo round)
{
	string name[3] = { "player1","computer","draw" };
	return name[round.winnerName - 1];
}

string choiceName(enGameChoice choice)
{
	string arrGamechoice[3] = { "rock", "paper", "scissor" };
	return arrGamechoice[choice - 1];
}

void setScreenColor(enWinner winner)
{
	switch (winner)
	{
	case enWinner::player1:
		system("color 2F");
		break;

	case enWinner::computer:
	{
		system("color 4F");
		cout << "\a";
		break;
	}
	default:
		system("color 6F");
		break;
	}
}
void printRoundResults(stRoundInfo roundResults)
{
	cout << "-------- round [" << roundResults.gameRounds << "] -------\n";
	cout << "player1 choice: " <<choiceName (roundResults.player1Choice) << endl;
	cout << "computer choice: " << choiceName(roundResults.computerChoice) << endl;
	cout << "round winner: " << roundResults.roundWinnerName << endl;

	setScreenColor(roundResults.winnerName);
}

enWinner whoWonTheGame(stGameResults game)
{
	if (game.player1WinTimes > game.computerWinTimes) return enWinner::player1;
	else if (game.computerWinTimes > game.player1WinTimes) return enWinner::computer;
	else return enWinner::draw;
}

string gameWinnerName(stGameResults game)
{
	string name[3] = { "player1", "computer", "no winner" };
	return name[game.gameWinner - 1];
}

stGameResults fillGameResults(short howManyRounds, short player1winTimes, short computerWinTimes, short drawTimes)
{
	stGameResults gameResults;
	gameResults.gameRounds = howManyRounds;
	gameResults.player1WinTimes = player1winTimes;
	gameResults.computerWinTimes = computerWinTimes;
	gameResults.drawTimes = drawTimes;
	gameResults.gameWinner = whoWonTheGame(gameResults);
	gameResults.gameWinnerName = gameWinnerName(gameResults);

	return gameResults;
}
stGameResults playGame(short howManyRounds)
{
	stRoundInfo roundResults;
	short player1WinTimes = 0, computerWinTimes = 0, drawTimes = 0;
	
	for (short gameRounds = 1; gameRounds <= howManyRounds; gameRounds++)
	{
		cout << "rounds [" << gameRounds << "] begin\n";
		roundResults.gameRounds = gameRounds;
		roundResults.player1Choice = readPlayerChoice();
		roundResults.computerChoice = getComputerChoice();
		roundResults.winnerName = winner(roundResults);
		roundResults.roundWinnerName = winnerName(roundResults);

		if (roundResults.roundWinnerName == "player1") player1WinTimes++;
		else if (roundResults.roundWinnerName == "computer") computerWinTimes++;
		else drawTimes++;

		printRoundResults(roundResults);
	}
	return fillGameResults(howManyRounds, player1WinTimes, computerWinTimes, drawTimes);
}

void gameOverScreen()
{	
	cout << tabs(2) << "-----------------------------------------------\n\n";
	cout << tabs(2) << "------------------ [GAME OVER] ------------------\n";
	cout << tabs(2) << "-----------------------------------------------\n\n";

}

void printFinalGameResults(stGameResults gameResults)
{
	cout << tabs(2) << "game rounds : " << gameResults.gameRounds << endl;
	cout << tabs(2) << "player 1 win times : " << gameResults.player1WinTimes << endl;
	cout << tabs(2) << "computer win times : " << gameResults.computerWinTimes << endl;
	cout << tabs(2) << "draw times : " << gameResults.drawTimes << endl;
	cout << tabs(2) << "game winner : " << gameResults.gameWinnerName << endl;
}
void resetScreen()
{
	system("cls");
	system("color 0F");
}

void startGame()
{
	char playAgain = 'Y';
	do
	{
		resetScreen();
		stGameResults game = playGame(howManyRounds());
		gameOverScreen();
		printFinalGameResults(game);
		

		cout << "do you want to play again? Y/N\n";
		cin >> playAgain;

	} while (playAgain == 'y' || playAgain == 'Y');

}
int main()
{
	srand((unsigned)time(NULL));
	startGame();



	return 0;
}