#ifndef SAMPLE_H
#define SAMPLE_H

#include <utility>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Point
{
public:
    /// Constructor.
    Point(int ID = -1, int cluster = 0, pair<double, double> featuresIn = make_pair(-1, -1));
    
    /// Destructor.
    ~Point();

    /// Setters.
    void setClusterID(int);
    void setFeatures(pair<double, double>);

    /// Getters.
    pair<double, double> getFeatures(void) const;
    int getClusterID(void) const;
    int getPointID(void) const;
    static int getPointCount(void);

    /// Print the point.
    virtual void print(void);
    
    /// Operators overloading.
    void operator=(const Point&);
    void operator=(const Point*);

private:
    pair<double, double> features; ///< The features of the point.
    static int pointCount; ///< The count of points.
    const int pointID; ///< The ID of the point.
    int clusterID;      ///< The cluster ID of the point.
    
};

#endif
