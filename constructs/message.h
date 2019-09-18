#ifndef MESSAGE_H
#define MESSAGE_H
#include "tari_ffi.h"
#include <QString>
#include <QDateTime>

class TariMessage
{
protected:
    QString mId;
    QString mSourceKey;
    QString mDestKey;
    QString mDisplay;
    QString mMessage;
    QDateTime mTimestamp;
    bool mAcknowledged;
    bool mOpened;

    TariMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, QString Display = QString::fromUtf8("Me"), bool Ack = false, bool Open = false);
public:
    virtual ~TariMessage();
    virtual QString getId() const = 0;
    virtual QString getSourceKey() const = 0;
    virtual QString getDisplayName() const = 0;
    virtual QString getDestinationKey() const = 0;
    virtual QString getMessage() const = 0;
    virtual QDateTime getTimestamp() const = 0;
    virtual bool getAcknowledged() const = 0;
    virtual bool getRead() const = 0;
    virtual void setRead() = 0;
};

#endif // MESSAGE_H
