#ifndef POINTS_H
#define POINTS_H

typedef struct {
    int x;
    int y;
} Point;

int ccw(Point a, Point b, Point c);
double getAngle(Point origin, Point p);
long long distSq(Point a, Point b);

int compare_points(Point a, Point b);
int compare_by_polar_angle(Point a, Point b);

void convexHull(Point pts[], int n);

#endif