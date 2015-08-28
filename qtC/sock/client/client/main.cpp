#include "chat_client.h"
#include <QtCore/QCoreApplication>

#include <QtNetwork>

int main(int argc, char *argv[])
{
   QCoreApplication a(argc, argv);
 /*
    ChatClient	client;
    char		ip[16]	= { 0 };
    quint16		port	= 0;

    client.ConnectToServer( "127.0.0.1", 33333 );
    client.waitForConnected( -1 );

    char		msg[1024]	= { 0 };
    printf( "please input message(exit with 'exit'): \n" );
    while( 1 ) {
        gets( msg );
        if( 0 == strcmp(msg, "exit") )
            break;

        if( !client.WriteData(msg, strlen(msg) + 1) ) {
            printf( "WriteData failed !\n" );
            break;
        }
    }

    client.Close();
*/

    QTcpSocket *client;
    char *data="hello qt!";
    client = new QTcpSocket();
    client->connectToHost(QHostAddress("127.0.0.1"),33333);
    client->write(data);

    return a.exec();
}

