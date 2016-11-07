#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "model.h"
#include "myglwidget.h"
#include <QtWidgets>
#include <QtOpenGL>
#include <QOpenGLFunctions_1_5>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "tree.h"
#include <unistd.h>

using namespace std;

Hand* hand;
Palm* palm;
extern int times;

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 0;
        yRot = 0;
        zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
}

QSize MyGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize MyGLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void MyGLWidget::clearScreen()
{
    inputFaces.clear();
    updateGL();
}

void MyGLWidget::renderAll(int test)
{
    inputFaces.clear();
    if (test == -1)
        inputFaces.push_back(-1);

    updateGL();


}

void MyGLWidget::renderFromButton(QString XMAX)
{
    std::string box_val = XMAX.toUtf8().constData();
    inputFaces.clear();
    std::vector<int> vect;


    std::stringstream ss(box_val);

    int i;

    while (ss >> i)
    {
        inputFaces.push_back(i-1);

        if (ss.peek() == ',')
            ss.ignore();
    }

    updateGL();
}

 void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::initializeGL()
{
    glClearColor(0.0, 0.0, .0, 0.0);
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 2.0, 2.0, 2.0, 1.0 };

    GLfloat spot_direction[] = { 0.0, 0.0, 0.0 };
    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    //~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //~ glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //~ glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    glEnable(GL_LIGHT0);

    model.readObject("cube2.ply");
    //model.readObject("all_parts.ply");
    //model.readObject("dolphins.ply");
    model.computeNormals();
    std::vector<std::vector<int> > allMode = model.getAllFaces();
    cout << "Total Number of Connected components are:" << " "<< allMode.size();
    std::vector<std::vector<Polygon*> > allModels = model.getPolyFaces(allMode);


    //creating palm
    palm = new Palm(allModels[6]);

    //creating finger 1
    Finger *finger1_1 = new Finger(allModels[0]);
    Finger *finger1_2 = new Finger(allModels[1]);
    Finger *finger1_3 = new Finger(allModels[2]);

    finger1_1->Finger::AddObject(finger1_2);
    finger1_2->Finger::AddObject(finger1_3);
    palm->Palm::AddObject(finger1_1);

    //creating finger 2
    Finger *finger2_1 = new Finger(allModels[3]);
    Finger *finger2_2 = new Finger(allModels[4]);
    Finger *finger2_3 = new Finger(allModels[5]);

    finger2_1->Finger::AddObject(finger2_2);
    finger2_2->Finger::AddObject(finger2_3);
    palm->Palm::AddObject(finger2_1);

    //creating thumb
    Thumb *thumb1_1 = new Thumb(allModels[7]);
    Thumb *thumb1_2 = new Thumb(allModels[8]);

    thumb1_1->Thumb::AddObject(thumb1_2);
    palm->Palm::AddObject(thumb1_1);



}

void MyGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -10.0);
    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int wt, int ht)
{
    if (ht  == 0)
            ht = 1;
        //Tell OpenGL how to convert from coordinates to pixel values
        w = wt;
        h = ht;

        glViewport(0, 0, wt, ht);

        //~ glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

        glEnable(GL_DEPTH_TEST);
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective( 60.0, wt / ht, 0.1, 50.0 );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
     if (event->buttons() & Qt::LeftButton) {
         oldX = event->x() ;
         oldY = event->y() ;
     }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        rotate(oldX, oldY, event->x() , event->y() );
        oldX = event->x() ;
        oldY = event->y() ;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }

    lastPos = event->pos();
}

void MyGLWidget::draw()
{
    glClearColor(0.0, 0.0, .0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat position[] = { 2.0, 2.0, 2.0, 1.0 };
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();


    gluLookAt
        (
        .05, .1, 2,
        0., 0., 0,
        0, 1, 0
        );

    static float rotation_transform[4][4];
    //model.drawAxis();
    //model.mergePoints(0.0001);
    trackball.rotationMatrix( rotation_transform );
    glLightfv (GL_LIGHT0, GL_POSITION, position);
    glPushMatrix();
    glEnable (GL_LIGHTING);
    glScalef(scale, scale, scale);
    glTranslatef(transx, transy, transz);
    glRotatef(angle, 1, 0, 0);
    glMultMatrixf( &rotation_transform[0][0]);
    //hand->Tree::drawScene();

    palm->Palm::drawScene();
    //model.drawObject(inputFaces);

    //~ model.drawBoundingBox();
    glDisable (GL_LIGHTING);
    glPopMatrix();
    times ++;
    swapBuffers();

    if (times < 31)
    {
        usleep(250000);
        updateGL();


    }
}
void MyGLWidget::rotate(float oldx, float oldy, float x, float y){
    trackball.rotate((2.0*oldx - w)/(float)w,
                     (h - 2.0*oldy)/(float)h,
                     (2.0*x - w)/(float)w,
                     (h - 2.0*y)/(float)h);
}
