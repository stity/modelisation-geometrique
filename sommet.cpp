#include "sommet.h"

Sommet::Sommet()
{
    this->position = QVector<float>(3);
}

void Sommet::setPosition(float x, float y, float z) {
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}
