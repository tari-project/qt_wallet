#include "messagelist.h"

MessageList::MessageList(QObject *parent) : QObject(parent) {}

QVector<MessageItem> MessageList::items() const
{
    return this->mItems;
}

bool MessageList::setItemAt(int index, const MessageItem &item)
{
    if (index < 0 || index >= mItems.size())
    {
        return false;
    }

    const MessageItem &oldItem = mItems.at(index);

    if(item.id == oldItem.id &&
            item.dest_key == oldItem.dest_key &&
                item.source_key == oldItem.source_key &&
                    item.timestamp == oldItem.timestamp &&
                        item.acknowledged == oldItem.acknowledged &&
                            item.message == oldItem.message &&
                                 item.unread == oldItem.unread)
    {
        return false;
    }

    mItems[index] = item;
    return true;
}

void MessageList::removeItemAt(int index)
{
    emit preItemRemoved(index);

    mItems.removeAt(index);

    emit postItemRemoved();
}

void MessageList::appendItem(TariMessage* message)
{
    emit preItemAppended();

    MessageItem item;
    item.id = message->getId();
    item.message = message->getMessage();
    item.dest_key = message->getDestinationKey();
    item.source_key = message->getSourceKey();
    item.timestamp = message->getTimestamp();
    item.acknowledged = message->getAcknowledged();
    item.unread = !(message->getRead());
    mItems.append(item);

    emit postItemAppended();
}

void MessageList::removeItem(TariMessage *message)
{
    if(!message)
        return;
    MessageItem item;
    item.id = message->getId();
    item.message = message->getMessage();
    item.dest_key = message->getDestinationKey();
    item.source_key = message->getSourceKey();
    item.timestamp = message->getTimestamp();
    item.acknowledged = message->getAcknowledged();
    item.unread = !(message->getRead());
    int index = 0;
    for (MessageItem message : items())
    {
        if(item.id == message.id &&
                item.dest_key == message.dest_key &&
                    item.source_key == message.source_key &&
                        item.timestamp == message.timestamp &&
                            item.acknowledged == message.acknowledged &&
                                item.message == message.message &&
                                    item.unread == message.unread)
        {
            removeItemAt(index);
        }
        else {
            ++index;
        }
    }
}
