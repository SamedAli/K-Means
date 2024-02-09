#include "../includes/csvHandler.h"

#include <string>
#include <fstream>	// for file-reading
#include <iostream> // for file-reading
#include <sstream>	// for file-reading

const char DELIMITOR = ',';

std::vector<point::Point2D> csvHandler::readcsv()
{
    std::vector<point::Point2D> points;
    std::string line;
    std::ifstream file("D:\\DEVEL\\Development_Datasets\\Mall_Customers.csv");

    getline(file, line); // Skip column names

    while (getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string bit;
        double x, y;

        // Skip the first three columns
        for (int i = 0; i < 3; ++i)
        {
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

void csvHandler::write_to_file(const std::vector<point::Point2D> *points)
{
	std::ofstream myfile;
	myfile.open("..\\output\\output.csv");
	myfile << "x,y,c" << std::endl;

	for (std::vector<point::Point2D>::const_iterator it = points->begin(); it != points->end(); ++it)
	{
		myfile << it->m_x << "," << it->m_y << "," << it->m_cluster << std::endl;
	}
	myfile.close();
}