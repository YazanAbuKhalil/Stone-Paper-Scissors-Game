#include <iostream>
#include <cstdlib>
using namespace std;

enum enWinner {Player1 = 1, Computer = 2, Draw = 3};

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

short ReadHowManyRounds() {

    short GameRounds = 0;

    do {
        cout << "How many rounds from 1 to 10 ?\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

int RandomNumber(int From, int To) {

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

struct stGameResults {
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

struct stRoundInfo {
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

enGameChoice ReadPlayer1Choice() {

    short Choice = 0;

    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ?";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);

    return (enGameChoice)Choice;
}

enGameChoice ReadComputerChoice() {
    
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {

    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {
        return enWinner::Draw;
    }

    switch (RoundInfo.Player1Choice) {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper) {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors) {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone) {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player1;

}
  
string WinnerName(enWinner Winner) {

    string arrWinnerName[3] = { "Player1", "Computer", "No winner" };

    return arrWinnerName[Winner - 1];
}

void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner) {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        break;
    default :
        system("color 6F");
        break;
    }
}

string ChoiceName(enGameChoice Choice) {

    string arrGameChoices[3] = {"Stone", "Paper", "Scissors"};

    return arrGameChoices[Choice - 1];
}

void PrintRoundResults(stRoundInfo RoundInfo) {

    cout << "\n------------Round [" << RoundInfo.RoundNumber << "]" << "------------\n\n";

    cout << "PLayer1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "--------------------------------\n";

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short PlayerWinTimes, short ComputerWinTimes) {

    if (PlayerWinTimes > ComputerWinTimes) {
        return enWinner::Player1;
    }
    else if (ComputerWinTimes > PlayerWinTimes) {
        return enWinner::Computer;
    }
    else {
        return enWinner::Draw;
    }

}

stGameResults FillGameResults(int GameRounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {

    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WinTimes = PlayerWinTimes;
    GameResults.ComputerWinTimes = ComputerWinTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = WhoWonTheGame(PlayerWinTimes, ComputerWinTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;

}

stGameResults PlayGame(short HowManyRounds) {

    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins: \n";

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = ReadComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WinTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(RoundInfo);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);


}

void ResetScreen() {

    system("cls");
    system("color 0F");
}

string Tabs(short NumberOfTabs) {

    string T = "";

    for (int i = 1; i <= NumberOfTabs; i++) {
        T = T + "\t";
    }

    return T;
}

void showGameOverScreen() {
    cout << Tabs(2) << "--------------------------------------------\n\n";
    cout << Tabs(2) << "            +++ Game Over +++               \n\n";
    cout << Tabs(2) << "--------------------------------------------\n\n";

}

void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "------------------- [Game Results] ------------------- \n\n";
    cout << Tabs(2) << "Game Rounds          :" << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 win times    :" << GameResults.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer win times   :" << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times           :" << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner         :" << GameResults.WinnerName << endl;
    cout << Tabs(2) << "------------------------------------------------------ \n\n" << endl;

    SetWinnerScreenColor(GameResults.GameWinner);
}

void StartGame() {

    char PlayAgain = 'y';

    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        showGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');


}


int main()
{
    srand((unsigned)time(NULL));

    StartGame();
        
}
