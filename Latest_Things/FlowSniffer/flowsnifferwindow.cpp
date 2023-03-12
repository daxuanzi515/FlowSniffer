#include "flowsnifferwindow.h"
#include "ui_flowsnifferwindow.h"
#include <QDebug>

FlowSnifferWindow::FlowSnifferWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FlowSnifferWindow)
{
    ui->setupUi(this);
    this->move(470,100);
    this->setWindowTitle("Flow Siffer");
    connect(ui->backto,&QPushButton::clicked,[=](){
        emit this->back();
    });
    connect(ui->Default,&QPushButton::clicked,[=](){
        Try *test1 = new Try();
        test1->command("./Stop.sh");
        delete test1;
        ui->sniffer_data->setPlainText("Please Click the 'Stop'!");
    });
    connect(ui->Stop,&QPushButton::clicked,[=](){
        QString fileName = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/MYLOG.txt";
        QFile file(fileName);
        QString str,ans;
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream filestream(&file);
            while(filestream.atEnd()==false)
            {
                str = filestream.readLine();
                ans += '\n';
                ans += str;
            }
        }
        file.close();

        ui->sniffer_data->setPlainText(ans);

        QString filepath = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/GROSS.txt";
        QFile gross(filepath);
        QString line,total;
        if(gross.open(QIODevice::ReadOnly))
        {
            QTextStream filestream(&gross);
            while(filestream.atEnd()==false)
            {
                line = filestream.readLine();
                total += '\n';
                total += line;
            }
        }
        gross.close();
        ui->gross->setPlainText(total);
    });
    connect(ui->instructions,&QPushButton::clicked,[=](){
        QMessageBox::information(this, "Use Help", "usage: ./ipdump [-aedht] [-p protocols] [-i ifrname] [-f filters],protocols: arp ip icmp tcp udp,filters: ip <IP addr> port <PORT number>,default: ./ipdump -p arp ip icmp tcp udp",QMessageBox::Yes|QMessageBox::No);
    });
    connect(ui->Run,&QPushButton::clicked,[=](){
        QString checkchain = "# !/bin/bash\n./Test -p ";
        //Check State Flag /Main Rules
        if(ui->arp->isChecked()==true)
        {
            checkchain += "arp";
        }
        if(ui->ip->isChecked()==true)
        {
            checkchain += " ip";
        }
        if(ui->tcp->isChecked()==true)
        {
            checkchain += " tcp";
        }
        if(ui->udp->isChecked()==true)
        {
            checkchain += " udp";
        }
        if(ui->icmp->isChecked()==true)
        {
            checkchain += " icmp";
        }
        if(ui->all->isChecked()==true)
        {
            checkchain += " all";
        }
        if(ui->dump->isChecked()==true)
        {
            checkchain += " dump";
        }
        if(ui->ether->isChecked()==true)
        {
            checkchain += " ether";
        }
        qDebug()<<checkchain;
        QByteArray ba2;
        ba2.append(checkchain);     //or ? ba2 = s2.toLatin1();
        char *c2 = ba2.data();
        QString filename = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Run_multi.sh";
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream fileStream(&file);
            fileStream<<c2;
        }
        file.close();
        Try *test1 = new Try();
        test1->command("./Stop_multi.sh");
        delete test1;
        ui->sniffer_data->setPlainText("Please Click the 'Stop'!");
    });
    ui->ipnet->setText("");
    connect(ui->ping,&QPushButton::clicked,[=](){
        QString desip = ui->ipnet->toPlainText();
        qDebug()<<desip;
        QByteArray ba2;
        ba2.append("# !/bin/bash\n");
        ba2.append("./Ping "+desip);
        char *c2 = ba2.data();
        qDebug()<<c2;
        QString filename = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Run_Ping.sh";
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream fileStream(&file);
            fileStream<<c2;
        }
        file.close();
        Try *test1 = new Try();
        test1->command("./Stop_Ping.sh");
        delete test1;
        ui->PiNG->setPlainText("Please Click the 'Stop'!");
    });

    connect(ui->stop,&QPushButton::clicked,[=](){
        QString fileName = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/PING.txt";
        QFile file(fileName);
        QString str,ans;
        if(file.open(QIODevice::ReadOnly))
        {
            QTextStream filestream(&file);
            while(filestream.atEnd()==false)
            {
                str = filestream.readLine();
                ans += '\n';
                ans += str;
            }
        }
        file.close();

        ui->PiNG->setPlainText(ans);
    });

    connect(ui->Clear,&QPushButton::clicked,[=](){
        ui->sniffer_data->setPlainText("");
    });
    connect(ui->clear,&QPushButton::clicked,[=](){
        ui->gross->setPlainText("");
    });
    connect(ui->clean,&QPushButton::clicked,[=](){
        ui->PiNG->setPlainText("");
    });


    //ARP Part
    //get all devices' msg in the Ubuntu.
    ui->mentions->setText("IP Addresses and MAC Addresses are all randomly made by function.");
    ui->mentions->setWordWrap(true);

    connect(ui->get_device_msg, &QPushButton::clicked,[=]{
        DetailedFuc test;
        QString device_msg = test.get_device_msg();
        ui->devices->setPlainText(device_msg);

        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();
        total_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n")+ device_msg;
    });

    box = new QMessageBox();
    box->setWindowTitle("Notice");
    box->setText("Your Input is Null! Please input again!");
    box->addButton("Accept", QMessageBox::AcceptRole);

    // scanning all hosts
    // use nmap to get all hosts in 192.168.43.0/24 reply for ping
    connect(ui->get_host_msg, &QPushButton::clicked,[=]{
        std::string Cmd = "nmap -sP 192.168.43.0/24";
        DetailedFuc *get_hosts = new DetailedFuc();
        QString host_msg = QString::fromStdString(get_hosts->getCmdResult(Cmd));
        qDebug()<<"host_msg"<<host_msg;
        delete get_hosts;
        ui->hosts->setPlainText(host_msg);

        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();
        total_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n") + host_msg;
    });
    //default localhost ip and mac address
//    ui->fake_ip->setPlaceholderText("192.168.43.131");
//    ui->fake_mac->setPlaceholderText("00:02:29:BA:5A:E2");
    // set default gateway IP -> target network disconnect
    ui->fake_ip->setText("192.168.43.1");
    ui->fake_mac->setText("00:0c:29:ba:5a:e2");
    //default attacked object
    // Kali system's details
    ui->target_ip->setText("Use Get Hosts");
    ui->target_mac->setText("00:0c:29:ea:4c:11");
    //default sending times
    ui->times->setPlaceholderText("1");

    connect(ui->arp_request,&QPushButton::clicked,[=]{
        if(ui->target_ip->text()==""||ui->target_mac->text()=="")
        {
            box->exec();
        }
        // you have to change the type to fill the parameters in the function
        QString i_fake_ip, i_fake_mac, i_target_ip, i_target_mac;
        i_fake_ip = ui->fake_ip->text();
        i_fake_mac = ui->fake_mac->text();
        i_target_ip = ui->target_ip->text();
        i_target_mac = ui->target_mac->text();
        QByteArray t_fake_ip = i_fake_ip.toLatin1();
        QByteArray t_fake_mac = i_fake_mac.toLatin1();
        QByteArray t_target_ip = i_target_ip.toLatin1();
        QByteArray t_target_mac = i_target_mac.toLatin1();
        char* fake_ip = t_fake_ip.data();
        char* fake_mac = t_fake_mac.data();
        char* target_ip = t_target_ip.data();
        char* target_mac = t_target_mac.data();
        int times = ui->times->text().toInt();
        arp_info ARP;
        char errbuf[PCAP_ERRBUF_SIZE];
        pcap_t *handle = pcap_open_live("ens33",65536,1,1000,errbuf);
        ARPPACKET ARPPacket_B = ARP.make_arp_packet(fake_ip, fake_mac, target_ip, target_mac,1);
        if(times == 1)
        {
            ARP.sendArpPacket(handle, ARPPacket_B);
            pcap_close(handle);
        }
        else
        {
            for(int i=0;i<times;i++)
            {
                ARP.sendArpPacket(handle, ARPPacket_B);
                sleep(1);
            }
            pcap_close(handle);
            ARP.arp_msg += "------Sending end.------\n";
        }
        ui->arpwin->append(ARP.arp_msg);

        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();
        total_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n") + ARP.arp_msg;

        // Write into our Attack_MSG.txt as a log
        QString filepath = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Attack_MSG.txt";
        QFile arp_file(filepath);
        // close Attack_MSG.txt cover the past file!
        if(arp_file.open(QIODevice::Append))
        {
            QTextStream filestream(&arp_file);
            filestream<<"--------Arp Message Log--------\n"+total_msg << endl;
        }
        arp_file.close();
    });

    connect(ui->arp_attack,&QPushButton::clicked,[=]{
        if(ui->target_ip->text()==""||ui->target_mac->text()=="")
        {
            box->exec();
        }
        else
        {
            arp_info ARP;
            char errbuf[PCAP_ERRBUF_SIZE];
            pcap_t *handle = pcap_open_live("ens33", 65536, 1, 1000, errbuf);
            int times = ui->times->text().toInt();
            //char* i_srcIP, char* i_desIP, char* i_srcMac, char* i_desMac, int i_opcode
            //a default example for real host
            // you have to change the type to fill the parameters in the function
            QString i_fake_ip, i_fake_mac, i_target_ip, i_target_mac;
            i_fake_ip = ui->fake_ip->text();
            i_fake_mac = ui->fake_mac->text();
            i_target_ip = ui->target_ip->text();
            i_target_mac = ui->target_mac->text();
            QByteArray t_fake_ip = i_fake_ip.toLatin1();
            QByteArray t_fake_mac = i_fake_mac.toLatin1();
            QByteArray t_target_ip = i_target_ip.toLatin1();
            QByteArray t_target_mac = i_target_mac.toLatin1();
            char* fake_ip = t_fake_ip.data();
            char* fake_mac = t_fake_mac.data();
            char* target_ip = t_target_ip.data();
            char* target_mac = t_target_mac.data();
            //pay attention to your code transformation
            for(int i=0;i<times;i++)
            {
                    ARPPACKET ARPPacket_A = ARP.make_arp_packet(fake_ip, fake_mac , target_ip, target_mac, 2);
                    ARP.sendArpPacket(handle, ARPPacket_A);
                    sleep(1);
            }
            pcap_close(handle);
            ARP.arp_msg += "------Sending end.------\n";
            ui->arpwin->append(ARP.arp_msg);
    //        qDebug()<<"table_data"<<ARP.arp_table;
            arp_table.append(ARP.arp_table);
    //        qDebug()<<"total_table_data"<<arp_table;
            QDateTime dateTime;
            dateTime = QDateTime::currentDateTime();
            total_msg += dateTime.toString("yyyy-MM-dd hh:mm:ss\n") + ARP.arp_msg;
            // Write into our Attack_MSG.txt as a log
            QString filepath = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Attack_MSG.txt";
            QFile arp_file(filepath);
            // close Attack_MSG.txt cover the past file!
            if(arp_file.open(QIODevice::WriteOnly))
            {
                QTextStream filestream(&arp_file);
                filestream<<"--------Arp Message Log--------\n"+total_msg << endl;
            }
            arp_file.close();
        }
    });

    connect(ui->Clear_arp,&QPushButton::clicked,[=]{
        ui->devices->setPlainText("");
        ui->arpwin->setPlainText("");
        ui->hosts->setPlainText("");
    });


    //Random Ip address to Arp Spoof
    connect(ui->M_arp_attack,&QPushButton::clicked,[=]{
        QString i_target_ip, i_target_mac;
        i_target_ip = ui->M_target_ip->text();
        i_target_mac = ui->M_target_mac->text();
        if(!i_target_ip.isEmpty()&&!i_target_mac.isEmpty())
        {
            QByteArray t_target_ip = i_target_ip.toLatin1();
            QByteArray t_target_mac = i_target_mac.toLatin1();
            char* target_ip = t_target_ip.data();
            char* target_mac = t_target_mac.data();
            int times = ui->M_times->text().toInt();
            // device configures
            char errbuf[PCAP_ERRBUF_SIZE];
            pcap_t *handle = pcap_open_live("ens33", 65536, 1, 1000, errbuf);
            arp_info ARP;
            for(int i=0;i<times;i++)
            {
                // random generator for ip and mac
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                int r = qrand()%100+1;
                arp_info Rand_data;
                // start to generate random number
                std::string ip = Rand_data.Random_IP(r);
                char* fake_ip = (char*)ip.data();
                char* fake_mac = Rand_data.Random_MAC(r);
                ARPPACKET ARP_Spoof = ARP.make_arp_packet(fake_ip, fake_mac , target_ip, target_mac, 2);
                ARP.sendArpPacket(handle, ARP_Spoof);
                sleep(1);
            }
            pcap_close(handle);
            ARP.arp_msg += "------Sending end.------\n";
            ui->MITM_msg->setPlainText(ARP.arp_msg);
            total_msg += ARP.arp_msg;
            // Write into our Attack_MSG.txt as a log
            QString filepath = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Attack_MSG.txt";
            QFile arp_file(filepath);
            // close Attack_MSG.txt cover the past file!
            if(arp_file.open(QIODevice::Append))
            {
                QTextStream filestream(&arp_file);
                filestream<<"--------Arp Message Log--------\n"+total_msg << endl;
            }
            arp_file.close();
//            qDebug()<<total_msg;
//            qDebug()<<"table_data"<<ARP.arp_table;
            arp_table.append(ARP.arp_table);
//            qDebug()<<"total_table_data"<<arp_table;
        }
        else
        {
            box->exec();
        }
    });

    ui->random_show->setPlainText("This is only a transient show template.\nRandom IP and MAC will be used for ArpSpoof.\n");
    connect(ui->Random_generate,&QPushButton::clicked,[=]{
        // random number generate by time
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        int r = qrand()%100+1;
        arp_info Rand_data;
        // start to generate random number
        std::string ip = Rand_data.Random_IP(r);
        char* mac = Rand_data.Random_MAC(r);
        ui->random_show->append("Fake IP:" + QString::fromStdString(ip));
        ui->random_show->append("Fake Mac:" + QString(mac));
    });
    connect(ui->M_arp_clear,&QPushButton::clicked,[=]{
        ui->MITM_msg->setPlainText("");
    });

    //SynFlood Attack
    connect(ui->syn_attack,&QPushButton::clicked,[=]{
        DetailedFuc test;
        QString i_target_ip, i_target_port, i_times;
        i_target_ip = ui->syn_target_ip->text();
        i_target_port = ui->syn_target_port->text();
        i_times = ui->syn_times->text();
        int attack_time = i_times.toInt();
        QByteArray t_target_ip = i_target_ip.toLatin1();
        QByteArray t_target_port = i_target_port.toLatin1();
        char* target_ip = t_target_ip.data();
        char* target_port = t_target_port.data();
//        QString syn_msg = test.run_syn_flood("192.168.43.135","80",4);//a example
        QString syn_msg = test.run_syn_flood(target_ip, target_port, attack_time);
        // Write into our Attack_MSG.txt as a log
        QString filepath = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Attack_MSG.txt";
        QFile syn_file(filepath);
        // close Attack_MSG.txt cover the past file!
        if(syn_file.open(QIODevice::Append))
        {
            QTextStream filestream(&syn_file);
            filestream<<"--------Syn Message Log--------\n"+syn_msg << endl;
        }
        syn_file.close();

        ui->syn_msg->setPlainText(syn_msg);
        syn_table.append(test.temp);
    });
    connect(ui->syn_clear,&QPushButton::clicked,[=]{
        ui->syn_msg->setPlainText("");
    });

    //QTable to output the data for arp attack
       ui->tableWidget->setColumnCount(6);
       ui->tableWidget->setFocusPolicy(Qt::NoFocus);
       QStringList headerText = {"srcIP","desIP","srcMac","desMac","Length","Attack Type"};
       ui->tableWidget->setHorizontalHeaderLabels(headerText);
       ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  // one row
       ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // set disable for editting
       ui->tableWidget->setStyleSheet("selection-background-color:rgb(208, 163, 246);"); //set selected color
       ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);// center align
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
       ui->tableWidget->setColumnWidth(3, 150);
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
       ui->tableWidget->setColumnWidth(2, 150);
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
       ui->tableWidget->setColumnWidth(0, 145);
       ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
       ui->tableWidget->setColumnWidth(1, 145);
       QTableWidgetItem *item = new QTableWidgetItem("item");
       //get font you can write item->font("?") ? is the style.
       QFont font = item->font();
       //bold
       font.setBold(true);
       //size
       font.setPointSize(10);
       //color
       item->setTextColor("rgb(255, 255, 255)");
       //set font
       item->setFont(font);

       connect(ui->show_details,&QPushButton::clicked,[=]{
           //show table details QList<QList{QStringList{QString}}>
           // QStringList format:{{srcIP,desIp,srcMac,desMac,Length,AttackType},{}} one unit
           // arp_table

           if(!arp_table.isEmpty())
           {
               int rowCount = arp_table.size(); // get data rows
               for(int i=0;i<rowCount;i++)
               {
                   QList<QStringList> innerList = arp_table[i]; // get QStringList
                   for(int j=0; j<innerList.size();j++)
                   {
                       // insert a new row
                       int row = ui->tableWidget->rowCount();
                       ui->tableWidget->insertRow(row);
                       QStringList temp = innerList[j];
//                       qDebug()<<"temp"<<temp;
                       for(int k=0; k< temp.size(); k++)
                       {
                           QTableWidgetItem *item = new QTableWidgetItem(temp[k]); // create a item
                           ui->tableWidget->setItem(row, k, item); // add item into the table
                       }
                   }
               }
           }
           if(!syn_table.isEmpty())
           {
               //syn_table
               int syn_row = syn_table.size(); // get rows
               for(int i=0;i<syn_row;i++)
               {
                   QList<QStringList> innerList = syn_table[i]; // get QStringList
    //               qDebug()<<"arp_table[i]"<<arp_table[i];
                   for(int j=0; j<innerList.size();j++)
                   {
                       // insert a new row
                       int row = ui->syn_table->rowCount();
                       ui->syn_table->insertRow(row);
                       QStringList temp = innerList[j];
    //                   qDebug()<<"temp"<<temp;
                       for(int k=0; k< temp.size(); k++)
                       {
                           QTableWidgetItem *item = new QTableWidgetItem(temp[k]); // create a new item
                           ui->syn_table->setItem(row, k, item); // add item into the table
                       }
                   }
               }
           }
       });
        // multi row
       connect(ui->table_clear,&QPushButton::clicked,[=]{
           QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
           QSet<int> rows;
           foreach(QTableWidgetItem *item, items)
           {
               rows.insert(item->row());
           }
           // from the last raw to delete it.
           foreach(int row, rows)
           {
               ui->tableWidget->removeRow(row);
           }

           QList<QTableWidgetItem*> syn_items = ui->syn_table->selectedItems();
           QSet<int> syn_rows;
           foreach(QTableWidgetItem *item, syn_items)
           {
               syn_rows.insert(item->row());
           }
           // from the last raw to delete it.
           foreach(int row, syn_rows)
           {
               ui->syn_table->removeRow(row);
           }
       });

        //all clear
       connect(ui->all_clear,&QPushButton::clicked,[=]{
           int rowCount = ui->tableWidget->rowCount();
           for (int i = rowCount - 1; i >= 0; i--) {
               ui->tableWidget->removeRow(i);
           }
           int syn_row= ui->syn_table->rowCount();
           for (int i = syn_row - 1; i >= 0; i--) {
               ui->syn_table->removeRow(i);
           }
       });

       // syn table data config
       ui->syn_table->setColumnCount(6);
       ui->syn_table->setFocusPolicy(Qt::NoFocus);
       QStringList syn_header = {"srcIP","desIP","srcPort","desPort","Length","Attack Type"};
       ui->syn_table->setHorizontalHeaderLabels(syn_header);
       ui->syn_table->setSelectionBehavior(QAbstractItemView::SelectRows);
       ui->syn_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
       ui->syn_table->setStyleSheet("selection-background-color:rgb(208, 163, 246);");
       ui->syn_table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);// center align
       ui->syn_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       ui->syn_table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
       ui->syn_table->setColumnWidth(3, 150);
       ui->syn_table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
       ui->syn_table->setColumnWidth(2, 150);
       ui->syn_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
       ui->syn_table->setColumnWidth(0, 145);
       ui->syn_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
       ui->syn_table->setColumnWidth(1, 145);
       QTableWidgetItem *syn_item = new QTableWidgetItem("item");
       QFont syn_font = syn_item->font();
       syn_font.setBold(true);
       syn_font .setPointSize(10);
       syn_item->setTextColor("rgb(255, 255, 255)");
       syn_item->setFont(syn_font);

}

FlowSnifferWindow::~FlowSnifferWindow()
{
    delete ui;
}
