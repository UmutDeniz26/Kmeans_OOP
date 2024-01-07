#include "PointVector.h"

using namespace std;

/**
 * @brief Constructor for PointVector that initializes an empty vector with a specified length.
 */
PointVector::PointVector(int ID, int vectorLength, string typeIn) : vectorID(ID), type(typeIn), vectorData(vector<Point>(vectorLength)){
}

/**
 * @brief Destructor for PointVector.
 */
PointVector::~PointVector()
{}


/**
 * @brief Sets the vector element at the specified index.
 */
void PointVector::setVectorElement(int index, Point &input){
    vectorData[index] = input;
}

/**
 * @brief Overloaded setVectorElement function to add a Point to the vector.
 */
void PointVector::setVectorElement(Point input){
	vectorData.push_back(input);
}

/**
 * @brief Prints the vector information.
 */
void PointVector::print(void)
{
    cout << "Vector ID: " << getVectorID() <<"     Vector Type: "<<  getType() << endl;
    for_each(getVector().begin(), getVector().end(),
        [&](Point& element) {
            cout << "      ";
            element.print();
        });
}

string PointVector::getType(void) const {return type;}
Point& PointVector::getPointElement(int index){return getVector()[index];}
int PointVector::getVectorID(void) const{return vectorID;}
vector<Point>& PointVector::getVector(void){return vectorData;}


/**
* @brief Overloaded less than operator for PointVector.
 * @param other The PointVector to compare to.
 * @return True if the vectorID of this PointVector is less than the vectorID of the other PointVector.
*/
bool PointVector::operator<(const PointVector& other) const{
    return vectorID < other.vectorID;
}

/**
 * @brief Overloaded assignment operator for PointVector.
 * @param other The PointVector to assign from.
 * @return A reference to the assigned PointVector.
 */
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
