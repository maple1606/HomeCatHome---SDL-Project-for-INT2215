#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
    for (Puzzle *&p : puzzle)
        delete p;

    for (Item *&i : item)
        delete i;

    delete character;
    character = NULL;
    delete background;
    background = NULL;
    delete board;
    board = NULL;
    delete lock;
    lock = NULL;
}

void Level::setup(const int itemNum, const int mode)
{
    character = new Character();
    background = new Background();
    lock = new LTexture();

    board = new NotiBoard();
    board->setNotiBoard();

    for (int i=0; i<frameNum; i++)
    {
        Puzzle *p = new Puzzle();
        puzzle.push_back(p);
    }
    for (int i=0; i<itemNum; i++)
    {
        Item *t = new Item();
        item.push_back(t);
    }

    initMode = mode;
}

void Level::render(int &mode, const int itemNum, SDL_Renderer *gRenderer)
{
    //clear screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //render background
    background->render(0, 0, gRenderer);

    //render lock
    for (int i=0; i<frameNum-1; i++)
    {
        lock->setAlpha(20);
        if (puzzle[i]->isLocked) lock->render(puzzle[i]->x, puzzle[i]->y, gRenderer);
    }

    //render item
    for (int i=0; i<itemNum; i++)
    {
        if (!item[i]->isHidden)
            item[i]->render(item[i]->x, item[i]->y, gRenderer);
    }

    //render puzzle
    for (int i=0; i<frameNum-1; i++)
    {
        puzzle[i]->render(puzzle[i]->x, puzzle[i]->y, gRenderer);
    }

    int xCoor = 0, yCoor = 0;
    SDL_GetMouseState(&xCoor, &yCoor);

    //render the selected platform
    for (int i=0; i<frameNum-1; i++)
    {
        if (puzzle[i]->push)
        {
            puzzle[i]->render(puzzle[i]->x, puzzle[i]->y, gRenderer);
        }
        if (isInBound(xCoor, yCoor, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and !puzzle[i]->isLocked)
        {
            puzzle[frameNum-1]->render(puzzle[i]->x, puzzle[i]->y, gRenderer);
        }
    }

    //render character
    character->render(character->x, character->y, gRenderer, character->currentClip, character->flipType);

    if (character->status != IN_GAME)
    {
        if (mode == initMode)
        {
            board->renderBoard(character->status, gRenderer);
            board->renderStatus(mode, character->status, gRenderer);
        }
    }

    //update screen
    SDL_RenderPresent(gRenderer);
}

void Level::handleEvent(const int itemNum, SDL_Event e)
{
    if (character->status == IN_GAME)
    {
        for (int i=0; i<frameNum-1; i++)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (isInBound(e.button.x, e.button.y, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and !swapOn and !puzzle[i]->isLocked)
                {
                    puzzle[i]->push = true;
                    character->freeze = true;
                    puzzle[i]->xPrev = puzzle[i]->x;
                    puzzle[i]->yPrev = puzzle[i]->y;
                    if (((isInBound(character->x+character->getWidth()/4, character->y, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and character->flipType == SDL_FLIP_NONE)
                            or (isInBound(character->x, character->y, puzzle[i]->x, puzzle[i]->y, puzzle[i]) and character->flipType == SDL_FLIP_HORIZONTAL)) and !character->charMove)
                    {
                        character->xPrev = character->x;
                        character->yPrev = character->y;
                        character->charMove = true;
                    }

                    for (int t=0; t<itemNum; t++)
                    {
                        if (isInBound(item[t]->x, item[t]->y, puzzle[i]->x, puzzle[i]->y, puzzle[i]))
                        {
                            item[t]->xPrev = item[t]->x;
                            item[t]->yPrev = item[t]->y;
                            item[t]->itemMove = true;
                        }
                    }
                }
            }

            if (puzzle[i]->push)
            {
                if (e.type == SDL_MOUSEBUTTONUP)
                {
                    puzzle[i]->push = false;
                    swapOn = true;

                    int coorX, coorY;
                    SDL_GetMouseState(&coorX, &coorY);

                    if (coorX < 0  or coorY < 0 or coorX > SCREEN_WIDTH or coorY > SCREEN_HEIGHT)
                    {
                        swapOn = false;
                        character->freeze = false;
                        puzzle[i]->x = puzzle[i]->xPrev;
                        puzzle[i]->y = puzzle[i]->yPrev;
                        if (character->charMove)
                        {
                            character->x = character->xPrev;
                            character->y = character->yPrev;
                            character->charMove = false;
                        }

                        for (int t=0; t<itemNum; t++)
                        {
                            if (item[t]->itemMove)
                            {
                                item[t]->x = item[t]->xPrev;
                                item[t]->y = item[t]->yPrev;
                                item[t]->itemMove = false;
                            }
                        }

                    }
                }

                else if (e.type == SDL_MOUSEMOTION)
                {
                    int moveX = e.motion.xrel;
                    int moveY = e.motion.yrel;

                    puzzle[i]->x += moveX;
                    puzzle[i]->y += moveY;

                    if (character->charMove)
                    {
                        character->x += moveX;
                        character->y += moveY;
                    }

                    for (int t=0; t<itemNum; t++)
                    {
                        if (item[t]->itemMove)
                        {
                            item[t]->x += moveX;
                            item[t]->y += moveY;
                        }
                    }
                }
            }

            if (swapOn)
            {
                for (int j=0; j<frameNum-1; j++)
                {
                    if (i == j)
                    {
                        if (isInBound(e.button.x, e.button.y, puzzle[i]->xPrev, puzzle[i]->yPrev, puzzle[i]) and !puzzle[i]->push)
                        {
                            swapOn = false;
                            character->freeze = false;
                            puzzle[i]->x = puzzle[i]->xPrev;
                            puzzle[i]->y = puzzle[i]->yPrev;
                            if (character->charMove)
                            {
                                character->x = character->xPrev;
                                character->y = character->yPrev;
                                character->charMove = false;
                            }

                            for (int t=0; t<itemNum; t++)
                            {
                                if (item[t]->itemMove)
                                {
                                    item[t]->x = item[t]->xPrev;
                                    item[t]->y = item[t]->yPrev;
                                    item[t]->itemMove = false;
                                }
                            }

                        }
                    }

                    else if (isInBound(e.button.x, e.button.y, puzzle[j]->x, puzzle[j]->y, puzzle[j]) and !puzzle[i]->push and !puzzle[j]->isLocked)
                    {
                        if (character->charMove)
                        {
                            character->x = character->xPrev + (puzzle[j]->x - puzzle[i]->xPrev);
                            character->y = character->yPrev + (puzzle[j]->y - puzzle[i]->yPrev);
                            character->charMove = false;
                        }


                        else if (!character->charMove and ((isInBound(character->x+character->getWidth()/4, character->y, puzzle[j]->x, puzzle[j]->y, puzzle[j]) and character->flipType == SDL_FLIP_NONE)
                                                           or (isInBound(character->x, character->y, puzzle[j]->x, puzzle[j]->y, puzzle[j]) and character->flipType == SDL_FLIP_HORIZONTAL)))
                        {
                            character->x += (puzzle[i]->xPrev - puzzle[j]->x);
                            character->y += (puzzle[i]->yPrev - puzzle[j]->y);
                        }

                        for (int t=0; t<itemNum; t++)
                        {
                            if (item[t]->itemMove)
                            {
                                item[t]->x = item[t]->xPrev + (puzzle[j]->x - puzzle[i]->xPrev);
                                item[t]->y = item[t]->yPrev + (puzzle[j]->y - puzzle[i]->yPrev);
                                item[t]->itemMove = false;
                            }
                            else if (!item[t]->itemMove and (isInBound(item[t]->x, item[t]->y, puzzle[j]->x, puzzle[j]->y, puzzle[j])))
                            {
                                item[t]->x += (puzzle[i]->xPrev - puzzle[j]->x);
                                item[t]->y += (puzzle[i]->yPrev - puzzle[j]->y);
                            }
                        }

                        puzzle[i]->x = puzzle[j]->x;
                        puzzle[i]->y = puzzle[j]->y;
                        puzzle[j]->x = puzzle[i]->xPrev;
                        puzzle[j]->y = puzzle[i]->yPrev;
                        swapOn = false;
                        character->freeze = false;
                        break;
                    }

                    else if (isInBound(e.button.x, e.button.y, puzzle[j]->x, puzzle[j]->y, puzzle[j]) and !puzzle[i]->push and puzzle[j]->isLocked)
                    {
                        swapOn = false;
                        puzzle[i]->x = puzzle[i]->xPrev;
                        puzzle[i]->y = puzzle[i]->yPrev;

                        character->freeze = false;
                        if (character->charMove)
                        {
                            character->x = character->xPrev;
                            character->y = character->yPrev;
                            character->charMove = false;
                        }

                        for (int t=0; t<itemNum; t++)
                        {
                            if (item[t]->itemMove)
                            {
                                item[t]->x = item[t]->xPrev;
                                item[t]->y = item[t]->yPrev;
                                item[t]->itemMove = false;
                            }
                        }
                    }

                    else if (!isInBound(e.button.x, e.button.y, puzzle[j]->x, puzzle[j]->y, puzzle[j]) and !puzzle[i]->push)
                    {
                        swapOn = false;
                        character->freeze = false;
                        puzzle[i]->x = puzzle[i]->xPrev;
                        puzzle[i]->y = puzzle[i]->yPrev;
                    }
                }
            }
            if (puzzle[i]->push) break;
        }
    }
}
