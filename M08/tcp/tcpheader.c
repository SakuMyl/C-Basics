#include "tcpheader.h"


int getSourcePort(const unsigned char *tcp_hdr)
{
    return tcp_hdr[0] << 8 | tcp_hdr[1];
}

int getDestinationPort(const unsigned char *tcp_hdr)
{
    return tcp_hdr[2] << 8 | tcp_hdr[3];
}

void setSourcePort(unsigned char *tcp_hdr, int port)
{
    tcp_hdr[0] = port >> 8;
    tcp_hdr[1] = port;
}

void setDestinationPort(unsigned char *tcp_hdr, int port)
{
    tcp_hdr[2] = port >> 8;
    tcp_hdr[3] = port;
}

int getAckFlag(const unsigned char *tcp_hdr)
{
    return tcp_hdr[13] >> 4 & 1;
}

void setAckFlag(unsigned char *tcp_hdr, int flag)
{
    unsigned char *byte = tcp_hdr + 13;
    if (flag) *byte |= 0x10;
    else *byte &= ~0x10;
}

int getDataOffset(const unsigned char *tcp_hdr)
{
    return tcp_hdr[12] >> 4;
}

void setDataOffset(unsigned char *tcp_hdr, int offset)
{
    tcp_hdr[12] &= 0x0f;
    tcp_hdr[12] |= offset << 4;
}
