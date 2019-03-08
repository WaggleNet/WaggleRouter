#include <Crypto.h>
#include <AES.h>
#include <Base64.h>
#include "spiffs_params.h"


static void decrypt_mqi_store(String& mqi_encrypted) {
    // Prepare the key
    uint8_t key[34];
    int keysize = param::get_secret_key(key);
    AES128 aes;
    aes.setKey(key, keysize);
    // Prepare the information
    uint8_t ciphertext[48];
    uint8_t plaintext[48];
    char mqi_b64[mqi_encrypted.length() + 1];
    strcpy(mqi_b64, mqi_encrypted.c_str());
    int cipher_size = Base64.decodedLength(mqi_b64, mqi_encrypted.length());
    // Serial.printf("Cipher len %d \n", cipher_size);
    Base64.decode((char*)ciphertext, mqi_b64, mqi_encrypted.length());
    // Do decryption
    for (int i = 0; i < 3; i++)
        aes.decryptBlock(plaintext+i*16, ciphertext+i*16);
    // Plaintext is size 36, so set byte 36 to 0
    plaintext[MQI_TOKEN_SIZE] = 0;
    // Serial.printf("Plaintext: %s\n", plaintext);
    param::set_mqtt_mqi_token(String(plaintext));
}