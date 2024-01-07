/**
 * @file Sample.h
 * @brief Header of the Sample class.
 */

#ifndef SAMPLE_H
#define SAMPLE_H

#include <utility>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

/**
 * @brief Class representing a sample with an ID, cluster ID, and features.
 */
class Sample
{
public:
    Sample(int ID = -1, int cluster = 0, pair<double, double> featuresIn = make_pair(-1, -1));
    ~Sample();

    static int getSampleCount(void);

    void setClusterID(int cluster);
    void setFeatures(pair<double, double> features);

    pair<double, double> getFeatures(void) const;
    int getClusterID(void) const;
    int getSampleID(void) const;

    virtual void print(void);
    void operator=(const Sample& other);

private:
    const int sampleID; ///< The ID of the sample.
    int clusterID;      ///< The cluster ID of the sample.
    static int sampleCount; ///< The count of samples.
    pair<double, double> features; ///< The features of the sample.
};

#endif
