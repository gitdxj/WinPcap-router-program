#ifndef NA_QT_TEST2_H
#define NA_QT_TEST2_H

#include <QtWidgets/QMainWindow>
#include "ui_na_qt_test2.h"
#include "capthread.h"
#include "func.h"

class NA_Qt_test2 : public QMainWindow, public Ui_NA_Qt_test2Class
{
	Q_OBJECT

public:
	NA_Qt_test2(QWidget *parent = 0);
	~NA_Qt_test2();
	void sendARPFrame(pcap_if_t *d, std::string IP_addr);
	void sendARPFrame(pcap_if_t *d, std::string desIp, std::string srcIp);

public slots:
	void onGetPacket(QString);
	void on_pushButton_clicked();
	void on_add_button_clicked();
	void on_route_button_clicked();
	void onGetMAC(QString);
	void setDesIp(std::string desIp);
	void setSrcIp(std::string srcIp);
private:
	//Ui::NA_Qt_test2Class ui;
	pcap_if_t *alldevs;
	capThread *capthread;
	std::string m_des_ip;
	std::string m_src_ip;
};

std::string ifprint(pcap_if_t *d);
std::string getAdapterip(pcap_if_t *d);
char *iptos(u_long in);




#endif // NA_QT_TEST2_H
