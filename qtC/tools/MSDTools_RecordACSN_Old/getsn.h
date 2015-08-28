#ifndef GETSN_H
#define GETSN_H
#include <QString>
#include <QVector>
#include <QCryptographicHash>

#include <openssl/aes.h>

class GetSN
{

public:
    GetSN();
    QString getSN(QVector<unsigned char> report);
};

#endif // GETSN_H
