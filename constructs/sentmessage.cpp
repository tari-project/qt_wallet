#include "sentmessage.h"

TariSentMessage::TariSentMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, bool Ack, bool Open, QString Display)
    : TariMessage (Id,Source,Dest,Message,Timestamp,Display,Ack, Open)
{

}

QString TariSentMessage::getId() const
{
    return mId;
}

QString TariSentMessage::getDisplayName() const
{
    return mDisplay;
}

QString TariSentMessage::getSourceKey() const
{
    return mSourceKey;
}

QString TariSentMessage::getDestinationKey() const
{
    return mDestKey;
}

QString TariSentMessage::getMessage() const
{
    return mMessage;
}

QDateTime TariSentMessage::getTimestamp() const
{
    return mTimestamp;
}

bool TariSentMessage::getAcknowledged() const
{
    return mAcknowledged;
}

bool TariSentMessage::getRead() const
{
    return mOpened;
}

void TariSentMessage::setRead()
{

}
