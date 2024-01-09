#include "Point.h"
using namespace std;

/// Point count is used to keep track of the number of points created
int Point::pointCount = 0;

/// Default constructor
Point::Point(int ID, int cluster, pair<double, double> featuresIn) : pointID(ID), clusterID(cluster), features(featuresIn) {

}

/// Setters
void Point::setClusterID(int a) {clusterID = a;}
void Point::setFeatures(pair<double, double> input) {features = input;}

/// Getters
int Point::getandIncrementPointCount() {return ++pointCount;}
int Point::getPointCount() { return pointCount; }
int Point::getClusterID(void) const {return clusterID;}
int Point::getPointID(void)const {return pointID;}
pair<double, double> Point::getFeatures(void) const { return features;}

/// Operators
void Point::operator=(const Point& b) {
    this->setFeatures(b.getFeatures());this->setClusterID(b.getClusterID());
}
void Point::operator=(const Point* b) {
    this->setFeatures(b->getFeatures());this->setClusterID(b->getClusterID());
}

/// Virtual print function
void Point::print(void) {
    cout <<
        "ID: " << setw(3) << getPointID() <<
        "  ,  value1: " << fixed << setw(12) << getFeatures().first <<
        "  |  value2: " << fixed << setw(12) << getFeatures().second <<
        "  |  Cluster " << fixed << setw(3) << getClusterID()<<endl;
}

/// Destructor
Point::~Point() {
}