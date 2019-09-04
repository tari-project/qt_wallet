#include "wallet.h"

TariWallet::TariWallet(char* host, char* public_address,TariWalletSettings* settings,char* listener_address, char* socks, int timeout_duration)
{
   this->pointer = create_wallet(host,public_address,settings->getPointer(),listener_address,socks,static_cast<uint64_t>(timeout_duration));
}

Wallet* TariWallet::getPointer()
{
    return this->pointer;
}

TariWallet::~TariWallet()
{
    destroy_wallet(this->pointer);
}
