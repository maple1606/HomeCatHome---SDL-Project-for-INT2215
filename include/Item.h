#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include "LTexture.h"

class Item: public LTexture
{
public:
    Item();
    ~Item();

    int xPrev, yPrev;
    bool itemMove;
    bool isDestination;
    bool isDangerous;
    bool isBarrier;
    bool isHidden;
    bool isMagic;
    bool isKey;
    Uint8 a;
    bool fade;
};
#endif // ITEM_H_INCLUDED
