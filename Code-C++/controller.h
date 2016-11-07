#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "myglwidget.h"
#include "model.h"

class Controller{
     int h, w;
    enum {UP = 1, DOWN, };
     int flag;
     int mState;
     int oldX, oldY;
     float centx, centy, centz;
public:
    void run(char**);
     void SpecialKeys(int key, int x, int y);
     void glutMotion(int x, int y);
     void glutMouse(int button, int state, int x, int y);
     void keyboard(unsigned char key, int x, int y);
};
#endif
