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
    int enemyLives;

    MultiplayerMode()
    {
        isEnabled = false;
        selectedGhost = Unknown_Ghost;
        enemyLives = 5;
    }
};

struct GameSettings
{
    bool musicIsEnabled;
    int complexityLevel;            // 0 means easy, 1 - norm, 2 - hard

    GameSettings()
    {
        musicIsEnabled = true;
        complexityLevel = 1;
    }
};

#endif // DATASTRUCTS_H
