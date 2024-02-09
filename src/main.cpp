#include <ctime>	// for a random seed
#include <fstream>	// for file-reading
#include <iostream> // for file-reading
#include <sstream>	// for file-reading
#include <vector>
#include <limits>

#include "includes/point.h"
#include "includes/csvHandler.h"

std::vector<point::Point2D> *kMeansClustering(std::vector<point::Point2D> *points, int epochs, int k)
{
	const int n_points = points->size();
	std::vector<point::Point2D> centroids;
	srand(time(0)); // need to set the random seed

	for (int i = 0; i < k; ++i)
	{
		centroids.push_back(points->at(rand() % n_points));
	}

	for (std::vector<point::Point2D>::iterator c = begin(centroids); c != end(centroids); ++c)
	{
		int clusterId = c - begin(centroids); // quick hack to get cluster index

		for (std::vector<point::Point2D>::iterator it = points->begin(); it != points->end(); ++it)
		{
			point::Point2D p = *it;
			double dist = c->distance(p);

			if (dist < p.m_min_distance)
			{
				p.m_min_distance = dist;
				p.m_cluster = clusterId;
			}
			*it = p;
		}
	}

	std::vector<int> nPoints;
	std::vector<double> sumX, sumY;

	// Initialise with zeroes
	for (int j = 0; j < k; ++j)
	{
		nPoints.push_back(0);
		sumX.push_back(0.0);
		sumY.push_back(0.0);
	}

	// Iterate over points to append data to centroids
	for (std::vector<point::Point2D>::iterator it = points->begin(); it != points->end(); ++it)
	{
		int clusterId = it->m_cluster;
		nPoints[clusterId] += 1;
		sumX[clusterId] += it->m_x;
		sumY[clusterId] += it->m_y;

		it->m_min_distance = std::numeric_limits<double>::max(); // reset distance
	}

	// Compute the new centroids
	for (std::vector<point::Point2D>::iterator c = begin(centroids); c != end(centroids); ++c)
	{
		int clusterId = c - begin(centroids);
		c->m_x = sumX[clusterId] / nPoints[clusterId];
		c->m_y = sumY[clusterId] / nPoints[clusterId];
	}

	return points;
}

int main()
{
	std::cout << "Reading datapoints \n";
	std::vector<point::Point2D> points = csvHandler::readcsv();

	std::cout << "KMeans clustering.. \n";
	std::vector<point::Point2D> *clustered_points = kMeansClustering(&points, 1000, 5);

	std::cout << "writing datapoints \n";
	csvHandler::write_to_file(clustered_points);
	return 0;
}