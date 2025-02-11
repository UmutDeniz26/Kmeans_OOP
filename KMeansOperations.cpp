#include "KMeansOperations.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;
using namespace std;

/// Constructors
KMeansOperations::KMeansOperations(string path ,int Kval, int epochVal) : epoch(epochVal), path(path),
	points(PointVector(1, 0, "Samples Vector")),K(Kval){
}
KMeansOperations::KMeansOperations(string path) : 
	path(path), K(0),epoch(0), points(PointVector( getandIncrementVectorCount(), 0, "Samples Vector")){
}

/// This function is used to initialize points with random values
void KMeansOperations::initPointsWithFile(string filePath) {
	
	ifstream inputFile(filePath);
	try{
		if (!inputFile.is_open()) {
			throw invalid_argument("File is not found!");
		}
	}
	catch (const invalid_argument& e)
	{
		cout << "Error: " <<e.what() << endl;
		exit(1);
	}
	double X, Y;int i = 0, j = 1;
	for_each(
		istream_iterator<double>(inputFile),istream_iterator<double>(),
		[&](double value) {
			if (i % 2 == 0){
				X = value;
			}
			else{
				Y = value;
				getPointsVector().setVectorElement(Point(getandIncrementPointCount(), 0, make_pair(X, Y)));
			}
			i++;
		}
	);
	inputFile.close();
}

/// This function is used to set K value and check if it is valid, then return true or false
bool KMeansOperations::setK(int k) {
	bool flag = k > 0 and k < Point::getPointCount();
	if ( flag ) {K = k;}
	return ( flag ) ? true: false;
}

/// This function is used to set Epoch value and check if it is valid, then return true or false
bool KMeansOperations::setEpoch(int epoch) {
	bool flag = epoch > 0;
	if (flag) { this->epoch = epoch; }
	return (flag) ? true : false;
}

/// This function is used to get user input for K and Epoch values
void KMeansOperations::getUserInput(void) {
	int temp_k, temp_epoch;
	bool flag = true;

	while (flag) {
		flag = false;
		try {
			cout << "Enter the number of clusters (K): "; cin >> temp_k;
			if (!setK(temp_k)) { throw invalid_argument("Invalid input. Please try again.");}

			cout << "Enter the number of epochs: "; cin >> temp_epoch;
			if (!setEpoch(temp_epoch)) { throw invalid_argument("Invalid input. Please try again."); }
		}
		catch ( const invalid_argument& e){ 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system( "cls" );
			cout << "Error: " << e.what() << endl;
			flag = true; 
			continue;
		}
	}	
}

/// This function is used to run the K-Means algorithm
void KMeansOperations::run(void) {
	initPointsWithFile(path);
	if (!setK(getK()) or !setEpoch(getEpoch())) {
		getUserInput();
	}
	centroids = PointVector(-2, getK(), "Centroid Vector");
	clusterVectors = vector<PointVector>(getK(), PointVector(-2, 0, "Cluster Vector"));

	initFirstCentroids();
	for (int i = 0; i < getEpoch(); i++) {
		updateCentroids();
	}
}

/// This function is used to initialize centroids with random values
void KMeansOperations::initFirstCentroids() {
	srand(static_cast<unsigned int>(time(nullptr)));
	
	vector<int> randomNumbers( getPointCount());
	for (int i = 0; i < getPointCount(); ++i) {randomNumbers[i] = i;}
	random_shuffle(randomNumbers.begin(), randomNumbers.end());

	int i = 0;
	for_each(centroids.getVector().begin(), centroids.getVector().end(),
		[&](Point& element) {
			element.setClusterID(i++);
			element.setFeatures(getPointsVector().getVector()[randomNumbers[i]].getFeatures());
		}
	);
}

/// This function is used to assign points to the closest cluster ( element.setClusterID() )
PointVector& KMeansOperations::assignPointsClosestCluster(void) {
	double d1, d2, d; int newCluster, i = 0;

	deque<double> tempDistanceArr(getK()); 
	deque<double>::iterator maxDistanceIt;
	size_t index;
	
	for_each(getPointsVector().getVector().begin(), getPointsVector().getVector().end(),
		[&](Point& element) {
			for_each(getCentroidVector().getVector().begin(), getCentroidVector().getVector().end(),
				[&](Point& centroid) {
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
	//assign new clusters to clusterVectors due to new cluster IDs
	assignNewClusters();
	return getPointsVector();
}

/// This function is used to assign new clusters to clusterVectors due to new cluster IDs ( to update clusterVectors )
vector<PointVector>& KMeansOperations::assignNewClusters() {
	clearClusterVectors(clusterVectors);
	for (int i = 0; i < getK(); i++) {
		remove_copy_if(getPointsVector().getVector().begin(), getPointsVector().getVector().end(), 
			back_inserter(clusterVectors[i].getVector()), //back_inserter is used to insert elements to the end of the vector
			[&](Point& element) {
				return element.getClusterID() != i;
			});
	}
	return clusterVectors;
}

/// This function is used to update centroids
void KMeansOperations::updateCentroids(void) {
	assignPointsClosestCluster();
	transform(getCentroidVector().getVector().begin(), getCentroidVector().getVector().end(), getCentroidVector().getVector().begin(),
		[&](Point& element) {
			return Point(0, element.getClusterID(), 
				calculateCentroidCoordinate(clusterVectors[element.getClusterID()].getVector()) );
		});
}

/// This function is used to calculate centroid coordinates
pair<double, double> KMeansOperations::calculateCentroidCoordinate(vector<Point> vectorInput) {
	double X = 0, Y = 0;
	for_each(vectorInput.begin(), vectorInput.end(),
		[&](Point& element) {
			X += element.getFeatures().first;
			Y += element.getFeatures().second;
		});
	X /= vectorInput.size();
	Y /= vectorInput.size();
	return make_pair(X, Y);
}

/// Getters and setters
int KMeansOperations::getK(void) const {return K;}
int KMeansOperations::getEpoch(void) const {return epoch;}
void KMeansOperations::setCentroid(int index, Point& input) {centroids.setVectorElement(index, input);}
PointVector& KMeansOperations::getCentroidVector(void) {return centroids;}
PointVector& KMeansOperations::getPointsVector(void) {return points;}
vector<PointVector>& KMeansOperations::getClusterVectors() {return clusterVectors;}


/// These three functions are used to add, clear and check if a vector is included in a vector of vectors
void KMeansOperations::addClusterVector(PointVector& a) {
	getClusterVectors().push_back(a);
}
void KMeansOperations::clearClusterVectors(vector<PointVector>& in) {
	for_each(in.begin(), in.end(), [&](PointVector& pointVectorElement) {
		pointVectorElement.getVector().clear();
		}
	);
}

/// This vector is used to store colors for clusters
const vector<string> colors = {
	"mediumaquamarine", "lawngreen", "mediumblue", "paleturquoise","mediumpurple", "dodgerblue",
	"mediumslateblue", "darkcyan", "mediumseagreen", "lightcyan", "lightblue", "mediumseagreen",
	"forestgreen", "olive", "darkolivegreen", "lightgoldenrodyellow", "olivedrab", "mediumturquoise",
	"cyan", "seashell", "darkgray", "darkslategray", "darkslateblue", "darkgreen", "darkblue", "darkred",
	"darkmagenta", "darkgoldenrod", "darkorange", "darkorchid", "darkviolet", "darkkhaki", "darkcyan",
	"darkturquoise", "cadetblue", "firebrick", "indianred", "indigo", "lightcoral", "lightpink", "lightsalmon"
};

/// This function is used to print information about the clusters
void KMeansOperations::print() {
	cout << "Centroids: " << endl << "   ";
	getCentroidVector().print();

	cout << endl << "Points: " << endl << "   ";
	getPointsVector().print();

	// Print information about clusters
	cout<<endl<<endl<<"Clusters: "<<endl;
	for (int i = 0; i < getClusterVectors().size(); ++i) {
		cout << "Cluster " << i + 1 <<"( " <<colors[i] <<" )" << ": "
			 <<"Number of points: " << getClusterVectors()[i].getVector().size() << endl;
	}
	cout <<endl<< "K value: " << getK() << endl;
	cout << "Epoch: " << getEpoch() << endl;

}

/// This function is used to plot the clusters
void KMeansOperations::plot() {

	// Plot each cluster
	for (int i = 0; i < getClusterVectors().size(); ++i) {
		vector<double> x, y;

		// Extract x and y coordinates from each point in the cluster
		for (const auto& point : getClusterVectors()[i].getVector()) {
			x.push_back(point.getFeatures().first);
			y.push_back(point.getFeatures().second);
		}

		// Plot the cluster points
		plt::scatter(x, y, 45, { {"c", colors[i]}});
	}

	// Add labels and show the plot
	plt::xlabel("X-axis");plt::ylabel("Y-axis");plt::title("K-Means Clustering");

	plotCentroids(getCentroidVector());
	plt::show();
}

/// This function is used to plot the centroids
void KMeansOperations::plotCentroids(PointVector& centroids) {
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

/// Destructor
KMeansOperations::~KMeansOperations()
{}