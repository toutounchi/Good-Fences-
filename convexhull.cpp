/**
 * @file convexhull.cpp
 * @description Implementation of methods used for computing convex hull using
 *              Graham scan algorithm
 *              https://en.wikipedia.org/wiki/Graham_scan
 *
 * @author      CPSC 221: Basic Algorithms and Data Structures
 *
 * THIS FILE MUST BE SUBMITTED
 **/

 #include "convexhull.h"
 #include <algorithm>
 #include <iostream>
 
 /***************************************************
  * IF YOU WISH TO DEFINE YOUR OWN CUSTOM FUNCTIONS, *
  * ADD THEM HERE                                    *
  ***************************************************/
 
 /**
  * Uses a sorting algorithm of your choice(must be fully implemented by you)
  * to sort the points in v to satisfy the following criteria:
  * 1. v[0] must contain the point with the smallest y-coordinate.
  *      If multiple points have the same smallest y-coordinate, v[0]
  *      must contain the one among those with the smallest x-coordinate.
  * 2. The remaining indices i contain the points, sorted in increasing order
  *      by the angle that the point forms with v[0] and the x-axis. THat is,
  * 	one of the legs of the angle is represened by the line through v[0] and
  *	v[i], and the other is the x-axis.
  * NOTE: "smallest" y-coordinate is actually closest to the TOP of a PNG image.
  **/
 void SortByAngle(vector<pair<double, double>> &v)
 {
    pair<double, double> min = v[0];
    int minIndex = 0;

    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i].second < min.second || (v[i].second == min.second && v[i].first < min.first))
        {
            min = v[i];
            minIndex = i;
        }
    }
    pair<double, double> temp = v[0];
    v[0] = min;
    v[minIndex] = temp;

    for (size_t i = 1; i < v.size(); i++)
    {
        minIndex = i;
        min = v[i];
        double distanceXOuter = v[i].first - v[0].first;
        double distanceYOuter = v[i].second - v[0].second;
        double thetaOuter = atan2(distanceYOuter, distanceXOuter);
        double distanceOuter = (distanceXOuter * distanceXOuter) + (distanceYOuter * distanceYOuter);

        for (size_t j = i; j < v.size(); j++)
        {
            double distanceXInner = v[j].first - v[0].first;
            double distanceYInner = v[j].second - v[0].second;
            double thetaInner = atan2(distanceYInner, distanceXInner);
            double distanceInner = (distanceXInner * distanceXInner) + (distanceYInner * distanceYInner);

            if (thetaInner < thetaOuter || ((abs(thetaInner - thetaOuter) < 1e-9) && (distanceInner < distanceOuter)))
            {
                min = v[j];
                minIndex = j;
                thetaOuter = thetaInner;
                distanceOuter = distanceInner;
            }
        }
        temp = v[i];
        v[i] = min;
        v[minIndex] = temp;
    }
 }
 
 /**
  * Determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
  **/
 bool CCW(pair<double, double> p1, pair<double, double> p2, pair<double, double> p3)
 {
     double ccw_factor = ((p2.first - p1.first) * (p3.second - p1.second)) - ((p2.second - p1.second) * (p3.first - p1.first));
 
 
     if (ccw_factor > 0)
         return true;
 
     return false;
 }
 
 /**
  * Returns a vector of points representing the convex hull of v
  * if c is the vector representing the convex hull, then c[k], c[k+1]
  * is an edge in the convex hull, for all k in 0 to n-1, where n is the
  * number of points in the hull. c[n-1],c[0] is also an edge in the hull.
  * Note that only the endpoints of a colinear sequence will belong in the hull.
  * The returned vector should be a subset of v
  * Input: v - a vector of points in arbitrary order
  **/
 vector<pair<double, double>> GetConvexHull(vector<pair<double, double>> &v)
 {
     if (v.size() < 3)
         return v;
 
     Stack<pair<double, double>> hullStack;
 
     SortByAngle(v);
 
     hullStack.Push(v[0]);
     hullStack.Push(v[1]);
 
     for (size_t i = 2; i < v.size(); i++)
     {
         while (hullStack.Size() > 1)
         {
             pair<double, double> top = hullStack.Pop();
             pair<double, double> next_to_top = hullStack.Peek();
 
             if (CCW(next_to_top, top, v[i]))
             {
                 hullStack.Push(top); // Put back the top element
                 break;
             }
         }
 
         hullStack.Push(v[i]);
     }
 
     vector<pair<double, double>> hull;
 
     while (!hullStack.IsEmpty())
         hull.push_back(hullStack.Pop());
 
     reverse(hull.begin(), hull.end());
 
     return hull;
 }