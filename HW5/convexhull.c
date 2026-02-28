#include <stdio.h>
#include <points.h>

Point reference_point;

void quicksort(Point arr[], int lo, int hi, int (*cmp)(Point, Point));
void mergesort(Point arr[], int l, int r, int (*cmp)(Point, Point));

int ccw(Point a, Point b, Point c) {
    int cross = (b.x - a.x) * (c.y - a.y) -
                (b.y - a.y) * (c.x - a.x);

    if (cross > 0) return 1;
    if (cross < 0) return -1;
    return 0;
}

int compare_points(Point p1, Point p2) {
    if (p1.y == p2.y)
        return p1.x - p2.x;
    return p1.y - p2.y;
}

long long distSq(Point a, Point b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return dx * dx + dy * dy;
}

int compare_by_polar_angle(Point p1, Point p2) {
    int orientation = ccw(reference_point, p1, p2);

    if (orientation == 0) {
        if (distSq(reference_point, p1) <
            distSq(reference_point, p2))
            return -1;
        else
            return 1;
    }

    return (orientation > 0) ? -1 : 1;
}

void convexHull(Point pts[], int n) {

    if (n <= 2) {
        printf("Not enough points\n");
        return;
    }

    
    quicksort(pts, 0, n - 1, compare_points);
    reference_point = pts[0];

    
    mergesort(pts, 1, n - 1, compare_by_polar_angle);

    
    int size = 1;
    for (int i = 1; i < n; i++) {
        while (i < n - 1 &&
               ccw(reference_point, pts[i], pts[i + 1]) == 0) {
            i++;
        }
        pts[size++] = pts[i];
    }

    if (size < 3)
        return;

    Point hull[n];
    int top = 0;

    hull[top++] = pts[0];
    hull[top++] = pts[1];
    hull[top++] = pts[2];

    for (int i = 3; i < size; i++) {
        while (top >= 2 &&
               ccw(hull[top - 2], hull[top - 1], pts[i]) <= 0) {
            top--;
        }
        hull[top++] = pts[i];
    }

    printf("Convex Hull: \n");
    for (int i = 0; i < top; i++) {
        printf("(%d, %d)\n", hull[i].x, hull[i].y);
    }
}