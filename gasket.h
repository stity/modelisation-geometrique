#ifndef GASKET_H
#define GASKET_H

#include <QtOpenGL>
#include <QGLWidget>

struct point {
    float x, y, z;
};

class Gasket
{
public:
    Gasket();

    void draw();

private:
    point * points;
};

#endif // GASKET_H
