#ifndef SYNFLOOD_H
#define SYNFLOOD_H
#include <QDateTime>
#include <sys/socket.h>     // for socket
#include <sys/types.h>      // for socket
#include <netinet/in.h>     // for sockaddr_in
#include <netinet/tcp.h>    // for tcp
#include <netinet/ip.h>     // for ip
#include <arpa/inet.h>      // for inet_
#include <net/if.h>         // for ifreq
#include <memory.h>         // for memset
#include <unistd.h>         // for usleep
#include <string>
#include <QDebug>
#include <QList>
class SynFlood
{
public:
    explicit SynFlood();
    virtual ~SynFlood();
    QString syn_msg = "";
    QList<QStringList> syn_table = {};
    QString desip = "";
    QString desport = "";

    /*SynFlood initiate */
    int init(std::string ip_addr, int port);

    /*SynFlood attack*/
    int attack(int flood_times);
protected:
    /*initiate rawSocket*/
    int initRawSocket();

    /*初始化ip数据报*/
    int initIpData();
private:
    /*addrInfo*/
    std::string ip_addr;
    int port;

    /*rawSocket*/
    struct sockaddr_in addr;    //address struct message
    int socket_fd;              //socket
    unsigned char ip_datagram[sizeof(struct ip) + sizeof(struct tcphdr)];       //ip datagram
    unsigned int ip_datagram_len = sizeof(struct ip) + sizeof(struct tcphdr);   //ip datagram length
    struct ip *ip_header;       //ip header pointer
    struct tcphdr *tcp_header;  //tcp header pointer
};

#endif // SYNFLOOD_H
