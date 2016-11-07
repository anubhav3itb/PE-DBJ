#include "controller.h"
#include "myglwidget.h"
#include "model.h"
#include "graph.h"

extern Model model;
extern View view;


int Controller::flag = 1;
int Controller::mState = UP;
int Controller::oldX = -13;
int Controller::oldY = -13;
float Controller::centx = 0.0;
float Controller::centy = 0.0;
float Controller::centz = 0.0;

using namespace std;

void Controller::keyboard(unsigned char key, int x, int y){
    if (key == char(27) || key == 'q'){
        std::cout<<"Quiting ..."<<std::endl;
        exit(-1);
    }else if (key == 'l'){
        view.angle += 0.5;
    }else if (key == 'r'){
        view.angle -= 0.5;
    }else if (key == '+'){
        view.scale += 0.2;
    }else if (key == '-'){
        view.scale -= 0.2;
    }
    glutPostRedisplay();
}

void Controller::glutMotion(int x, int y)
{
    if (mState == DOWN)
    {
        view.rotate(oldX, oldY, x, y);
        glutPostRedisplay();
    }
    oldX = x;
    oldY = y;
}

void Controller::glutMouse(int button, int state, int x, int y)
{
    float dist = 0.0;
    float px = 0, py = 0;
    if(state == GLUT_DOWN)
    {
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                mState = DOWN;
                oldX = x;
                oldY = y;
                break;
            case GLUT_RIGHT_BUTTON:
                oldX = x;
                oldY = y;
            break;
        }
    } else if (state == GLUT_UP){
        mState = UP;
        switch(button)
        {
            case GLUT_LEFT_BUTTON:
                view.rotate(0, 0, 0, 0);
                oldX = x;
                oldY = y;
                break;
            case GLUT_RIGHT_BUTTON:
                std::cout<<"Hello"<<std::endl;
                //~ view.transx += (float)(x - oldX);
                //~ view.transy -= (float)(y - oldY);
                break;
        }
        glutPostRedisplay();
    }
}

void Controller::SpecialKeys(int key, int x, int y){
    if (key == GLUT_KEY_LEFT){
        view.transx+=0.1;
    }
    else if (key == GLUT_KEY_UP){
        view.transy-=0.1;
    }
    else if (key == GLUT_KEY_RIGHT){
        view.transx-=0.1;
    }
    else if (key == GLUT_KEY_DOWN){
        view.transy+=0.1;
    }
    glutPostRedisplay();
}
void Controller::run(char** argv){
    model.readObject(argv[1]);
    Point *p1 = new Point(0.032027, 0.056575, -0.0503644); //point 0
    Point *p2 = new Point(0.032377, 0.0565645, -0.0503375); //point 2

    std::vector<Point*> points = model.returnPoints();

    std::vector<std::vector<int> > faces = model.getAllFaces();

    for(int i=0; i<faces.size(); i++)
    {
        for(int j=0; j<faces[i].size(); j++)
        {
            cout << faces[i][j] << " ";
        }
        cout << endl;
    }

    model.computeNormals();
    //model.mergePoints(0.0001);
    view.initRendering(); //Initialize rendering
    //Set handler function for drawing
    glutDisplayFunc(view.draw);
    //Set handler function for window resize
    glutReshapeFunc(view.handleResize);
    //Set handler function for keypress
    glutKeyboardFunc(keyboard);
    //Set handler function for Special keypress
    glutSpecialFunc(SpecialKeys);
    glutMotionFunc(glutMotion);
    glutMouseFunc(glutMouse);
    glutMainLoop(); //Start the main loop.
}
