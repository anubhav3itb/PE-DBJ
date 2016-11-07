#include "tree.h"
#include <QtWidgets>
#include <QtOpenGL>

int times=0;

Tree::Tree()
{
    translation[0]=0;
    translation[1]=0;
    translation[2]=0;

    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;

    scaling[0] = 1.0;
    scaling[1] = 1.0;
    scaling[2] = 1.0;
}

void Tree::AddPolygon(std::vector<Polygon*> objectPolygon)
{
    polygons = objectPolygon;
}

void Tree::AddObject(Tree* object)
{
    listObjects.push_back(object);
}

void Tree::drawScene()
{
    nextPosition();
    glPushMatrix();

    Render();
    for(int i=0; i<listObjects.size(); i++)
    {
        listObjects[i]->drawScene();
    }
    glPopMatrix();
}


void Tree::nextPosition()
{

}

void Hand::nextPosition()
{

}

void Palm::nextPosition()
{
    if(times <= 10)
        {

            translation[1] = times * 0.04;
        }
}

void Finger::nextPosition()
{
    if(times > 10)
    {
        if(times <= 15)
        {

            rotation[1] = -(times - 10)*9;
        }

        if(times > 15 && times <= 20)
        {
            rotation[1] += 9;
        }
    }

}

void Thumb::nextPosition()
{
    if(times > 10)
    {
        if(times <= 15)
        {

            rotation[0] = (times - 10)*9;
        }

        if(times > 15 && times <= 20)
        {
            rotation[0] -= 9;
        }
    }

}



void Tree::Render()
{

    float centroidx = 0.0;
    float centroidy = 0.0;
    float centroidz = 0.0;

    for(int i=0; i<polygons.size(); i++)
    {
        std::vector<Point*> points;
        points = polygons[i]->getVertices();
        for(int j=0; j< points.size(); j++)
        {

            centroidx += points[j]->getX();
            centroidy += points[j]->getY();
            centroidz += points[j]->getZ();
        }
    }

    centroidx /= (3*polygons.size());
    centroidy /= (3*polygons.size());
    centroidz /= (3*polygons.size());


    glRotatef(rotation[0], 1.0, 0.0, 0.0);
    glRotatef(rotation[1], 0.0, 1.0, 0.0);
    glRotatef(rotation[2], 0.0, 0.0, 1.0);

    glScalef(scaling[0], scaling[1], scaling[2]);
    glTranslatef(translation[0], translation[1], translation[2]);

    for(int i=0;i < polygons.size();i++)
    {
        polygons[i]->drawPolygon();
    }
}

void Tree::setTranslation(float translate[])
{
    translation[0] = translate[0];
    translation[1] = translate[1];
    translation[2] = translate[2];
}

void Tree::setRotation(float rotate[])
{
    rotation[0] = rotate[0];
    rotation[1] = rotate[1];
    rotation[2] = rotate[2];
}

void Tree::setScale(float scale[])
{
    scaling[0] = scale[0];
    scaling[1] = scale[1];
    scaling[2] = scale[2];
}

Hand::Hand()
{
}


Hand::Hand(vector<Polygon*> polys)
{
    translation[0]=0;
    translation[1]=0;
    translation[2]=0;

    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;

    scaling[0] = 1.0;
    scaling[1] = 1.0;
    scaling[2] = 1.0;

    polygons = polys;
}

Palm::Palm()
{
}


Palm::Palm(vector<Polygon*> polys)
{
    translation[0]=0;
    translation[1]=0;
    translation[2]=0;

    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;

    scaling[0] = 1.0;
    scaling[1] = 1.0;
    scaling[2] = 1.0;

    polygons = polys;
}

Finger::Finger()
{
}

Finger::Finger(vector<Polygon*> polys)
{
    translation[0]=0;
    translation[1]=0;
    translation[2]=0;

    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;

    scaling[0] = 1.0;
    scaling[1] = 1.0;
    scaling[2] = 1.0;

    polygons = polys;
}

Thumb::Thumb()
{
}

Thumb::Thumb(vector<Polygon*> polys)
{
    translation[0]=0;
    translation[1]=0;
    translation[2]=0;

    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;

    scaling[0] = 1.0;
    scaling[1] = 1.0;
    scaling[2] = 1.0;

    polygons = polys;
}
