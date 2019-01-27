// graphics.h
//
//
#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#define _USE_MATH_DEFINES
#include <math.h>

///////////////////////////////////////////////////////////////////////

typedef struct Point2f
{
    float x;
    float y;
} Point2f;


typedef struct LineVector
{
    Point2f start;
    Point2f end;
    float azimuth;
} LineVector;


static float GetAzimuth(const Point2f * start, const Point2f * end)
{
	float az = atan2(end->y - start->y, end->x - start->x);

    if (az < 0) {
        az += (float) M_PI * 2;
    }

    if (az > 2 * M_PI) {
        az -= (float) M_PI * 2;
    }

	return (float) az;
}


static int IsVertical(float az1, float az2, float threshold)
{
    float d = fabs(az1 - az2);

    if (d > (float) M_PI_2 - threshold && d < (float) M_PI_2 + threshold) {
        return 1;
    }

    if (d > (float) (M_PI + M_PI_2) - threshold && d < (float) (M_PI + M_PI_2) + threshold) {
        return 1;
    }

    return 0;
}


int IsParallel(float az1, float az2, float threshold)
{
    int n;

    for (n = -3; n < 3; ++n) {
        if (fabs(az1+n*M_PI - az2) < threshold) {
            return 1;
        }
    }

    return 0;
}


static double GetDistanceSq(const Point2f * start, const Point2f * end)
{
    return (double) ((end->y - start->y) * (end->y - start->y) + (end->x - start->x) * (end->x - start->x));
}


static float GetDistance(const Point2f * start, const Point2f * end)
{
    return (float) sqrt((end->y - start->y) * (end->y - start->y) + (end->x - start->x) * (end->x - start->x));
}


// group lines by azimuth
//
static int GroupLines(LineVector * lines, int num, int * in_out_groups, float threshold_degree)
{
    int i, j;
    float threshold = (float) (M_PI * threshold_degree/180.0);

    int azimuthid = 1;
    in_out_groups[0] = azimuthid;

    for (i = 1; i < num; ++i) {
        in_out_groups[i] = 0;

        for (j = 0; j < i; ++j) {
            if (IsParallel(lines[i].azimuth, lines[j].azimuth, threshold)) {
                in_out_groups[i] = in_out_groups[j];
            }
        }

        if (in_out_groups[i] == 0) {
            in_out_groups[i] = ++azimuthid;
        }
    }

    if (azimuthid > 1) {
        /* bubble sort by groupid */
        int grpid;
        LineVector lvec;

        for (j = 0; j < num - 1; j++) {
            for (i = 0; i < num - 1 - j; i++) {
                if (in_out_groups[i] > in_out_groups[i + 1]) {
                    grpid = in_out_groups[i];
                    in_out_groups[i] = in_out_groups[i + 1];
                    in_out_groups[i + 1] = grpid;

                    lvec = lines[i];
                    lines[i] = lines[i + 1];
                    lines[i + 1] = lvec;
                }
            }
        }
    }

    return azimuthid;
}


static int IsIntersect(Point2f * a1, Point2f * a2, Point2f * b1, Point2f * b2, Point2f * pt, double epsilon)
{
    float dx1 = a2->x - a1->x;
    float dy1 = a2->y - a1->y;
    float dx2 = b2->x - b1->x;
    float dy2 = b2->y - b1->y;

    float delta = dy1 * dx2 - dx1 * dy2;

    if (fabs(delta) < epsilon) {
        // parallel
        return 0;
    }

	float dx = (b1->y - a1->y) * dx1 * dx2  + a1->x * dx2 * dy1 - b1->x * dx1 * dy2;
	float dy = (a1->x - b1->x) * dy1 * dy2 - a1->y * dx1 * dy2 + b1->y * dy1 * dx2;

	if (pt) {
		pt->x = dx / delta;
		pt->y = dy / delta;
	}

    // intersect
	return 1;
}



static void SortPointsAscYX(Point2f * points, int num)
{
    int i, j;
    Point2f pt;

    /* bubble sort by Y-coord */
    for (j = 0; j < num - 1; j++) {
        for (i = 0; i < num - 1 - j; i++) {
            if (points[i].y > points[i + 1].y) {
                pt = points[i];
                points[i] = points[i + 1];
                points[i + 1] = pt;
            } else if (points[i].y < points[i + 1].y) {
                // do nothing
            } else {
                if (points[i].x > points[i + 1].x) {
                    pt = points[i];
                    points[i] = points[i + 1];
                    points[i + 1] = pt;
                }
            }
        }
    }
}


static int IntersectGroupLines(LineVector * lines, int numlines, int * groups, Point2f ** out_intersect_points,
    int ** out_ptgroups, double snap_pixels)
{
    int i, j;
    int num = 0;

    for (i = 1; i < numlines; ++i) {
        for (j = 0; j < i; ++j) {
            if (groups[i] != groups[j]) {
                if (IsIntersect(&lines[i].start, &lines[i].end, &lines[j].start, &lines[j].end, 0, FLT_EPSILON)) {
                    ++num;
                }
            }
        }
    }

    if (num > 0) {
        Point2f pt;
        Point2f * points = (Point2f *) calloc(num, sizeof(Point2f));

        num = 0;

        for (i = 1; i < numlines; ++i) {
            for (j = 0; j < i; ++j) {
                if (groups[i] != groups[j]) {
                    if (IsIntersect(&lines[i].start, &lines[i].end, &lines[j].start, &lines[j].end, &pt, FLT_EPSILON)) {
                        points[num++] = pt;
                    }
                }
            }
        }

        SortPointsAscYX(points, num);

        if (out_ptgroups) {
            int * ptgroups = (int *) calloc(num + 1, sizeof(int));

            int ptgrpid = 0;
            ptgroups[0] = ++ptgrpid;

            for (i = 1; i < num; ++i) {
                for (j = 0; j < i; ++j) {
                    if (GetDistance(&points[i], &points[j]) < snap_pixels) {
                        ptgroups[i] = ptgroups[j];
                        break;
                    }
                }

                if (! ptgroups[i]) {
                    ptgroups[i] = ++ptgrpid;
                }
            }

            ptgroups[num] = ptgrpid;

            *out_ptgroups = ptgroups;
        }

        *out_intersect_points = points;
    }

    return num;
}


///////////////////////////////////////////////////////////////////////
#endif // GRAPHICS_H_INCLUDED