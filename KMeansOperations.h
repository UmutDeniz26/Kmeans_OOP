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

class KMeansOperations : public PointVector
{
public:
    /// Constructors
    KMeansOperations(string path,int=0, int=0);
    KMeansOperations(string path);

    /// Destructor
    ~KMeansOperations(void);

    /// Vector Operations
    void setCentroid(int, Point&);
    void addClusterVector(PointVector& a) ;
    void clearClusterVectors(vector<PointVector>&);
    bool doesItIncludeVector(PointVector, vector<PointVector>);

    /// Setters
    bool setK(int);
    bool setEpoch(int);

    /// Getters
    int getK(void) const;
    int getEpoch(void) const;
    void getUserInput(void);
    PointVector& getPointsVector(void);
    PointVector& getCentroidVector(void);
    vector<PointVector>& getClusterVectors(void);
    vector<PointVector>& assignNewClusters(void);
    
    /// Print operations
    void print(void);
    void plotClusters();
    void plotCentroids(PointVector&);

    /// K-Means operations
    void run(void);
    void updateCentroids(void);
    void initFirstCentroids(void);
    void initPointsWithFile(string);
    PointVector& assignPointsClosestCluster();
    pair<double, double> calculateCentroidCoordinate(vector<Point>);

private:
    int K;                              /**< Number of clusters */
    int epoch;                          /**< Number of iterations */
    const string path;                  /**< Path of the file */

    PointVector points;                 /**< Vector of points */
    PointVector centroids;              /**< Vector of centroids */
    vector<PointVector> clusterVectors; /**< Vector of clusters */

};

#endif
