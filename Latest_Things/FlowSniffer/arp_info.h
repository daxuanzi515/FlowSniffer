#ifndef ARP_INFO_H
#define ARP_INFO_H
#include <QDateTime>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>
#include <string.h>
#include <QString>
#include <QRegExp>
#include <sstream>
#include <string>
#include <QList>
// C/C++ +Qt

#define EtherType 0x0806
#define HardWareType 0x0001
#define ProtocolType 0x0800
#define ARP_Response 0x0002
#define ARP_Request 0x0001
typedef struct tagARPFrame
{
    unsigned short  HW_Type;//hardware type，2 bytes，0x0001
    unsigned short Prot_Type;//protocol type，2 bytes，0x0800
    unsigned char HW_Addr_Len;//MAC address length,1 byte
    unsigned char Prot_Addr_Len;//IP address lenth，1 byte
    unsigned short  Opcode;//operative code，2 bytes，0x0001 request，0x0002 reply
    unsigned char Send_HW_Addr[6];//sender mac
    unsigned char Send_Prot_Addr[4];//sender ip
    unsigned char Targ_HW_Addr[6];//target mac
    unsigned char Targ_Prot_Addr[4];//target ip
    unsigned char padding[18];// padding data -> all 0
} ARPFRAME, *PARPFRAME;

typedef struct tagDLCHeader
{
    unsigned char DesMAC[6];//ethernet destination mac
    unsigned char SrcMAC[6];//ethernet source mac
    unsigned short Ethertype;//frame type
} DLCHEADER, *PDLCHEADER;
// ARP Packet = DLC header + ARP Frame
typedef struct tagARPPacket
{
    DLCHEADER dlcHeader; //ethernet header
    ARPFRAME arpFrame;//arp header
} ARPPACKET, *PARPPACKET;

class arp_info
{
public:
    arp_info();
//    QMessageBox *box = NULL;
    void sendArpPacket(pcap_t * fp, ARPPACKET &ARPPacket);
    ARPPACKET make_arp_packet(char* i_srcIP, char* i_srcMac, char* i_desIP, char* i_desMac, int opCode);
    std::string Random_IP(int r);
    char* Random_MAC(int r);


    char Char_set[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};// mac char array
    char target_set[18] = {'0','0',':','0','0',':','0','0',':','0','0',':','0','0',':','0','0','\0'};
    char temp_set[16] = {};
    QString arp_msg = "";
    QList<QStringList> arp_table = {};
};

#endif // ARP_INFO_H
