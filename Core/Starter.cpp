#include "Starter.h"

Starter::Starter()
{

}

Starter::~Starter()
{
    disconnect(this, SIGNAL(started()), this, SLOT(initJob()));
    delete m_parentThread;
}

Starter* Starter::get()
{
    static Starter starter;

    return &starter;
}

void Starter::runStarter(QThread* parentThread)
{
    Starter* starter = get();
    starter->m_parentThread = parentThread;
    starter->moveToThread(static_cast<QThread*>(starter));
    starter->connect(starter, SIGNAL(started()), starter, SLOT(initJob()));
    starter->start();
}

void Starter::quitStarter()
{
    Starter* starter = get();

    starter->quit();
}

void Starter::initJob()
{
    initDatabase();
}

void Starter::initDatabase()
{
    bool success = createDatabase();

    emit databaseCreated(success);
}

bool Starter::createDatabase()
{
    CoreGlobals::g_database = new Database();

    if (!CoreGlobals::g_database->open())
    {
#ifdef DEBUG_UTILS
        qDebug() << "Failed to open db" << "\n";
#endif
        return false;
    }

    if (!CoreGlobals::g_database->populate())
    {
#ifdef DEBUG_UTILS
        qDebug() << "Failed to populate db" << "\n";
#endif
        return false;
    }

    return true;
}
