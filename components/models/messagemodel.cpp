#include "messagemodel.h"
#include "components/messagelist.h"

MessageModel::MessageModel(QObject *parent) : QAbstractListModel(parent), mList(nullptr) {}

int MessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const MessageItem
             item = mList->items().at(index.row());
    switch (role)
    {
        case IdRole:
            return QVariant(item.id);
        case SourceKeyRole:
            return QVariant(item.source_key);
        case DestinationKeyRole:
            return QVariant(item.dest_key);
        case MessageRole:
            return QVariant(item.message);
        case  TimestampRole:
            return QVariant(item.timestamp);
        case AcknowledgedRole:
            return QVariant(item.acknowledged);
        case UnreadRole:
        return QVariant(item.unread);
        default: return QVariant();
    }
}

QHash<int, QByteArray> MessageModel::roleNames() const
{  
    QHash<int, QByteArray> names;
    names[IdRole] = "id";
    names[SourceKeyRole] = "source_key";
    names[DestinationKeyRole] = "dest_key";
    names[MessageRole] = "message";
    names[TimestampRole] = "timestamp";
    names[AcknowledgedRole] = "acknowledged";
    names[UnreadRole] = "unread";
    return names;
}

MessageList *MessageModel::list() const
{
    return mList;
}

void MessageModel::setList(MessageList *list)
{
    beginResetModel();

    if (mList)
    {
        mList->disconnect(this);
    }
    mList = list;

    if (mList) {
        connect(mList, &MessageList::preItemAppended, this, [=]() {
            const int index = mList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &MessageList::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mList, &MessageList::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(),index,index);
        });

        connect(mList, &MessageList::preItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }
    endResetModel();
}

Qt::ItemFlags MessageModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

bool MessageModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mList)
        return false;

    MessageItem
             item = mList->items().at(index.row());

    switch (role)
    {
        case IdRole :
            item.id = value.toString();
        break;
        case SourceKeyRole:
            item.source_key = value.toString();
        break;
        case DestinationKeyRole:
            item.dest_key = value.toString();
        break;
        case MessageRole:
            item.message = value.toString();
        break;
        case TimestampRole:
            item.timestamp = value.toDateTime();
        break;
        case AcknowledgedRole:
            item.acknowledged = value.toBool();
        break;
        case UnreadRole:
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
