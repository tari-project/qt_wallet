#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
//#include "components/qpeer.h"
#include <string>
#include "constructs/peer.h"
#include "constructs/wallet.h"
#include "helpers/jsonhelper.h"
#include <thread>
#include <QDir>
#include <QSettings>
#include "constructs/ThreadedWorker/workerservice.h"
#include "constructs/myclass.h"
#include "components/models/peermodel.h"
#include "components/peerlist.h"
#include "components/models/messagemodel.h"
#include "components/messagelist.h"

int main(int argc, char *argv[])
{

    QDir directory = QDir::currentPath();

    //todo: windows, linux, ios, android paths
    directory.cdUp();directory.cdUp(); //mac specific: application bundling
    directory.cdUp();directory.cdUp();
    QString settingsFileString = directory.path() + QString::fromUtf8("/tari/applications/grpc_wallet/sample_config/wallet_config_node1.toml");
    QString fileString = directory.path() + QString::fromUtf8("/tari/applications/grpc_wallet/sample_config/node1_peers.json");
    QVariantMap JSON = JSONHelper::parseJSON(fileString);

    QSettings settings(settingsFileString, QSettings::IniFormat);
    QHash<QString, QString> hash;
    QStringList keys = settings.allKeys();
    foreach (const QString &key, keys) {
      hash.insert(key, settings.value(key).toString());
    }

    qmlRegisterType<PeerModel>("Components",1,0,"PeerModel");
    qmlRegisterUncreatableType<PeerList>("Components",1,0,"PeerList","QML Uncreatable");
    qmlRegisterType<MessageModel>("Components",1,0,"MessageModel");
    qmlRegisterUncreatableType<MessageList>("Components",1,0,"MessageList","QML Uncreatable");
    qRegisterMetaType<TariMessage*>("TariMessage*");

    PeerList peerlist;
    MessageList messagelist;
    MyClass m; //TODO: Refactor!!

    QGuiApplication app(argc, argv);
    qDebug()<<QThread::currentThreadId();
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("Peers"),&peerlist);
    engine.rootContext()->setContextProperty(QStringLiteral("Messages"),&messagelist);
    engine.rootContext()->setContextProperty(QStringLiteral("MetaObj"),&m);
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    auto walletSettings = new TariWalletSettings(hash);
    auto wallet = new TariWallet(nullptr,get_local_ip_(),walletSettings,nullptr,nullptr,5000);
    foreach (QVariant peerJSON, JSON.first().toList())
    {
        QVariantMap data = peerJSON.toMap();
        auto peer = new TariPeer(data.value("screen_name").toString(),data.value("pub_key").toString(),data.value("address").toString());
        wallet_add_peer(peer->getPointer(),wallet->getPointer());
        peerlist.appendItem(peer); //TODO: .appendItems(wallet_get_peers()) after foreach, extend ffi
        const char* l = QString("Test").toUtf8();
        char* t = const_cast<char*>(l);
        //wallet_send_message(wallet->getPointer(),peer->getPointer(),t);
    }
    m.init(wallet,&peerlist);

    WorkerService WalletService(wallet,&messagelist,SLOT(appendItem(TariMessage*))); //connect receiver
    WalletService.ProcessReceivedMessages();

    int rc = app.exec();

    WalletService.WorkerStop(); // processed after engine shutdown, necessary for cleanup
    return rc;
}
