#include "Database.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "Utils/StandardQueries.h"

#include <QDebug>

Database::Database()
{

}

Database::~Database()
{
    close();
}

bool Database::open()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GameData.db");

    if (!database.open())
        return false;
    return true;
}

bool Database::close()
{
    QSqlDatabase database;
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("GameData.db");

    database.close();

    if(database.isOpen())
        return false;
    return true;
}

bool Database::populate()
{
    // If database is already populated
    if(containsData())
        return true;

    // Drop Tables - Create Tables - Insert Data
    if (!dropTables() || !createTables())
        return false;

    return true;
}

bool Database::containsData()
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM sqlite_master WHERE type = 'table'");
    res = query.exec();

    int count = 0;
    while(query.next())
    {
        count = query.value(0).toInt();
    }

    if (!res)
    {
        qDebug() << "Res from get users count = " << res << "\n";
        return false;
    }

    qDebug() << "Count of tables " << count;

    if (count != StandardQueries::createTables.count())
        return false;

    return true;
}

bool Database::dropTables()
{
    QSqlQuery query;
    bool res = false;
    for(int i = 0; i < StandardQueries::dropTables.length(); i++)
    {
        res = query.exec(StandardQueries::dropTables.at(i));
        qDebug() << "Res from Drop tables = " << res << "\n";
    }
    return res;
}

bool Database::createTables()
{
    QSqlQuery query;
    bool res = false;
    for(int i = 0; i < StandardQueries::createTables.length(); i++)
    {
        res = query.exec(StandardQueries::createTables.at(i));
        qDebug() << "Res from Create tables = " << res << "\n";
    }
    return res;
}

///         ***         ///         Public API`s            ///         ***         ///
bool Database::GetBestScoreAndName(Score &bestScore)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT id, username, score FROM	scores WHERE score = (SELECT MAX(score) FROM scores);");
    res = query.exec();

    while(query.next())
    {
        qDebug() << query.value(0);
        bestScore.name = query.value(1).toString();
        bestScore.score = query.value(2).toInt();

        qDebug() << "Data = " << bestScore.score << " + " << bestScore.name;
    }

    if(!res)
    {
        qDebug() << "Error in get best score = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::GetTop5Scores(QList<Score> &scores)
{
    scores.clear();

    QSqlQuery query;
    bool res = query.prepare("SELECT id, username, score FROM scores ORDER BY score DESC LIMIT 5;");
    res = query.exec();

    while(query.next())
    {
        Score temp;

        temp.name = query.value(1).toString();
        temp.score = query.value(2).toInt();

        qDebug() << "Data = " << temp.score << " + " << temp.name;

        scores.append(temp);
    }

    if(!res)
    {
        qDebug() << "Error in getDepartment = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::AddNewScore(Score score)
{
    int id;
    GetLastScoreId(id);

    QSqlQuery query;
    bool res = query.prepare("INSERT INTO scores(id, username, score) VALUES(:id, :username, :score);");

    query.bindValue(":id", ++id);
    query.bindValue(":username", score.name);
    query.bindValue(":score", score.score);

    res = query.exec();

    if(!res)
    {
        qDebug() << "Error in add score = " << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::GetLastScoreId(int &last_id)
{
    QSqlQuery query;
    bool res = query.prepare("SELECT count(*) FROM scores;");
    res = query.exec();

    last_id = -1;
    while(query.next())
    {
        last_id = query.value(0).toInt();
        qDebug() << "ids from query = " << last_id;
        break;
    }

    if(!res)
    {
        qDebug() << "Error in get last scores id = " << query.lastError().text();
        return false;
    }
    return true;
}
