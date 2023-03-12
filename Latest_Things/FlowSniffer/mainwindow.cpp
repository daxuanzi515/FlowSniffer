#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Start Page");
    this->setWindowState(Qt::WindowNoState);
    this->move(700,300);
    this->p = new FlowSnifferWindow();
    connect(ui->enter,&QPushButton::clicked,[=](){
        this->hide();
        this->p->show();
    });
    connect(this->p,&FlowSnifferWindow::back,[=](){
        this->p->hide();
        this->show();
    });

    connect(ui->log,&QPushButton::clicked,[=](){
        // open the log file and append the content of arp file to it.
        QString outfile = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/MYLOG.txt";
        QString infile = "/home/cxx/CXX_Programs/Work_Projects/Latest_Things/build-FlowSniffer-Desktop-Debug/Attack_MSG.txt";

        QFile logfile(outfile);
        QFile attackfile(infile);
        if(attackfile.open(QIODevice::ReadOnly) && logfile.open(QIODevice::Append))
        {
            QTextStream inStream(&attackfile);
            QTextStream outStream(&logfile);
            QString line = inStream.readLine();

            while(!line.isNull())
            {
                outStream << line << endl;
                line = inStream.readLine();
            }
            attackfile.close();
            logfile.close();
        }
        QDesktopServices::openUrl(QUrl::fromLocalFile(outfile));
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

