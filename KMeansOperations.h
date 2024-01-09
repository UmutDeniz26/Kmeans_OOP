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
    KMeansOperations(string path,int, int); // Constructor with parameters
    KMeansOperations(string path);          // Constructor with only path

    /// Destructor
    ~KMeansOperations(void);

    /// Vector Operations
    void setCentroid(int, Point&);                              // Set centroid of the cluster
    void addClusterVector(PointVector& a) ;                     // Add a cluster vector to the vector of clusters
    void clearClusterVectors(vector<PointVector>&);             // Clear the vector of clusters

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

    /// Print operations
    void print(void);
    void plot();
    void plotCentroids(PointVector&);

    /// K-Means operations
    void run(void);                                                  // Run the K-Means algorithm
    void updateCentroids(void);                                      // Update the centroids
    void initFirstCentroids(void);                                   // Initialize the centroids with random values
    void initPointsWithFile(string);                                 // Initialize the points with the file
    PointVector& assignPointsClosestCluster();                       // Assign points to the closest cluster
    vector<PointVector>& assignNewClusters(void);                    // Assign new clusters to clusterVectors due to new cluster IDs
    pair<double, double> calculateCentroidCoordinate(vector<Point>); // Calculate the centroid coordinate

private:
    int K;                              /**< Number of clusters */
    int epoch;                          /**< Number of iterations */
    const string path;                  /**< Path of the file */

    PointVector points;                 /**< Vector of points */
    PointVector centroids;              /**< Vector of centroids */
    vector<PointVector> clusterVectors; /**< Vector of clusters */

};

#endif
