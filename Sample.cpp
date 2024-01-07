/**
 * @file Sample.cpp
 * @brief Implementation of the Sample class.
 */

#include "Sample.h"
using namespace std;

/**
 * @brief Static member to keep track of the total number of samples.
 */
int Sample::sampleCount = 0;

/**
 * @brief Constructor for the Sample class.
 * @param ID The sample ID.
 * @param cluster The cluster ID.
 * @param featuresIn A pair representing the features of the sample.
 */
Sample::Sample(int ID, int cluster, pair<double, double> featuresIn) : sampleID(ID), clusterID(cluster), features(featuresIn) {
    //cout<<"Constructor of sample "<<ID<<endl;
    if (ID >0) {
        sampleCount += 1;
    }
}

void Sample::setClusterID(int a) {clusterID = a;}
void Sample::setFeatures(pair<double, double> input) {features = input;}
int Sample::getSampleCount() {return sampleCount;}
int Sample::getClusterID(void) const {return clusterID;}
int Sample::getSampleID(void)const {return sampleID;}
pair<double, double> Sample::getFeatures(void) const { return features;}

/**
 * @brief Assignment operator overload.
 * @param b The Sample object to assign.
 */
void Sample::operator=(const Sample& b) {
    this->setFeatures(b.getFeatures());
    this->setClusterID(b.getClusterID());
}

void Sample::operator=(const Sample* b) {
    this->setFeatures(b->getFeatures());
    this->setClusterID(b->getClusterID());
}
/**
 * @brief Print the sample information.
 */
void Sample::print(void) {
    cout <<
        "ID: " << setw(3) << getSampleID() <<
        "  ,  value1: " << fixed << setw(12) << getFeatures().first <<
        "  |  value2: " << fixed << setw(12) << getFeatures().second <<
        "  |  Cluster " << fixed << setw(3) << getClusterID()<<endl;
}

/**
 * @brief Destructor for the Sample class.
 */
Sample::~Sample() {

}
