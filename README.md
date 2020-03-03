# 使用KDtree进行天文坐标KNN查询

本工程包含一个简易的球坐标系KD树，支持球坐标系(经纬度坐标)中的最近点查询，其中距离被定义为角距离.

算法介绍: [](https://mhy12345.xyz/technology/angular-kdtree/)

一个最简单的Demo为——

```c++
#include "kdtree.h"
#include <iostream>
using namespace std;

int main() {
    KDTree kdt = KDTree(); // 新建一个KDTree实例
    Point point_to_insert = Point(
        random()%10000/10000.0*PI*2,  // x, 维度坐标，范围(0, 2pi)
        random()%10000/10000.0*PI - PI/2,  // y, 精度坐标，范围(0, 2*pi)
        NULL // tag, 一个类型为const char*的标签，可用于储存必要的信息
        );
    kdt.Insert(point_to_insert);
    Point point_to_query = Point(0,0,NULL);
    pair<double,const Point*> kdt_res = kdt.Search(
        point_to_query,  // pt, 待查询的坐标, tag可为空，
        0.1 // r, 搜索距离，即查询角距离小于该值的区域
        );
    if (kdt_res.second) { // NULL表示没有找到，反之储存结果
        cout<<"Distance : "<<kdt_res.first<<endl;
        cout<<Point : "<<kdt_res.second->x<<" "<<kdt_res.second.y<<endl;
    }
}
```


## 工程结构

 * `./examples.cpp` 若干使用的例子
 * `./kdt_toolbox.cpp/h` 为Python提供的若干简化接口，可以使用`ctypes`库直接调用
 * `./kdtree.cpp/h` 核心代码

## 运行方式

使用如下命令运行该算法——

```
make
./examples
```
