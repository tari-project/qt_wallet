#ifndef QPEER_H
#define QPEER_H

#include<QQuickItem>
#include <QtGlobal>

class QPeer : public QQuickItem
{
    Q_OBJECT
    //Q_PROPERTY(QString name)
    //Q_PROPERTY(QString public_key)
    //Q_PROPERTY(QString ip_address)
    //Q_PROPERTY(int port)

public:
    QPeer(QQuickItem *parent = nullptr);

private:

signals:

};




#endif // QPEER_H
