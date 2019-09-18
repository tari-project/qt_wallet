#ifndef MESSAGEMODEL_H
#define MESSAGEMODEL_H

#include <QAbstractListModel>

class MessageList;

class MessageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(MessageList *list READ list WRITE setList)

public:
    enum {
        IdRole = Qt::UserRole,
        SourceKeyRole,
        DestinationKeyRole,
        MessageRole,
        TimestampRole,
        AcknowledgedRole,
        UnreadRole
    };

    explicit MessageModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    MessageList *list() const;
    void setList(MessageList *list);

private:
    MessageList *mList;
};

#endif // MESSAGEMODEL_H
