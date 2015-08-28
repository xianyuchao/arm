#ifndef __my_socket_h__
#define __my_socket_h__

#include <QThread>
//#include <QTcpServer>
#include <QtNetwork/QTcpSocket>

class ChatServer;

class MySocket : public QTcpSocket
{
    Q_OBJECT

public:
    MySocket	( QObject *parent = NULL );
    ~MySocket	();

private slots:
    void	onReadyRead		();
};

#endif // __my_socket_h__
