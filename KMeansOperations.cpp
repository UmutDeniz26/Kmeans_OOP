/**
 * @file KMeansOperations.cpp
 * @brief Implementation of the KMeansOperations class for K-Means clustering.
 */
#include "KMeansOperations.h"
#include <cstdlib> 
#include <cmath>
#include <algorithm>
#include <numeric>
#include <deque>
#include <iostream>
#include <random>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

/**
 * @brief Constructor for the KMeansOperations class.
 * @param Kval The number of clusters (K) for K-Means.
 * @param epochVal The number of epochs for K-Means clustering.
 */
KMeansOperations::KMeansOperations(int Kval, int epochVal) : K(Kval), epoch(epochVal), 
	centroids(-2, getK(), "Centroid Vector"), samples(-3,0,"Samples Vector"), 
	clusterVectors(vector<SampleVector> (Kval,SampleVector(-4,0,"Cluster Vector"))) {
	cout << "Constructor of KMEAN " << K << " - " << epoch << endl;

}

/**
 * @brief Initializes samples with data from a file.
 * @param a The file path containing sample data.
 */
void KMeansOperations::initSamplesWithFile(string a) {
	ifstream inputFile(a);
	double X, Y;int i = 0, j = 1;
	
	for_each(
		istream_iterator<double>(inputFile),
		istream_iterator<double>(),
		[&](double value) {
			if (i % 2 == 0)
			{
				X = value;
			}
			else
			{
				Y = value;
				getSamplesVector().addVectorElement(Sample(j++, 0, std::make_pair(X, Y)));
			}
			i++;
		}
	);
	inputFile.close();
}

/**
 * @brief Runs the K-Means clustering algorithm.
 */
void KMeansOperations::run(void) {
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
			return Sample(-1, i++, getSamplesVector().getSampleElement(dis(gen)).getFeatures());
		}
	);

}

/**
 * @brief Assigns each sample to its closest cluster based on current centroids.
 * @return The updated samples vector.
 */
SampleVector& KMeansOperations::assignClosestCluster(void) {
	double d1, d2, d; int newCluster, i = 0;

	deque<double> tempDistanceArr(getK()); deque<double>::iterator maxDistanceIt;
	size_t index;
	
	for_each(getSamplesVector().getVector().begin(), getSamplesVector().getVector().end(),
		[&](Sample& element) {
			for_each(getCentroidVector().getVector().begin(), getCentroidVector().getVector().end(),
			[&](Sample& centroid) {
					d1 = element.getFeatures().first - centroid.getFeatures().first;
					d2 = element.getFeatures().second - centroid.getFeatures().second;
					d = sqrt(pow(d1, 2) + pow(d2, 2));
					tempDistanceArr[(int(i++) % getK())] = d; //overwrite distances by using mod
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
	assignClosestCluster();
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
/**
 * @brief Getter for the number of clusters (K).
 * @return The number of clusters.
 */
int KMeansOperations::getK(void) const {
	return K;
}


/**
 * @brief Getter for the number of epochs.
 * @return The number of epochs.
 */
int KMeansOperations::getEpoch(void) const {
	return epoch;
}


/**
 * @brief Sets a centroid at a specific index in the centroid vector.
 * @param index The index at which to set the centroid.
 * @param input The centroid sample to set.
 */
void KMeansOperations::setCentroid(int index, Sample& input) {
	centroids.setVectorElement(index, input);
}

/**
 * @brief Getter function to obtain the centroid vector.
 * @return Reference to the centroid vector.
 */
SampleVector& KMeansOperations::getCentroidVector(void) {
	return centroids;
}

/**
 * @brief Getter function to obtain the samples vector.
 * @return Reference to the samples vector.
 */
SampleVector& KMeansOperations::getSamplesVector(void) {
	return samples;
}

/**
 * @brief Gets the vectors corresponding to each cluster.
 * @return Vector containing the cluster vectors.
 */
vector<SampleVector>& KMeansOperations::getClusterVectors() {
	return clusterVectors;
}
const std::vector<std::string> colors = {
	"mediumaquamarine", "lawngreen", "mediumblue", "paleturquoise",
	"mediumpurple", "dodgerblue", "mediumslateblue", "darkcyan",
	"mediumseagreen", "lightcyan", "lightblue", "mediumseagreen",
	"forestgreen", "olive", "darkolivegreen", "lightgoldenrodyellow",
	"olivedrab", "mediumturquoise", "cyan", "seashell", "darkgray",
	"mediumslateblue", "darkblue", "lightyellow", "yellowgreen",
	"silver", "papayawhip", "green", "midnightblue", "mediumcyan",
	"aquamarine", "rebeccapurple", "lemonchiffon", "plum", "lightgray",
	"mediumorchid", "darkgray", "royalblue", "limegreen", "skyblue",
	"darkmagenta", "blue", "blueviolet", "indigo", "lightblue",
	"darkviolet", "cyan", "mediumblue", "moccasin", "blueviolet",
	"darkcyan", "mediumseagreen", "ivory", "lightskyblue", "yellowgreen",
	"chartreuse", "darkorchid", "teal", "seagreen", "navy", "azure",
	"darkgreen", "palegreen", "lightgray", "mediumorchid", "mediumslateblue",
	"navajowhite", "beige", "lightyellow", "orchid", "lightskyblue",
	"mediumspringgreen", "antiquewhite", "lavender", "deepskyblue",
	"powderblue", "darkslateblue", "lightgreen", "palegreen", "thistle",
	"azure", "orchid", "blue", "darkorchid", "violet", "cornflowerblue",
	"palegreen", "cornflowerblue", "wheat", "snow", "mediumturquoise",
	"springgreen", "darkblue", "violet", "lightcyan", "seagreen",
	"palegreen", "darkorchid", "darkslateblue", "springgreen", "lavender",
	"chartreuse", "mediumcyan", "mediumpurple", "darkslateblue", "turquoise",
	"mediumturquoise", "fuchsia", "darkcyan", "mediumpurple", "mediumaquamarine",
	"plum", "magenta", "darkgreen", "mediumcyan", "springgreen", "darkorchid",
	"slateblue", "chartreuse", "mediumspringgreen", "chartreuse", "mediumorchid",
	"darkslateblue", "mediumblue"


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
	vector<SampleVector> clusterVectorslocal = getClusterVectors();
	for (int i = 0; i < clusterVectorslocal.size(); ++i) {
		cout << "Cluster " << i + 1 <<"( " <<colors[i] <<" )" << ": ";
		cout << "Number of samples: " << clusterVectorslocal[i].getVector().size() << endl; //clusterVectors[i].size() << endl;


	}
}

/**
 * @brief Plots the clusters using matplotlibcpp library.
 */
void KMeansOperations::plotClusters() {
	// Get cluster vectors
	vector<SampleVector> clusterVectors = assignNewClusters();

	// Plot each cluster
	for (int i = 0; i < clusterVectors.size(); ++i) {
		vector<double> x, y;

		// Extract x and y coordinates from each sample in the cluster
		for (const auto& sample : clusterVectors[i].getVector()) {
			x.push_back(sample.getFeatures().first);
			y.push_back(sample.getFeatures().second);
		}

		// Plot the cluster points
		plt::scatter(x, y, 45, { {"c", colors[i]}});
	}

	// Add labels and show the plot
	plt::xlabel("X-axis");
	plt::ylabel("Y-axis");
	plt::title("K-Means Clustering");

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