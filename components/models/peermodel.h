#ifndef PEERMODEL_H
#define PEERMODEL_H

#include <QAbstractListModel>

class PeerList;

class PeerModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(PeerList *list READ list WRITE setList)

public:
    enum {
        ScreenNameRole = Qt::UserRole,
        PublicKeyRole,
        AddressRole,
        NewUnreadRole

    };

    explicit PeerModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PeerList *list() const;
    void setList(PeerList *list);

private:
    PeerList *mList;
};

#endif // PEERMODEL_H
