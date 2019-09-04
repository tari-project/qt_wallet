#ifndef WorkerTHREAD_H
#define WorkerTHREAD_H
#include <QObject>
#include <QThread>
#include "constructs/ThreadedWorker/walletworker.h"
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include "tari_ffi.h"

template <typename TWorker>
class WorkerThread : public QThread
{
    public:
        WorkerThread(TWorker *worker, QObject *parent);

        ~WorkerThread();

        TWorker* worker() const;

    protected:
        void run() override;

    private:
        TWorker* threadworker;

};

#include "workerthread.cpp"

#endif // WorkerTHREAD_H
