#include <windows.h>
#include "uno-main.h"


// Deck cards
const int NormalN = 2 * 9;
const int DrawN = 2;
const int ReverseN = 2;
const int ZeroN = 1;
const int SkipN = 2;

const int ColorN = ZeroN + NormalN + DrawN + ReverseN + SkipN;
const int SumOfColor = ColorN * 4;

const int WildsN = 4;
int SumOfWilds = WildsN * 2;

int Sum = SumOfColor + SumOfWilds;


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

void DeckManager::DeckReset()
{
    for (auto &kv : deckCount)
        kv.second = 0;
    cout << Sum << endl;
    cout << "Deck reshuffled!" << endl;
}

Table::Table(){}

void Table::GiveInitialCards(vector<Card> &PlayerHand, DeckManager &Deck)
{
    for (int i = 0; i < 7; i++)
        GiveRandomCard(PlayerHand, Deck);
}

int Table::PlayCardReq(vector<Card> PlayerHand)
{
    int index;
    while (true)
    {
        cout << "Place a card: ";
        if (cin >> index)
        {
            if (index < (PlayerHand.size()))
            {
                return index;
                break;
            }
            cout << "Invalid index. Try again." << endl;
        }
        else
        {
            cin.clear();    // clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    // flush bad input
            cout << "Please enter an index, not text." << endl;
        }
    }
}

bool Table::CanPlace(Card topCard, Card PlacerCard)
{
    if (topCard.Color == wilds)
    {
        return true;
    }
    else if (topCard.Color == PlacerCard.Color)
    {
        return true;
    }
    else if (topCard.Number == PlacerCard.Number)
    {
        return true;
    }
    else 
        return false;
}

void Table::TakeEffect(vector<Card> &PlacerHand, int index, vector<Card> &targetHand, Card &TopCard, DeckManager &Deck)
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

void Table::PlayCard(vector<Card> &PlayerHand, vector<Card> &targetHand, Card &TopCard, DeckManager &Deck)
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
            break;
        }
        else
        {
            cout << "Card can't be placed" << endl;
            //break;
        }
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

void PutRandomCard(Card &Table, DeckManager &Deck)
{
    int indexNumber = rand() % 10;
    // Only put normal cards first
    int indexColor = rand() % ColorPrint_len;
    Table.Number = static_cast<NumberPrint>(indexNumber);
    Table.Color = static_cast<ColorPrint>(indexColor);
    Deck.deckCount[{Table.Color, Table.Number}]++;
}

void GiveRandomCard(vector<Card> &Hand, DeckManager &Deck)
{
    if (Deck.DeckCounter() == Sum)
    {
        Deck.DeckReset();
    }
    // 10% to get a wildcard
    int randN = rand() % 10;
    if(randN == 1)
    {
        GiveRandomWildCard(Hand, Deck);            
    }
    else
    {
        GiveRandomNormalCard(Hand, Deck);
    }
}

// Display functions 

void DisplayCard(Card Card)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(Card.Color)
    {
        case red: SetConsoleTextAttribute(hConsole,FOREGROUND_RED); cout << Card.Display; break;
        case yellow: SetConsoleTextAttribute(hConsole,14); cout << Card.Display; break;
        case green: SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); cout << Card.Display; break;
        case blue: SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE); cout << Card.Display; break;
        // case wilds: SetConsoleTextAttribute(hConsole,FOREGROUND_RED); cout << "W" ;
        //            SetConsoleTextAttribute(hConsole,14); cout << "i" ;
        //            SetConsoleTextAttribute(hConsole,FOREGROUND_GREEN); cout << "l";
        //            SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE); cout << "d "; break;
        case wilds: SetConsoleTextAttribute(hConsole,11); cout<< Card.Display; break; 
    }            
    // switch(Card.Number)
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
    //     case plustwo : cout << "+2" << endl; break;
    //     case skip : cout << "skip" << endl; break;
    //     case NumberPrint::reverse : cout << "reverse" << endl; break;
    //     case wild : cout << "wild" << endl; break;
    //     case plusfour : cout << "+4" << endl; break;
    // }
    SetConsoleTextAttribute(hConsole,0);
}

void DisplayAllCards(vector<Card> Hand)
{
    for (int index = 0; index < Hand.size(); index++)
    {
        cout << index << ":";
        DisplayCard(Hand[index]);
        cout << "\n";
    }
}

// Display Helpers

string NumberToString(Card Card)
{
    switch(Card.Number)
    {
        case zero : return "0 ";
        case one : return "1 ";
        case two : return "2 ";
        case three : return "3 ";
        case four : return "4 ";
        case five : return "5 ";
        case six : return "6 ";
        case seven : return "7 ";
        case eight : return "8 ";
        case nine : return "9 ";
        case plustwo : return "+2";
        case skip : return "⛔";
        case NumberPrint::reverse : return "🔁";
        case wild : return "🌈";
        case plusfour : return "+4";
        default: return "";
    }    
}

void ColorToString(Card &Card)
{
    switch(Card.Color)
    {
        case red: Card.Display = "+---------+\n  |         |\n  |   Red   |\n  |   "+ NumberToString(Card)+"    |\n  |         |\n  +---------+ "; break;
        case yellow: Card.Display = "+---------+\n  |         |\n  | Yellow  |\n  |   "+ NumberToString(Card)+"    |\n  |         |\n  +---------+ "; break;
        case green: Card.Display = "+---------+\n  |         |\n  | Green   |\n  |   "+ NumberToString(Card)+"    |\n  |         |\n  +---------+ "; break;
        case blue: Card.Display = "+---------+\n  |         |\n  |  Blue   |\n  |   "+ NumberToString(Card)+"    |\n  |         |\n  +---------+ "; break; 
        case wilds: Card.Display = "+---------+\n  |         |\n  |  Wild   |\n  |   "+ NumberToString(Card)+"    |\n  |         |\n  +---------+ "; break;
    } 
}