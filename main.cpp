#include "Sample.h"
#include "SampleVector.h"
#include "KMeansOperations.h"
#include "Timer.h"

int main(int argc, char** argv) {

    // Start the timer to measure the overall runtime of the program.
    Timer timerRunTime;
    timerRunTime.start();

    // Create an instance of KMeansOperations with 3 clusters and 20 epochs.
    KMeansOperations Kmean1(6, 10);

    // Initialize sample data from the file "40.txt".
    Kmean1.initSamplesWithFile("40.txt");

    // Run the K-Means clustering algorithm.
    Kmean1.run();

    // Print the results of the clustering.
    Kmean1.print();
    // Stop the timer and print the overall runtime of the program.
    timerRunTime.end();
    timerRunTime.print();

    // Plot the clusters using matplotlibcpp.
    Kmean1.plotClusters();


    Sample a(1, 0, make_pair(-1, -1));
    cout << a;

    return 0;
}
