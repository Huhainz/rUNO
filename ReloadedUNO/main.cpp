#include "uno-main.h"


int main() 
{
    srand(time(nullptr));
    vector<Card> PlayerHand;
    DeckManager Deck;
    Card Table;
    PutRandomCard(Table);
    GiveRandomCard(PlayerHand, Deck);
    // NOT FINISHED
    return 0;
}