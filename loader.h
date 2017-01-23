#ifndef LOADER_H
#define LOADER_H
#include <QString>
#include <QVector>
#include <QMap>
#include <QPair>
#include "sommet.h"
#include "triangle.h"
#include "maillage.h"

class Loader
{
public:
    Loader();
    Maillage * load(QString filename);
    int nb_points;
    int nb_faces;
};

#endif // LOADER_H
