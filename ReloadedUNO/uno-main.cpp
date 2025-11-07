#include <windows.h>
#include "uno-main.h"


// Deck cards
const int NormalN = 2;
const int DrawN = 2;
const int ReverseN = 2;
const int ZeroN = 1;
const int SkipN = 2;

const int ColorN = ZeroN + NormalN + DrawN + ReverseN + SkipN;
const int SumOfColor = ColorN * 13;

const int WildsN = 4;
const int SumOfWilds = WildsN * 2;

const int Sum = SumOfColor + SumOfWilds;


DeckManager::DeckManager()
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

bool DeckManager::canDraw (ColorPrint c, NumberPrint n)
{
    return deckCount[{c,n}] < maxCount[{c,n}];
}
int DeckManager::NormalCardCounter()
{
    int NormalCount = 0;
    for (int i = 0;  i < ColorPrint_len; i++)
    {
        ColorPrint color = static_cast<ColorPrint>(i);
        for (int z = 0; z < NumberPrint_len; z++)
        {
            NumberPrint number = static_cast<NumberPrint>(z);
            NormalCount = NormalCount+ deckCount[{color,number}];           
        }
    }
    return NormalCount;  
}
        
int DeckManager::WildsCounter()
{
    int wildscount = 0;
    ColorPrint color = wilds;
    for (int w = 12; w < 15; w++)
    {
        NumberPrint number = static_cast<NumberPrint>(w);
        wildscount = wildscount + deckCount[{color,number}];
    }
    return wildscount;
}

int DeckManager::DeckCounter()
{
    return NormalCardCounter() + WildsCounter();
}

Table::Table(){}

int Table::PlayCardReq(vector<Card> PlayerHand)
{
    int index;
    cout << "Place a card: ";
    cin >> index;
    while (index > (sizeof(PlayerHand) - 1))
    {
        cout << "Index invalid." << endl << "Place a card: ";
        cin >> index;
    }
    return index;
}

bool Table::CanPlace(Card topCard, Card PlacerCard)
{
    return (topCard.Color == (wilds || PlacerCard.Color) || topCard.Number == PlacerCard.Number);
}

void Table::TakeEffect(vector<Card>& PlacerHand, int index, vector<Card>& targetHand, Card &TopCard, DeckManager &Deck)
{
    TopCard = PlacerHand[index];
    PlacerHand.erase(PlacerHand.begin() + index);
    if (TopCard.Color == wilds)
    {
        bool ColorValid = false;
        string wildcolor;
        ColorPrint WildColor;
        cout << "Choose a color: ";
        while (ColorValid == false)
        {
            cin >> wildcolor;
            if (wildcolor == "yellow")
            {
                WildColor = yellow;
                ColorValid = true;
            }
            else if (wildcolor == "blue")
            {
                WildColor = blue;
                ColorValid = true;
            }
            else if (wildcolor == "red")
            {
                WildColor = red;
                ColorValid = true;
            }
            else if (wildcolor == "green")
            {
                WildColor = green;
                ColorValid = true;
            }
            else
                cout << "Color invalid." << endl << "Choose a color: ";
        }
        if (TopCard.Number == plusfour)
        {
            for (int i = 0; i < 4; i++)
            {
                GiveRandomCard(targetHand, Deck);
            }
        }
    }
    else if(TopCard.Number == plustwo)
    {
        for (int y = 0; y < 2; y++)
        {
            GiveRandomCard(targetHand, Deck);
        }
    }
    // Reverse, block and skip not added yet in singleplayer (MISSING)
}

void Table::PlayCard(vector<Card> &PlayerHand, vector<Card>& targetHand, Card &TopCard, DeckManager &Deck)
{
    int index;
    bool valid = false;
    while (valid == false)
    {
        index = PlayCardReq(PlayerHand);
        valid = CanPlace(TopCard, PlayerHand[index]);
        if (valid == true)
        {
            TakeEffect(PlayerHand, index, targetHand, TopCard, Deck);
        }
        else
            cout << "Card can't be placed";
    }
  
}

// Give cards functions

void GiveRandomNormalCard (vector<Card> &Hand, DeckManager &Deck)
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
    else if (Deck.NormalCardCounter() != SumOfColor)
        GiveRandomNormalCard(Hand, Deck);
    else if (Deck.WildsCounter() != SumOfWilds)
    {
        GiveRandomWildCard(Hand, Deck);
        return;
    }
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
    else if(Deck.NormalCardCounter() != SumOfColor)
    {
        GiveRandomNormalCard(Hand, Deck);
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

void GiveRandomCard(vector<Card> &Hand, DeckManager &Deck)
{
        int randN = rand() % 2;
        if(randN == 1)
        {
            GiveRandomWildCard(Hand, Deck);            
        }
        else
        {
            GiveRandomNormalCard(Hand, Deck);
        }
}