#include "Encryption.h"
/*
Encryption * Encryption::m_inst = 0;

Encryption::Encryption()
{
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(m_rng, KEYSIZE);
    m_privateKey = RSA::PrivateKey(params);
    m_publicKey = RSA::PublicKey(params);
}

Encryption * Encryption::Instance()
{
    if(m_inst == 0)
    {
        m_inst = new Encryption();
    }

    return m_inst;
}

void Encryption::AddKey(const QHostAddress & host, const unsigned char * e, size_t esize,
                        const unsigned char * n, size_t nsize)
{
    quint32 addr(host.toIPv4Address());

    if(!m_keys.contains(addr))
    {
        Integer inte(e, esize);
        Integer intn(n, nsize);

        RSA::PublicKey pkey;
        pkey.Initialize(intn, inte);

        m_keys.insert(addr, pkey);
    }
}

void Encryption::AddKey(const QHostAddress & host, const string & key)
{
    quint32 addr(host.toIPv4Address());

    if(!m_keys.contains(addr))
    {
        StringSource pubFile(key, true, new HexDecoder);
        RSA::PublicKey pkey;
        pkey.Load(pubFile);

        m_keys.insert(addr, pkey);
    }
}

string Encryption::Encrypt(string source, size_t & size, const QHostAddress & host)
{
    quint32 addr(host.toIPv4Address());

    if(m_keys.contains(addr))
    {
        RSA::PublicKey pkey(m_keys.value(addr));
        RSAES_OAEP_SHA_Encryptor e(pkey);

        string cipher;

        StringSource(source, true,
            new PK_EncryptorFilter(m_rng, e, new HexEncoder(new StringSink(cipher))));

        size = cipher.size();
        return cipher;
    }
    else
    {
        size = 0;
        return "";
    }
}

char * Encryption::Encrypt(const char * source, size_t & size, const QHostAddress & host)
{
    string enc(Encrypt(string(source, size), size, host));

    if(size != 0)
    {
        char * ptr = new char[size];
        memcpy_s(ptr, size, enc.c_str(), size);
        return ptr;
    }
    else
    {
        return 0;
    }
}

string Encryption::Decrypt(string source, size_t & size)
{
    string decrypted;

    RSAES_OAEP_SHA_Decryptor d(m_privateKey);

    StringSource(source, true,
        new HexDecoder(new PK_DecryptorFilter(m_rng, d, new StringSink(decrypted))));

    size = decrypted.size();
    return decrypted;
}

char * Encryption::Decrypt(const char * source, size_t & size)
{
    string decr(Decrypt(string(source, size), size));

    char * ptr = new char[size];
    memcpy_s(ptr, size, decr.c_str(), size);
    return ptr;
}

string Encryption::GetPublicKey()
{
    string key;

    HexEncoder pubString(new StringSink(key));
    m_publicKey.DEREncode(pubString);
    pubString.MessageEnd();

    return key;
}

void Encryption::Test()
{
    QHostAddress addr("127.0.0.1");

    string key = GetPublicKey();
    AddKey(addr, key);

    char * plain = "Test this encryption!";
    size_t size = strlen(plain);

    quint64 val = 38012840430;
    plain = reinterpret_cast<char *> (&val);
    size = 8;

    char * encryptedMsg = Encrypt(plain, size, addr);
    char * decryptedMsg = Decrypt(encryptedMsg, size);

    const quint64 * dval = reinterpret_cast<const quint64 *> (decryptedMsg);
    val = val + 1;

    delete encryptedMsg;
    delete decryptedMsg;
}
*/
