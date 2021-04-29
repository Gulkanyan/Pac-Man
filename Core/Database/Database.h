#ifndef DATABASE_H
#define DATABASE_H

#include "Utils/DataStructs.h"

#include <QList>

class Database
{
public:
    Database();

    ~Database();

    // Public API`s (like Open, Close)
public:
    //  ***         GENERAL API         *** ///
    // Standart Open
    bool open();

    // Standart Close
    bool close();

    // When DB is empty, then populate it with initial data
    bool populate();

    //  **  // helpers
    bool containsData();

    bool dropTables();

    bool createTables();

public:

    bool GetBestScoreAndName(Score &bestScore);

    bool GetTop5Scores(QList<Score> &cores);

    bool AddNewScore(Score score);

    bool GetLastScoreId(int &last_id);
};

#endif // DATABASE_H
