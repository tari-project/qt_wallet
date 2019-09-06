#include "peermodel.h"
#include "components/peerlist.h"

PeerModel::PeerModel(QObject *parent) : QAbstractListModel(parent), mList(nullptr) {}

int PeerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant PeerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const PeerItem
             item = mList->items().at(index.row());
    switch (role)
    {
        case ScreenNameRole:
            return QVariant(item.screen_name);
        case PublicKeyRole:
            return QVariant(item.public_key);
        case AddressRole:
            return QVariant(item.ip_address);
        case NewUnreadRole:
            return QVariant(QVariant(false));
        default: return QVariant();
    }
}

QHash<int, QByteArray> PeerModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ScreenNameRole] = "screen_name";
    names[PublicKeyRole] = "public_key";
    names[AddressRole] = "ip_address";
    names[NewUnreadRole] = "unread";
    return names;
}

PeerList *PeerModel::list() const
{
    return mList;
}

void PeerModel::setList(PeerList *list)
{
    beginResetModel();

    if (mList)
    {
        mList->disconnect(this);
    }
    mList = list;

    if (mList) {
        connect(mList, &PeerList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PeerList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &PeerList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(),index,index);
        });

        connect(mList, &PeerList::preItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}

Qt::ItemFlags PeerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool PeerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    PeerItem
             item = mList->items().at(index.row());

    switch (role)
    {
        case ScreenNameRole:
            item.screen_name = value.toString();
        break;
        case PublicKeyRole:
            item.public_key = value.toString();
        break;
        case AddressRole:
            item.ip_address = value.toString();
        break;
        case NewUnreadRole:
            item.unread = value.toBool();
        break;
    }

    if (mList->setItemAt(index.row(),item))
    {
        emit dataChanged(index,index, QVector<int>() << role);
        return true;
    }

    return false;
}
