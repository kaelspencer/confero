#ifndef PACKETDEFS_H
#define PACKETDEFS_H

#define SESSIONHOST     0x10	//receiving a list of hosts in a session
#define SESSIONJOIN     0x11	//confirmation of joining a session
#define SESSIONOFFER    0x12	//remote host is offering a session key
#define SESSIONREQUEST  0x15	//a request for all available keys
#define MESSAGE         0x20	//a string message
#define SESSIONS        0x30	//a list of all available keys; response to SESSIONREQUEST
#define SESSIONCOURTESY 0x31	//a list of all available keys; this isn't a response
#define EDIT            0x40	//an edit in qscintilla

typedef struct
{
    unsigned char type;
} Header;

typedef struct
{
    unsigned char type;
    unsigned short length;
} EncHeader;

typedef struct
{
    unsigned int key;
    unsigned char hostCount;
} SessionHosts;

typedef struct
{
    unsigned int key;
} SessionJoin;

typedef struct
{
    unsigned short length;
} Message;

typedef struct
{
    unsigned short count;
} Sessions;

typedef struct
{
    unsigned int size;
} EditStruct;

typedef struct
{
    unsigned short length;
} ConPublicKey;

#endif
