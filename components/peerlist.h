#ifndef PEERLIST_H
#define PEERLIST_H

#include <QObject>
#include <QVector>
#include "constructs/peer.h"

struct PeerItem
{
    QString screen_name;
    QString public_key;
    QString ip_address;
    bool unread;
};

class PeerList : public QObject
{
    Q_OBJECT
public:
    explicit PeerList(QObject *parent = nullptr);

    QVector<PeerItem> items() const;

    bool setItemAt(int index, const PeerItem &item);
    void removeItemAt(int index);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();


public slots:
    void appendItem(TariPeer* peer);
    void removeItem(TariPeer* peer);
private:
    QVector<PeerItem> mItems;
};

#endif // PEERLIST_H
