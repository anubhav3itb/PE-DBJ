#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include<model.h>

#include <QGLWidget>
#include "fasttrackball.h"


class MyGLWidget : public QGLWidget
{
    Q_OBJECT
     int w, h;
     Trackball trackball;
     Model model;

public:
     float transx=0.0, transy=0.0, transz=0.0;
     float angle=0.0, scale=1;
     float oldX = 0.0, oldY=0.0;
    // void rotate(float x1, float y1, float x2, float y2);
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    void rotate(float oldx, float oldy, float x, float y);
    void renderFromButton(QString XMAX);
    void clearScreen();
    void renderAll(int test);

    std::vector<int> inputFaces;

signals:
    // signaling rotation from mouse movement
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);


public slots:
    // slots for xyz-rotation slider
        void setXRotation(int angle);
        void setYRotation(int angle);
        void setZRotation(int angle);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
        void draw();

            int xRot;
            int yRot;
            int zRot;

            QPoint lastPos;


};

#endif // MYGLWIDGET_H
