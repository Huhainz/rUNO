#include "uno-main.h"

int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Table TableManager;
    Card Table;
    PutRandomCard(Table, Deck);
    DisplayCard(Table);
    TableManager.GiveInitialCards(PlayerHand, Deck);
    DisplayAllCards(PlayerHand);
    TableManager.PlayCard(PlayerHand, PlayerHand, Table, Deck);
    DisplayAllCards(PlayerHand);
    return 0;
}