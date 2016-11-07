#include "model.h"
#include "graph.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

float color1 = 1.0;
float color2 = 0.0;
float color3 = 0.0;


Point::Point(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
    normx = 0.0;
    normy = 0.0;
    normz = 0.0;
}

Point::Point(double x_coor, double y_coor, double z_coor){
    x = x_coor;
    y = y_coor;
    z = z_coor;
    normx = 0.0;
    normy = 0.0;
    normz = 0.0;
}

void Point::reloadVector(std::vector<Point*> temp)
{
    adjList.clear();
    for(int j=0; j<temp.size(); j++)
    {
        adjList.push_back(temp[j]);
    }
}

std::vector<Point*> Model::returnPoints()
{
    return points;
}

void Point::addAdjacentNode(Point *point)
{
    adjList.push_back(point);
}

std::vector<Point*> Point::getAdjList()
{
    return adjList;
}

double Point::getX(){
    return x;
}

void Point::setX(double x_coor){
    x = x_coor;
}

double Point::getY(){
    return y;
}
void Point::setY(double y_coor){
    y = y_coor;
}
double Point::getZ(){
    return z;
}
void Point::setZ(double z_coor){
    z = z_coor;
}
double Point::getNormX(){
    return normx;
}

double Point::getNormY(){
    return normy;
}
double Point::getNormZ(){
    return normz;
}
void Point::print(){
    std::cout<<x<<" "<<y<<" "<<z<<std::endl;
}

void Point::setIndex(int i)
{
    index = i;
}

void Point::addFaces(int index)
{
    connectedFaces.push_back(index);
}

std::vector<int> Point::getFaces()
{
    return connectedFaces;
}

int Point::getIndex()
{
    return index;
}

void Point::setNormal(double nx, double ny, double nz){
    normx = nx;
    normy = ny;
    normz = nz;
}
void Point::addNormal(double nx, double ny, double nz){
    normx += nx;
    normy += ny;
    normz += nz;
}
void Point::normNormal(){
    double n = 0;
    n = sqrt(normx*normx + normy*normy + normz*normz);
    normx /= n; normy /= n; normz /= n;
}
Polygon::Polygon(){
    no = -1;
}

NewPolygon::NewPolygon(){}

void NewPolygon::addVer(long int val){
    return vertexes.push_back(val);
}
long int NewPolygon::getIdx(long int idx){
    return vertexes[idx];
}


void NewPolygon::setIdx(long int idx, long int value){
    vertexes[idx] = value;
}

void Polygon::addVertex(Point* p){
    //vertices.push_back(new Point(p->getX(),p->getY(),p->getZ()));
    vertices.push_back(p);
}
Point* Polygon::getPointAt(int i){
    if (no != -1 && no != i)
        return vertices[i];
    return nullptr;
}

std::vector<Point*> Polygon::getVertices()
{
    return vertices;
}

void Polygon::printVertices(){
    int i;
    for (i=0;i<vertices.size();i++)
        vertices[i]->print();
}
void Polygon::drawPolygon(){
    glBegin(GL_TRIANGLES);
    glColor4f(color1, color2, color3, 0.5);
    for (int i=0;i < vertices.size(); i++){
        glVertex3f(vertices[i]->getX(), vertices[i]->getY(), vertices[i]->getZ());
    }
    glEnd();
}
void Polygon::computeNormal(){
    double n = 0;
    double v1x, v1y, v1z, v2x, v2y, v2z;
    v1x = vertices[1]->getX() - vertices[0]->getX();
    v1y = vertices[1]->getY() - vertices[0]->getY();
    v1z = vertices[1]->getZ() - vertices[0]->getZ();

    v2x = vertices[2]->getX() - vertices[0]->getX();
    v2y = vertices[2]->getY() - vertices[0]->getY();
    v2z = vertices[2]->getZ() - vertices[0]->getZ();

    normx = v1y*v2z - v1z*v2y;
    normy = v1z*v2x - v1x*v2z;
    normz = v1x*v2y - v1y*v2x;
    n = sqrt(normx*normx + normy*normy + normz*normz);
    normx /= n; normy /= n; normz /= n;
    for (int i=0;i<vertices.size(); i++)
        vertices[i]->addNormal(normx, normy, normz);
}

Model::Model(){
    minx = 9999.0; miny = 9999.0; minz = 9999.0;
    maxx = -9999.0; maxy = -9999.0; maxz = -9999.0;
    tolerance = 0.0001;
}
void Model::render(){
    //drawAxis();
    //drawObject();
    glPointSize(5);
    glBegin(GL_POINTS);
    glColor3f (1, 0, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}
void Model::drawAxis(){
    glBegin(GL_LINES);
    double axis = 2;
    //drawing x -axis
    glColor4f(0, 0, 1, 0);
    glVertex3f( axis, 0, 0);
    glVertex3f(-axis, 0, 0);

    //drawing y -axis
    glColor4f(0, 1, 0, 0);
    glVertex3f(0, axis, 0);
    glVertex3f(0, -axis,0);

    //drawing z -axis
    glColor4f(1, 0, 0, 0);
    glVertex3f(0, 0, axis);
    glVertex3f(0, 0, -axis);
    glEnd();
}
void Model::drawObject(std::vector<int> tests){
    long int i;
    newPolygon.clear();
    std::vector<std::vector<int> >outs =  getAllFaces();

    if(tests.size() == 1 && tests[0] == -1)
    {
        for(i=0;i < polygons.size();i++)
            {polygons[i]->drawPolygon();}
    }
    else
    {
        for(int j=0; j<tests.size(); j++)
        {

            for(int k=0; k<outs[tests[j]].size(); k++)
            {
                newPolygon.push_back(polygons[outs[tests[j]][k]]);
            }
            for(i=0;i < newPolygon.size();i++)
                {newPolygon[i]->drawPolygon();}
        }
    }
}

std::vector<std::vector<int> > Model::getAllFaces()
{
    std::vector<std::vector<int> > outs;
    Graph g5(points.size());
    for(int i=0; i<points.size(); i++)
    {
        std::vector<Point*> list = points[i]->getAdjList();
        for (int j=0; j<list.size(); j++)
        {
            g5.addEdge(i, list[j]->getIndex());
        }
    }


    std::vector<std::vector<int> > val = g5.SCC();

    for(int i =0; i< val.size(); i++)
    {
        std::vector<int> temp;
        for(int j=0; j < val[i].size(); j++)
        {
            for(int k=0; k < points[val[i][j]]->getFaces().size();k++)
            {
                temp.push_back(points[val[i][j]]->getFaces()[k]);
            }
        }

        set<int> s( temp.begin(), temp.end() );
        temp.assign( s.begin(), s.end() );
        if(temp.size() > 10)
        {
            outs.push_back(temp);
        }
    }

    return outs;


}

std::vector<std::vector<Polygon*> > Model::getPolyFaces(std::vector<std::vector<int> > intFaces)
{
    std::vector<std::vector<Polygon*> > allPolyFaces;

    for(int i=0; i<intFaces.size();i++)
    {
        std::vector<Polygon*> tempPolygon;

        for(int j=0; j < intFaces[i].size(); j++)
        {
            tempPolygon.push_back(polygons[intFaces[i][j]]);
        }
        allPolyFaces.push_back(tempPolygon);
    }

    return allPolyFaces;

}

bool Model::double_equals(double a, double b, double epsilon)
{
    return std::abs(a - b) < epsilon;
}

std::vector<int> Model::returnFacesEdges(Point* p1, Point* p2)
{
    Polygon *polygon;
    std::vector<int> allFaces;
    for(int i=0; i<polygons.size(); i++)
    {
        polygon = polygons[i];

        for(int j=0; j<(polygon->getVertices()).size(); j++)
        {
            double chx = polygon->getVertices()[j]->getX()*maxval + avgx;
            double chy = polygon->getVertices()[j]->getY()*maxval + avgy;
            double chz = polygon->getVertices()[j]->getZ()*maxval + avgz;


            if (double_equals(chx, p1->getX(), 0.00001)&& double_equals(chy, p1->getY(), 0.00001) && double_equals(chz, p1->getZ(), 0.00001))
            {
                for(int k=0; k<(polygon->getVertices()).size(); k++)
                {
                    if(k != j)
                    {
                        double dhx = polygon->getVertices()[k]->getX()*maxval + avgx;
                        double dhy = polygon->getVertices()[k]->getY()*maxval + avgy;
                        double dhz = polygon->getVertices()[k]->getZ()*maxval + avgz;
                        if (double_equals(dhx, p2->getX(), 0.00001)&& double_equals(dhy, p2->getY(), 0.00001) && double_equals(dhz, p2->getZ(), 0.00001))
                        {
                            allFaces.push_back(i);
                        }
                    }
                }

            }
        }

    }
    return allFaces;
}

bool Model::isComplete()
{
    int less2 = 0;
    for(int i = 0; i<points.size(); i++)
    {
        Point *p1 = points[i];
        for(int j=0;j < adjList[i].size(); j++)
        {
            Point *p2 = adjList[i][j];
            if (returnFacesEdges(p1, p2).size() < 2)
            {
                less2++;
            }
        }
    }

    if (less2 == 0)
        return true;
    else
        return false;

}

void Model::readObject(char *filename){

    std::cout<<filename<<std::endl;
    std::ifstream ifile;
    ifile.open(filename);
    std::string s;
    long int num_vertex, num_faces; long long i;
    double x, y, z, nx, ny, nz;
    int co_in = 0, norm = 0;
    long int vertex_idx, j, sides = 0;
    Polygon* polygon;
    NewPolygon* poly;
    while(ifile>>s){
        if (s.compare("vertex") == 0){
            ifile>>s;
            num_vertex = std::stoi(s);
            std::cout<<num_vertex<<std::endl;
        }else if (s.compare("face") == 0){
            ifile>>s;
            num_faces = std::stoi(s);
            std::cout<<num_faces<<std::endl;
        }else if (s.compare("confidence") == 0 || s.compare("intensity") == 0){
            co_in = 1;
        }else if (s.compare("nx") == 0){
            norm = 1;
        }else if (s.compare("end_header") == 0){
            for ( i=0; i < num_vertex; i++){
                ifile>>s;
                x = std::stof(s);
                ifile>>s;
                y = std::stof(s);
                ifile>>s;
                z = std::stof(s);
                Point *p = new Point(x, y, z);
                p->setIndex(i);
                points.push_back(p);
                if (minx > x)
                    minx = x;
                if (miny > y)
                    miny = y;
                if (minz > z)
                    minz = z;
                if (maxx < x)
                    maxx = x;
                if (maxy < y)
                    maxy = y;
                if (maxz < z)
                    maxz = z;
                if (co_in){
                    ifile>>s;
                    ifile>>s;
                }else if (norm){
                    ifile>>s;
                    ifile>>s;
                    ifile>>s;
                }
            }
            avgx = (maxx+minx)/2;
                  avgy = (maxy+miny)/2;
                  avgz = (maxz+minz)/2;
            maxval = -9999;
            if (abs(maxx - minx) > abs(maxy - miny) && abs(maxx - minx) > abs(maxz - minz))
                maxval = maxx - minx;
            else if (abs(maxy - miny) > abs(maxz - minz))
                maxval = maxy - miny;
            else
                maxval = maxz - minz;

            for ( i=0; i < num_vertex; i++){
                points[i]->setX((points[i]->getX() - avgx)/maxval);
                points[i]->setY((points[i]->getY() - avgy)/maxval);
                points[i]->setZ((points[i]->getZ() - avgz)/maxval);
            }
            minx = (minx - avgx)/maxval;
            miny = (miny - avgy)/maxval;
            minz = (minz - avgz)/maxval;

            maxx = (maxx - avgx)/maxval;
            maxy = (maxy - avgy)/maxval;
            maxz = (maxz - avgz)/maxval;
            std::cout<<minx<<" "<<maxx<<std::endl;
            std::cout<<miny<<" "<<maxy<<std::endl;
            std::cout<<minz<<" "<<maxz<<std::endl;
            std::cout<<"Maxval"<<maxval<<std::endl;



            for ( i=0; i < num_faces; i++){
                polygon = new Polygon();
                poly = new NewPolygon(); //similar to polygon
                ifile>>s;
                sides = std::stoi(s);
                std::vector<int> indices;
                std::vector<Point*> tempPoints;

                for ( j=0; j < sides; j++){
                    ifile>>s;
                    vertex_idx = std::stoi(s);
                    indices.push_back(vertex_idx);
                    Point* p = points[vertex_idx];
                    tempPoints.push_back(new Point(p->getX(),p->getY(),p->getZ()));
                    polygon->addVertex(points[vertex_idx]);
                }

                polygons.push_back(polygon);
            }
            std::cout<<points.size()<<std::endl;
        }
    }
    ifile.close();


    for (int i = 0; i<polygons.size(); i++)
    {

        for(int j=0; j<3;j++)
        {
            for (int k=0; k<3; k++)
            {
                if(k != j)
                {

                    points[(polygons[i]->getVertices()[j])->getIndex()]->addAdjacentNode(polygons[i]->getVertices()[k]);

                }
            }
        }
    }

    for (int i = 0; i<polygons.size(); i++)
    {
        for(int j=0; j<3;j++)
        {
            points[(polygons[i]->getVertices()[j])->getIndex()]->addFaces(i);
        }
    }


    for(int i=0; i<points.size(); i++)
    {
        std::vector<Point*> temp;
        std::vector<Point*> list = points[i]->getAdjList();
        temp.push_back(list[0]);
        for(int j=1; j<list.size(); j++)
        {
            int count = 0;
            for(int k=0; k<temp.size(); k++)
            {
                if(temp[k]->getIndex() != list[j]->getIndex())
                {
                    count++;
                }
            }
            if(count == temp.size())
            {
                temp.push_back(list[j]);
            }
        }
        points[i]->reloadVector(temp);
    }

}



bool Model::isEdgeInt(int idx1, int idx2)
{
    for(int i=0; i<adjListInt[idx1].size(); i++)
    {
        if (adjListInt[idx1][i] == idx2)
        {
            return true;
        }
    }
    return false;
}

bool Model::isEdgePoint(Point* p1, Point* p2)
{

    int idx= 0;
    for (int i = 0; i <points.size(); i++)
    {
        double chx = points[i]->getX()*maxval + avgx;
        double chy = points[i]->getY()*maxval + avgy;
        double chz = points[i]->getZ()*maxval + avgz;


        if (double_equals(chx, p1->getX(), 0.00001)&& double_equals(chy, p1->getY(), 0.00001) && double_equals(chz, p1->getZ(), 0.00001))
        {

            idx = i;
        }
    }



    for(int i=0; i<adjList[idx].size(); i++)
    {

        double listx = adjList[idx][i]->getX()*maxval + avgx;
        double listy = adjList[idx][i]->getY()*maxval + avgy;
        double listz = adjList[idx][i]->getZ()*maxval + avgz;

        if (double_equals(listx, p2->getX(), 0.00001) && double_equals(listy, p2->getY(), 0.00001) &&  double_equals(listz, p2->getZ(), 0.00001))
        {

            return true;
        }
    }
    return false;

}


bool Model::getDistance(Point p1, Point p2)
{
    double distance = sqrt(pow(p1.getX() - p2.getX(), 2.0) + pow(p1.getY() - p2.getY(), 2.0) + pow(p1.getZ() - p2.getZ(), 2.0));
    if (distance < tolerance)
        return true;
    else
        return false;
}

/*void Model::mergePoints(double tolerance)
{
    int count = 0;
    Polygon* polygon;
    Point *p1 = new Point;
    Point *p2 = new Point;
    //std::vector<Point*> copyPoints = points;
    //std::vector<Polygon*> copyPoly = polygons;
    long int i, j;
    for(i=0;i < 100;i++)
    {
        cout << "current i is:" <<i << endl;
        p1 = points[i];
        for(j=i+1;j < points.size();j++)
        {
            p2 = points[j];

            //If distance between points is less than tolerance
            if (getDistance(*p1, *p2))
            {
                p2 = p1;
                //compare index of that point to all other in faces
                for(int k=0; k<polygos.size();k++)
                {
                    for(int l=0; l<3;l++)
                    {
                        //and if it matches, replace it
                        if (polygos[k]->getIdx(l) == j)
                        {

                            polygos[k]->setIdx(l,i);
                        }
                    }
                }

                count++;
            }
        }
    }


    for (int i = 0; i<polygons.size(); i++)
    {

        for(int j=0; j<3;j++)
        {
            for (int k=0; k<3; k++)
            {
                if(k != j)
                {
                    points[polygos[i]->getIdx(j)]->addAdjacentNode(polygos[i]->getIdx(k));
                }
            }
        }
    }

}
*/


void Model::computeNormals(){
    long int i;
    for(i=0;i < polygons.size();i++)
        polygons[i]->computeNormal();

    for(i=0;i < points.size();i++)
        points[i]->normNormal();
}
void Model::drawBoundingBox(){
    glBegin(GL_LINES);
    glColor4f(0.4, 0.1, 0.25, 0);
    glVertex3f(minx, miny, minz);
    glVertex3f(maxx, miny, minz);

    glVertex3f(maxx, miny, minz);
    glVertex3f(maxx, maxy, minz);

    glVertex3f(maxx, maxy, minz);
    glVertex3f(minx, maxy, minz);

    glVertex3f(minx, maxy, minz);
    glVertex3f(minx, miny, minz);

    glEnd();

    glBegin(GL_LINES);
    glColor4f(1, 0, 0.2, 0);
    glVertex3f(minx, miny, maxz);
    glVertex3f(maxx, miny, maxz);

    glVertex3f(maxx, miny, maxz);
    glVertex3f(maxx, maxy, maxz);

    glVertex3f(maxx, maxy, maxz);
    glVertex3f(minx, maxy, maxz);

    glVertex3f(minx, maxy, maxz);
    glVertex3f(minx, miny, maxz);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(1, 1, 0, 0);
    glVertex3f(minx, miny, minz);
    glVertex3f(minx, miny, maxz);

    glVertex3f(maxx, miny, minz);
    glVertex3f(maxx, miny, maxz);
    glEnd();

    glBegin(GL_LINES);
    glColor4f(1, 1, 0, 0);
    glVertex3f(minx, maxy, minz);
    glVertex3f(minx, maxy, maxz);

    glVertex3f(maxx, maxy, minz);
    glVertex3f(maxx, maxy, maxz);
    glEnd();

}
