#ifndef FLOWSNIFFERWINDOW_H
#define FLOWSNIFFERWINDOW_H
#include <unistd.h>
#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include "try.h"
#include "detailedfuc.h"
#include "arp_info.h"
#include "synflood.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <QList>
namespace Ui {
class FlowSnifferWindow;
}

class FlowSnifferWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlowSnifferWindow(QWidget *parent = nullptr);
    ~FlowSnifferWindow();
    QMessageBox *box = nullptr;

    QString total_msg = "";
    QList<QList<QStringList>> arp_table ={};
    QList<QList<QStringList>> syn_table ={};
signals:
    void back();
private:
    Ui::FlowSnifferWindow *ui;
};

#endif // FLOWSNIFFERWINDOW_H
