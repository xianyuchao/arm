#include "chat_server.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ChatServer server;
    server.Run( 33333 );

    return a.exec();
}
