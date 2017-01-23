#ifndef SOMMET_H
#define SOMMET_H
#include <QVector>
#include "triangle.h"

class Triangle;

class Sommet
{
public:
    Sommet();
    QVector<float> position;
    int triangle;
    void setPosition(float, float, float);
};

#endif // SOMMET_H
