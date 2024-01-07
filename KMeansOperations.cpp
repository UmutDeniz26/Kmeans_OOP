/**
 * @file KMeansOperations.cpp
 * @brief Implementation of the KMeansOperations class for K-Means clustering.
 */
#include "KMeansOperations.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

/**
 * @brief Constructor for the KMeansOperations class.
 * @param Kval The number of clusters (K) for K-Means.
 * @param epochVal The number of epochs for K-Means clustering.
 */
KMeansOperations::KMeansOperations(string path ,int Kval, int epochVal) : epoch(epochVal), path(path),
	samples(SampleVector(-3, 0, "Samples Vector")), K(Kval){}

KMeansOperations::KMeansOperations(string path) : path(path), K(0),epoch(0){}

/**
 * @brief Initializes samples with data from a file.
 * @param a The file path containing sample data.
 */
void KMeansOperations::initSamplesWithFile(string a) {
	ifstream inputFile(a);
	double X, Y;int i = 0, j = 1;
	for_each(
		istream_iterator<double>(inputFile),istream_iterator<double>(),
		[&](double value) {
			if (i % 2 == 0){
				X = value;
			}
			else{
				Y = value;
				getSamplesVector().setVectorElement(Sample(j++, 0, std::make_pair(X, Y)));
			}
			i++;}
	);
	inputFile.close();
}

bool KMeansOperations::setK(int k) {
	bool flag = k > 0 and k < Sample::getSampleCount();
	if ( flag ) {K = k;}
	return ( flag ) ? true: false;
}

bool KMeansOperations::setEpoch(int epoch) {
	bool flag = epoch > 0;
	if (flag) { this->epoch = epoch; }
	return (flag) ? true : false;
}

void KMeansOperations::getUserInput(void) {
	int temp_k, temp_epoch;
	bool flag = true;

	while (flag) {
		cout << "Enter the number of clusters (K): ";cin >> temp_k;
		if (!setK(temp_k)) { cout << "Invalid input. Please try again." << endl; continue; }
		
		cout << "Enter the number of epochs: ";cin >> temp_epoch;
		if (!setEpoch(temp_epoch)) { cout << "Invalid input. Please try again." << endl; continue;}
	}	
}


/**
 * @brief Runs the K-Means clustering algorithm.
 */
void KMeansOperations::run(void) {
	initSamplesWithFile(path);
	if (!setK(getK())) {
		getUserInput();
	}
	centroids = SampleVector(-2, getK(), "Centroid Vector");
	clusterVectors = vector<SampleVector>(getK(), SampleVector(-4, 0, "Cluster Vector"));

	initFirstCentroids();
	for (int i = 0; i < getEpoch(); i++) {
		updateCentroids();
	}
}

/**
 * @brief Initializes the first set of centroids randomly.
 */
void KMeansOperations::initFirstCentroids() {
	int i = 0;
	srand(static_cast<unsigned int>(time(nullptr)));//random time
	random_device rd;mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, Sample::getSampleCount());
	transform(centroids.getVector().begin(), centroids.getVector().end(), centroids.getVector().begin(),
		[&](Sample& element) {
			return new Sample(-5, i++, getSamplesVector().getSampleElement(dis(gen)).getFeatures());
		}
	);
}

/**
 * @brief Assigns each sample to its closest cluster based on current centroids.
 * @return The updated samples vector.
 */
SampleVector& KMeansOperations::assignSamplesClosestCluster(void) {
	double d1, d2, d; int newCluster, i = 0;

	deque<double> tempDistanceArr(getK()); 
	deque<double>::iterator maxDistanceIt;
	size_t index;
	
	for_each(getSamplesVector().getVector().begin(), getSamplesVector().getVector().end(),
		[&](Sample& element) {
			for_each(getCentroidVector().getVector().begin(), getCentroidVector().getVector().end(),
			[&](Sample& centroid) {
					d1 = element.getFeatures().first - centroid.getFeatures().first;
					d2 = element.getFeatures().second - centroid.getFeatures().second;
					d = sqrt(pow(d1, 2) + pow(d2, 2));
					tempDistanceArr[(i++ % getK())] = d; //overwrite distances by using mod
			});
		maxDistanceIt = min_element(tempDistanceArr.begin(), tempDistanceArr.end());  // find iterator
		index = distance(tempDistanceArr.begin(), maxDistanceIt); // calculate index
		newCluster = getCentroidVector().getVector()[index].getClusterID(); // decide newCluster
		element.setClusterID(newCluster);
		}
	);

	assignNewClusters();
	return getSamplesVector();
}

void KMeansOperations::addClusterVector(SampleVector& a) {
	getClusterVectors().push_back(a);
}

bool KMeansOperations::isItIncludeVector(SampleVector target, vector<SampleVector> whereToFind) {
	const int k_id = target.getClusterID();
	bool flag=false;
	for_each(whereToFind.begin(), whereToFind.end(), [&](SampleVector& vectorElement) {
		if (vectorElement.getClusterID() == k_id) {
			flag = true;
			return;
		}
	});
	return flag;
}

/**
 * @brief Retrieves vectors of samples classified into individual clusters.
 * @return A vector of SampleVector, each containing samples for a specific cluster.
 */
vector<SampleVector>& KMeansOperations::assignNewClusters() {

	clearClusterVectors(clusterVectors);

	for (int i = 0; i < getK(); i++) {
		remove_copy_if(getSamplesVector().getVector().begin(), getSamplesVector().getVector().end(), back_inserter(clusterVectors[i].getVector()),
			[&](Sample& element) {
				return element.getClusterID() != i;
			});
	}
	return clusterVectors;
}

void KMeansOperations::clearClusterVectors(vector<SampleVector>& in) {
	for_each(in.begin(), in.end(), [&](SampleVector& sampleVectorElement) {
		sampleVectorElement.getVector().clear();
		}
	);
}


/**
 * @brief Updates the centroids based on the current assignment of samples to clusters.
 */
void KMeansOperations::updateCentroids(void) {
	assignSamplesClosestCluster();
	transform(getCentroidVector().getVector().begin(), getCentroidVector().getVector().end(), getCentroidVector().getVector().begin(),
		[&](Sample& element) {
			return Sample(0, element.getClusterID(), calculateCentroidCoordinate(clusterVectors[element.getClusterID()].getVector()));
		});
}


/**
 * @brief Calculates the centroid coordinates based on a vector of samples.
 * @param vectorInput The vector of samples for which to calculate centroid coordinates.
 * @return The centroid coordinates as a pair of doubles.
 */
pair<double, double> KMeansOperations::calculateCentroidCoordinate(vector<Sample> vectorInput) {
	double X = 0, Y = 0;
	for_each(vectorInput.begin(), vectorInput.end(),
		[&](Sample& element) {
			X += element.getFeatures().first;
			Y += element.getFeatures().second;
		});
	X /= vectorInput.size();
	Y /= vectorInput.size();
	//cout << "X: " << X << "    Y: " << Y <<"     size: "<<vectorInput.size() << endl;
	return make_pair(X, Y);
}

int KMeansOperations::getK(void) const {return K;}
int KMeansOperations::getEpoch(void) const {return epoch;}
void KMeansOperations::setCentroid(int index, Sample& input) {centroids.setVectorElement(index, input);}
SampleVector& KMeansOperations::getCentroidVector(void) {return centroids;}
SampleVector& KMeansOperations::getSamplesVector(void) {return samples;}
vector<SampleVector>& KMeansOperations::getClusterVectors() {return clusterVectors;}

const std::vector<std::string> colors = {
	"mediumaquamarine", "lawngreen", "mediumblue", "paleturquoise",
	"mediumpurple", "dodgerblue", "mediumslateblue", "darkcyan",
	"mediumseagreen", "lightcyan", "lightblue", "mediumseagreen",
	"forestgreen", "olive", "darkolivegreen", "lightgoldenrodyellow",
	"olivedrab", "mediumturquoise", "cyan", "seashell", "darkgray",
	"mediumslateblue", "darkblue", "lightyellow", "yellowgreen"
};
/**
 * @brief Prints the centroids and samples vectors.
 */
void KMeansOperations::print() {
	cout << "Centroids: " << endl << "   ";
	getCentroidVector().print();

	cout << endl << "Samples: " << endl << "   ";
	getSamplesVector().print();

	// Print information about clusters
	for (int i = 0; i < getClusterVectors().size(); ++i) {
		cout << "Cluster " << i + 1 <<"( " <<colors[i] <<" )" << ": ";
		cout << "Number of samples: " << getClusterVectors()[i].getVector().size() << endl;
	}

	cout <<endl<< "K value: " << getK() << endl;
	cout << "Epoch: " << getEpoch() << endl;

}

/**
 * @brief Plots the clusters using matplotlibcpp library.
 */
void KMeansOperations::plotClusters() {

	// Plot each cluster
	for (int i = 0; i < getClusterVectors().size(); ++i) {
		vector<double> x, y;

		// Extract x and y coordinates from each sample in the cluster
		for (const auto& sample : getClusterVectors()[i].getVector()) {
			x.push_back(sample.getFeatures().first);
			y.push_back(sample.getFeatures().second);
		}

		// Plot the cluster points
		plt::scatter(x, y, 45, { {"c", colors[i]}});
	}

	// Add labels and show the plot
	plt::xlabel("X-axis");plt::ylabel("Y-axis");plt::title("K-Means Clustering");

	plotCentroids(getCentroidVector());
	plt::show();
}

/**
 * @brief Plots the centroids as red crosses.
 * @param centroids Reference to the centroid vector.
 */
void KMeansOperations::plotCentroids(SampleVector& centroids) {
	vector<double> x, y;
	// Extract x and y coordinates from each centroid
	for (const auto& centroid : centroids.getVector()) {
		x.push_back(centroid.getFeatures().first);
		y.push_back(centroid.getFeatures().second);
	}
	// Plot crosses at the final centroids
	plt::plot(x, y, "rx");  // "rx" specifies red crosses
	plt::pause(0.01);  // Pause to update the plot
}

/**
 * @brief Destructor for the KMeansOperations class.
 */
KMeansOperations::~KMeansOperations()
{
}