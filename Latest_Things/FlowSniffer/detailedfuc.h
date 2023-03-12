#ifndef DETAILEDFUC_H
#define DETAILEDFUC_H
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <QString>

#include <sys/types.h>
#include <ifaddrs.h>
#include <string.h>

#include <QtNetwork/QNetworkInterface>
#include <QList>
#include <QtNetwork/QHostInfo>
#include <QStringList>
#include <pcap/pcap.h>

#include "synflood.h"

class DetailedFuc
{
public:
    DetailedFuc();
    QString run_syn_flood(char* target_ip, char* target_port, int times); // syn flood run
    QString get_mac_address();
    QString get_main_device();
    QString get_device_msg();
    QString local_ip_address();
    QString device_ip_address();
    QList<QStringList> temp = {};
    std::string getCmdResult(const std::string &strCmd);
};

#endif // DETAILEDFUC_H
