#include "PointVector.h"
using namespace std;

/// Constructors
PointVector::PointVector(int ID, int vectorLength, string typeIn) : 
    vectorID(ID), type(typeIn), vectorData(vector<Point>(vectorLength)){
}

/// Destructor
PointVector::~PointVector(){
}

int PointVector::vectorCount = 0;

/// Vector Operations
void PointVector::setVectorElement(int index, Point &input){
    vectorData[index] = input;
}
void PointVector::setVectorElement(Point input){
	vectorData.push_back(input);
}

/// Getters
string PointVector::getType(void) const {return type;}
Point& PointVector::getPointElement(int index){return getVector()[index];}
int PointVector::getVectorID(void) const{return vectorID;}
vector<Point>& PointVector::getVector(void){return vectorData;}
int PointVector::getandIncrementVectorCount(void){return ++vectorCount;}

/// Prints the vector and its features
void PointVector::print(void){
    cout << "Vector ID: " << getVectorID() << "     Vector Type: " << getType() << endl;
    for_each(getVector().begin(), getVector().end(),
        [&](Point& element) {
            cout << "      ";
            element.print();
        });
}

/// Overloaded Operators
bool PointVector::operator<(const PointVector& other) const{
    return vectorID < other.vectorID;
}
PointVector& PointVector::operator=(const PointVector& other)
{
    if (this != &other)
    {
        // Perform a deep copy of vectorData or use the copy constructor
        this->type = other.type;
        this->vectorData = other.vectorData;
    }
    return *this;
}
