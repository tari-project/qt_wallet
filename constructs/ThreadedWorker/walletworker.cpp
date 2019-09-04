#include "constructs/ThreadedWorker/walletworker.h"
#include "constructs/ThreadedWorker/workerthread.h"
#include <QTest>

WalletWorker::WalletWorker(TariWallet* wallet, QObject *receiver, const char* slot, QObject *parent) :
  QObject(parent), wallet(wallet->getPointer())
{
    connect(this, SIGNAL(WorkerNotify(QString)),receiver,slot); // to send data back to main thread
};

void WalletWorker::WorkerStop() {
    mMutex.lock();
    this->mStop = true;
    mMutex.unlock();
};

bool WalletWorker::Stopped() {
    bool m;
    mMutex.lock();
    m = this->mStop;
    mMutex.unlock();
    return m;
};

void WalletWorker::ProcessReceivedMessages()
{
    int currentmsg = -1;

    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) { //critical, event loop was not available, currently returns but should emit signal back down the scaffold so application execution could be retried/teminated
        return;
    }

    do {
        if (this->wallet != nullptr)
        {
            auto messagesVec = wallet_get_receivedmessages(this->wallet);
            int messagelist = wallet_get_receivedmessages_length(messagesVec);
            for (int i = 0; i < messagelist; i++)
            {
                if (i > currentmsg)
                {
                    auto receivedmessage = wallet_get_receivedmessages_contents(messagesVec,i);
                    auto timestamp = receivedtextmessage_get_timestamp(receivedmessage);
                    auto screen_name = receivedtextmessage_get_screenname(receivedmessage,this->wallet);
                    auto message = receivedtextmessage_get_message(receivedmessage);
                    currentmsg++;
                    std::string buf(timestamp);
                    buf.append("::");
                    buf.append(screen_name);
                    buf.append(": ");
                    buf.append(message);
                    QString fullmessage = QString(buf.c_str());
                    emit WorkerNotify(fullmessage);
                    free_string(timestamp);
                    free_string(screen_name);
                    free_string(message);
                }
            }
            destroy_receivedmessages(messagesVec);
        }
        if (!Stopped()) //ensure further events in the event loop are not processed if stopped, for thead shutdown
        {
            dispatcher->processEvents(QEventLoop::AllEvents); //continue processing events received
        }
    } while (!Stopped());
}

void WalletWorker::WorkerEvent(const QString &event) {
    emit WorkerNotify(event + "emitted");
};



