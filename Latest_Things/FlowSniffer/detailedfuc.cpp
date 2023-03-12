#include "detailedfuc.h"
DetailedFuc::DetailedFuc()
{

}

// synflood interface
QString DetailedFuc::run_syn_flood(char* target_ip, char* target_port, int times)
{
    //targte ip
    std::string ip_addr = target_ip;

        //target port
    int port = atoi(target_port);

        //attacked times
    unsigned int flood_times = times;

    SynFlood syn_flood;
    if(syn_flood.init(ip_addr,port)==0)
    {
        if(syn_flood.attack(flood_times)==0)
        {
            temp.append(syn_flood.syn_table);
            qDebug()<<"temp"<<temp;
            qDebug()<<"attack end"<<endl;
            return syn_flood.syn_msg + "-------Attack end------\n";
        }
    }
    else
    {
        qDebug()<<"attack Fail"<<endl;
        return "-------Attack Fail!-------\n";
    }

}



std::string DetailedFuc::getCmdResult(const std::string &strCmd)
{
    char buf[10240] = {0};
    FILE *pf = NULL;

    if( (pf = popen(strCmd.c_str(), "r")) == NULL )
    {
        return "";
    }

    std::string strResult;
    while(fgets(buf, sizeof buf, pf))
    {
        strResult += buf;
    }

    pclose(pf);

    unsigned int iSize =  strResult.size();
    if(iSize > 0 && strResult[iSize - 1] == '\n')  // linux
    {
        strResult = strResult.substr(0, iSize - 1);
    }

    return strResult;
}

QString DetailedFuc::get_mac_address()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// get all interfaces list
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}


QString DetailedFuc::get_main_device()
{
    QList<QNetworkInterface> netList =  QNetworkInterface::allInterfaces();
    QString main_device = "";
    foreach(QNetworkInterface net,netList)
    {
        //get list of interfaces
        qDebug()<<"id:"<<net.index();//id
        qDebug()<<"Device:"<<net.name();//name
        qDebug()<<"HardwareAddress:"<<net.hardwareAddress();//get mac
        if(net.index() == 2)
        {
            main_device = net.name();
        }
     }
     return main_device;
}

QString DetailedFuc::get_device_msg()
{

    QString device_name;
    device_name.clear();

    QList<QNetworkInterface> netList =  QNetworkInterface::allInterfaces();
            foreach(QNetworkInterface net,netList)
            {
                //get interfaces
                qDebug()<<"id:"<<net.index();//id
                qDebug()<<"Device:"<<net.name();//name
                qDebug()<<"HardwareAddress:"<<net.hardwareAddress();//mac
                device_name += QString("id:%1\nDevice:%2\nHardwareAddress:%3\n").arg(net.index()).arg(net.name()).arg(net.hardwareAddress());
                QList<QNetworkAddressEntry> entryList = net.addressEntries();
                foreach(QNetworkAddressEntry entry,entryList)
                {//遍历ip条目列表
                    qDebug()<<"IP address："<<entry.ip().toString();//ip
                    qDebug()<<"Netmask:"<<entry.netmask().toString();//netmask
                    qDebug()<<"Broadcast:"<<entry.broadcast().toString();//broadcast
                    device_name += QString("IP address:%1\nNetmask:%2\nBroadcast:%3\n").arg(entry.ip().toString()).arg(entry.netmask().toString()).arg(entry.broadcast().toString());
                }
            }
    return device_name;
}

QString DetailedFuc::device_ip_address()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // get the first one ipv4
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
               ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress = ipAddressesList.at(i).toString();
               break;
           }
     }
     //local ip
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}

QString DetailedFuc::local_ip_address()
{
    char hname[128];
    struct hostent *hent;
    int i;
    QString msg;
    msg.clear();
    gethostname(hname, sizeof(hname));

    //hent = gethostent();
    hent = gethostbyname(hname);
//    char str1[200];
    char str2[200];
//    sprintf(str1,"hostname: %s/naddress list: ", hent->h_name);
//    msg += QString::fromStdString(str1);
    for(i = 0; hent->h_addr_list[i]; i++) {
        sprintf(str2,"%s", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }
    msg += QString::fromStdString(str2);
    return msg;
}
