#include "maillage.h"
#include <iostream>

Maillage::Maillage(int nbsommets, int nbtriangles)
{
    this->sommets = QVector<Sommet>(nbsommets);
    this->triangles = QVector<Triangle>(nbtriangles);
}

void Maillage::addTriangle(int index, int i, int j, int k) {
    this->triangles[index].setSommets(i, j, k);
    this->sommets[i].triangle = index;
    this->sommets[j].triangle = index;
    this->sommets[k].triangle = index;
    QVector<QPair<int, int> > p = QVector<QPair<int, int> >(3);
    p[0] = QPair<int, int>(std::min(i,j),std::max(i,j));
    p[1] = QPair<int, int>(std::min(k,j),std::max(k,j));
    p[2] = QPair<int, int>(std::min(i,k),std::max(i,k));
    for (int p_index = 0; p_index < 3; p_index++) {
        if (!this->map.contains(p[p_index])) {
            this->map[p[p_index]] = QVector<int>(2);
            this->map[p[p_index]][0] = index;
        }
        else {
            this->map[p[p_index]][1] = index;
        }
    }
}


void Maillage::addSommet(int index, float x, float y, float z) {
    this->sommets[index].setPosition(x,y,z);
}

void Maillage::parseMap() {
    QMap<QPair<int,int>, QVector<int> >::iterator i;
    for (i = this->map.begin(); i != this->map.end(); ++i) {
        QPair<int,int> p = i.key();
        QVector<int> v = i.value();
        int index1 = 3-this->triangles[v[0]].sommets.indexOf(p.first)-this->triangles[v[0]].sommets.indexOf(p.second);
        this->triangles[v[0]].triangles[index1] = v[1];
        int index2 = 3-this->triangles[v[1]].sommets.indexOf(p.first)-this->triangles[v[1]].sommets.indexOf(p.second);
        this->triangles[v[1]].triangles[index2] = v[0];
    }
    this->map.clear();
    std::cout << "done mapping" << std::endl;
}

bool Maillage::seeArrete(int index, int a, int b) {
    float abx = this->sommets[a].position[0] - this->sommets[b].position[0];
    float aby = this->sommets[a].position[1] - this->sommets[b].position[1];
    float apx = this->sommets[a].position[0] - this->sommets[index].position[0];
    float apy = this->sommets[a].position[1] - this->sommets[index].position[1];
    return abx*apy-aby*apx >= 0;
}

bool Maillage::isInTrianle(int pointIndex, int triangleIndex) {
    bool result = true;
    int a,b;
    float abx, aby, apx, apy;
    for (int i = 0; i<3; i++) {
        a = this->triangles[triangleIndex].sommets[i];
        b = this->triangles[triangleIndex].sommets[(i+1)%3];
        abx = this->sommets[a].position[0] - this->sommets[b].position[0];
        aby = this->sommets[a].position[1] - this->sommets[b].position[1];
        apx = this->sommets[a].position[0] - this->sommets[pointIndex].position[0];
        apy = this->sommets[a].position[1] - this->sommets[pointIndex].position[1];
        result = result && (abx*apy-aby*apx < 0);
    }
    return result;
}

void Maillage::flipArrete(int triangleA, int triangleB) {
    //a et b sont les sommets en commun, c et d les autres
    int c;
    int d;
    int a;
    int b;
    int i;
    for (i = 0; i <3; i++) {
        a = this->triangles[triangleA].sommets[i];
        if(this->triangles[triangleB].sommets.indexOf(a) < 0) {
            c = a;
            break;
        }
    }
    a = this->triangles[triangleA].sommets[(i+1)%3];
    b = this->triangles[triangleA].sommets[(i+2)%3];
    d = this->triangles[triangleB].sommets[0] + this->triangles[triangleB].sommets[1] + this->triangles[triangleB].sommets[2] - a - b;

    //récupérer les triangles voisins :
    int triangle1 = this->triangles[triangleA].triangles[(i+2)%3];
    int triangle2 = this->triangles[triangleA].triangles[(i+1)%3];
    i = this->triangles[triangleB].sommets.indexOf(a);
    int triangle3 = this->triangles[triangleB].triangles[i];
    int triangle4 = this->triangles[triangleB].triangles[(i+2)%3];

    //flip
    this->triangles[triangleA].sommets[0] = a;
    this->triangles[triangleA].sommets[1] = d;
    this->triangles[triangleA].sommets[2] = c;
    this->triangles[triangleB].sommets[0] = d;
    this->triangles[triangleB].sommets[1] = b;
    this->triangles[triangleB].sommets[2] = c;

    //repositionner les triangles voisins

    this->triangles[triangleA].triangles[0] = triangleB;
    this->triangles[triangleA].triangles[1] = triangle1;
    this->triangles[triangleA].triangles[2] = triangle4;

    this->triangles[triangleB].triangles[0] = triangle2;
    this->triangles[triangleB].triangles[1] = triangleA;
    this->triangles[triangleB].triangles[2] = triangle3;

}

bool Maillage::divideTriangle(int sommet, int triangle) {
    if(!this->isInTrianle(sommet, triangle)) {
        return false;
    }
    int a = this->triangles[triangle].sommets[0];
    int b = this->triangles[triangle].sommets[1];
    int c = this->triangles[triangle].sommets[2];

    int triangleVoisin0 = this->triangles[triangle].triangles[0];
    int triangleVoisin1 = this->triangles[triangle].triangles[1];

    this->triangles[triangle].sommets[2] = sommet;

    Triangle T1;
    T1.setSommets(b, c, sommet);
    this->triangles.push_back(T1);
    int t1 = this->triangles.size()-1;
    Triangle T2;
    T2.setSommets(c, a, sommet);
    this->triangles.push_back(T2);
    int t2 = this->triangles.size()-1;

    this->triangles[triangle].triangles[0] = t1;
    this->triangles[triangle].triangles[1] = t2;
    this->triangles[t1].triangles[0] = t2;
    this->triangles[t1].triangles[1] = triangle;
    this->triangles[t1].triangles[2] = triangleVoisin0;
    this->triangles[t2].triangles[0] = triangle;
    this->triangles[t2].triangles[1] = t2;
    this->triangles[t2].triangles[2] = triangleVoisin1;

    return true;
}
