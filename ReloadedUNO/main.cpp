#include "uno-main.h"

int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Table TableManager;
    Card Table;
    PutRandomCard(Table, Deck);
    cout << "Card on the Table:" << endl << "  ";
    ColorToString(Table);
    DisplayCard(Table);
    TableManager.GiveInitialCards(PlayerHand, Deck);
    for (int i = 0; i < PlayerHand.size(); i++)
    {
        ColorToString(PlayerHand[i]);
    }
    cout << endl << "Player's cards:" << endl;
    DisplayAllCards(PlayerHand);
    TableManager.PlayCard(PlayerHand, PlayerHand, Table, Deck);
    cout << "Card on the Table:" << endl << "  ";
    ColorToString(Table);
    DisplayCard(Table);
    cout << endl << "Player's cards:" << endl;
    DisplayAllCards(PlayerHand);
    return 0;
}