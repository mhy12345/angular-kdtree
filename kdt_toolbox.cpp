#include <iostream>
#include <cstring>
#include "kdtree.h"
#define PI 3.1415926535897
#define CRI ((0.5/3600/180*PI) * 2)
using namespace std;

KDTree kdt;

extern "C" {  
    void KDTBatchInsert(int n, double *dx, double *dy, const char** tag) {
        Point* pts = new Point[n];
        for (int i=0;i<n;i++) {
            char* buffer = new char[strlen(tag[i]) + 1];
            strcpy(buffer, tag[i]);
            pts[i] = Point(dx[i] / 180 * PI, dy[i] / 180 * PI, buffer);
        }
        kdt.InsertPoints(pts, pts + n);
        delete[] pts;
    }
    void KDTInsert(double dx, double dy, const char* tag) {
        char* buffer = new char[strlen(tag) + 1];
        strcpy(buffer, tag);
        Point pt = Point(dx / 180 * PI, dy / 180 * PI, buffer);
        kdt.Insert(pt);
    }

    const char* KDTSearch(double dx, double dy) {
        cout<<"find "<<dx<<" "<<dy<<endl;
        Point pt = Point(dx / 180 * PI, dy / 180 * PI, NULL);
        pair<double, const Point*> res = kdt.Search(pt, 1e10);
        if (res.second && res.first < CRI) {
            cout<<"result "<<res.second->tag<<endl;
            return ((const char*)res.second->tag);
        } else {
            cout<<"result null"<<endl;
            return NULL;
        }
    }
    
    void KDTInit() {
        kdt.Release();
        cout<<"Rebuild kdt..."<<endl;
    }
}

