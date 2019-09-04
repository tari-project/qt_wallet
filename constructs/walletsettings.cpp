#include "walletsettings.h"

TariWalletSettings::TariWalletSettings(const QHash<QString,QString> &settingsConfig)
{
    this->pointer = create_settings(static_cast<uint32_t>(settingsConfig.value("control_port").toInt()),
                                    static_cast<uint32_t>(settingsConfig.value("grpc_port").toInt()),
                                        settingsConfig.value("secret_key").toStdString().c_str(),
                                        settingsConfig.value("data_path").toStdString().c_str(),
                                        QString("./data/text_message_service.sqlite3").toStdString().c_str(), // TODO: Add to configuration file
                                        settingsConfig.value("screen_name").toStdString().c_str());
}

Settings* TariWalletSettings::getPointer()
{
    return this->pointer;
}

TariWalletSettings::~TariWalletSettings()
{
    destroy_settings(this->pointer);
}
