#ifndef SAMPLEVECTOR_H
#define SAMPLEVECTOR_H

#include "Point.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * @brief Class representing a vector of points.
 *
 * This class extends the Point class and provides functionality
 * for managing a vector of points.
 */

class PointVector : public Point
{
public:
    PointVector(int ID = -1, int vectorLength = 0, string typeIn = "Not Defined");
    ~PointVector();

    void setVectorElement(int index, Point &input);
    void setVectorElement(Point input);


    Point& getPointElement(int index);
    int getVectorID(void) const;
    vector<Point>& getVector(void);
    string getType(void) const;

    virtual void print(void);
    PointVector& operator=(const PointVector& other);

    bool operator<(const PointVector& other) const;

private:
    string type;
    const int vectorID; /**< The ID of the vector. */
    vector<Point> vectorData; /**< The vector containing points. */
};

#endif
