#include "CoreGlobals.h"

namespace CoreGlobals
{
    QApplication* app = 0;

    Database *g_database = 0;

    Coords playersCoords;

    MultiplayerMode multiplayerSettings;

    GameSettings gameSettings;
}

Database& db()
{
    return *CoreGlobals::g_database;
}
