#ifndef SAMPLEVECTOR_H
#define SAMPLEVECTOR_H

#include "Point.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class PointVector : public Point
{
public:
    /// Constructor 
    PointVector(int ID = getandIncrementVectorCount(), int vectorLength = 0, string typeIn = "Not Defined");
    
    /// Destructor
    ~PointVector();

    /// Setters
    void setVectorElement(int index, Point &input);
    void setVectorElement(Point input);

    /// Getters
    Point& getPointElement(int index);
    int getVectorID(void) const;
    vector<Point>& getVector(void);
    string getType(void) const;
    static int getandIncrementVectorCount(void);

    /// Prints the vector
    virtual void print(void);
    
    /// Overloaded operators
    PointVector& operator=(const PointVector& other);
    bool operator<(const PointVector& other) const;

private:
    static int vectorCount;   /**< The number of vectors. */
    string type;              /**< The type of the vector. */
    const int vectorID;       /**< The ID of the vector. */
    vector<Point> vectorData; /**< The vector containing points. */
};

#endif
