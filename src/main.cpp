#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>
#include <limits>

char DELIMITOR = ',';

struct Point {
	double m_x, m_y;
	int m_cluster;
	double m_min_distance;

	Point() : m_x{ 0.0 }, m_y{ 0.0 }, m_cluster{ -1 }, m_min_distance{ std::numeric_limits<double>::max() } {}
	Point(double x, double y) : m_x{x}, m_y{y}, m_cluster{ -1 }, m_min_distance{ std::numeric_limits<double>::max() } {}

	double distance(Point p)
	{
		return (p.m_x - m_x) * (p.m_x - m_x) + (p.m_y - m_y) * (p.m_y - m_y);
	}
};

std::vector<Point> readcsv(){
    std::vector<Point> points;
    std::string line;
    std::ifstream file("D:\\DEVEL\\Development_Datasets\\Mall_Customers.csv");
	
	getline(file, line); // Skip column names

    while (getline(file, line)) {
        std::stringstream lineStream(line);
        std::string bit;
        double x, y;

		// Skip the first three columns
        for (int i = 0; i < 3; ++i) {
            getline(lineStream, bit, ',');
        }

        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }
    return points;
}

std::vector<Point>* kMeansClustering(std::vector<Point> *points, int epochs, int k){
	const int n_points = points->size();
	std::vector<Point> centroids;
	srand(time(0));  // need to set the random seed
	
	for (int i = 0; i < k; ++i) {
		centroids.push_back(points->at(rand() % n_points));
	}

	for (std::vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
    int clusterId = c - begin(centroids); // quick hack to get cluster index

		for (std::vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {	
			Point p = *it;
			double dist = c->distance(p);

			if (dist < p.m_min_distance) {
				p.m_min_distance = dist;
				p.m_cluster = clusterId;
			}
			*it = p;
		}
	}

	std::vector<int> nPoints;
	std::vector<double> sumX, sumY;

	// Initialise with zeroes
	for (int j = 0; j < k; ++j) {
		nPoints.push_back(0);
		sumX.push_back(0.0);
		sumY.push_back(0.0);
	}


	// Iterate over points to append data to centroids
	for (std::vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
		int clusterId = it->m_cluster;
		nPoints[clusterId] += 1;
		sumX[clusterId] += it->m_x;
		sumY[clusterId] += it->m_y;

		it->m_min_distance = std::numeric_limits<double>::max();  // reset distance
	}

	// Compute the new centroids
	for (std::vector<Point>::iterator c = begin(centroids); c != end(centroids); ++c) {
		int clusterId = c - begin(centroids);
		c->m_x = sumX[clusterId] / nPoints[clusterId];
		c->m_y = sumY[clusterId] / nPoints[clusterId];
	}

	return points;
}

void write_to_file(std::vector<Point> *points){
	std::ofstream myfile;
	myfile.open("..\\output\\output.csv");
	myfile << "x,y,c" << std::endl;

	for (std::vector<Point>::iterator it = points->begin(); it != points->end(); ++it) {
		myfile << it->m_x << "," << it->m_y << "," << it->m_cluster << std::endl;
	}
	myfile.close();
}

int main() {
	std::cout << "Reading datapoints \n";
	std::vector<Point> points = readcsv();

	std::cout << "KMeans clustering.. \n";
	std::vector<Point> *clustered_points = kMeansClustering(&points, 1000, 5);

	std::cout << "writing datapoints \n";
	write_to_file(clustered_points);
	return 0;
}