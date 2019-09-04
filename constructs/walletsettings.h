#ifndef WALLETSETTINGS_H
#define WALLETSETTINGS_H
#include "tari_ffi.h"
#include <QHash>
#include <QString>

class TariWalletSettings
{
private:
    Settings* pointer;
public:
    TariWalletSettings(const QHash<QString,QString> &settingsConfig);
    Settings* getPointer();
    ~TariWalletSettings();
};

#endif // WALLETSETTINGS_H
