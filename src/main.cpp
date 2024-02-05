#include <ctime>     // for a random seed
#include <fstream>   // for file-reading
#include <iostream>  // for file-reading
#include <sstream>   // for file-reading
#include <vector>
#include <limits>

#include "includes/point.h"
char DELIMITOR = ',';

std::vector<point::Point2D> readcsv(){
    std::vector<point::Point2D> points;
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

        points.push_back(point::Point2D(x, y));
    }
    return points;
}

std::vector<point::Point2D>* kMeansClustering(std::vector<point::Point2D> *points, int epochs, int k){
	const int n_points = points->size();
	std::vector<point::Point2D> centroids;
	srand(time(0));  // need to set the random seed
	
	for (int i = 0; i < k; ++i) {
		centroids.push_back(points->at(rand() % n_points));
	}

	for (std::vector<point::Point2D>::iterator c = begin(centroids); c != end(centroids); ++c) {
    int clusterId = c - begin(centroids); // quick hack to get cluster index

		for (std::vector<point::Point2D>::iterator it = points->begin(); it != points->end(); ++it) {	
			point::Point2D p = *it;
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
	for (std::vector<point::Point2D>::iterator it = points->begin(); it != points->end(); ++it) {
		int clusterId = it->m_cluster;
		nPoints[clusterId] += 1;
		sumX[clusterId] += it->m_x;
		sumY[clusterId] += it->m_y;

		it->m_min_distance = std::numeric_limits<double>::max();  // reset distance
	}

	// Compute the new centroids
	for (std::vector<point::Point2D>::iterator c = begin(centroids); c != end(centroids); ++c) {
		int clusterId = c - begin(centroids);
		c->m_x = sumX[clusterId] / nPoints[clusterId];
		c->m_y = sumY[clusterId] / nPoints[clusterId];
	}

	return points;
}

void write_to_file(std::vector<point::Point2D> *points){
	std::ofstream myfile;
	myfile.open("..\\output\\output.csv");
	myfile << "x,y,c" << std::endl;

	for (std::vector<point::Point2D>::iterator it = points->begin(); it != points->end(); ++it) {
		myfile << it->m_x << "," << it->m_y << "," << it->m_cluster << std::endl;
	}
	myfile.close();
}

int main() {
	std::cout << "Reading datapoints \n";
	std::vector<point::Point2D> points = readcsv();

	std::cout << "KMeans clustering.. \n";
	std::vector<point::Point2D> *clustered_points = kMeansClustering(&points, 1000, 5);

	std::cout << "writing datapoints \n";
	write_to_file(clustered_points);
	return 0;
}