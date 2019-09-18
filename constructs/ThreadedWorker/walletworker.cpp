#include "constructs/ThreadedWorker/walletworker.h"
#include "constructs/ThreadedWorker/workerthread.h"
#include "constructs/receivedmessage.h"
#include "constructs/sentmessage.h"
#include <QTest>

WalletWorker::WalletWorker(TariWallet* wallet, QObject *receiver, const char* slot, QObject *parent) :
  QObject(parent), wallet(wallet->getPointer())
{
    connect(this, SIGNAL(WorkerNotify(TariMessage*)),receiver,slot); // to send data back to main thread
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
    int currentreceivedmsg = -1;
    int currentsentmsg = -1;

    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) { //critical, event loop was not available, currently returns but should emit signal back down the scaffold so application execution could be retried/teminated
        return;
    }

    do {
        if (this->wallet != nullptr)
        {
            //received messages
            auto messagesVec = wallet_get_receivedmessages(this->wallet);
            int messagelist = wallet_get_receivedmessages_length(messagesVec);
            for (int i = 0; i < messagelist; i++)
            {
                if (i > currentreceivedmsg)
                {
                    auto receivedmessage = wallet_get_receivedmessages_contents(messagesVec,i);

                    auto p_id = receivedtextmessage_get_identifier(receivedmessage);
                    QString id = QString::fromUtf8(p_id);
                    auto p_source = receivedtextmessage_get_source_public_key(receivedmessage);
                    QString source = QString::fromUtf8(p_source);
                    auto p_dest = receivedtextmessage_get_destination_public_key(receivedmessage);
                    QString dest = QString::fromUtf8(p_dest);
                    auto p_timestamp = receivedtextmessage_get_timestamp(receivedmessage);
                    QDateTime timestamp = QDateTime::fromString(QString::fromUtf8(p_timestamp));
                    auto p_screen = receivedtextmessage_get_screenname(receivedmessage,this->wallet);
                    QString screen_name = QString::fromUtf8(p_screen);
                    auto p_message = receivedtextmessage_get_message(receivedmessage);
                    QString message = QString::fromUtf8(p_message);

                    TariMessage* tarimessage = new TariReceivedMessage(id,source,dest,message,timestamp,screen_name);
                    free_string(p_id);
                    free_string(p_source);
                    free_string(p_dest);
                    free_string(p_timestamp);
                    free_string(p_screen);
                    free_string(p_message);
                    currentreceivedmsg++;
                    emit WorkerNotify(tarimessage);
                }
            }
            destroy_receivedmessages(messagesVec);
        }

        //sent messages
        auto messagesVec = wallet_get_sentmessages(this->wallet);
        int messagelist = wallet_get_sentmessages_length(messagesVec);
        for (int i = 0; i < messagelist; i++)
        {
            if (i > currentsentmsg)
            {
                auto sentmessage = wallet_get_sentmessages_contents(messagesVec,i);

                auto p_id = senttextmessage_get_identifier(sentmessage);
                QString id = QString::fromUtf8(p_id);
                auto p_source = senttextmessage_get_source_public_key(sentmessage);
                QString source = QString::fromUtf8(p_source);
                auto p_dest = senttextmessage_get_destination_public_key(sentmessage);
                QString dest = QString::fromUtf8(p_dest);
                auto p_timestamp = senttextmessage_get_timestamp(sentmessage);
                QDateTime timestamp = QDateTime::fromString(QString::fromUtf8(p_timestamp));
                auto p_message = senttextmessage_get_message(sentmessage);
                QString message = QString::fromUtf8(p_message);
                bool acknowledged = senttextmessage_get_acknowledged(sentmessage);
                bool opened = senttextmessage_get_opened(sentmessage);
                TariMessage* tarimessage = new TariSentMessage(id,source,dest,message,timestamp,acknowledged,opened);
                free_string(p_id);
                free_string(p_source);
                free_string(p_dest);
                free_string(p_timestamp);
                free_string(p_message);
                currentsentmsg++;
                emit WorkerNotify(tarimessage);
            }
        }
        destroy_sentmessages(messagesVec);

        if (!Stopped()) //ensure further events in the event loop are not processed if stopped, for thead shutdown
        {
            dispatcher->processEvents(QEventLoop::AllEvents); //continue processing events received
        }
    } while (!Stopped());
}

void WalletWorker::WorkerEvent(TariMessage* event) {
    emit WorkerNotify(event);
};



