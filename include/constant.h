#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

#include <string>

using namespace std;

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 500;
const string WINDOW_TITLE = "meoconlonton";
const string defaultFont = "asset/font/SigmarOne.ttf";

const int frameNum = 7;
const int column = 3;
const int row = 2;
const int frameLength = 250;
const int animationFrame = 4;

//mode
const int MENU = 0;
const int EASY = 1;
const int NORMAL = 2;
const int HARD = 3;

//status
const int IN_GAME = -1;
const int WIN = 0;
const int LOSE = 1;
const int PAUSE = 2;

//button text
const int REPLAY = 3;
const int NEXT_LEVEL = 4;
const int BACK = 5;
const int keyPress = 6;

//menu
const int buttonNum = 6;
const int START_BUTTON = 0;
const int LEVEL_BUTTON = 1;
const int HELP_BUTTON = 2;
const int EASY_BUTTON = 3;
const int NORMAL_BUTTON = 4;
const int HARD_BUTTON = 5;

//easy
const int EasyItemNum = 3;
const int EASY_GATE = 0;
const int EASY_STONE_FI = 1;
const int EASY_STONE_SE = 2;

//normal
const int NormalItemNum = 6;
const int NORMAL_GATE = 0;
const int NORMAL_STONE_FI = 1;
const int NORMAL_STONE_SE = 2;
const int NORMAL_CACTUS_FI = 3;
const int NORMAL_CACTUS_SE = 4;
const int NORMAL_CACTUS_TH = 5;

//hard
const int HardItemNum = 9;
const int HARD_TREASURE = 0;
const int HARD_STONE = 1;
const int HARD_CACTUS_FI = 2;
const int HARD_CACTUS_SE = 3;
const int HARD_CACTUS_TH = 4;
const int HARD_CACTUS_FO = 5;
const int HARD_KEY = 6;
const int HARD_MAGIC = 7;
const int HIDDEN_PUZZLE = 8;

#endif // CONSTANT_H_INCLUDED
