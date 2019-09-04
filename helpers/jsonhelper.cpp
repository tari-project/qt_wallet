#include "jsonhelper.h"

namespace JSONHelper
{
    QVariantMap parseJSON(QString file) {
        QFile JSONFile(file);
        JSONFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&JSONFile);
        QString JSONText = in.readAll();
        JSONFile.close();

        QJsonDocument JSONDocument = QJsonDocument::fromJson(JSONText.toUtf8());
        QJsonObject JSONObject = JSONDocument.object();
        QVariantMap RootMap = JSONObject.toVariantMap();

        return RootMap;
    }
}
