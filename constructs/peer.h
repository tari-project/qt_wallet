#ifndef PEER_H
#define PEER_H
#include "tari_ffi.h"
#include <QString>
#include "helpers/jsonhelper.h"

class TariPeer
{
private:
    ConfigPeer* pointer;
public:
    TariPeer(QString screenName, QString publicKey, QString address);
    ConfigPeer* getPointer();
    QString getScreenName();
    QString getPublicKey();
    QString getAddress();
    ~TariPeer();
};

#endif // PEER_H
