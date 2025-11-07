#include "uno-main.h"


int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Table TableManager;
    Card Table;
    Table.Color = yellow;
    Table.Number = two;
    // PutRandomCard to be fixed
    for (int i = 0; i < 7; i++)
    {
        GiveRandomCard(PlayerHand, Deck);
        DisplayCard(PlayerHand, i);
    }
    TableManager.PlayCard(PlayerHand, PlayerHand, Table, Deck);
    for (int y = 0; y < PlayerHand.size() ; y++)
    {
        DisplayCard(PlayerHand, y);
    }
    return 0;
}