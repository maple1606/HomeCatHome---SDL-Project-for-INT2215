#include "MainControl.h"

using namespace std;

int main(int argc, char* argv[])
{
    MainControl *control = new MainControl();
    if (control->init())
    {
        while (!control->isQuit())
        {
            control->setMode();
        }
    }
    control->close();
    delete control;
    control = NULL;
    return 0;
}
