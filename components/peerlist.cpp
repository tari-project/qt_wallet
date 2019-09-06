#include "peerlist.h"

PeerList::PeerList(QObject *parent) : QObject(parent) {}

QVector<PeerItem> PeerList::items() const
{
    return this->mItems;
}

bool PeerList::setItemAt(int index, const PeerItem &item)
{
    if (index < 0 || index >= mItems.size())
    {
        return false;
    }

    const PeerItem &oldItem = mItems.at(index);

    if(item.unread == oldItem.unread &&
            item.ip_address == oldItem.ip_address &&
                item.public_key == oldItem.public_key &&
                    item.screen_name == oldItem.screen_name)
    {
        return false;
    }

    mItems[index] = item;
    return true;
}

void PeerList::removeItemAt(int index)
{
    emit preItemRemoved(index);

    mItems.removeAt(index);

    emit postItemRemoved();
}

void PeerList::appendItem(TariPeer* peer)
{
    emit preItemAppended();

    PeerItem item;
    item.unread = false;
    item.ip_address = peer->getAddress();
    item.public_key = peer->getPublicKey();
    item.screen_name = peer->getScreenName();
    mItems.append(item);

    emit postItemAppended();
}

void PeerList::removeItem(TariPeer *peer)
{
    if(!peer)
        return;
    PeerItem item;
    item.unread = false;
    item.ip_address = peer->getAddress();
    item.screen_name = peer->getScreenName();
    item.public_key = peer->getPublicKey();
    int index = 0;
    for (PeerItem peer : items())
    {
        if(item.unread == peer.unread &&
                item.ip_address == peer.ip_address &&
                    item.public_key == peer.public_key &&
                        item.screen_name == peer.screen_name)
        {
            removeItemAt(index);
        }
        else {
            ++index;
        }
    }
}
