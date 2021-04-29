#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QString>

struct Coords
{
    double x;
    double y;

    Coords()
    {
        x = y = 0;
    }
};

struct Score
{
    int score;
    QString name;
};

#endif // DATASTRUCTS_H
