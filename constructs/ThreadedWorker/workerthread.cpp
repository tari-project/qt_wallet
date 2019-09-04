#include "constructs/ThreadedWorker/workerthread.h"

template <typename TWorker>
WorkerThread<TWorker>::WorkerThread(TWorker *worker, QObject *parent) : QThread(parent), threadworker(worker) {
    threadworker->moveToThread(this); //run concurrently
    start(); //start thread
}

template <typename TWorker>
WorkerThread<TWorker>::~WorkerThread() {
    if (worker()) //if thread is still processing events
    {
        worker()->WorkerStop(); //explicitly set stop
    }
    quit(); //close thread
    wait(); //wait for quit to finish
    delete threadworker;
}

template <typename TWorker>
TWorker* WorkerThread<TWorker>::worker() const {
    return threadworker; //return the worker
}

template <typename TWorker>
void WorkerThread<TWorker>::run() {
    qDebug()<<QThread::currentThreadId(); //current thread identifier
    QThread::run();
}
