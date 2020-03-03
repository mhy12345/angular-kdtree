#include <cassert>
#include <vector>
#include <iostream>
#include <random>
#include <map>
#include "kdtree.h"
#include "kdt_toolbox.h"
using namespace std;
#define PI 3.1415926535


void test_kdtree() {
    printf(" ======= TEST kdtree =======\n");
    srand(0);
    vector<Point> plist;
    KDTree kdt = KDTree();
    int n = 150;
    for (int i=0;i<n;i++) {
        Point pt = Point(random()%10000/10000.0*PI*2, random()%10000/10000.0*PI - PI/2, NULL);
        double res = 0.1;
        for (int j=0;j<plist.size();j++) {
            res = min(res, point_dist(pt, plist[j]));
        }
        plist.push_back(pt);
        
        pair<double,const Point*> kdt_res = kdt.Search(pt, 0.1);
        kdt.Insert(pt);
        if (kdt_res.second) {
            printf("Insert a new Point(% 6.4f, % 6.4f), the nearest point is (% 6.4f, % 6.4f) with distance %f\n", pt.x, pt.y, kdt_res.second->x, kdt_res.second->y, kdt_res.first);
        } else {
            printf("Insert a new Point(% 6.4f, % 6.4f), which is the first point in the neighbourhood.\n", pt.x, pt.y);
        }
        assert(abs(res - kdt_res.first) < 1e-6); //Check if the distance is correct.
    }
    kdt.Release();
}

int test_toolbox() { // Python APIs
    printf(" ======= TEST kdt-toolbox =======\n");
    int n = 10;
    double xs[] = {24.9583002704574, 25.1251411711769, 26.46375, 27.1367, 25.015202, 27.1, 25.8252163601644, 25.1061233286553, 27.104, 26.317882};
    double ys[] = {3.2076758723864, 5.0988428363439, 2.71889, 3.1394, 3.072006, 5.05, 2.645163603061, 5.0712414473906, 5.037, 2.651119};
    const char* tags[] = {"5e19e92130cc0659e484dcb3", "5e19e92130cc0659e484dcbb", "5e19e92130cc0659e484dcb2", "5e19e92130cc0659e484dcb9", "5e19e92130cc0659e484dccd", "5e19e92130cc0659e484dcd0", "5e19e92130cc0659e484dcc7", "5e19e92130cc0659e484dcb7", "5e19e92130cc0659e484dcc9", "5e19e92130cc0659e484dcc1"};
    KDTInit();
    KDTBatchInsert(n, xs, ys, tags);
    cout<<KDTSearch(xs[0], ys[0])<<endl;
}

int main() {
    test_kdtree();
    test_toolbox();
}
