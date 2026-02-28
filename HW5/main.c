#include <stdio.h>
#include <points.h>

void run_test(Point pts[], int count) {

    printf("Input Points: \n");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", pts[i].x, pts[i].y);
    }

    convexHull(pts, count);
}

int main() {

    Point ex1[] = {{0, 0}, {2, 0}, {1, 1}, {2, 2}, {1, 3}, {0, 2}};

    printf("\nBasic Convex Hull: \n");
    run_test(ex1, 6);

    Point ex2[] = {{0, 0}, {1, 1}, {2, 2}, {3, 3}    };

    printf("\nCollinear Points: \n");
    run_test(ex2, 4);

    return 0;
}