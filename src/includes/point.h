#ifndef POINT_H
#define POINT_H

namespace point{

    struct Point2D  {
        double m_x, m_y;
        int m_cluster;
        double m_min_distance;

        Point2D ();
        Point2D (double x, double y);

        double distance(Point2D p);
    };

    struct Clustered2DPoint: Point2D  {
       
    };
}

#endif 