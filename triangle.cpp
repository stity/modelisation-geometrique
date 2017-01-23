#include "triangle.h"

Triangle::Triangle()
{
    this->sommets = QVector<int>(3);
    this->triangles = QVector<int>(3);
}

void Triangle::setSommets(int s1, int s2, int s3) {
    this->sommets[0] = s1;
    this->sommets[1] = s2;
    this->sommets[2] = s3;
}

void Triangle::setTriangles(int t1, int t2, int t3) {
    this->triangles[0] = t1;
    this->triangles[1] = t2;
    this->triangles[2] = t3;
}
