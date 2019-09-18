#ifndef TARI_FFI_H
#define TARI_FFI_H

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <new>

/// ConfigPeer
struct ConfigPeer;

/// Received Messages
struct ReceivedMessages;

/// Sent Messages
struct SentMessages;

/// Wallet Settings
struct Settings;

/// Once bindings are generated via cbindgen, change the using to struct, remove the equals sign and anything after it
/// on the line. These are used as opaque pointers
struct Wallet;

struct ReceivedTextMessage;

struct SentTextMessage;

extern "C" {

/// Returns ip address for peer as char*
char *configpeer_get_address(ConfigPeer *o);

/// Returns public key for peer as char*
char *configpeer_get_public_key(ConfigPeer *o);

/// Returns display name for peer as char*
char *configpeer_get_screen_name(ConfigPeer *o);

/// Returns a pointer to ConfigPeer
ConfigPeer *create_configpeer(const char *s, const char *p, const char *a);

/// Returns pointer to wallet settings
Settings *create_settings(uint32_t c,
                          uint32_t g,
                          const char *sk,
                          const char *d,
                          const char *db,
                          const char *n);

/// Returns a pointer to a wallet
Wallet *create_wallet(const char *host_s,
                      const char *public_address_s,
                      Settings *settings_p,
                      const char *listener_s,
                      const char *socks_s,
                      uint64_t duration_n);

/// Frees memory for ConfigPeer pointer
void destroy_configpeer(ConfigPeer *o);

/// Frees memory for ReceivedMessages pointer
void destroy_receivedmessages(ReceivedMessages *obj);

/// Frees memory for SentMessages pointer
void destroy_sentmessages(SentMessages *obj);

/// Frees memory for wallet settings pointer
void destroy_settings(Settings *o);

/// Shuts down services and frees memory for wallet pointer
void destroy_wallet(Wallet *w);

/// Frees memory for string pointer
void free_string(char *o);

/// Returns ip address as char*
char *get_local_ip_();

/// Returns the destination from the ReceivedTextMessage as char*
char *receivedtextmessage_get_destination_public_key(const ReceivedTextMessage *o);

/// Returns the identifier from the ReceivedTextMessage as char*
char *receivedtextmessage_get_identifier(const ReceivedTextMessage *o);

/// Returns the message from the ReceivedTextMessage as char*
char *receivedtextmessage_get_message(const ReceivedTextMessage *o);

/// Returns the display name from the ReceivedTextMessage as string
char *receivedtextmessage_get_screenname(const ReceivedTextMessage *o, Wallet *w);

/// Returns the source from the ReceivedTextMessage as char*
char *receivedtextmessage_get_source_public_key(const ReceivedTextMessage *o);

/// Returns the timestamp of a ReceivedText Message as string
char *receivedtextmessage_get_timestamp(const ReceivedTextMessage *o);

/// Returns the acknowledged of a SentText Message as bool
bool senttextmessage_get_acknowledged(const SentTextMessage *o);

/// Returns the destination from the SentTextMessage as char*
char *senttextmessage_get_destination_public_key(const SentTextMessage *o);

/// Returns the identifier from the SentTextMessage as char*
char *senttextmessage_get_identifier(const SentTextMessage *o);

/// Returns the message from the SentTextMessage as char*
char *senttextmessage_get_message(const SentTextMessage *o);

/// Returns the is_read of a SentText Message as bool
bool senttextmessage_get_opened(const SentTextMessage *o);

/// Returns the source from the SentTextMessage as char*
char *senttextmessage_get_source_public_key(const SentTextMessage *o);

/// Returns the timestamp of a SentText Message as string
char *senttextmessage_get_timestamp(const SentTextMessage *o);

/// Sets the is_read of a SentText Message, returns if successful or not
bool senttextmessage_set_opened(SentTextMessage *o, Wallet *w);

/// Returns control port for wallet settings as integer
uint32_t settings_get_control_port(Settings *o);

/// Returns data path for wallet settings as char*
char *settings_get_data_path(Settings *o);

/// Returns database path for wallet settings as char*
char *settings_get_database_path(Settings *o);

/// Returns grpc port for wallet settings as integer
uint32_t settings_get_grpc_port(Settings *o);

/// Returns display name for wallet settings as char*
char *settings_get_screen_name(Settings *o);

/// Returns secret key for wallet settings as char*
char *settings_get_secret_key(Settings *o);

/// Adds peer to wallet and adds peer as contact to wallet message service
void wallet_add_peer(ConfigPeer *o, Wallet *w);

/// Returns a pointer to the received messages
ReceivedMessages *wallet_get_receivedmessages(Wallet *w);

/// Returns a pointer to the received messages vector
const ReceivedTextMessage *wallet_get_receivedmessages_contents(ReceivedMessages *msgs, int i);

/// Returns the number of received messages, zero-indexed
int wallet_get_receivedmessages_length(const ReceivedMessages *vec);

/// Returns a pointer to the sent messages
SentMessages *wallet_get_sentmessages(Wallet *w);

/// Returns a pointer to the received messages vector
const SentTextMessage *wallet_get_sentmessages_contents(SentMessages *msgs, int i);

/// Returns the number of sent messages, zero-indexed
int wallet_get_sentmessages_length(const SentMessages *vec);

/// Sends a message from the wallet to the peers wallet
void wallet_send_message(Wallet *w, ConfigPeer *o, char *s);

} // extern "C"

#endif // TARI_FFI_H
