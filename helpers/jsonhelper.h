#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

namespace JSONHelper
{
    QVariantMap parseJSON(QString file);
}

#endif // JSONHELPER_H
