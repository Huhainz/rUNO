#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum ColorPrint {black, white};
enum NumberPrint{zero, one, two, three, four, five, six, seven, eight, nine};

const int numbers[10] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
const string colors[2] = {"black" , "white"};
class Card
{
    public:
        ColorPrint Color;
        NumberPrint Number;
        string Display;
};

void GiveRandomCard (vector<Card> &Hand)
{
    Card tempCard;
    int indexNumber = rand() % 10;
    int indexColor = rand() % 2;
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
int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    Card Table;
    PutRandomCard(Table);
    GiveRandomCard(PlayerHand);

    cout << "Card on the table: ";
    switch(PlayerHand[0].Color)
    {
        case black: cout << "Black "; break;
        case white: cout << "White "; break;
    }
    switch(PlayerHand[0].Number)
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