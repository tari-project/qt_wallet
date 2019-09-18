#ifndef MESSAGELIST_H
#define MESSAGELIST_H

#include <QObject>
#include <QVector>
#include <QDateTime>
#include "constructs/message.h"

struct MessageItem
{
    QString id;
    QString source_key;
    QString dest_key;
    QString message;
    QDateTime timestamp;
    bool acknowledged;
    bool unread;
};

class MessageList : public QObject
{
    Q_OBJECT
public:
    explicit MessageList(QObject *parent = nullptr);

    QVector<MessageItem> items() const;

    bool setItemAt(int index, const MessageItem &item);
    void removeItemAt(int index);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem(TariMessage* message);
    void removeItem(TariMessage* message);
private:
    QVector<MessageItem> mItems;
};

#endif // MESSAGELIST_H
