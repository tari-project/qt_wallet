#include "constructs/ThreadedWorker/workerservice.h"

WorkerService::WorkerService(TariWallet* wallet, QObject *receiver, const char* slot,QObject *parent) : WorkerThread<WalletWorker>(new WalletWorker(wallet, receiver,slot), parent) {
     connect(this, &WorkerService::WorkerEvent, worker(), &WalletWorker::WorkerEvent);
     connect(this, &WorkerService::ProcessReceivedMessages, worker(), &WalletWorker::ProcessReceivedMessages);
     connect(this, &WorkerService::WorkerStop, worker(), &WalletWorker::WorkerStop);
}
