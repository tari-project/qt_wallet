#ifndef WorkerSERVICE_H
#define WorkerSERVICE_H
#include <QObject>
#include <QThread>
#include "constructs/ThreadedWorker/workerthread.h"
#include "constructs/ThreadedWorker/walletworker.h"
#include "constructs/wallet.h"

class WorkerService : public WorkerThread<WalletWorker>
{
    Q_OBJECT

public:
    explicit WorkerService(TariWallet* wallet, QObject *receiver, const char* slot, QObject *parent = nullptr);

signals:
    void WorkerEvent(const QString &event);
    void WorkerStop();
    void ProcessReceivedMessages();

};

#endif // WorkerSERVICE_H
