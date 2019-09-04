#ifndef ThreadWorker_H
#define ThreadWorker_H
#include <QObject>
#include <QAbstractEventDispatcher>
#include <QtDebug>
#include <QThread>
#include "constructs/wallet.h"

class WalletWorker: public QObject
{
    Q_OBJECT

public:
    explicit WalletWorker(TariWallet* wallet, QObject *receiver, const char* slot,QObject *parent = nullptr);

public slots:
    void WorkerEvent(const QString &event);
    void ProcessReceivedMessages();
    void WorkerStop();

private:
    bool mStop = false;
    bool Stopped();
    QMutex mMutex;
    Wallet* wallet = nullptr;

signals:
    void WorkerNotify(const QString &event);
};


#endif // ThreadWorker_H
