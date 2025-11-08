#ifndef UNO_MAIN_H
#define UNO_MAIN_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

enum ColorPrint {red, yellow, green, blue, wilds};
const int ColorPrint_len = 4; // Length without wilds
enum NumberPrint{zero, one, two, three, four, five, six, seven, eight, nine, plustwo, skip, reverse, wild, plusfour};
const int NumberPrint_len = 13; // Length without wilds


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
        DeckManager();
        bool canDraw (ColorPrint c, NumberPrint n);
        int NormalCardCounter();
        int WildsCounter();
        int DeckCounter();
        void DeckReset();
};

class Table
{
    public:
        Card topCard;
        Table();
        int PlayCardReq(vector<Card> PlayerHand);
        bool CanPlace(Card topCard, Card PlacerHand);
        void TakeEffect(vector<Card> &PlacerHand, int index, vector<Card> &targetHand, Card &TopCard, DeckManager &Deck);
        void PlayCard(vector<Card> &PlayerHand, vector<Card>& targetHand, Card &TopCard, DeckManager &Deck);
};



// Give cards functions

void GiveRandomNormalCard (vector<Card> &Hand, DeckManager &Deck);
void GiveRandomWildCard (vector<Card> &Hand, DeckManager &Deck);
void PutRandomCard(Card &Table, DeckManager &Deck);
void DisplayCard(vector<Card> PlayerHand, int CardIndex);
void GiveRandomCard(vector<Card> &Hand, DeckManager &Deck);


#endif