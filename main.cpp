#include "Point.h"
#include "PointVector.h"
#include "KMeansOperations.h"

int main(int argc, char** argv) {

    KMeansOperations Kmean1("40.txt",2,5);

    Kmean1.run();
    Kmean1.print();
    Kmean1.plot();

    return 0;
}
