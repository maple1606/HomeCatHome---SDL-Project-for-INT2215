#include "Instruction.h"
#include "constant.h"
#include <fstream>

Instruction::Instruction()
{
    board = new LTexture();
}

Instruction::~Instruction()
{
    delete board;
    board = NULL;
    for (LTexture *&t : txt)
        delete t;
}

bool Instruction::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    if (!board->loadFromFile("asset/image/instructionBack.png", gRenderer))
        success = false;

    ifstream file("asset/font/instruction.txt");

    while (!file.eof())
    {
        LTexture *t = new LTexture();
        txt.push_back(t);

        string line;
        getline(file, line);

        int fontSize = 18;

        if (!txt.back()->loadFromRenderedText(line, gRenderer, fontSize, "asset/font/Alata.ttf"))
        {
            success = false;
        }
    }

    file.close();

    LTexture *t = new LTexture();
    txt.push_back(t);
    string line = "Scroll for more";
    if (!txt.back()->loadFromRenderedText(line, gRenderer, 15, "asset/font/Asap.ttf"))
    {
        success = false;
    }

    LTexture *tp = new LTexture();
    txt.push_back(tp);
    line = "Press ESC to return";
    if (!txt.back()->loadFromRenderedText(line, gRenderer, 15, "asset/font/Asap.ttf"))
    {
        success = false;
    }

    return success;
}

void Instruction::reset()
{
    int _y = 0;
    for (LTexture *&t : txt)
    {
        t->x = 300;
        t->y = 50 + 40 * (_y++);
    }
    txt[(int)txt.size()-2]->x = 425;
    txt[(int)txt.size()-2]->y = 355;
    txt.back()->x = 414;
    txt.back()->y = 355 + 30;
    fade = false;
    a = 255;
}

void Instruction::render(SDL_Renderer *gRenderer)
{
    board->render(0, 0, gRenderer);
    for (LTexture *&t : txt)
    {
        if (t->y < 50)
            continue;
        if (t->y > 300)
            continue;
        t->render(t->x, t->y, gRenderer);
    }

    txt.back()->blink_blink(a, fade);
    txt[(int)txt.size()-2]->setAlpha(a);
    txt[(int)txt.size()-2]->render(txt[(int)txt.size()-2]->x, txt[(int)txt.size()-2]->y, gRenderer);
    txt.back()->setAlpha(a);
    txt.back()->render(txt.back()->x, txt.back()->y, gRenderer);
}

void Instruction::popUp(SDL_Event e, SDL_Renderer *gRenderer)
{
    if (e.type == SDL_MOUSEWHEEL)
    {
        int yWheel = 10*e.wheel.y;
        if (!((txt.front()->y >= 300 and yWheel > 0) or (txt[(int)txt.size()-3]->y <= 50 and yWheel < 0)))
        {
            for (int i=0; i<(int)txt.size()-2; i++)
            {
                txt[i]->y += yWheel;
            }
        }
    }
}
