#ifndef POINT_H
#define POINT_H

namespace point
{

    class Point2D
    {
    public:
        double m_x, m_y;
        int m_cluster;
        double m_min_distance;

        Point2D();
        Point2D(double x, double y);

        virtual double distance(Point2D p);

    private:
    };

    class Clustered2DPoint : public Point2D
    {
    public:
        double distance(Point2D p) final;
    };
}

#endif