#include "StandardQueries.h"

namespace StandardQueries
{
    const QStringList dropTables =
    {
        "DROP TABLE IF EXISTS scores;"
    };

    const QStringList createTables =
    {
        "CREATE TABLE scores (id INT PRIMARY KEY NOT NULL, username TEXT, score INT);"
    };
}
