#ifndef TREE_H
#define TREE_H
#include<stdlib.h>
#include <GL/gl.h>
#include<vector>
#include<iostream>
#include "model.h"

using namespace std;

class Tree
{  
    int id;

    protected:
        float translation[3];
        float rotation[3];
        float scaling[3];
        std::vector<Tree*> listObjects;
        std::vector<Polygon*> polygons;

    public:
        Tree();
        void AddObject(Tree* object);
        void AddPolygon(std::vector<Polygon*> objectPolygon);
        void drawScene();
        void Render();
        void setTranslation(float translate[3]);
        void setRotation(float rotate[3]);
        void setScale(float scale[3]);
        virtual void nextPosition();
};


class Hand:public Tree
{
    int id;
    public:
        Hand();
        Hand(vector<Polygon*> polys);
        void nextPosition();
};

class Palm:public Tree
{
    int id;
    public:
        Palm();
        Palm(vector<Polygon*> polys);
        void nextPosition();
};

class Finger:public Tree
{
    int id;
    public:
        Finger();
        Finger(vector<Polygon*> polys);
        void nextPosition();
};

class Thumb:public Tree
{
    int id;
    public:
        Thumb();
        Thumb(vector<Polygon*> polys);
        void nextPosition();
};



#endif // TREE_H
