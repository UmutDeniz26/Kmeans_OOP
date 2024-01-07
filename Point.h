/**
 * @file Point.h
 * @brief Header of the Point class.
 */

#ifndef SAMPLE_H
#define SAMPLE_H

#include <utility>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/**
 * @brief Class representing a point with an ID, cluster ID, and features.
 */
class Point
{
public:
    Point(int ID = -1, int cluster = 0, pair<double, double> featuresIn = make_pair(-1, -1));
    ~Point();

    void setClusterID(int);
    void setFeatures(pair<double, double>);

    pair<double, double> getFeatures(void) const;
    int getClusterID(void) const;
    int getPointID(void) const;
    static int getPointCount(void);

    virtual void print(void);
    void operator=(const Point&);
    void operator=(const Point*);

private:
    pair<double, double> features; ///< The features of the point.
    static int pointCount; ///< The count of points.
    const int pointID; ///< The ID of the point.
    int clusterID;      ///< The cluster ID of the point.
    
};

#endif
