#include "peer.h"

TariPeer::TariPeer(QString screenName, QString publicKey, QString address)
{
    this->pointer = create_configpeer(screenName.toStdString().c_str(),publicKey.toStdString().c_str(),address.toStdString().c_str());
}

ConfigPeer* TariPeer::getPointer() const
{
    return this->pointer;
}

QString TariPeer::getScreenName() const
{
    char* name_p = configpeer_get_screen_name(this->pointer);
    QString name = QString::fromUtf8(configpeer_get_screen_name(this->pointer));
    free_string(name_p);
    return name;
}

QString TariPeer::getPublicKey() const
{
    char* pk_p = configpeer_get_public_key(this->pointer);
    QString pk = QString::fromUtf8(configpeer_get_public_key(this->pointer));
    free_string(pk_p);
    return pk;
}

QString TariPeer::getAddress() const
{
    char* address_p = configpeer_get_address(this->pointer);
    QString address = QString::fromUtf8(configpeer_get_address(this->pointer));
    free_string(address_p);
    return address;
}

TariPeer::~TariPeer()
{
    destroy_configpeer(this->pointer);
}
