#include "SampleVector.h"

using namespace std;

/**
 * @brief Constructor for SampleVector that initializes an empty vector with a specified length.
 */
SampleVector::SampleVector(int ID, int vectorLength, string typeIn) : vectorID(ID), type(typeIn), vectorData(vector<Sample>(vectorLength)){
}

/**
 * @brief Destructor for SampleVector.
 */
SampleVector::~SampleVector()
{}


/**
 * @brief Sets the vector element at the specified index.
 */
void SampleVector::setVectorElement(int index, Sample &input){
    vectorData[index] = input;
}

/**
 * @brief Overloaded setVectorElement function to add a Sample to the vector.
 */
void SampleVector::setVectorElement(Sample input){
	vectorData.push_back(input);
}

/**
 * @brief Prints the vector information.
 */
void SampleVector::print(void)
{
    cout << "Vector ID: " << getVectorID() <<"     Vector Type: "<<  getType() << endl;
    for_each(getVector().begin(), getVector().end(),
        [&](Sample& element) {
            cout << "      ";
            element.print();
        });
}

string SampleVector::getType(void) const {return type;}
Sample& SampleVector::getSampleElement(int index){return getVector()[index];}
int SampleVector::getVectorID(void) const{return vectorID;}
vector<Sample>& SampleVector::getVector(void){return vectorData;}


/**
* @brief Overloaded less than operator for SampleVector.
 * @param other The SampleVector to compare to.
 * @return True if the vectorID of this SampleVector is less than the vectorID of the other SampleVector.
*/
bool SampleVector::operator<(const SampleVector& other) const{
    return vectorID < other.vectorID;
}

/**
 * @brief Overloaded assignment operator for SampleVector.
 * @param other The SampleVector to assign from.
 * @return A reference to the assigned SampleVector.
 */
SampleVector& SampleVector::operator=(const SampleVector& other)
{
    if (this != &other)
    {
        // Perform a deep copy of vectorData or use the copy constructor
        this->type = other.type;
        this->vectorData = other.vectorData;
    }
    return *this;
}
