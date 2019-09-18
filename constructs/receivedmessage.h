#ifndef RECEIVEDTARIMESSAGE_H
#define RECEIVEDTARIMESSAGE_H
#include <QObject>
#include "message.h"

class TariReceivedMessage : public TariMessage
{
public:
    TariReceivedMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, QString Display);
    QString getId() const override;
    QString getSourceKey() const override;
    QString getDisplayName() const override;
    QString getDestinationKey() const override;
    QString getMessage() const override;
    QDateTime getTimestamp() const override;
    bool getAcknowledged() const override;
    bool getRead() const override;
    void setRead() override;
};

#endif // RECEIVEDTARIMESSAGE_H
