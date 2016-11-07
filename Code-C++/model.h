#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <GL/gl.h>
#include <math.h>

class Point{
    double x, y, z;
    double normx, normy, normz;
    int index;
    std::vector<Point*> adjList;
    std::vector<int> connectedFaces;
public:
    Point();
    Point(double x_coor, double y_coor, double z_coor);
    double getX();
    void setX(double x_coor);
    double getY();
    void setY(double y_coor);
    double getZ();
    void setZ(double z_coor);
    void setIndex(int idx);
    int getIndex();
    double getNormX();
    double getNormY();
    double getNormZ();
    void print();
    void setNormal(double normx, double normy, double normz);
    void addNormal(double normx, double normy, double normz);
    void normNormal();
    void addAdjacentNode(Point *point);
    std::vector<Point*> getAdjList();
    void addFaces(int index);
    std::vector<int> getFaces();
    void reloadVector(std::vector<Point*> temp);
};

class Polygon{
    int no;
    std::vector<Point*> vertices;
    double normx, normy, normz;
public:
    Polygon();
    void addVertex(Point *p);
    Point* getPointAt(int i);
    void printVertices();
    std::vector<Point*> getVertices();
    void drawPolygon();
    void computeNormal();
};

class NewPolygon{
    double normx, normy, normz;
    std::vector<int> vertexes;
public:
    NewPolygon();
    void addVer(long int val);
    long int getIdx(long int idx);
    void setIdx(long int idx, long int value);
};

class Model{
    std::vector<Point*> points; // List of input points
    std::vector<Polygon*> polygons; // List of polygons
    std::vector<Polygon*> newPolygon;
    std::vector<std::vector<Point*> > adjList; //List of list of Points, adj list
    std::vector<std::vector<int> > adjListInt;
    double minx, miny, minz;
    double maxx, maxy, maxz;
    double tolerance;
    double avgx, avgy, avgz, maxval;
public:
    Model();
    void render();
    void drawAxis();
    void drawObject(std::vector<int> inputFaces);
    void readObject(char* fname);
    void computeNormals();
    void drawBoundingBox();
    void mergePoints(double tolerance);
    bool getDistance(Point p1, Point p2);
    bool isEdgeInt(int idx1, int idx2);
    bool isEdgePoint(Point* p1, Point* p2);
    bool double_equals(double a, double b, double epsilon);
    std::vector<Point*> returnPoints();
    std::vector<int> returnFacesEdges(Point* p1, Point* p2);
    std::vector<std::vector<int> > getAllFaces();
    std::vector<std::vector<Polygon*> > getPolyFaces(std::vector<std::vector<int> > intFaces);
    bool isComplete();
};

#endif
