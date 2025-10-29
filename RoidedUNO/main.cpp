#include "uno-main.h"


int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Card Table;
    PutRandomCard(Table);
    while (size(PlayerHand) < 107)
    {
        GiveRandomCard(PlayerHand, Deck);       
        DisplayCard(PlayerHand, size(PlayerHand)-1);
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