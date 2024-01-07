#ifndef KMEANSOPERATIONS_H
#define KMEANSOPERATIONS_H

#include "SampleVector.h"
#include <string>
#include <cstdlib> 
#include <cmath>
#include <algorithm>
#include <numeric>
#include <deque>
#include <iostream>
#include <random>

using namespace std;

/**
 * @brief Class representing KMeansOperations for K-Means clustering.
 *
 * This class extends SampleVector and provides functionality for K-Means operations.
 */
class KMeansOperations : public SampleVector
{
public:
    KMeansOperations(string path,int=0, int=0);
    KMeansOperations(string path);

    ~KMeansOperations(void);

    void setCentroid(int, Sample&);
    void addClusterVector(SampleVector& a) ;
    bool isItIncludeVector(SampleVector, vector<SampleVector>);

    bool setK(int);
    bool setEpoch(int);


    int getK(void) const;
    int getEpoch(void) const;
    void getUserInput(void);
    SampleVector& getSamplesVector(void);
    SampleVector& getCentroidVector(void);
    vector<SampleVector>& getClusterVectors(void);
    vector<SampleVector>& assignNewClusters(void);
    void clearClusterVectors(vector<SampleVector>&);

    void print(void);
    void plotClusters();
    void plotCentroids(SampleVector&);

    void run(void);
    void updateCentroids(void);
    void initFirstCentroids(void);
    void initSamplesWithFile(string);
    SampleVector& assignSamplesClosestCluster();
    pair<double, double> calculateCentroidCoordinate(vector<Sample>);

private:
    int K; /**< The number of clusters (K). */
    int epoch; /**< The number of epochs. */
    const string path; /**< The path of the file. */

    SampleVector samples; /**< The samples vector. */
    SampleVector centroids; /**< The centroid vector. */
    vector<SampleVector> clusterVectors; /**< Vectors of cluster centroids. */

};

#endif
