#ifndef WALLET_H
#define WALLET_H
#include "tari_ffi.h"
#include "walletsettings.h"


class TariWallet
{
private:
    Wallet* pointer;
public:
    TariWallet(char* host, char* public_address,TariWalletSettings* settings, char* listener_address, char* socks, int timeout_duration);
    Wallet* getPointer();
    ~TariWallet();
};

#endif // WALLET_H
