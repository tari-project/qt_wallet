#include <QGuiApplication>
#include <QQmlApplicationEngine>
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

    //qmlRegisterType<Peer>("TariComponents",1,0,"Peer"); // for qml integration
    QGuiApplication app(argc, argv);
    qDebug()<<QThread::currentThreadId();
    QQmlApplicationEngine engine;
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
    MyClass* m = new MyClass();
    foreach (QVariant peerJSON, JSON.first().toList())
    {
        QVariantMap data = peerJSON.toMap();
        qDebug()<<data.value("screen_name").toString()+" "+data.value("pub_key").toString()+" "+data.value("address").toString();
        auto peer = new TariPeer(data.value("screen_name").toString(),data.value("pub_key").toString(),data.value("address").toString());
        wallet_add_peer(peer->getPointer(),wallet->getPointer());
    }
    WorkerService WalletService(wallet,m,SLOT(saveText(QString))); //connect receiver
    WalletService.ProcessReceivedMessages();

    int rc = app.exec();

    WalletService.WorkerStop(); // processed after engine shutdown, necessary for cleanup
    return rc;
}
