#ifndef SENTTARIMESSAGE_H
#define SENTTARIMESSAGE_H
#include "message.h"

class TariSentMessage : public TariMessage
{
public:
    TariSentMessage(QString Id, QString Source, QString Dest, QString Message, QDateTime Timestamp, bool Ack, bool Open, QString Display = QString::fromUtf8("Me"));
    QString getId() const override;
    QString getDisplayName() const override;
    QString getSourceKey() const override;
    QString getDestinationKey() const override;
    QString getMessage() const override;
    QDateTime getTimestamp() const override;
    bool getAcknowledged() const override;
    bool getRead() const override;
private:
    void setRead() override;
};

#endif // SENTTARIMESSAGE_H
