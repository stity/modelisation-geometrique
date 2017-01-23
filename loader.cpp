#include "loader.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QStringList>
#include <iostream>
#include <sstream>
#include <QDebug>
#include "maillage.h"

Loader::Loader()
{
}

Maillage *Loader::load(QString filename) {
    QFile fichier(filename);
    int currentLine = 0;
    Maillage * maillage;

    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&fichier);
        while(!flux.atEnd())
        {
            QString temp = flux.readLine();
            if (currentLine == 1) {
                QStringList list = temp.split(' ');
                this->nb_points = list[0].toInt();
                this->nb_faces = list[1].toInt();
                maillage = new Maillage(this->nb_points, this->nb_faces);
            }
            else if (currentLine > 1 && currentLine <= this->nb_points+1) {
                QStringList list = temp.split(' ');
                float x = list[0].toFloat();
                float y = list[1].toFloat();
                float z = list[2].toFloat();
                maillage->addSommet(currentLine-2, x, y, z);
            }
            else if (currentLine > 1 && currentLine <= this->nb_points+1+this->nb_faces) {
                int triangleIndex = currentLine - this->nb_points -2;
                QStringList list = temp.split(' ');
                int i = list[1].toInt();
                int j = list[2].toInt();
                int k = list[3].toInt();
                maillage->addTriangle(triangleIndex, i, j, k);
            }
            currentLine++;
        }
        fichier.close();
    }
    else {
        qDebug() << "Unable to open file: " << fichier.fileName() << " because of error " << fichier.errorString() << endl;

        return maillage;
    }

    std::cout << "end of file" << std::endl;
    std::cout << currentLine <<std::endl;

    maillage->parseMap();

    return maillage;


}

