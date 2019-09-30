#include "messagesender.h"

MessageSender::MessageSender(QObject *parent) : QObject(parent)
{

}

void MessageSender::init(TariWallet *w,PeerList* p)
{
    wallet = w;
    peerlist = p;
}

void MessageSender::metaPass(QVariantMap map) {
    if (wallet)
    {
        if (peerlist)
        {
            TariPeer* p;
            for (int i = 0; i < peerlist->items().count(); i++)
            {
               if (peerlist->items().at(i).public_key == map.value("peerid").toString())
               {
                   p = new TariPeer(peerlist->items().at(i).screen_name,peerlist->items().at(i).public_key,peerlist->items().at(i).ip_address);
               }
            }
            if (p)
            {
                std::string str =  map.value("message").toString().toStdString();
                const char* ptr = str.c_str();
                wallet_send_message(wallet->getPointer(),p->getPointer(),const_cast<char*>(ptr));
                delete p;
            }
        }
    }
}
