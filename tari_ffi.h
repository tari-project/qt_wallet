#ifndef TARI_FFI_H
#define TARI_FFI_H

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <new>


struct ConfigPeer;

struct ReceivedMessages;

struct Settings;

struct Wallet;

struct ReceivedTextMessage;

extern "C" {

char *configpeer_get_address(ConfigPeer *o);

char *configpeer_get_public_key(ConfigPeer *o);

char *configpeer_get_screen_name(ConfigPeer *o);

ConfigPeer *create_configpeer(const char *s, const char *p, const char *a);

Settings *create_settings(uint32_t c,
                          uint32_t g,
                          const char *sk,
                          const char *d,
                          const char *db,
                          const char *n);

Wallet *create_wallet(const char *host_s,
                      const char *public_address_s,
                      Settings *settings_p,
                      const char *listener_s,
                      const char *socks_s,
                      uint64_t duration_n);

void destroy_configpeer(ConfigPeer *o);

void destroy_receivedmessages(ReceivedMessages *obj);

void destroy_settings(Settings *o);

void destroy_wallet(Wallet *w);

void free_string(char *o);

char *get_local_ip_();

char *receivedtextmessage_get_message(const ReceivedTextMessage *o);

char *receivedtextmessage_get_public_key(const ReceivedTextMessage *o);

char *receivedtextmessage_get_screenname(const ReceivedTextMessage *o, Wallet *w);

char *receivedtextmessage_get_timestamp(const ReceivedTextMessage *o);

uint32_t settings_get_control_port(Settings *o);

char *settings_get_data_path(Settings *o);

uint32_t settings_get_grpc_port(Settings *o);

char *settings_get_screen_name(Settings *o);

char *settings_get_secret_key(Settings *o);

void wallet_add_peer(ConfigPeer *o, Wallet *w);

ReceivedMessages *wallet_get_receivedmessages(Wallet *w);

const ReceivedTextMessage *wallet_get_receivedmessages_contents(ReceivedMessages *msgs, int i);

int wallet_get_receivedmessages_length(const ReceivedMessages *vec);

void wallet_send_message(Wallet *w, ConfigPeer *o, char *s);

} // extern "C"


#endif // TARI_FFI_H
