#ifndef SAMPLEVECTOR_H
#define SAMPLEVECTOR_H

#include "Sample.h"
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

/**
 * @brief Class representing a vector of samples.
 *
 * This class extends the Sample class and provides functionality
 * for managing a vector of samples.
 */

class SampleVector : public Sample
{
public:
    SampleVector(int ID = -1, int vectorLength = 0, string typeIn = "Not Defined");
    ~SampleVector();

    void setVectorElement(int index, Sample &input);
    void setVectorElement(Sample input);


    Sample& getSampleElement(int index);
    int getVectorID(void) const;
    vector<Sample>& getVector(void);
    string getType(void) const;

    virtual void print(void);
    SampleVector& operator=(const SampleVector& other);

    bool operator<(const SampleVector& other) const;

private:
    string type;
    const int vectorID; /**< The ID of the vector. */
    vector<Sample> vectorData; /**< The vector containing samples. */
};

#endif
