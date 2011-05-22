#ifndef ENCRYPT_H
#define ENCRYPT_H

/*
#include <QHostAddress>
#include <QMap>
#include <string>
#include "cryptopp560/rsa.h"
#include "cryptopp560/osrng.h"
#include "cryptopp560/hex.h"

using namespace CryptoPP;
using std::string;

const quint32 KEYSIZE = 2048;

class Encryption
//class CONFERONET_EXPORT Encryption
{
private:
    static Encryption * m_inst;
    QMap<quint32, RSA::PublicKey> m_keys;
    AutoSeededRandomPool m_rng;
    RSA::PrivateKey m_privateKey;
    RSA::PublicKey m_publicKey;

    Encryption();
    Encryption(const Encryption & );
    Encryption & operator=(const Encryption & );
public:
    static Encryption * Instance();
    ~Encryption() {};

    string Encrypt(string source, size_t & size, const QHostAddress & host);
    char * Encrypt(const char * source, size_t & size, const QHostAddress & host);
    string Decrypt(string source, size_t & size);
    char * Decrypt(const char * source, size_t & size);
    void AddKey(const QHostAddress & host, const unsigned char * e, size_t esize,
                                            const unsigned char * n, size_t nsize);
    void AddKey(const QHostAddress & host, const string & key);
    string GetPublicKey();

    void Test();
};
*/
#endif
