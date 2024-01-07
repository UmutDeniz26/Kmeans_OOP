/**
 * @file Point.cpp
 * @brief Implementation of the Point class.
 */

#include "Point.h"
using namespace std;

/**
 * @brief Static member to keep track of the total number of points.
 */
int Point::pointCount = 0;

/**
 * @brief Constructor for the Point class.
 * @param ID The point ID.
 * @param cluster The cluster ID.
 * @param featuresIn A pair representing the features of the point.
 */
Point::Point(int ID, int cluster, pair<double, double> featuresIn) : pointID(ID), clusterID(cluster), features(featuresIn) {
    //cout<<"Constructor of point "<<ID<<endl;
    if (ID >0) {
        pointCount += 1;
    }
}

void Point::setClusterID(int a) {clusterID = a;}
void Point::setFeatures(pair<double, double> input) {features = input;}
int Point::getPointCount() {return pointCount;}
int Point::getClusterID(void) const {return clusterID;}
int Point::getPointID(void)const {return pointID;}
pair<double, double> Point::getFeatures(void) const { return features;}

/**
 * @brief Assignment operator overload.
 * @param b The Point object to assign.
 */
void Point::operator=(const Point& b) {
    this->setFeatures(b.getFeatures());
    this->setClusterID(b.getClusterID());
}

void Point::operator=(const Point* b) {
    this->setFeatures(b->getFeatures());
    this->setClusterID(b->getClusterID());
}
/**
 * @brief Print the point information.
 */
void Point::print(void) {
    cout <<
        "ID: " << setw(3) << getPointID() <<
        "  ,  value1: " << fixed << setw(12) << getFeatures().first <<
        "  |  value2: " << fixed << setw(12) << getFeatures().second <<
        "  |  Cluster " << fixed << setw(3) << getClusterID()<<endl;
}

/**
 * @brief Destructor for the Point class.
 */
Point::~Point() {

}
