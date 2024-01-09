#include "Point.h"
#include "PointVector.h"
#include "KMeansOperations.h"

int main(int argc, char** argv) {

    // Create an instance of KMeansOperations with 3 clusters and 20 epochs.
    KMeansOperations Kmean1("40.txt",5,10);

    // Run the K-Means clustering algorithm.
    Kmean1.run();

    // Print the results of the clustering.
    Kmean1.print();

    // Plot the clusters using matplotlibcpp.
    Kmean1.plotClusters();

    return 0;
}
