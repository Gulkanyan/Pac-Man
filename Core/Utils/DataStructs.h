#ifndef DATASTRUCTS_H
#define DATASTRUCTS_H

#include <QString>

#include "Enums.h"

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

struct MultiplayerMode
{
    bool isEnabled;
    Ghosts selectedGhost;

    MultiplayerMode()
    {
        isEnabled = false;
        selectedGhost = Unknown_Ghost;
    }
};

#endif // DATASTRUCTS_H
