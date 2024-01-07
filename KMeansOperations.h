#ifndef KMEANSOPERATIONS_H
#define KMEANSOPERATIONS_H

#include "PointVector.h"
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
 * This class extends PointVector and provides functionality for K-Means operations.
 */
class KMeansOperations : public PointVector
{
public:
    KMeansOperations(string path,int=0, int=0);
    KMeansOperations(string path);

    ~KMeansOperations(void);

    void setCentroid(int, Point&);
    void addClusterVector(PointVector& a) ;
    bool isItIncludeVector(PointVector, vector<PointVector>);

    bool setK(int);
    bool setEpoch(int);


    int getK(void) const;
    int getEpoch(void) const;
    void getUserInput(void);
    PointVector& getPointsVector(void);
    PointVector& getCentroidVector(void);
    vector<PointVector>& getClusterVectors(void);
    vector<PointVector>& assignNewClusters(void);
    void clearClusterVectors(vector<PointVector>&);

    void print(void);
    void plotClusters();
    void plotCentroids(PointVector&);

    void run(void);
    void updateCentroids(void);
    void initFirstCentroids(void);
    void initPointsWithFile(string);
    PointVector& assignPointsClosestCluster();
    pair<double, double> calculateCentroidCoordinate(vector<Point>);

private:
    int K; /**< The number of clusters (K). */
    int epoch; /**< The number of epochs. */
    const string path; /**< The path of the file. */

    PointVector points; /**< The points vector. */
    PointVector centroids; /**< The centroid vector. */
    vector<PointVector> clusterVectors; /**< Vectors of cluster centroids. */

};

#endif
