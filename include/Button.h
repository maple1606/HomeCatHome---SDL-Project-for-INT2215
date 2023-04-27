#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include "LTexture.h"
#include "constant.h"

class Button: public LTexture
{
public:
    Button();
    ~Button();
    bool isPushed;

protected:

private:

};

#endif // BUTTON_H_INCLUDED
