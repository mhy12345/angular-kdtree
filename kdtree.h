#ifndef __POINT_H
#define __POINT_H

#include <algorithm>

class Point {
    public:
        double x, y;
        const char* tag;

        // Constructers
        Point(double x, double y, const char* tag = NULL);
        Point(const Point& p);
        Point();
};

class KDNode {
    public:
        static const double balance_ratio; // KDTree rebuild when size(child) > size(parent) * balance_ratio
        Point p;
        Point box_min, box_max;
        int size;
        KDNode *lch, *rch;
        int direction;
        double midv;
        KDNode(const Point& p, int d);
        bool is_balanced();
        void update_box(const Point& p);
        double box_dist(const Point& p);
        Point* box_corners();
        void update_size();
};

class KDTree {
    private:
        KDNode* root;
        KDNode** imb_node;
        void insert(KDNode* &node, const Point& p, int d);
        KDNode* build(Point* begin, Point* end);
        void extract(KDNode* &now, Point* &cur);
        std::pair<double, const Point*> search(KDNode* now, const Point& p, double r);
    public:
        KDTree();
        void Insert(const Point& p); // Insert a coordinate into the kd-tree.
        void InsertPoints(const Point* begin, const Point* end); // Insert multiple coordinate into the kd-tree
        std::pair<double, const Point*> Search(const Point& p, double r); // Find the nearest coordinate with angular distance less than `r`
        void Release(); // Destroy the kd-tree, release the allocated memory
};

double point_dist(const Point& p1, const Point& p2);
#endif
