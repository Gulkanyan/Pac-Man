#include "StandardQueries.h"

namespace StandardQueries
{
    const QStringList dropTables =
    {
        "DROP TABLE IF EXISTS scores;"
    };

    const QStringList createTables =
    {
        "CREATE TABLE users (id INT PRIMARY KEY NOT NULL, username TEXT, score INT);"
    };
}
