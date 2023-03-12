#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/ethernet.h>
#include <net/if.h>

#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/if_ether.h>

#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

//opt和包的显示
#define IFRLEN 20//network interface length
#define MAXSIZE 4096//buffer size
struct cmd_flags{
    bool a;//arp和ip,其他
    bool e;//显示Ethernet报头
    bool d;//包的内容是以16进制整数和ASCII码来显示
    bool i;
    char ifname[IFRLEN];
    bool p;
    bool f;
};
struct print_out{//只在指定了-p时有用
    bool arp;
    bool ip;
    bool icmp;
    bool tcp;
    bool udp;
};
struct cmd_flags f={false,false,false,false,false,false};
struct print_out p={false,false,false,false,false};
FILE *file;
FILE *gross;
void print_ethernet(struct ether_header *eth);
void print_arp(struct ether_arp *arp);
void print_ip(struct ip *ip);
void print_icmp(struct icmp *icmp);
void print_tcp(struct tcphdr *tcp);
void print_udp(struct udphdr *udp);
void dump_packet(unsigned char *buff,int len);
char* mac_ntoa(u_char *d);//将MAC地址变换为字符串的函数
char* ip_ttoa(int flag);//将IP报头中的标志变换为ASCII码的辅助函数。
char* ip_ftoa(int flag);//将IP报头标志变换为ASCII码的辅助函数。
char* tcp_ftoa(int flag);//TCP报头中的标志变换为ASCII码的辅助函数。
int ip_atou(char *ipa,unsigned int *ip32);
//显示ipdump的使用方法
void help();
//发现网元
struct ne{
    u_char a[6];
    struct ne *next;
};
struct ne nenode={0,0,0,0,0,0,NULL};
int find_ne(u_char *d);//to find the net element
void p_ne(struct ne *neptr);//to display the net element in the linked list
void free_ne(struct ne *neptr);//to free the net element linked list
//统计
struct count{
    //main
    time_t st;
    int mac_s;
    int mac_l;
    int macbyte;
    int mac;
    //p_count
    int macbroad;

    int ipbroad;
    int ipbyte;
    int ip;
    int tcp;
    int udp;

    int icmp;
    int icmp_r;
    int icmp_d;
};
struct count ct={0,0,0,0,0, 0,0,0,0,0, 0,0,0};
unsigned int submask;

void p_table();//to show the statistical information
void p_count(struct ether_header *eth);//to count the statistical information
int getif1(char *ifname,int i);//i>=0,get the first network interface name after i-th
//过滤
struct filter{
    bool i;
    bool p;
    unsigned int ip;
    int port;
};
struct filter pf={false,false,0,0};
int iszero(char *a,int len);//a is all zeros
int ip_atou(char *ipa,unsigned int *ip32);//ip adrress,char to u_int
int p_filter(struct ether_header *eth);//返回0则进一部处理，1则不处理//过滤出需要的包
//signal
void endfun();//the thing after ctrl c (Pay attention to your ctrl+c whether if ocuppied.It must can be used.)

//5.main函数
int main(int argc,char *argv[]){
    file = fopen("./MYLOG.txt", "r");
    if (file!=NULL)
    {
        remove("./MYLOG.txt");
    }
    file = fopen("./MYLOG.txt", "a");
    fputs(" Hello FlowSniffer!\n", file);

    gross = fopen("./GROSS.txt", "r");
    if (gross!=NULL)
    {
        remove("./GROSS.txt");
    }
    gross = fopen("./GROSS.txt", "a");
    int opt;
    while((opt=getopt(argc,argv,"aedhp:i:f:"))!=-1){
        switch(opt){
        case 'a':
        f.a=true;
        break;
        case 'e':
        f.e=true;
        break;
        case 'd':
        f.d=true;
        break;
        case 'h':
        help();
        exit(0);
        case 'i':
        f.i=true;
        if(strlen(optarg)<IFRLEN)
                    strcpy(f.ifname,optarg);
        else{
            fputs("the size of the ifname is too big\n", file);
            printf("the size of the ifname is too big\n");
            exit(1);
        }
                break;
        case 'p':
        f.p=true;
        optind--;
        while(argv[optind]!=NULL&&argv[optind][0]!='-'){
            if(strcmp(argv[optind],"arp")==0)
                p.arp=true;
            else if(strcmp(argv[optind],"ip")==0)
                p.ip=true;
            else if(strcmp(argv[optind],"icmp")==0)
                p.icmp=true;
            else if(strcmp(argv[optind],"tcp")==0)
                p.tcp=true;
            else if(strcmp(argv[optind],"udp")==0)
                p.udp=true;
            else{
                printf("unknown parameter:%s",argv[optind]);
                fprintf(file,"unknown parameter:%s",argv[optind]);
                exit(1);
            }
            optind++;
        }
        break;
    case 'f':
        f.f=true;//设定为过滤出需要的包
        optind--;
        while(argv[optind]!=NULL&&argv[optind][0]!='-'){
            if(strcmp(argv[optind],"ip")==0){
                pf.i=true;
                optind++;
            if(argv[optind]==NULL){
                fprintf(file,"input the ip address\n");
                printf("input the ip address\n");
                exit(1);
            }
                if(ip_atou(argv[optind],&pf.ip)==1){
                    fprintf(file,"bad parameter of ip address:%s\n",argv[optind]);
                    printf("bad parameter of ip address:%s\n",argv[optind]);
                    exit(1);
                }
                //printf("pf.ip:%u\n",pf.ip);
            }else if(strcmp(argv[optind],"port")==0){
                pf.p=true;
                optind++;
            if(argv[optind]==NULL){
                fprintf(file,"input the port number\n");
                printf("input the port number\n");
                exit(1);
            }
                pf.port=atoi(argv[optind]);
                if(pf.port<=0){
                    fprintf(file,"bad parameter of port:%s\n",argv[optind]);
                    printf("bad parameter of port:%s\n",argv[optind]);
                    exit(1);
                }
            }else{
                fprintf(file,"unknown parameter:%s",argv[optind]);
                printf("unknown parameter:%s",argv[optind]);
                exit(1);
            }
            optind++;
        }
        break;
        case ':':
                fprintf(file,"option need a value\n");
                printf("option need a value\n");
                break;
        case '?':
                fprintf(file,"option need a value\n");
                printf("unknown option:%c\n",optopt);
                exit(1);
    default:
        fprintf(file,"未知错误");
        printf("未知错误");
        exit(1);
        }
    }
    if(optind<argc){
        for(;optind<argc;optind++)
        {
            fprintf(file,"unknown:%s\n",argv[optind]);
            printf("unknown:%s\n",argv[optind]);
        }
    exit(1);
    }

    //信号
    signal(SIGINT,endfun);
    //原始套接字
    int s;
    if((s=socket(PF_PACKET,SOCK_PACKET,htons(ETH_P_ALL)))<0){
        perror(" socket");
        exit(1);
    }
    //未指定网口,获取网口名
    struct ifreq ifr_mask;
    char ifname[20];
    unsigned int* intptr;
    int ret=0;
    if(f.i==false){//get first ifname that has a submask//统计
        while(1){
            if((ret=getif1(ifname,ret))==-1){
                fprintf(file,"can\'t get a network interface name that has a submask");
                printf("can\'t get a network interface name that has a submask");
                exit(1);
            }
            memset(&ifr_mask, 0, sizeof(ifr_mask));
            strcpy(ifr_mask.ifr_name,ifname);
            if(ioctl(s,SIOCGIFNETMASK,&ifr_mask)< 0){
                ret++;
                    continue;
            }else{
                printf(" Listen to the network interface:%s\n",ifname);
                //input file
                fprintf(file," Listen to the network interface:%s\n",ifname);
                intptr=(unsigned int*)&(ifr_mask.ifr_netmask);//int 32bit
                submask=intptr[1];
                break;
            }
        }

    }
    //指定网口//
    struct ifreq interface;
    if(f.i==true){
        memset(&interface, 0, sizeof(interface));
        strncpy(interface.ifr_ifrn.ifrn_name,f.ifname,strlen(f.ifname));
        if(setsockopt(s,SOL_SOCKET,SO_BINDTODEVICE,(char *)&interface,sizeof(interface))<0){
            printf("network interface %s bind failed\n",f.ifname);
            fprintf(file,"network interface %s bind failed\n",f.ifname);
            exit(1);
        }
        if(ioctl(s,SIOCGIFNETMASK,&interface)< 0){
            fprintf(file,"get submask failed\n");
            printf("get submask failed\n");
            exit(1);
        }
        fprintf(file,"Listen to the network interface:%s\n",f.ifname);
        printf("Listen to the network interface:%s\n",f.ifname);
        intptr=(unsigned int*)&(interface.ifr_netmask);//int 32bit
        submask=intptr[1];
    }
    //抓包处理
    int len;
    char *ptr0;//指针
    char *ptr;//指针
    unsigned char buff[MAXSIZE];

    struct ether_header *eth;
    struct ether_arp *arp;
    struct ip *ip;
    struct icmp *icmp;
    struct tcphdr *tcp;
    struct udphdr *udp;

    time(&ct.st);//设置开始时间
    int pack_num=1;
    while(true){
        if((len=read(s,buff,MAXSIZE))<0){
            perror(" read");
            exit(1);
        }

        ptr= ptr0 = buff;
        //以太包匹配
        eth=(struct ether_header *)ptr;
        //统计
        ct.mac++;
        ct.macbyte+=len;
        if(len<64)
            ct.mac_s++;
        else if(len>1518)
            ct.mac_l++;
        p_count(eth);
        //网元发现
        find_ne(eth->ether_dhost);
        find_ne(eth->ether_shost);
        //过滤
        if(f.f==true){
            if(p_filter(eth)==1)
                continue;
        }
        //显示
        ptr=ptr+sizeof(struct ether_header);
        if(ntohs(eth->ether_type)==ETHERTYPE_ARP){//ARP
            if(f.p==false||p.arp==true){
                printf("\n\n Packet Number:%d\n",pack_num++);
                fprintf(file,"\n\n Packet Number:%d\n",pack_num);
                if(f.e==true){
                    print_ethernet(eth);
                }
                arp=(struct ether_arp*)ptr;//ARP匹配
                print_arp(arp);
            }
        }else if(ntohs(eth->ether_type)==ETHERTYPE_IP){//IP
            if(f.p&&(!p.ip)&&(!p.icmp)&&(!p.tcp)&&(!p.udp))
                continue;
            printf("\n\n Packet Number:%d\n",pack_num++);
            fprintf(file,"\n\n Packet Number:%d\n",pack_num);
            ip=(struct ip *)ptr;//ip匹配
            ptr=ptr+((int)(ip->ip_hl)<<2);//ip首部长乘4(Byte/char)
            if(f.e==true){
                print_ethernet(eth);
            }
            if(f.p==false||p.ip==true){
                print_ip(ip);
            }
            switch(ip->ip_p){
            case IPPROTO_TCP://TCP匹配
                tcp=(struct tcphdr *)ptr;
                //ptr=ptr+((int)(tcp->th_off)<<2);
                if(f.p==false||p.tcp==true)
                    print_tcp(tcp);
                break;
            case IPPROTO_UDP://UDP匹配
                udp=(struct udphdr *)ptr;
                //ptr=ptr+sizeof(struct udphdr);
                if(f.p==false||p.udp==true)
                    print_udp(udp);
                break;
            case IPPROTO_ICMP://ICMP匹配
                icmp=(struct icmp *)ptr;
                //ptr=ptr+sizeof(struct udphdr);
                if(f.p==false||p.icmp==true)
                    print_icmp(icmp);
                break;
            default://IP其他
                printf("Protocol:unknown\n");
                fprintf(file,"Protocol:unknown\n");
                break;
            }
        }else if(f.a){//以太其他
            if(f.e==true){
                printf("\n\n Packet Number:%d\n",pack_num++);
                fprintf(file,"\n\n Packet Number:%d\n",pack_num);
                print_ethernet(eth);
            }
            printf(" protocol:unknown\n");
            fprintf(file," protocol:unknown\n");
        }
        if(f.d){
            dump_packet(ptr0,len);
            printf("\n");
            fprintf(file,"\n");
        }
    }
    return 0;
}


//struct ether_header
//{
//u_int8_t ether_dhost[ETH_ALEN];      // destination eth addr
//u_int8_t ether_shost[ETH_ALEN];      // source ether addr
//u_int16_t ether_type;                 // packet type ID field
//} __attribute__ ((__packed__));

//6B(48bit)每行
void print_ethernet(struct ether_header *eth){
//作用是将一个16位数由网络字节顺序转换为主机字节顺序
    int type=ntohs(eth->ether_type);
    if(type<=1500)
    {
        fprintf(file," IEEE 802.3 Ethernet Frame:\n");
        printf(" IEEE 802.3 Ethernet Frame:\n");
    }
    else
    {
        printf(" Ethernet Frame:\n");
        fprintf(file," Ethernet Frame:\n");
    }

    printf(" +----------------+----------------+----------------+\n");
    printf(" |Destination MAC Adress:%27s|\n",mac_ntoa(eth->ether_dhost));
    printf(" +----------------+----------------+----------------+\n");
    printf(" |Source MAC Adress:%32s|\n",mac_ntoa(eth->ether_shost));
    printf(" +----------------+----------------+----------------+\n");
    //input file
    fprintf(file," +----------------+----------------+----------------+\n");
    fprintf(file," |Destination MAC Adress:%27s|\n",mac_ntoa(eth->ether_dhost));
    fprintf(file," +----------------+----------------+----------------+\n");
    fprintf(file," |Source MAC Adress:%32s|\n",mac_ntoa(eth->ether_shost));
    fprintf(file," +----------------+----------------+----------------+\n");
    if(type<=1500)
    {
        printf(" |LenghL:%9u|\n",type);
        fprintf(file," |LenghL:%9u|\n",type);
    }
    else
    {
        fprintf(file," |E-Type:   0x%04x|\n",type);
        printf(" |E-Type:   0x%04x|\n",type);
    }
    fprintf(file," +----------------+\n");
    printf(" +----------------+\n");
}
char* mac_ntoa(u_char *d){//将MAC地址变换为字符串的函数
    static char str[50];
    sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",
        d[0],d[1],d[2],d[3],d[4],d[5]);
    return str;
}


// typedef struct ether_arp
//{
//    struct arphdr ea_hdr;
//    u_char arp_sha[ETHER_ADDR_LEN];
//    u_char arp_spa[4];
//    u_char arp_tha[ETHER_ADDR_LEN];
//    u_char arp_tpa[4];
//}ETH_ARP;
//#define arp_hrd ea_hdr.ar_hrd
//#define arp_pro ea_hdr.ar_pro
//#define arp_hln ea_hdr.ar_hln
//#define arp_pln ea_hdr.ar_pln
//#define arp_op ea_hdr.ar_op
//#define ARPHRD 1
void print_arp(struct ether_arp *arp){
    static char *arp_operation[]={
        "(Undefine)",
        "(ARP Request)",
        "(ARP Reply)",
        "(RARP Requst)",
        "(RARP Reply)"
        };
    int op=ntohs(arp->ea_hdr.ar_op);
    if(op<=0||op>=5)
        op=0;
    //input file
    fprintf(file," Protocal:ARP\n");
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |H-Ty:%2u%-10s|P:0x%04x%-9s|\n",
        ntohs(arp->ea_hdr.ar_hrd),
        (ntohs(arp->ea_hdr.ar_hrd)==ARPHRD_ETHER)?"(Ether)":"(Not Ether)",
        ntohs(arp->ea_hdr.ar_pro),
        (ntohs(arp->ea_hdr.ar_pro)==ETHERTYPE_IP)?"(IP)":"(Not IP)"
        );
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |H-len:%2u|P-Len:%2u|op:%d%12s|\n",
        arp->ea_hdr.ar_hln,
        arp->ea_hdr.ar_pln,
        ntohs(arp->ea_hdr.ar_op),
        arp_operation[op]
        );
    fprintf(file," +--------+--------+--------+--------+--------+--------+\n");
    fprintf(file," |Source MAC Adress:%35s|\n",mac_ntoa(arp->arp_sha));
    fprintf(file," +--------+--------+--------+--------+--------+--------+\n");
    fprintf(file," |Source IP Address:%17s|\n",inet_ntoa(*(struct in_addr *)&arp->arp_spa));
    fprintf(file," +--------+--------+--------+--------+--------+--------+\n");
    fprintf(file," |Destination MAC Adress:%30s|\n",mac_ntoa(arp->arp_tha));
    fprintf(file," +--------+--------+--------+--------+--------+--------+\n");
    fprintf(file," |Dest   IP Address:%17s|\n",inet_ntoa(*(struct in_addr *)&arp->arp_tpa));
    fprintf(file," +--------+--------+--------+--------+\n");
    //------
    printf(" Protocal:ARP\n");
    printf(" +--------+--------+--------+--------+\n");
    printf(" |H-Ty:%2u%-10s|P:0x%04x%-9s|\n",
        ntohs(arp->ea_hdr.ar_hrd),
        (ntohs(arp->ea_hdr.ar_hrd)==ARPHRD_ETHER)?"(Ether)":"(Not Ether)",
        ntohs(arp->ea_hdr.ar_pro),
        (ntohs(arp->ea_hdr.ar_pro)==ETHERTYPE_IP)?"(IP)":"(Not IP)"
        );
    printf(" +--------+--------+--------+--------+\n");
    printf(" |H-len:%2u|P-Len:%2u|op:%d%12s|\n",
        arp->ea_hdr.ar_hln,
        arp->ea_hdr.ar_pln,
        ntohs(arp->ea_hdr.ar_op),
        arp_operation[op]
        );
    printf(" +--------+--------+--------+--------+--------+--------+\n");
    printf(" |Source MAC Adress:%35s|\n",mac_ntoa(arp->arp_sha));
    printf(" +--------+--------+--------+--------+--------+--------+\n");
    printf(" |Source IP Address:%17s|\n",inet_ntoa(*(struct in_addr *)&arp->arp_spa));
    printf(" +--------+--------+--------+--------+--------+--------+\n");
    printf(" |Destination MAC Adress:%30s|\n",mac_ntoa(arp->arp_tha));
    printf(" +--------+--------+--------+--------+--------+--------+\n");
    printf(" |Dest   IP Address:%17s|\n",inet_ntoa(*(struct in_addr *)&arp->arp_tpa));
    printf(" +--------+--------+--------+--------+\n");
}

// typedef struct ip
//{
//    u_int ip_v:4; //version(版本)
//    u_int ip_hl:4; //header length(报头长度)
//    u_char ip_tos;
//    u_short ip_len;
//    u_short ip_id;
//    u_short ip_off;
//    u_char ip_ttl;
//    u_char ip_p;
//    u_short ip_sum;
//    struct in_addr ip_src;
//    struct in_addr ip_dst;
//}IP_HEADER;

//struct in_addr {
//    in_addr_t s_addr;
//};
//表示一个32位的IPv4地址。
//in_addr_t一般为32位的unsigned int，其字节顺序为网络字节序，即该无符号数采用大端字节序。
void print_ip(struct ip *ip){
    //input file
    fprintf(file," Protocal:IP\n");
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |IV:%1u|HL:%02u|T:%8s|T-Length:%4u|\n",
        ip->ip_v,ip->ip_hl,ip_ttoa(ip->ip_tos),ntohs(ip->ip_len));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Identifier:%6u|FF:%3s|FO:%7u|\n",
        ntohs(ip->ip_id),ip_ftoa(ntohs(ip->ip_off)),ntohs(ip->ip_off)&IP_OFFMASK);
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |TTL:%4u|Pro:%4u|Checksum:%8u|\n",
        ip->ip_ttl,ip->ip_p,ntohs(ip->ip_sum));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Source IP Address:%17s|\n",
        inet_ntoa(*(struct in_addr *)&(ip->ip_src)));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Dest   IP Address:%17s|\n",
        inet_ntoa(*(struct in_addr *)&(ip->ip_dst)));
    fprintf(file," +--------+--------+--------+--------+\n");

    printf(" Protocal:IP\n");
    printf(" +--------+--------+--------+--------+\n");
    printf(" |IV:%1u|HL:%02u|T:%8s|T-Length:%4u|\n",
        ip->ip_v,ip->ip_hl,ip_ttoa(ip->ip_tos),ntohs(ip->ip_len));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Identifier:%6u|FF:%3s|FO:%7u|\n",
        ntohs(ip->ip_id),ip_ftoa(ntohs(ip->ip_off)),ntohs(ip->ip_off)&IP_OFFMASK);
    printf(" +--------+--------+--------+--------+\n");
    printf(" |TTL:%4u|Pro:%4u|Checksum:%8u|\n",
        ip->ip_ttl,ip->ip_p,ntohs(ip->ip_sum));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Source IP Address:%17s|\n",
        inet_ntoa(*(struct in_addr *)&(ip->ip_src)));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Dest   IP Address:%17s|\n",
        inet_ntoa(*(struct in_addr *)&(ip->ip_dst)));
    printf(" +--------+--------+--------+--------+\n");
}
char* ip_ttoa(int flag){//将IP报头中的标志变换为ASCII码的辅助函数。
    static int f_it[]={'1','1','1','D','T','R','C','X'};
    static char str[17];
    u_int mask=0x80;
    int i;
    for(i=0;i<8;i++){
        if(((flag<<i)&mask)!=0)
            str[i]=f_it[i];
        else
            str[i]='0';
    }
    str[i]='\0';
    return str;
}
char* ip_ftoa(int flag){//将IP报头标志变换为ASCII码的辅助函数。
    static int f_if[]={'R','D','M'};
    static char str[17];
    u_int mask=0x8000;
    int i;
    for(i=0;i<3;i++){
        if(((flag<<i)&mask)!=0)
            str[i]=f_if[i];
        else
            str[i]='0';
    }
    str[i]='\0';
    return str;
}

void print_icmp(struct icmp *icmp){
    static char *type_name[]={
        "Echo Reply",//0
        "Undifine",//1
        "Undifine",//2
        "Destination Unreachable",//3
        "Source Quench",//4
        "Redirect",//5
        "Undifine",//6
        "Undifine",//7
        "Echo Request",//8
        "Router Advertisement",//9
        "Route Solicitation",//10
        "Time Exceeded",//11
        "Parameter Problem",//12
        "Timestamp Request*",//13
        "Timestamp Reply*",//14
        "Information Request*",//15
        "Information Reply*",//16
        "Address Mask Request",//17
        "Address Mask Reply",//18
        "Unknown"
        };
    int type=icmp->icmp_type;
    if(type<0||type>18)
        type=19;
    //input file
    fprintf(file," Protocal:ICMP(%s)\n",type_name[type]);
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Type:%3u|Code:%3u|Checksum:%8u|\n",
        icmp->icmp_type,icmp->icmp_code,ntohs(icmp->icmp_cksum));
    fprintf(file," +--------+--------+--------+--------+\n");

    printf(" Protocal:ICMP(%s)\n",type_name[type]);
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Type:%3u|Code:%3u|Checksum:%8u|\n",
        icmp->icmp_type,icmp->icmp_code,ntohs(icmp->icmp_cksum));
    printf(" +--------+--------+--------+--------+\n");
    bool fl=false;
    if(type==0||type==8)
    {
        fprintf(file," |Identifi:%8u|Seq  Num:%8u|\n",
        ntohs(icmp->icmp_id),ntohs(icmp->icmp_seq));
        printf(" |Identifi:%8u|Seq  Num:%8u|\n",
        ntohs(icmp->icmp_id),ntohs(icmp->icmp_seq));
    }
    else if(type==3){
        if(icmp->icmp_code==4)
        {
            fprintf(file," |void:%5u|Next MTU:%5u|\n",
            ntohs(icmp->icmp_pmvoid),ntohs(icmp->icmp_nextmtu));
            printf(" |void:%5u|Next MTU:%5u|\n",
            ntohs(icmp->icmp_pmvoid),ntohs(icmp->icmp_nextmtu));
        }
        else
        {
            fprintf(file," |Unsed:%10lu|\n",
                (u_long)ntohl(icmp->icmp_void));
            printf(" |Unsed:%10lu|\n",
                (u_long)ntohl(icmp->icmp_void));
        }
    }else if(type==5)
    {
        fprintf(file," |Router IP Address:%15s|\n",
        inet_ntoa(*(struct in_addr *)&(icmp->icmp_gwaddr)));
        printf(" |Router IP Address:%15s|\n",
        inet_ntoa(*(struct in_addr *)&(icmp->icmp_gwaddr)));
    }
    else if(type==11)
    {
        fprintf(file," |Unused:%10lu|\n",
        (u_long)ntohl(icmp->icmp_void));
        printf(" |Unused:%10lu|\n",
        (u_long)ntohl(icmp->icmp_void));
    }
    else
        fl=true;
    if(fl==false){
        printf(" +--------+--------+--------+--------+\n");
        fprintf(file," +--------+--------+--------+--------+\n");
    }
    if(type==3||type==5||type==11)
        print_ip((struct ip *)(((char *)icmp)+8));
}

void print_tcp(struct tcphdr *tcp){
    //input file
    fprintf(file," Protocol:TCP\n");
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Source Port:%5u|Dest Port:%7u|\n",
        ntohs(tcp->th_sport),ntohs(tcp->th_dport));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |sequnce Number:%20lu|\n",
        (u_long)ntohl(tcp->th_seq));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Acknowlegement Number:%13lu|\n",
        (u_long)ntohl(tcp->th_ack));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Do%3u|RR|F:%6s|Window Size:%5u|\n",
        tcp->th_off,tcp_ftoa(tcp->th_flags),ntohs(tcp->th_win));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Cheksum:%9u|Urgent-P:%8u|\n",
        ntohs(tcp->th_sum),ntohs(tcp->th_urp));
    fprintf(file," +--------+--------+--------+--------+\n");
    //每行32bit
    printf(" Protocol:TCP\n");
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Source Port:%5u|Dest Port:%7u|\n",
        ntohs(tcp->th_sport),ntohs(tcp->th_dport));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |sequnce Number:%20lu|\n",
        (u_long)ntohl(tcp->th_seq));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Acknowlegement Number:%13lu|\n",
        (u_long)ntohl(tcp->th_ack));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Do%3u|RR|F:%6s|Window Size:%5u|\n",
        tcp->th_off,tcp_ftoa(tcp->th_flags),ntohs(tcp->th_win));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Cheksum:%9u|Urgent-P:%8u|\n",
        ntohs(tcp->th_sum),ntohs(tcp->th_urp));
    printf(" +--------+--------+--------+--------+\n");
}
char* tcp_ftoa(int flag){//TCP报头中的标志变换为ASCII码的辅助函数。
    static int f_tf[]={'U','A','P','R','S','F'};
    static char str[17];
    u_int mask=1<<5;
    int i;
    for(i=0;i<6;i++){
        if(((flag<<i)&mask)!=0)
            str[i]=f_tf[i];
        else
            str[i]='0';
    }
    str[i]='\0';
    return str;
}

// typedef struct udphdr
//{
//    u_short uh_sport;
//    u_short uh_dport;
//    u_short uh_ulen;
//    u_short uh_sum;
//}UDP_HEADER;
void print_udp(struct udphdr *udp){
    //input file
    fprintf(file," Protocol:UDP\n");
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Source Port:%5u|Dest Port:%7u|\n",
        ntohs(udp->uh_sport),ntohs(udp->uh_dport));
    fprintf(file," +--------+--------+--------+--------+\n");
    fprintf(file," |Length:%10u|Checksum:%8u|\n",
        ntohs(udp->uh_ulen),ntohs(udp->uh_sum));
    fprintf(file," +--------+--------+--------+--------+\n");
    //每行32bit
    printf(" Protocol:UDP\n");
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Source Port:%5u|Dest Port:%7u|\n",
        ntohs(udp->uh_sport),ntohs(udp->uh_dport));
    printf(" +--------+--------+--------+--------+\n");
    printf(" |Length:%10u|Checksum:%8u|\n",
        ntohs(udp->uh_ulen),ntohs(udp->uh_sum));
    printf(" +--------+--------+--------+--------+\n");
}

void dump_packet(unsigned char *buff,int len){
    int i,j;
    fprintf(file," Frame Dump:\n");
    printf(" Frame Dump:\n");
    for(i=0;i<len;i+=16){
        //16
        for(j=i;j<i+16&&j<len;j++){
            fprintf(file,"%02x",buff[j]);
            printf("%02x",buff[j]);
            if(j%2==1)
            {
                fprintf(file," ");
                printf(" ");
            }
        }
        if(j==len&&len%16!=0)
            for(j=0;j<40-(len%16)*2.5;j++){
                fprintf(file," ");
                printf(" ");
        }
        fprintf(file,"    ");
        printf("    ");
        //ASCII
        for(j=i;j<i+16&&j<len;j++){
            if((buff[j]>=0x20)&&(buff[j]<=0x7e))
            {
                fprintf(file,"%c",buff[j]);
                putchar(buff[j]);
            }
            else
            {
                fprintf(file,".");
                printf(".");
            }
        }
        fprintf(file,"\n");
        printf("\n");
        fflush(stdout);
    }
}
void help(){
    fprintf(file,"usage: ./ipdump [-aedht] [-p protocols] [-i ifrname] [-f filters]\n");
    fprintf(file,"protocols: arp ip icmp tcp udp \n");//other??
    fprintf(file,"filters: ip <IP addr> port <PORT number>\n");
    fprintf(file,"default: ./ipdump -p arp ip icmp tcp udp\n");

    printf("usage: ./ipdump [-aedht] [-p protocols] [-i ifrname] [-f filters]\n");
    printf("protocols: arp ip icmp tcp udp \n");//other??
    printf("filters: ip <IP addr> port <PORT number>\n");
    printf("default: ./ipdump -p arp ip icmp tcp udp\n");
}
//
//过滤
int iszero(char *a,int len){
    for(int i=0;i<len;i++){
        if(a[i]!='0')
            return -1;
    }
    return 0;
}
int ip_atou(char *ipa,unsigned int *ip32){
    //u_char *ip=(u_char *)ip32;
    *ip32=0;
    unsigned int ret=0;
    if(strlen(ipa)<7||strlen(ipa)>15)//0.0.0.0 255.255.255.255
        return 1;
    char *temp=strtok(ipa,".");
    if(temp==NULL||atoi(temp)>255||atoi(temp)<0)
        return 1;
    if(atoi(temp)==0){
        if(iszero(temp,strlen(temp))==-1)
            return 1;
    }
    //*ip32=*ip32<<8+(unsigned int)atoi(temp);
    *ip32=(*ip32)*256+(unsigned int)atoi(temp);
    //printf("test\n");
    //printf("%u\n",*ip32);
    for(int i=0;i<3;i++){
        temp=strtok(NULL,".");
        if(temp==NULL||atoi(temp)>255||atoi(temp)<0)
            return 1;
        if(atoi(temp)==0){
            if(iszero(temp,strlen(temp))==-1)
                return 1;
        }
        //*ip32=*ip32<<8+(unsigned int)atoi(temp);
        *ip32=(*ip32)*256+(unsigned int)atoi(temp);
    }
    return 0;
}
int p_filter(struct ether_header *eth){//0则进一部处理，1则不处理
    char *ptr=(char *)eth;
    ptr=ptr+sizeof(struct ether_header);
    struct ip *ip;
    struct tcphdr *tcp;
    struct udphdr *udp;
    if(ntohs(eth->ether_type)==ETHERTYPE_IP){
        ip=(struct ip *)ptr;
        if(pf.i==true){
            //printf("pf.ip:%u\n",pf.ip);
            //printf("ip->ip_src.s_addr:%u\n",ip->ip_src.s_addr);
            //printf("ntohl(ip->ip_src.s_addr):%u\n",ntohl(ip->ip_src.s_addr));
            //if(pf.ip!=ip->ip_src.s_addr&&pf.ip!=ip->ip_dst.s_addr){
            if(pf.ip!=ntohl(ip->ip_src.s_addr)&&pf.ip!=ntohl(ip->ip_dst.s_addr)){
                return 1;
            }else if(pf.port==false){
                return 0;
            }
        }
        ptr=ptr+((int)(ip->ip_hl)<<2);
        switch(ip->ip_p){
            case IPPROTO_TCP://TCP匹配
                tcp=(struct tcphdr *)ptr;
                if(ntohs(tcp->th_sport)==pf.port||ntohs(tcp->th_dport)==pf.port)
                    return 0;
                break;
            case IPPROTO_UDP://UDP匹配
                udp=(struct udphdr *)ptr;
                if(ntohs(udp->uh_sport)==pf.port||ntohs(udp->uh_dport)==pf.port)
                    return 0;
                break;
        }
    }
    return 1;
}
//
//发现网元
int find_ne(u_char *d){
    struct ne* neptr=&nenode;
    while(neptr->next!=NULL){
        if(neptr->a[0]==d[0]&&neptr->a[1]==d[1]&&neptr->a[2]==d[2]&&neptr->a[3]==d[3]&&neptr->a[4]==d[4]&&neptr->a[5]==d[5])
            return 1;
        else
            neptr=neptr->next;
    }
    for(int i=0;i<6;i++){
        neptr->a[i]=d[i];
    }
    neptr->next=(struct ne*)malloc(sizeof(struct ne));
    neptr=neptr->next;
    neptr->next=NULL;
    return 0;
}

void p_ne(struct ne *neptr){
    fprintf(file,"\n	Find these mac address:\n");
    fprintf(gross,"\n	Find these mac address:\n");
    printf("\n	Find these mac address:\n");
    while(neptr->next!=NULL){//nenode.next的值是否为空，判断对于数组a[]是否有效
        fprintf(file,"	%s\n",mac_ntoa(neptr->a));
        fprintf(gross,"	%s\n",mac_ntoa(neptr->a));
        printf("	%s\n",mac_ntoa(neptr->a));
        neptr=neptr->next;
    }
}

void free_ne(struct ne *neptr){
    struct ne *neptr0;
    while(neptr!=NULL){
        neptr0=neptr;
        neptr=neptr->next;
        free(neptr0);
    }
}
//
//统计
void p_count(struct ether_header *eth){
    int i;
    for(i=0;i<6;i++){
        if(eth->ether_dhost[0]!=0xff)
            break;
    }
    if(i==6){
        ct.macbroad++;
    }
    char *ptr=(char *)eth;
    ptr=ptr+sizeof(struct ether_header);
    struct ip *ip;
    struct icmp *icmp;
    struct udphdr *udp;
    if(ntohs(eth->ether_type)==ETHERTYPE_IP){
        ct.ip++;
        ip=(struct ip *)ptr;
        ct.ipbyte+=ntohs(ip->ip_len)-ip->ip_hl*4;
        if((ntohl(ip->ip_dst.s_addr)|submask)==0xFFFFFFFF)//目的地址后面全1
            ct.ipbroad++;
        switch(ip->ip_p){
            case IPPROTO_TCP://TCP匹配
                ct.tcp++;
                break;
            case IPPROTO_UDP://UDP匹配
                ct.udp++;
                break;
            case IPPROTO_ICMP://ICMP匹配
                ct.icmp++;
                icmp=(struct icmp *)ptr;
                if(icmp->icmp_type==3)
                    ct.icmp_d++;
                if(icmp->icmp_type==5)
                    ct.icmp_r++;
                break;
        }
    }
}

int getif1(char *ifname,int i) {
    char bad_if[6][6]= {"lo:","lo","stf","gif","dummy","vmnet"};
    struct if_nameindex* ifn=if_nameindex();
    if(ifn == NULL) {
        return -1;
    }
    for(int j=0;j<6;j++){
        if (strcmp(ifn[i].if_name,bad_if[j]) == 0){
            i++;
            if(ifn[i].if_index==0){
                if_freenameindex(ifn);
                return -1;
            }
            j=0;
        }
    }
    strcpy(ifname,ifn[i].if_name);
    if_freenameindex(ifn);
    return i;
}
void p_table(){
    time_t et;
    time(&et);

    //input file
    fprintf(file,"\n\n");
    fprintf(file,"	The statistical  information\n");
    fprintf(file,"	varibale	 values\n");
    fprintf(file,"	StartTime	 %s",ctime(&ct.st));
    fprintf(file,"	EndTime		 %s",ctime(&et));
    fprintf(file,"	MAC Broad	 %d\n",ct.macbroad);
    fprintf(file,"	MAC Short	 %d\n",ct.mac_s);
    fprintf(file,"	MAC Long	 %d\n",ct.mac_l);
    fprintf(file,"	MAC Byte	 %d\n",ct.macbyte);
    fprintf(file,"	MAC Packet	 %d\n",ct.mac);
    fprintf(file,"	Bit/s		 %d\n",ct.macbyte/(int)(et-ct.st)*8);
    fprintf(file,"	MAC ByteSpeed	 %d\n",ct.macbyte/(int)(et-ct.st));
    fprintf(file,"	MAC PacketSpeed  %d\n",ct.mac/(int)(et-ct.st));
    fprintf(file,"	IP Broadcast	 %d\n",ct.ipbroad);
    fprintf(file,"	IP Byte		 %d\n",ct.ipbyte);
    fprintf(file,"	IP Packet	 %d\n",ct.ip);
    fprintf(file,"	UDP Packet	 %d\n",ct.udp);
    fprintf(file,"	ICMP Packet	 %d\n",ct.icmp);
    fprintf(file,"	ICMP Redirect	 %d\n",ct.icmp_r);
    fprintf(file,"	ICMP Destination %d\n",ct.icmp_d);

    //input gross
    fprintf(gross,"\n\n");
    fprintf(gross,"	The statistical  information\n");
    fprintf(gross,"	varibale	 values\n");
    fprintf(gross,"	StartTime	 %s",ctime(&ct.st));
    fprintf(gross,"	EndTime		 %s",ctime(&et));
    fprintf(gross,"	MAC Broad	 %d\n",ct.macbroad);
    fprintf(gross,"	MAC Short	 %d\n",ct.mac_s);
    fprintf(gross,"	MAC Long	 %d\n",ct.mac_l);
    fprintf(gross,"	MAC Byte	 %d\n",ct.macbyte);
    fprintf(gross,"	MAC Packet	 %d\n",ct.mac);
    fprintf(gross,"	Bit/s		 %d\n",ct.macbyte/(int)(et-ct.st)*8);
    fprintf(gross,"	MAC ByteSpeed	 %d\n",ct.macbyte/(int)(et-ct.st));
    fprintf(gross,"	MAC PacketSpeed  %d\n",ct.mac/(int)(et-ct.st));
    fprintf(gross,"	IP Broadcast	 %d\n",ct.ipbroad);
    fprintf(gross,"	IP Byte		 %d\n",ct.ipbyte);
    fprintf(gross,"	IP Packet	 %d\n",ct.ip);
    fprintf(gross,"	UDP Packet	 %d\n",ct.udp);
    fprintf(gross,"	ICMP Packet	 %d\n",ct.icmp);
    fprintf(gross,"	ICMP Redirect	 %d\n",ct.icmp_r);
    fprintf(gross,"	ICMP Destination %d\n",ct.icmp_d);

    printf("\n\n");
    printf("	The statistical  information\n");
    printf("	varibale	 values\n");
    printf("	StartTime	 %s",ctime(&ct.st));
    printf("	EndTime		 %s",ctime(&et));
    printf("	MAC Broad	 %d\n",ct.macbroad);
    printf("	MAC Short	 %d\n",ct.mac_s);
    printf("	MAC Long	 %d\n",ct.mac_l);
    printf("	MAC Byte	 %d\n",ct.macbyte);
    printf("	MAC Packet	 %d\n",ct.mac);
    printf("	Bit/s		 %d\n",ct.macbyte/(int)(et-ct.st)*8);
    printf("	MAC ByteSpeed	 %d\n",ct.macbyte/(int)(et-ct.st));
    printf("	MAC PacketSpeed  %d\n",ct.mac/(int)(et-ct.st));
    printf("	IP Broadcast	 %d\n",ct.ipbroad);
    printf("	IP Byte		 %d\n",ct.ipbyte);
    printf("	IP Packet	 %d\n",ct.ip);
    printf("	UDP Packet	 %d\n",ct.udp);
    printf("	ICMP Packet	 %d\n",ct.icmp);
    printf("	ICMP Redirect	 %d\n",ct.icmp_r);
    printf("	ICMP Destination %d\n",ct.icmp_d);
    fclose(file);
    fclose(gross);
}
//signal
void endfun(){
    //网元
    p_ne(&nenode);
    free_ne(nenode.next);
    p_table();
    exit(0);
}
