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
    if (ID != -1) {
        sampleCount += 1;
    }
}

/**
 * @brief Setter for the cluster ID.
 * @param a The cluster ID to set.
 */
void Sample::setClusterID(int a) {
    clusterID = a;
}

/**
 * @brief Setter for the features.
 * @param input A pair representing the features to set.
 */
void Sample::setFeatures(pair<double, double> input) {
    features = input;
}

/**
 * @brief Getter for the total sample count.
 * @return The total sample count.
 */
int Sample::getSampleCount() {
    return sampleCount;
}

/**
 * @brief Getter for the features.
 * @return A pair representing the features.
 */
pair<double, double> Sample::getFeatures(void) const {
    return features;
}

/**
 * @brief Getter for the cluster ID.
 * @return The cluster ID.
 */
int Sample::getClusterID(void) const {
    return clusterID;
}

/**
 * @brief Getter for the sample ID.
 * @return The sample ID.
 */
int Sample::getSampleID(void)const {
    return sampleID;
}

/**
 * @brief Assignment operator overload.
 * @param b The Sample object to assign.
 */
void Sample::operator=(const Sample& b) {
    this->setFeatures(b.getFeatures());
    this->setClusterID(b.getClusterID());
}

/**
 * @brief Print the sample information.
 */
void Sample::print(void) {
    cout <<
        "ID: " << setw(3) << getSampleID() <<
        "  ,  value1: " << fixed << setw(12) << getFeatures().first <<
        "  |  value2: " << fixed << setw(12) << getFeatures().second <<
        "  |  Cluster " << fixed << setw(3) << getClusterID() << endl;
}

ostream& Sample::operator<<(ostream& output) const{
        output <<
        "ID: " << setw(3) << getSampleID() <<
        "  ,  value1: " << fixed << setw(12) << getFeatures().first <<
        "  |  value2: " << fixed << setw(12) << getFeatures().second <<
        "  |  Cluster " << fixed << setw(3) << getClusterID() << endl;
        return output;
}   

/**
 * @brief Destructor for the Sample class.
 */
Sample::~Sample() {
    //cout<<"Destructor of sample "<<clusterID<<endl;
    //sampleCount-=1;
}
