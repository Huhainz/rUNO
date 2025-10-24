#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>   // For randomizing
#include <ctime>     // For randomizing
#include <windows.h> // Terminal colors

using namespace std;

enum ColorPrint {red, yellow, green, blue};
const int ColorPrint_len = 4;
enum NumberPrint{zero, one, two, three, four, five, six, seven, eight, nine, plustwo, skip, reverse};
const int NumberPrint_len = 13;
// Deck cards
const int NormalN = 2;
const int DrawN = 2;
const int ReverseN = 2;
const int ZeroN = 1;

const int ColorN = ZeroN + NormalN + DrawN + ReverseN + SkipN;

const int SkipN = 2;
const int WildsN = 4;

class Card
{
    public:
        ColorPrint Color;
        NumberPrint Number;
        string Display;
};

// Give cards functions
void GiveRandomCard (vector<Card> &Hand)
{
    Card tempCard;
    int indexNumber = rand() % NumberPrint_len;
    int indexColor = rand() % ColorPrint_len;
    tempCard.Number = static_cast<NumberPrint>(indexNumber);
    tempCard.Color = static_cast<ColorPrint>(indexColor);
    Hand.push_back(tempCard);
}

void PutRandomCard(Card &Table)
{
    int indexNumber = rand() % 10;
    int indexColor = rand() % 2;
    Table.Number = static_cast<NumberPrint>(indexNumber);
    Table.Color = static_cast<ColorPrint>(indexColor);
}

// Display functions 
void DisplayCard(vector<Card> PlayerHand, int CardIndex)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(PlayerHand[CardIndex].Color)
    {
        case red: SetConsoleTextAttribute(hConsole,FOREGROUND_RED); cout << "Red "; break;
        case yellow: SetConsoleTextAttribute(hConsole,14); cout << "Yellow "; break;
        case green: SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); cout << "Green "; break;
        case blue: SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE); cout << "Blue "; break;
    }
    switch(PlayerHand[CardIndex].Number)
    {
        case zero : cout << "0" << endl; break;
        case one : cout << "1" << endl; break;
        case two : cout << "2" << endl; break;
        case three : cout << "3" << endl; break;
        case four : cout << "4" << endl; break;
        case five : cout << "5" << endl; break;
        case six : cout << "6" << endl; break;
        case seven : cout << "7" << endl; break;
        case eight : cout << "8" << endl; break; 
        case nine : cout << "9" << endl; break;
    }
    SetConsoleTextAttribute(hConsole,0);
}

int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    Card Table;
    PutRandomCard(Table);
    for (int i = 0; i < 7; i++)
    {
        GiveRandomCard(PlayerHand);
        DisplayCard(PlayerHand, i);
    }



    // cout << "Card on the table: ";
    // switch(PlayerHand[0].Color)
    // {
    //     case black: cout << "Black "; break;
    //     case white: cout << "White "; break;
    // }
    // switch(PlayerHand[0].Number)
    // {
    //     case zero : cout << "0" << endl; break;
    //     case one : cout << "1" << endl; break;
    //     case two : cout << "2" << endl; break;
    //     case three : cout << "3" << endl; break;
    //     case four : cout << "4" << endl; break;
    //     case five : cout << "5" << endl; break;
    //     case six : cout << "6" << endl; break;
    //     case seven : cout << "7" << endl; break;
    //     case eight : cout << "8" << endl; break; 
    //     case nine : cout << "9" << endl; break;
    // }
    // cout << PlayerHand[0].Color << " " << PlayerHand[0].Number  << endl ;
    // if (PlayerHand[0].Color == Table.Color || PlayerHand[0].Number == Table.Number)
    // {
    //     cout << "Card can be put!" << endl;
    // }
    // else
    // {
    //     cout << "Card can't be put!" << endl;
    // }

    return 0;
}