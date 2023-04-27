#include "MainMenu.h"
#include <fstream>

using namespace std;

MainMenu::MainMenu()
{
    character = new Character();
    background = new Background();
    board = new NotiBoard();
    instruction = new Instruction();

    for (int i=0; i<buttonNum; i++)
    {
        Button *b = new Button();
        LTexture *tb = new LTexture();
        button.push_back(b);
        textButton.push_back(tb);
    }
}

MainMenu::~MainMenu()
{
    for (Button *&b : button)
        delete b;

    for (LTexture *&t : textButton)
        delete t;

    delete character;
    character = NULL;
    delete background;
    background = NULL;
    delete board;
    board = NULL;
    delete instruction;
    instruction = NULL;
}

bool MainMenu::loadMedia(SDL_Renderer *gRenderer)
{
    bool success = true;

    for (int i=0; i<buttonNum-3; i++)
    {
        if (!button[i]->loadFromFile("asset/image/button.png", gRenderer))
        {
            success = false;
        }
    }

    for (int i=buttonNum-3; i<buttonNum; i++)
    {
        if (!button[i]->loadFromFile("asset/image/levelButton.png", gRenderer))
        {
            success = false;
        }
    }

    if (!background->loadFromFile("asset/image/MenuBackground.png", gRenderer))
        success = false;

    if (!board->loadMedia(gRenderer))
        success = false;

    if (!instruction->loadMedia(gRenderer))
        success = false;

    ifstream file("asset/font/buttonText.txt");

    for (int i=0; i<buttonNum; i++)
    {
        string line;
        getline(file, line);

        if (!textButton[i]->loadFromRenderedText(line, gRenderer))
        {
            return false;
        }
    }
    file.close();

    if (!character->loadFromFile("asset/image/character.png", gRenderer))
    {
        success = false;
    }

    return success;
}

void MainMenu::render(SDL_Renderer *gRenderer)
{
    //clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    if (button[HELP_BUTTON]->isPushed)
    {
        instruction->render(gRenderer);
    }
    else
    {
        //render background
        background->render(background->scrollingOffset, 0, gRenderer);
        background->render(background->scrollingOffset + SCREEN_WIDTH, 0, gRenderer);

        int coorX, coorY;
        SDL_GetMouseState(&coorX, &coorY);
        for (int i=0; i<buttonNum; i++)
        {
            if (isInBound(coorX, coorY, button[i]->x, button[i]->y, button[i]))
            {
                button[i]->setColor(230, 190, 100);
            }
            else
            {
                button[i]->setColor(255, 255, 255);
            }
        }

        //render button
        for (int i=0; i<buttonNum-3; i++)
        {
            button[i]->x = 400;
            button[i]->y = 80 + 95*i;
            button[i]->render(button[i]->x, button[i]->y, gRenderer);

            textButton[i]->x = button[i]->x + button[i]->getWidth()/2 - textButton[i]->getWidth()/2;
            textButton[i]->y = button[i]->y + button[i]->getHeight()/2 - textButton[i]->getHeight()/2 - 5;
            textButton[i]->render(textButton[i]->x, textButton[i]->y, gRenderer);
        }

        //render character
        character->render(character->x, character->y, gRenderer, character->currentClip, character->flipType, 1.5);

        if (button[LEVEL_BUTTON]->isPushed)
        {
            board->renderBoard(character->status, gRenderer);

            for (int i=buttonNum-3; i<buttonNum; i++)
            {
                button[i]->x = SCREEN_WIDTH/2 - button[i]->getWidth()/2;
                button[i]->y = 120 + 80*(i-3);

                button[i]->render(button[i]->x, button[i]->y, gRenderer);

                textButton[i]->x = button[i]->x + button[i]->getWidth()/2 - textButton[i]->getWidth()/2;
                textButton[i]->y = button[i]->y + button[i]->getHeight()/2 - textButton[i]->getHeight()/2;
                textButton[i]->render(textButton[i]->x, textButton[i]->y, gRenderer);
            }
        }
    }

    //update screen
    SDL_RenderPresent(gRenderer);
}

void MainMenu::resetMenu()
{
    Instruction *p = new Instruction();
    p = instruction;
    instruction = NULL;
    delete p;
    p = NULL;
    instruction = new Instruction();
    board->setNotiBoard();
    character->x = 120;
    character->y = 250;
    character->flipType = SDL_FLIP_NONE;
    character->status = IN_GAME;

    for (int i=0; i<buttonNum; i++)
    {
        button[i]->isPushed = false;
    }
}

void MainMenu::setMenu(int &mode, SDL_Event e, bool &quit, SDL_Renderer *gRenderer)
{
    if (loadMedia(gRenderer))
    {
        while (mode == MENU and !quit)
        {
            while(SDL_PollEvent(&e) != 0)
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int coorX, coorY;
                    SDL_GetMouseState(&coorX, &coorY);

                    if (button[LEVEL_BUTTON]->isPushed)
                    {
                        for (int i=EASY_BUTTON; i<=HARD_BUTTON; i++)
                        {
                            if (isInBound(coorX, coorY, button[i]->x, button[i]->y, button[i]))
                            {
                                mode = i-2;
                            }
                        }
                    }

                    else
                    {
                        if (isInBound(coorX, coorY, button[START_BUTTON]->x, button[START_BUTTON]->y, button[START_BUTTON]))
                        {
                            mode = EASY;
                        }
                        else if (isInBound(coorX, coorY, button[LEVEL_BUTTON]->x, button[LEVEL_BUTTON]->y, button[LEVEL_BUTTON]))
                        {
                            button[LEVEL_BUTTON]->isPushed = true;
                        }
                        else if (isInBound(coorX, coorY, button[HELP_BUTTON]->x, button[HELP_BUTTON]->y, button[HELP_BUTTON]))
                        {
                            button[HELP_BUTTON]->isPushed = true;
                            instruction->reset();
                        }
                    }
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    if (e.key.keysym.sym == SDLK_ESCAPE)
                    {
                        if (button[LEVEL_BUTTON]->isPushed)
                        {
                            button[LEVEL_BUTTON]->isPushed = false;
                        }
                        else if (button[HELP_BUTTON]->isPushed)
                        {
                            button[HELP_BUTTON]->isPushed = false;
                        }
                    }
                }
                else if (e.type == SDL_MOUSEWHEEL)
                {
                    if (button[HELP_BUTTON]->isPushed)
                    {
                        instruction->popUp(e, gRenderer);
                    }
                }

                else if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
            background->scrollBackground();
            character->handleAnimation();
            render(gRenderer);
        }
    }
}

