/********************************************************************************
** Form generated from reading UI file 'flowsnifferwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWSNIFFERWINDOW_H
#define UI_FLOWSNIFFERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlowSnifferWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QFrame *frame;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QPushButton *Default;
    QPushButton *Run;
    QPushButton *Clear;
    QPushButton *Stop;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *arp;
    QCheckBox *ip;
    QCheckBox *tcp;
    QCheckBox *udp;
    QCheckBox *icmp;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *ether;
    QCheckBox *all;
    QCheckBox *dump;
    QTextBrowser *sniffer_data;
    QWidget *tab_2;
    QTextBrowser *gross;
    QPushButton *clear;
    QWidget *tab_3;
    QTextBrowser *PiNG;
    QPushButton *ping;
    QPushButton *stop;
    QTextEdit *ipnet;
    QPushButton *clean;
    QWidget *tab_4;
    QWidget *layoutWidget_9;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_48;
    QTextBrowser *devices;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_41;
    QTextBrowser *hosts;
    QTextBrowser *arpwin;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *verticalLayout_13;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_42;
    QLineEdit *target_ip;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_43;
    QLineEdit *target_mac;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_44;
    QLineEdit *fake_ip;
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_45;
    QLineEdit *fake_mac;
    QLineEdit *times;
    QPushButton *arp_attack;
    QPushButton *arp_request;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_34;
    QPushButton *get_host_msg;
    QPushButton *Clear_arp;
    QPushButton *get_device_msg;
    QWidget *tab_5;
    QTextBrowser *MITM_msg;
    QLabel *mentions;
    QPushButton *Random_generate;
    QTextBrowser *random_show;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_46;
    QLineEdit *M_target_ip;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_47;
    QLineEdit *M_target_mac;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *M_times;
    QPushButton *M_arp_attack;
    QPushButton *M_arp_clear;
    QWidget *tab_6;
    QTextBrowser *syn_msg;
    QWidget *layoutWidget6;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_49;
    QLineEdit *syn_target_ip;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_50;
    QLineEdit *syn_target_port;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_52;
    QLineEdit *syn_times;
    QPushButton *syn_attack;
    QPushButton *syn_clear;
    QWidget *tab_7;
    QTableWidget *tableWidget;
    QPushButton *show_details;
    QTableWidget *syn_table;
    QPushButton *table_clear;
    QPushButton *all_clear;
    QLabel *label;
    QPushButton *backto;
    QPushButton *instructions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FlowSnifferWindow)
    {
        if (FlowSnifferWindow->objectName().isEmpty())
            FlowSnifferWindow->setObjectName(QString::fromUtf8("FlowSnifferWindow"));
        FlowSnifferWindow->resize(863, 600);
        FlowSnifferWindow->setStyleSheet(QString::fromUtf8("color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));
        centralwidget = new QWidget(FlowSnifferWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 861, 541));
        tabWidget->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 10, 231, 481));
        frame->setStyleSheet(QString::fromUtf8("background:rgb(69, 64, 93);\n"
"font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 10, 91, 17));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 200, 101, 17));
        layoutWidget = new QWidget(frame);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 330, 104, 140));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        Default = new QPushButton(layoutWidget);
        Default->setObjectName(QString::fromUtf8("Default"));
        Default->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout_3->addWidget(Default);

        Run = new QPushButton(layoutWidget);
        Run->setObjectName(QString::fromUtf8("Run"));
        Run->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout_3->addWidget(Run);

        Clear = new QPushButton(layoutWidget);
        Clear->setObjectName(QString::fromUtf8("Clear"));
        Clear->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout_3->addWidget(Clear);

        Stop = new QPushButton(layoutWidget);
        Stop->setObjectName(QString::fromUtf8("Stop"));
        Stop->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));

        verticalLayout_3->addWidget(Stop);

        layoutWidget1 = new QWidget(frame);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 30, 91, 166));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        arp = new QCheckBox(layoutWidget1);
        arp->setObjectName(QString::fromUtf8("arp"));
        arp->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(arp);

        ip = new QCheckBox(layoutWidget1);
        ip->setObjectName(QString::fromUtf8("ip"));
        ip->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ip);

        tcp = new QCheckBox(layoutWidget1);
        tcp->setObjectName(QString::fromUtf8("tcp"));
        tcp->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(tcp);

        udp = new QCheckBox(layoutWidget1);
        udp->setObjectName(QString::fromUtf8("udp"));
        udp->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(udp);

        icmp = new QCheckBox(layoutWidget1);
        icmp->setObjectName(QString::fromUtf8("icmp"));
        icmp->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(icmp);

        layoutWidget2 = new QWidget(frame);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(80, 230, 86, 98));
        verticalLayout_2 = new QVBoxLayout(layoutWidget2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ether = new QCheckBox(layoutWidget2);
        ether->setObjectName(QString::fromUtf8("ether"));
        ether->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(ether);

        all = new QCheckBox(layoutWidget2);
        all->setObjectName(QString::fromUtf8("all"));
        all->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(all);

        dump = new QCheckBox(layoutWidget2);
        dump->setObjectName(QString::fromUtf8("dump"));
        dump->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(dump);

        sniffer_data = new QTextBrowser(tab);
        sniffer_data->setObjectName(QString::fromUtf8("sniffer_data"));
        sniffer_data->setGeometry(QRect(250, 10, 591, 481));
        sniffer_data->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
""));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gross = new QTextBrowser(tab_2);
        gross->setObjectName(QString::fromUtf8("gross"));
        gross->setGeometry(QRect(30, 20, 611, 441));
        gross->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
""));
        clear = new QPushButton(tab_2);
        clear->setObjectName(QString::fromUtf8("clear"));
        clear->setGeometry(QRect(710, 210, 91, 31));
        clear->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        PiNG = new QTextBrowser(tab_3);
        PiNG->setObjectName(QString::fromUtf8("PiNG"));
        PiNG->setGeometry(QRect(40, 20, 631, 441));
        PiNG->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);"));
        ping = new QPushButton(tab_3);
        ping->setObjectName(QString::fromUtf8("ping"));
        ping->setGeometry(QRect(720, 160, 101, 31));
        ping->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        stop = new QPushButton(tab_3);
        stop->setObjectName(QString::fromUtf8("stop"));
        stop->setGeometry(QRect(720, 250, 101, 31));
        stop->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        ipnet = new QTextEdit(tab_3);
        ipnet->setObjectName(QString::fromUtf8("ipnet"));
        ipnet->setGeometry(QRect(690, 80, 151, 70));
        ipnet->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));
        clean = new QPushButton(tab_3);
        clean->setObjectName(QString::fromUtf8("clean"));
        clean->setGeometry(QRect(720, 330, 101, 31));
        clean->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        layoutWidget_9 = new QWidget(tab_4);
        layoutWidget_9->setObjectName(QString::fromUtf8("layoutWidget_9"));
        layoutWidget_9->setGeometry(QRect(440, 10, 401, 181));
        horizontalLayout_44 = new QHBoxLayout(layoutWidget_9);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        horizontalLayout_44->setContentsMargins(0, 0, 0, 0);
        label_48 = new QLabel(layoutWidget_9);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setStyleSheet(QString::fromUtf8("background:rgb(69, 64, 93);\n"
"font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253)"));

        horizontalLayout_44->addWidget(label_48);

        devices = new QTextBrowser(layoutWidget_9);
        devices->setObjectName(QString::fromUtf8("devices"));
        devices->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);"));

        horizontalLayout_44->addWidget(devices);

        layoutWidget_5 = new QWidget(tab_4);
        layoutWidget_5->setObjectName(QString::fromUtf8("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 10, 401, 181));
        horizontalLayout_37 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalLayout_37->setContentsMargins(0, 0, 0, 0);
        label_41 = new QLabel(layoutWidget_5);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setStyleSheet(QString::fromUtf8("background:rgb(69, 64, 93);\n"
"font: 63 12pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253)"));

        horizontalLayout_37->addWidget(label_41);

        hosts = new QTextBrowser(layoutWidget_5);
        hosts->setObjectName(QString::fromUtf8("hosts"));
        hosts->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);"));

        horizontalLayout_37->addWidget(hosts);

        arpwin = new QTextBrowser(tab_4);
        arpwin->setObjectName(QString::fromUtf8("arpwin"));
        arpwin->setGeometry(QRect(340, 240, 491, 251));
        arpwin->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
""));
        layoutWidget3 = new QWidget(tab_4);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 230, 311, 261));
        verticalLayout_17 = new QVBoxLayout(layoutWidget3);
        verticalLayout_17->setSpacing(3);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        label_42 = new QLabel(layoutWidget3);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        horizontalLayout_38->addWidget(label_42);

        target_ip = new QLineEdit(layoutWidget3);
        target_ip->setObjectName(QString::fromUtf8("target_ip"));
        target_ip->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_38->addWidget(target_ip);


        verticalLayout_14->addLayout(horizontalLayout_38);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        label_43 = new QLabel(layoutWidget3);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        horizontalLayout_39->addWidget(label_43);

        target_mac = new QLineEdit(layoutWidget3);
        target_mac->setObjectName(QString::fromUtf8("target_mac"));
        target_mac->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_39->addWidget(target_mac);


        verticalLayout_14->addLayout(horizontalLayout_39);


        verticalLayout_13->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        label_44 = new QLabel(layoutWidget3);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        horizontalLayout_40->addWidget(label_44);

        fake_ip = new QLineEdit(layoutWidget3);
        fake_ip->setObjectName(QString::fromUtf8("fake_ip"));
        fake_ip->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_40->addWidget(fake_ip);


        verticalLayout_15->addLayout(horizontalLayout_40);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        label_45 = new QLabel(layoutWidget3);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        horizontalLayout_41->addWidget(label_45);

        fake_mac = new QLineEdit(layoutWidget3);
        fake_mac->setObjectName(QString::fromUtf8("fake_mac"));
        fake_mac->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_41->addWidget(fake_mac);


        verticalLayout_15->addLayout(horizontalLayout_41);


        verticalLayout_13->addLayout(verticalLayout_15);


        verticalLayout_17->addLayout(verticalLayout_13);

        times = new QLineEdit(layoutWidget3);
        times->setObjectName(QString::fromUtf8("times"));
        times->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        verticalLayout_17->addWidget(times);

        arp_attack = new QPushButton(layoutWidget3);
        arp_attack->setObjectName(QString::fromUtf8("arp_attack"));

        verticalLayout_17->addWidget(arp_attack);

        arp_request = new QPushButton(layoutWidget3);
        arp_request->setObjectName(QString::fromUtf8("arp_request"));

        verticalLayout_17->addWidget(arp_request);

        layoutWidget4 = new QWidget(tab_4);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(160, 200, 541, 32));
        horizontalLayout_34 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_34->setSpacing(70);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(0, 0, 0, 0);
        get_host_msg = new QPushButton(layoutWidget4);
        get_host_msg->setObjectName(QString::fromUtf8("get_host_msg"));

        horizontalLayout_34->addWidget(get_host_msg);

        Clear_arp = new QPushButton(layoutWidget4);
        Clear_arp->setObjectName(QString::fromUtf8("Clear_arp"));

        horizontalLayout_34->addWidget(Clear_arp);

        get_device_msg = new QPushButton(layoutWidget4);
        get_device_msg->setObjectName(QString::fromUtf8("get_device_msg"));

        horizontalLayout_34->addWidget(get_device_msg);

        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        MITM_msg = new QTextBrowser(tab_5);
        MITM_msg->setObjectName(QString::fromUtf8("MITM_msg"));
        MITM_msg->setGeometry(QRect(350, 10, 491, 481));
        MITM_msg->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));
        mentions = new QLabel(tab_5);
        mentions->setObjectName(QString::fromUtf8("mentions"));
        mentions->setGeometry(QRect(20, 40, 301, 61));
        Random_generate = new QPushButton(tab_5);
        Random_generate->setObjectName(QString::fromUtf8("Random_generate"));
        Random_generate->setGeometry(QRect(70, 460, 201, 31));
        random_show = new QTextBrowser(tab_5);
        random_show->setObjectName(QString::fromUtf8("random_show"));
        random_show->setGeometry(QRect(20, 320, 311, 131));
        random_show->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));
        layoutWidget5 = new QWidget(tab_5);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(20, 140, 311, 170));
        verticalLayout_4 = new QVBoxLayout(layoutWidget5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_46 = new QLabel(layoutWidget5);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        horizontalLayout->addWidget(label_46);

        M_target_ip = new QLineEdit(layoutWidget5);
        M_target_ip->setObjectName(QString::fromUtf8("M_target_ip"));
        M_target_ip->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout->addWidget(M_target_ip);


        verticalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_47 = new QLabel(layoutWidget5);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        horizontalLayout_2->addWidget(label_47);

        M_target_mac = new QLineEdit(layoutWidget5);
        M_target_mac->setObjectName(QString::fromUtf8("M_target_mac"));
        M_target_mac->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_2->addWidget(M_target_mac);


        verticalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(layoutWidget5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        M_times = new QLineEdit(layoutWidget5);
        M_times->setObjectName(QString::fromUtf8("M_times"));
        M_times->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_3->addWidget(M_times);


        verticalLayout_4->addLayout(horizontalLayout_3);

        M_arp_attack = new QPushButton(layoutWidget5);
        M_arp_attack->setObjectName(QString::fromUtf8("M_arp_attack"));

        verticalLayout_4->addWidget(M_arp_attack);

        M_arp_clear = new QPushButton(layoutWidget5);
        M_arp_clear->setObjectName(QString::fromUtf8("M_arp_clear"));

        verticalLayout_4->addWidget(M_arp_clear);

        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        syn_msg = new QTextBrowser(tab_6);
        syn_msg->setObjectName(QString::fromUtf8("syn_msg"));
        syn_msg->setGeometry(QRect(280, 20, 561, 481));
        syn_msg->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
""));
        layoutWidget6 = new QWidget(tab_6);
        layoutWidget6->setObjectName(QString::fromUtf8("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(10, 140, 258, 170));
        verticalLayout_5 = new QVBoxLayout(layoutWidget6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_49 = new QLabel(layoutWidget6);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        horizontalLayout_4->addWidget(label_49);

        syn_target_ip = new QLineEdit(layoutWidget6);
        syn_target_ip->setObjectName(QString::fromUtf8("syn_target_ip"));
        syn_target_ip->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_4->addWidget(syn_target_ip);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_50 = new QLabel(layoutWidget6);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        horizontalLayout_5->addWidget(label_50);

        syn_target_port = new QLineEdit(layoutWidget6);
        syn_target_port->setObjectName(QString::fromUtf8("syn_target_port"));
        syn_target_port->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_5->addWidget(syn_target_port);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_52 = new QLabel(layoutWidget6);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        horizontalLayout_7->addWidget(label_52);

        syn_times = new QLineEdit(layoutWidget6);
        syn_times->setObjectName(QString::fromUtf8("syn_times"));
        syn_times->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);\n"
"font: 63 12pt \"URW Bookman\";"));

        horizontalLayout_7->addWidget(syn_times);


        verticalLayout_5->addLayout(horizontalLayout_7);

        syn_attack = new QPushButton(layoutWidget6);
        syn_attack->setObjectName(QString::fromUtf8("syn_attack"));

        verticalLayout_5->addWidget(syn_attack);

        syn_clear = new QPushButton(layoutWidget6);
        syn_clear->setObjectName(QString::fromUtf8("syn_clear"));

        verticalLayout_5->addWidget(syn_clear);

        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        tableWidget = new QTableWidget(tab_7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 841, 221));
        tableWidget->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);"));
        show_details = new QPushButton(tab_7);
        show_details->setObjectName(QString::fromUtf8("show_details"));
        show_details->setGeometry(QRect(710, 470, 111, 31));
        show_details->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        syn_table = new QTableWidget(tab_7);
        syn_table->setObjectName(QString::fromUtf8("syn_table"));
        syn_table->setGeometry(QRect(10, 240, 841, 221));
        syn_table->setStyleSheet(QString::fromUtf8("border:1px solid rgb(166, 142, 253);"));
        table_clear = new QPushButton(tab_7);
        table_clear->setObjectName(QString::fromUtf8("table_clear"));
        table_clear->setGeometry(QRect(570, 470, 111, 31));
        table_clear->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        all_clear = new QPushButton(tab_7);
        all_clear->setObjectName(QString::fromUtf8("all_clear"));
        all_clear->setGeometry(QRect(430, 470, 111, 31));
        all_clear->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        tabWidget->addTab(tab_7, QString());
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(620, 540, 231, 31));
        label->setStyleSheet(QString::fromUtf8("font: 63 15pt \"URW Bookman\";\n"
"color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49)"));
        backto = new QPushButton(centralwidget);
        backto->setObjectName(QString::fromUtf8("backto"));
        backto->setGeometry(QRect(20, 540, 81, 31));
        backto->setStyleSheet(QString::fromUtf8("color:rgb(166, 142, 253);\n"
"background:rgb(36, 31, 49);\n"
"font: 63 12pt \"URW Bookman\";"));
        instructions = new QPushButton(centralwidget);
        instructions->setObjectName(QString::fromUtf8("instructions"));
        instructions->setGeometry(QRect(130, 540, 111, 31));
        instructions->setStyleSheet(QString::fromUtf8("font: 63 12pt \"URW Bookman\";"));
        FlowSnifferWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FlowSnifferWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FlowSnifferWindow->setStatusBar(statusbar);

        retranslateUi(FlowSnifferWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FlowSnifferWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FlowSnifferWindow)
    {
        FlowSnifferWindow->setWindowTitle(QApplication::translate("FlowSnifferWindow", "MainWindow", nullptr));
        label_2->setText(QApplication::translate("FlowSnifferWindow", "Filter Rules", nullptr));
        label_3->setText(QApplication::translate("FlowSnifferWindow", "Other Rules", nullptr));
        Default->setText(QApplication::translate("FlowSnifferWindow", "DEFAULT", nullptr));
        Run->setText(QApplication::translate("FlowSnifferWindow", "RUN", nullptr));
        Clear->setText(QApplication::translate("FlowSnifferWindow", "CLEAR", nullptr));
        Stop->setText(QApplication::translate("FlowSnifferWindow", "STOP", nullptr));
        arp->setText(QApplication::translate("FlowSnifferWindow", "ARP", nullptr));
        ip->setText(QApplication::translate("FlowSnifferWindow", "IP", nullptr));
        tcp->setText(QApplication::translate("FlowSnifferWindow", "TCP", nullptr));
        udp->setText(QApplication::translate("FlowSnifferWindow", "UDP", nullptr));
        icmp->setText(QApplication::translate("FlowSnifferWindow", "ICMP", nullptr));
        ether->setText(QApplication::translate("FlowSnifferWindow", "ETHER", nullptr));
        all->setText(QApplication::translate("FlowSnifferWindow", "ALL", nullptr));
        dump->setText(QApplication::translate("FlowSnifferWindow", "DUMP", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("FlowSnifferWindow", "Start Sniffing", nullptr));
        clear->setText(QApplication::translate("FlowSnifferWindow", "CLEAR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("FlowSnifferWindow", "Gross Statistic", nullptr));
        ping->setText(QApplication::translate("FlowSnifferWindow", "PING", nullptr));
        stop->setText(QApplication::translate("FlowSnifferWindow", "STOP", nullptr));
        clean->setText(QApplication::translate("FlowSnifferWindow", "CLEAR", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("FlowSnifferWindow", "Send Packages", nullptr));
        label_48->setText(QApplication::translate("FlowSnifferWindow", "Devices", nullptr));
        label_41->setText(QApplication::translate("FlowSnifferWindow", "Hosts", nullptr));
        label_42->setText(QApplication::translate("FlowSnifferWindow", "Target IP", nullptr));
        label_43->setText(QApplication::translate("FlowSnifferWindow", "Target Mac", nullptr));
        label_44->setText(QApplication::translate("FlowSnifferWindow", "Fake IP", nullptr));
        label_45->setText(QApplication::translate("FlowSnifferWindow", "Fake Mac", nullptr));
        times->setText(QApplication::translate("FlowSnifferWindow", "Please Input Times of Sending", nullptr));
        arp_attack->setText(QApplication::translate("FlowSnifferWindow", "ARP Attack", nullptr));
        arp_request->setText(QApplication::translate("FlowSnifferWindow", "ARP Request", nullptr));
        get_host_msg->setText(QApplication::translate("FlowSnifferWindow", "Get Hosts", nullptr));
        Clear_arp->setText(QApplication::translate("FlowSnifferWindow", "Clear", nullptr));
        get_device_msg->setText(QApplication::translate("FlowSnifferWindow", "Get Devices", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("FlowSnifferWindow", "ARP Attack", nullptr));
        mentions->setText(QString());
        Random_generate->setText(QApplication::translate("FlowSnifferWindow", "Random IP&& Mac", nullptr));
        label_46->setText(QApplication::translate("FlowSnifferWindow", "Target IP", nullptr));
        label_47->setText(QApplication::translate("FlowSnifferWindow", "Target Mac", nullptr));
        label_4->setText(QApplication::translate("FlowSnifferWindow", "Attack Times", nullptr));
        M_times->setText(QString());
        M_arp_attack->setText(QApplication::translate("FlowSnifferWindow", "ARP Attack", nullptr));
        M_arp_clear->setText(QApplication::translate("FlowSnifferWindow", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("FlowSnifferWindow", "ARP Spoof", nullptr));
        label_49->setText(QApplication::translate("FlowSnifferWindow", "Target IP", nullptr));
        label_50->setText(QApplication::translate("FlowSnifferWindow", "Target Port", nullptr));
        label_52->setText(QApplication::translate("FlowSnifferWindow", "Times", nullptr));
        syn_attack->setText(QApplication::translate("FlowSnifferWindow", "SYN Attack", nullptr));
        syn_clear->setText(QApplication::translate("FlowSnifferWindow", "Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("FlowSnifferWindow", "SYN Flood", nullptr));
        show_details->setText(QApplication::translate("FlowSnifferWindow", "Show Details", nullptr));
        table_clear->setText(QApplication::translate("FlowSnifferWindow", "Clear", nullptr));
        all_clear->setText(QApplication::translate("FlowSnifferWindow", "All Clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("FlowSnifferWindow", "Data Table", nullptr));
        label->setText(QApplication::translate("FlowSnifferWindow", "Chen Xuanxin's Work", nullptr));
        backto->setText(QApplication::translate("FlowSnifferWindow", "BackTo", nullptr));
        instructions->setText(QApplication::translate("FlowSnifferWindow", "Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlowSnifferWindow: public Ui_FlowSnifferWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWSNIFFERWINDOW_H
