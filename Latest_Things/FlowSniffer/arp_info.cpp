#include "arp_info.h"

arp_info::arp_info()
{
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    arp_msg = "-------Arp-Packet Sending Information-------\n";
    arp_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n");
}
// char* change to binary data char* like 01:23:45:67:89:AB -> 0123456789AB
int mac_str_to_bin(char *str, char *mac)
{
    int i;
    char *s, *e;
    if ((mac == nullptr) || (str == nullptr))
    {
        return -1;
    }
    s = (char *)str;
    for (i = 0; i < 6; ++i)
    {
        mac[i] = s ? strtoul(s, &e, 16) : 0;//strtoul() 16 char* -> unsigned long
        if (s)
            s = (*e) ? e + 1 : e;
    }
    return 0;
}



void arp_info::sendArpPacket(pcap_t * fp, ARPPACKET &ARPPacket)
{
    /* Send down the packet */
    if (pcap_sendpacket(fp,             // Adapter
        (const u_char *)&ARPPacket,     // buffer with the packet
        sizeof(ARPPacket)               // size
        ) != 0)
    {
        fprintf(stderr, "\nError sending the packet: %s\n", pcap_geterr(fp));
        qDebug()<<QString("send NULL ! \n");
        arp_msg += QString("Error sending the packet\n Send NULL!\n");
        return;
    }
    else
    {
        arp_msg += QString("Send Arp Packet size:%1 successfully!\n").arg(sizeof(ARPPacket));
        qDebug()<<QString("send OK! \n");
    }
}


ARPPACKET arp_info::make_arp_packet(char* i_srcIP, char* i_srcMac, char* i_desIP, char* i_desMac, int opCode)
{
    ARPPACKET Arp_packet;

    mac_str_to_bin(i_srcMac, (char*)Arp_packet.dlcHeader.SrcMAC);
    mac_str_to_bin(i_desMac, (char*)Arp_packet.dlcHeader.DesMAC);

    Arp_packet.dlcHeader.Ethertype = htons(EtherType);
    Arp_packet.arpFrame.HW_Type = htons(HardWareType);
    Arp_packet.arpFrame.Prot_Type = htons(ProtocolType);
    Arp_packet.arpFrame.HW_Addr_Len = 6;
    Arp_packet.arpFrame.Prot_Addr_Len = 4;
    if(opCode == 1)
    {
        Arp_packet.arpFrame.Opcode = htons(ARP_Request);
        arp_msg += QString("-----The arp packet is a Request packet.-----\n");
    }
    else{
        Arp_packet.arpFrame.Opcode = htons(ARP_Response);
        arp_msg += QString("-----The arp packet is a Response packet.-----\n");
    }
    //inet_pton() 10->2
    //ntohl() Network byte order 32bit > host byte order 32bit
    // AF_INET ipv4 address family
    inet_pton(AF_INET, i_srcIP, Arp_packet.arpFrame.Send_Prot_Addr);
    inet_pton(AF_INET, i_desIP, Arp_packet.arpFrame.Targ_Prot_Addr);
    mac_str_to_bin(i_srcMac, (char*)Arp_packet.arpFrame.Send_HW_Addr);
    mac_str_to_bin(i_desMac, (char*)Arp_packet.arpFrame.Targ_HW_Addr);

    qDebug()<<"send_mac_bin"<<Arp_packet.arpFrame.Send_HW_Addr;
    qDebug()<<"to_mac_bin"<<Arp_packet.arpFrame.Targ_HW_Addr;
    // fit 0
    memset(Arp_packet.arpFrame.padding, 0, sizeof(Arp_packet.arpFrame.padding));
    QStringList temp = {QString("%1").arg(i_srcIP),QString("%1").arg(i_desIP),QString("%1").arg(i_srcMac),QString("%1").arg(i_desMac),QString("%1").arg(sizeof(Arp_packet)),"ARP"};
    arp_table.append(temp);

    arp_msg += QString("Sender Host from ip:[%1],mac:[%2]\n-----sends %3 size arp packet to-----\nTarget Host from ip:[%4],mac:[%5]\n").arg(i_srcIP).arg(i_srcMac).arg(sizeof(Arp_packet)).arg(i_desIP).arg(i_desMac);
    qDebug()<<QString("Sender Host from ip:[%1],mac:[%2]\n-----sends %3 size arp packet to-----\nTarget Host from ip:[%4],mac:[%5]\n").arg(i_srcIP).arg(i_srcMac).arg(sizeof(Arp_packet)).arg(i_desIP).arg(i_desMac);

    return Arp_packet;
}


std::string arp_info::Random_IP(int r)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+r);
    int start = 0;
    int end = 256;
    std::string res = "";
     for (int i=0; i<4; ++i)
     {
         // random range [0,255]
        int k= qrand() % end+start;
        std::string temp = std::to_string(k);
        res += temp;
        if(i<3)
        {
            res += ".";
        }
     }
     return res;
}
char* arp_info::Random_MAC(int r)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime())+r);
    int start = 0;
    int end = 16;
    for(int i = 0; i < 12; i++)
    {
        // random range [0,11],[a,f]
        int k = start + qrand() % end;
        temp_set[i] = Char_set[k];
    }
    int i = 0, j = 0;
    for(i =0; i<12; i++, j++)
    {
        if(target_set[j]!=':')
        {
           target_set[j] = temp_set[i];
        }
        else
        {
            j++;
            target_set[j] = temp_set[i];
        }
    }
    return target_set;
}
