/**
 * @file        convexintersection.cpp
 * @description Implementation of methods used for computing convex intersection using
 *              Sutherland-Hodgman algorithm
 *              https://en.wikipedia.org/wiki/Sutherland�Hodgman_algorithm
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
 **/

#include "convexintersection.h"
#include "convexhull.h"
/***************************************************
 * IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
 * ADD THEM HERE                                    *
 ***************************************************/

/**
 * Determines whether a point p1 is inside or outside
 * of a line segment defined by sp1 and sp2
 * sp1 and sp2 should be consistently provided
 * from the convex hull algorithm such that the edges
 * are listed in a CCW direction
 * p1 belongs to the subject polygon
 * sp1 and sp2 belong to the clipping polygon
 **/
bool Inside(pair<double, double> p1, pair<double, double> sp1, pair<double, double> sp2)
{
    return !CCW(sp1, sp2, p1);
}

/**
 * computes the point of intersection between the line segment
 * defined by s1 and s2, and the infinite line defined by
 * i1 and i2.
 * Assume that this will only be called when the intersection exists.
 **/
pair<double, double> ComputeIntersection(pair<double, double> s1, pair<double, double> s2, pair<double, double> i1, pair<double, double> i2)
{
        double x1 = s1.first;
        double y1 = s1.second;

        double x2 = s2.first;
        double y2 = s2.second;

        double x3 = i1.first;
        double y3 = i1.second;

        double x4 = i2.first;
        double y4 = i2.second;
        double m1 = 0, m2 = 0, b1 = 0, b2 = 0, x, y;

        if (fabs((x2 - x1)) < 1e-10)
        {
            x = x1;
            y = m1 * x + b1;
            return pair<double, double>(x, y);
        }

        if (fabs((x4 - x3)) < 1e-10)
        {
            x = x3;
            y = m1 * x + b1;
            return pair<double, double>(x, y);
        }

        m1 = (y2 - y1) / (x2 - x1);
        m2 = (y4 - y3) / (x4 - x3);

        b1 = y1 - (m1 * x1);
        b2 = y3 - (m2 * x3);

        x = (b2 - b1) / (m1 - m2);
        y = m1 * x + b1;

        return pair<double, double>(x, y);
    }

    /**
     * Returns a vector containing a sequence of points defining
     * the intersection of two convex polygons poly1 and poly2
     * Inputs: poly1 and poly2 - sequences of points defining the
     *                           borders of convex polygons
     **/
    vector<pair<double, double>> GetConvexIntersection(vector<pair<double, double>> & poly1, vector<pair<double, double>> & poly2)
    {

        if (poly1.empty() || poly2.empty())
            return vector<pair<double, double>>();

        vector<pair<double, double>> isect = poly1;

        for (size_t i = 0; i < poly2.size(); i++)
        {

            pair<double, double> clipStart = poly2[i];
            pair<double, double> clipEnd = poly2[(i + 1) % poly2.size()];

            vector<pair<double, double>> inputList = isect;
            isect.clear();

            for (size_t j = 0; j < inputList.size(); j++)
            {
                pair<double, double> pointCurr = inputList[j];
                pair<double, double> pointPrev = inputList[(j + inputList.size() - 1) % inputList.size()];

                bool currentInside = Inside(pointCurr, clipStart, clipEnd);
                bool previousInside = Inside(pointPrev, clipStart, clipEnd);

                if (currentInside != previousInside)
                    isect.push_back(ComputeIntersection(clipStart, clipEnd, pointCurr, pointPrev));

                if (currentInside)
                    isect.push_back(pointCurr);
            }
        }

        return isect;
    }
    /*
    reference used for math calculation:
    https://stackoverflow.com/questions/16524096/how-to-calculate-the-point-of-intersection-between-two-lines
    */