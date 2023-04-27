#include "Button.h"

using namespace std;

Button::Button()
{
    isPushed = false;
    x = SCREEN_WIDTH/2;
    y = SCREEN_HEIGHT/2;
}

Button::~Button()
{
    free();
}
