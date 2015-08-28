#ifndef __chat_client_h__
#define __chat_client_h__

#include <QtNetwork/QTcpSocket>

class ChatClient : public QTcpSocket
{
    Q_OBJECT

public:
    ChatClient	( QObject *parent = NULL );
    ~ChatClient	();

    void	ConnectToServer	( const char *ip, quint16 port );
    void	Close			();
    bool	WriteData		( const char *data, qint64 len );

protected:
    void	ParseData	( const char *data, qint64 len );

private slots:
    void	OnConnected	();
    void	OnReadyRead	();

private:
    enum { BUFFERSIZE_MAX = 1024 };
};

#endif // __chat_client_h__
