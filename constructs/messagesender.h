#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include <QObject>
#include "wallet.h"
#include "components/peerlist.h"
#include "ffi/ffi.h"

class MessageSender : public QObject
{
    Q_OBJECT
public:
    explicit MessageSender(QObject *parent = nullptr);
    void init(TariWallet* w, PeerList* p);
    Q_INVOKABLE void metaPass (QVariantMap map);
private:
    TariWallet* wallet;
    PeerList* peerlist;
signals:

public slots:

};

#endif // MESSAGESENDER_H
