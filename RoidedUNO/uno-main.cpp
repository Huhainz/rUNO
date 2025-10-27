#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdlib>   // For randomizing
#include <ctime>     // For randomizing
#include <windows.h> // Terminal colors

using namespace std;

enum ColorPrint {red, yellow, green, blue, wilds};
const int ColorPrint_len = 4; // Length without wilds
enum NumberPrint{zero, one, two, three, four, five, six, seven, eight, nine, plustwo, skip, reverse, wild, plusfour};
const int NumberPrint_len = 13; // Length without wilds

// Deck cards
const int NormalN = 2;
const int DrawN = 2;
const int ReverseN = 2;
const int ZeroN = 1;
const int SkipN = 2;

const int ColorN = ZeroN + NormalN + DrawN + ReverseN + SkipN;

const int WildsN = 4;

class Card
{
    public:
        ColorPrint Color;
        NumberPrint Number;
        string Display;
};


class DeckManager 
{
    public:
        map<pair<ColorPrint, NumberPrint>, int> deckCount;
        map<pair<ColorPrint, NumberPrint>, int> maxCount;
        DeckManager()
        {
            for (int c=0; c < ColorPrint_len; c++)
            {
                ColorPrint color = static_cast<ColorPrint>(c);
                maxCount[{color,zero}] = ZeroN;
                for (int n = one; n <= nine; n++)
                    maxCount[{color,static_cast<NumberPrint>(n)}] = NormalN;
                maxCount[{color, plustwo}] = DrawN;
                maxCount[{color, skip}] = SkipN;
                maxCount[{color, NumberPrint::reverse}] = ReverseN;
            }
            maxCount[{wilds, wild}] = WildsN;
            maxCount[{wilds, plusfour}] = WildsN;
            for (auto &init : maxCount)
                deckCount[init.first] = 0;
        }
        bool canDraw (ColorPrint c, NumberPrint n)
        {
            return deckCount[{c,n}] < maxCount[{c,n}];
        }
        int DeckCounter()
        {
            int count = 0;
            for (int i = 0;  i < ColorPrint_len; i++)
            {
                ColorPrint color = static_cast<ColorPrint>(i);
                for (int z = 0; z < NumberPrint_len; z++)
                {
                    NumberPrint number = static_cast<NumberPrint>(z);
                    count = count + deckCount[{color,number}];           
                }
            }
            ColorPrint color = wilds;
            for (int w = 12; w < 15; w++)
            {
                NumberPrint number = static_cast<NumberPrint>(w);
                count = count + deckCount[{color,number}];
            }
            return count;  
        }
};

// Give cards functions
void GiveRandomCard (vector<Card> &Hand, DeckManager &Deck)
{
    Card tempCard;
    int indexNumber = rand() % NumberPrint_len;
    int indexColor = rand() % ColorPrint_len;
    tempCard.Number = static_cast<NumberPrint>(indexNumber);
    tempCard.Color =  static_cast<ColorPrint>(indexColor);
    if (Deck.canDraw(tempCard.Color, tempCard.Number))
    {
        Hand.push_back(tempCard);
        Deck.deckCount[{tempCard.Color, tempCard.Number}]++;
    }
    else
        GiveRandomCard(Hand, Deck);
}

void GiveRandomWildCard (vector<Card> &Hand, DeckManager &Deck)
{
    Card tempWildCard;
    int indexWild = rand() % 2; // 0 = wild, 1 = +4
    tempWildCard.Color = wilds;
    if (indexWild == 0 && Deck.canDraw(wilds, wild))
    {
        tempWildCard.Number = wild;
        Hand.push_back(tempWildCard);
        Deck.deckCount[{tempWildCard.Color, tempWildCard.Number}]++;
    }
    else if (indexWild == 1 && Deck.canDraw(wilds, plusfour))
    {    
        tempWildCard.Number = plusfour;
        Hand.push_back(tempWildCard);
        Deck.deckCount[{tempWildCard.Color, tempWildCard.Number}]++;
    }
    else
    {
        GiveRandomCard(Hand, Deck);
        return;

    }
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
        case wilds: SetConsoleTextAttribute(hConsole,FOREGROUND_RED); cout << "W" ;
                   SetConsoleTextAttribute(hConsole,14); cout << "i" ;
                   SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); cout << "l";
                   SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE); cout << "d "; break;
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
        case plustwo : cout << "+2" << endl; break;
        case skip : cout << "skip" << endl; break;
        case NumberPrint::reverse : cout << "reverse" << endl; break;
        case wild : cout << "wild" << endl; break;
        case plusfour : cout << "+4" << endl; break;
    }
    SetConsoleTextAttribute(hConsole,0);
}

int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Card Table;
    PutRandomCard(Table);
    while (size(PlayerHand) < 90)
    {
        int randN = rand() % 2;
        if(randN == 1)
        {
            GiveRandomWildCard(PlayerHand, Deck);            
            DisplayCard(PlayerHand, size(PlayerHand)-1);
        }
        else
        {
            GiveRandomCard(PlayerHand, Deck);
            DisplayCard(PlayerHand, size(PlayerHand)-1);
        }
    }
    cout << Deck.DeckCounter() << endl;





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