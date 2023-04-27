#include "Item.h"

using namespace std;

Item::Item()
{
    itemMove = false;
    isDestination = false;
    isDangerous = false;
    isBarrier = false;
    isHidden = false;
    isMagic = false;
    isKey = false;
    a = 255;
    fade = false;
}

Item::~Item()
{
    free();
}
