#include "SampleVector.h"

using namespace std;

/**
 * @brief Constructor for SampleVector that initializes an empty vector with a specified length.
 * @param ID The identifier for the vector.
 * @param vectorLength The length of the vector to be created.
 */
SampleVector::SampleVector(int ID, int vectorLength, string typeIn) : vectorID(ID), type(typeIn)
{
    cout << "Constructor of vector " << vectorID << " - " << getType() << endl;
    sampleVectorData = vector<Sample>(vectorLength);
}

/**
 * @brief Destructor for SampleVector.
 */
SampleVector::~SampleVector()
{
    cout<<"Destructor of vector "<<vectorID<< " - " << getType() << endl;
}

/**
 * @brief Sets the vector element at the specified index.
 * @param index The index of the element to set.
 * @param input The Sample object to set at the specified index.
 */
void SampleVector::setVectorElement(int index, Sample input)
{
    sampleVectorData[index] = input;
}

/**
 * @brief Adds a Sample object to the end of the vector.
 * @param input The Sample object to add to the vector.
 */
void SampleVector::addVectorElement(Sample input)
{
    sampleVectorData.push_back(input);
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


string SampleVector::getType(void) const {
    return type;
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
        // Perform a deep copy of sampleVectorData or use the copy constructor
        this->type = other.type;
        this->sampleVectorData = other.sampleVectorData;
    }
    return *this;
}

/**
 * @brief Gets the Sample object at the specified index.
 * @param index The index of the Sample object to retrieve.
 * @return A reference to the Sample object at the specified index.
 */
Sample& SampleVector::getSampleElement(int index)
{
    return getVector()[index];
}

/**
 * @brief Gets the identifier of the vector.
 * @return The identifier of the vector.
 */
int SampleVector::getVectorID(void) const
{
    return vectorID;
}

bool SampleVector::operator<(const SampleVector& other) const{
    return vectorID < other.vectorID;
}

/**
 * @brief Gets the vector data.
 * @return A reference to the vector data.
 */
vector<Sample>& SampleVector::getVector(void)
{
    return sampleVectorData;
}
