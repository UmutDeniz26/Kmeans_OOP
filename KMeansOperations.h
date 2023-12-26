#ifndef KMEANSOPERATIONS_H
#define KMEANSOPERATIONS_H

#include "SampleVector.h"
#include <string>

using namespace std;

/**
 * @brief Class representing KMeansOperations for K-Means clustering.
 *
 * This class extends SampleVector and provides functionality for K-Means operations.
 */
class KMeansOperations : public SampleVector
{
public:
    KMeansOperations(int, int);
    ~KMeansOperations(void);

    void setCentroid(int, Sample&);
    void addClusterVector(SampleVector& a) ;
    bool isItIncludeVector(SampleVector, vector<SampleVector>);

    int getK(void) const;
    int getEpoch(void) const;
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
    SampleVector& assignClosestCluster();
    pair<double, double> calculateCentroidCoordinate(vector<Sample>);

private:
    const int K; /**< The number of clusters (K). */
    const int epoch; /**< The number of epochs. */

    SampleVector samples; /**< The samples vector. */
    SampleVector centroids; /**< The centroid vector. */
    vector<SampleVector> clusterVectors; /**< Vectors of cluster centroids. */

};

#endif
