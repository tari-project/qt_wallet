#include "message.h"

TariMessage::TariMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, QString Display, bool Ack, bool Open)
    : mId(Id), mSourceKey(Source), mDestKey(Dest), mDisplay(Display), mMessage(Message), mTimestamp(Timestamp), mAcknowledged(Ack), mOpened(Open)
{}

TariMessage::~TariMessage()
{

}
