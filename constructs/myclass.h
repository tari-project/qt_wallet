#ifndef MYCLASS_H
#define MYCLASS_H
#include <QObject>
#include <QtDebug>
#include "ffi/ffi.h"
#include "components/peerlist.h"
#include "constructs/wallet.h"
#include "constructs/peer.h"

class MyClass : public QObject
{
    Q_OBJECT
public:
    explicit MyClass(QObject *parent = nullptr);
    void init(Wallet* w, PeerList* p);
    Q_INVOKABLE void metaPass (QVariantMap map);
private:
    Wallet* wallet;
    PeerList* peerlist;
signals:

public slots:

};

#endif // MYCLASS_H
