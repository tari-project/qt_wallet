#include "receivedmessage.h"

TariReceivedMessage::TariReceivedMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, QString Display)
    : TariMessage (Id, Source, Dest, Message, Timestamp, Display)
{

}

QString TariReceivedMessage::getId() const
{
    return mId;
}

QString TariReceivedMessage::getSourceKey() const
{
    return mSourceKey;
}

QString TariReceivedMessage::getDisplayName() const
{
    return mDisplay;
}

QString TariReceivedMessage::getDestinationKey() const
{
    return mDestKey;
}

QString TariReceivedMessage::getMessage() const
{
    return mMessage;
}

QDateTime TariReceivedMessage::getTimestamp() const
{
    return mTimestamp;
}

bool TariReceivedMessage::getAcknowledged() const
{
    return false;
}

bool TariReceivedMessage::getRead() const
{
    return false;
}

void TariReceivedMessage::setRead()
{
    //extend ffi for this
    mAcknowledged = true;
    mOpened = true;
}
