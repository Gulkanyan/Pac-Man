#ifndef COREGLOBALS_H
#define COREGLOBALS_H

#include <QApplication>

#include "Utils/DataStructs.h"
#include "Utils/Enums.h"
#include "Utils/Levels.h"
#include "GlobalDefs.h"
#include "Database/Database.h"

#include <QPushButton>
#include <QMessageBox>

namespace CoreGlobals
{
    extern QApplication* app;

    extern Database* g_database;

    extern Coords playersCoords;

    extern MultiplayerMode multiplayerSettings;
};

Database& db();

#endif // COREGLOBALS_H
