#include "na_qt_test2.h"
using namespace std;

NA_Qt_test2::NA_Qt_test2(QWidget *parent)
	: QMainWindow(parent)
{
	this->setupUi(this);
	capthread = new capThread(this);
	connect(this->capthread, &capThread::getPacket, this, &NA_Qt_test2::onGetPacket);
	connect(this->capthread, &capThread::getMAC, this, &NA_Qt_test2::onGetMAC);
	

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &(this->alldevs), NULL) == -1)
		exit(1);
	pcap_if_t *d = this->alldevs;
	
	string adapterInfo = ifprint(d);
	this->deviceInfo->insertPlainText(QString::fromStdString(adapterInfo));

	string IP = getAdapterip(d);
	this->setSrcIp(IP);

	capthread->setPara(d, IP);

	capthread->start();
	//for(d=alldevs; d; d=d->next)
 //   {
	//	if(d->name)
	//	{
	//		std::string dev_name = d->name;
	//		QString Qdev_name = QString::fromStdString(dev_name);
	//		this->contentBrowser->insertPlainText(Qdev_name);
	//	}
	//}
}

NA_Qt_test2::~NA_Qt_test2()
{

}

void NA_Qt_test2::onGetPacket(QString packet)
{

	//this->contentBrowser->insertPlainText(packet);
}

void NA_Qt_test2::onGetMAC(QString MAC)
{
	this->contentBrowser->insertPlainText(MAC);
}

void NA_Qt_test2::on_pushButton_clicked()
{
	QString QIPAddr = this->lineEdit->text();
	//this->contentBrowser->insertPlainText(QIPAddr + "->");


	std::string IP_addr = QIPAddr.toStdString();
	this->setDesIp(IP_addr);
	this->capthread->setPara(IP_addr);

	sendARPFrame(this->alldevs, this->m_des_ip, this->m_src_ip);

}

void NA_Qt_test2::setDesIp(std::string desIp)
{
	this->m_des_ip = desIp;
}
void NA_Qt_test2::setSrcIp(std::string srcIp)
{
	this->m_src_ip = srcIp;
}


void NA_Qt_test2::sendARPFrame(pcap_if_t *d, std::string IP_addr)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *adhandle;
	if ( (adhandle= pcap_open(d->name,          // name of the device
                              65536,            // portion of the packet to capture. 
                                                // 65536 guarantees that the whole packet will be captured on all the link layers
                              PCAP_OPENFLAG_PROMISCUOUS,    // promiscuous mode
                              1000,             // read timeout
                              NULL,             // authentication on the remote machine
                              errbuf            // error buffer
                              ) ) == NULL)
	{
		exit(1);
	}

	unsigned char *ip = new unsigned char[4];
	parseIP(IP_addr, ip);

	ARPFrame_t ARPFrame;

	//set Destination MAC address
	ARPFrame.FrameHeader.DesMAC[0] = 0xff;
	ARPFrame.FrameHeader.DesMAC[1] = 0xff;
	ARPFrame.FrameHeader.DesMAC[2] = 0xff;
	ARPFrame.FrameHeader.DesMAC[3] = 0xff;
	ARPFrame.FrameHeader.DesMAC[4] = 0xff;
	ARPFrame.FrameHeader.DesMAC[5] = 0xff;

	//set Source MAC address
	ARPFrame.FrameHeader.SrcMAC[0] = 0x00;
	ARPFrame.FrameHeader.SrcMAC[1] = 0x0c;
	ARPFrame.FrameHeader.SrcMAC[2] = 0x29;
	ARPFrame.FrameHeader.SrcMAC[3] = 0x73;
	ARPFrame.FrameHeader.SrcMAC[4] = 0x70;
	ARPFrame.FrameHeader.SrcMAC[5] = 0xdd;

	ARPFrame.FrameHeader.FramType = htons(0x0806);

	ARPFrame.HardwareType = htons(0x0001);

	ARPFrame.ProtocolType = htons(0x0800);
	ARPFrame.HLen = 6;
	ARPFrame.PLen = 4;

	ARPFrame.Operation = htons(0x0001);

	ARPFrame.SendHa[0] = 0x00;
	ARPFrame.SendHa[1] = 0x0c;
	ARPFrame.SendHa[2] = 0x29;
	ARPFrame.SendHa[3] = 0x73;
	ARPFrame.SendHa[4] = 0x70;
	ARPFrame.SendHa[5] = 0xdd;

	ARPFrame.SendIP[0] = 0xc0;
	ARPFrame.SendIP[1] = 0xa8;
	ARPFrame.SendIP[2] = 0x8b;
	ARPFrame.SendIP[3] = 0x81;

	for(int i = 0; i<6; i++)
		ARPFrame.RecvHa[i] = 0x00;

	for(int i = 0; i<4; i++)
	{
		ARPFrame.RecvIP[i] = ip[i];
	}

	if(pcap_sendpacket(adhandle, (u_char *)&ARPFrame, sizeof(ARPFrame_t)) != 0)
	{
		//err
	}
	else
	{

	}
}

void NA_Qt_test2::sendARPFrame(pcap_if_t *d, std::string desIp, std::string srcIp)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_t *adhandle;
	if ( (adhandle= pcap_open(d->name,          // name of the device
                              65536,            // portion of the packet to capture. 
                                                // 65536 guarantees that the whole packet will be captured on all the link layers
                              PCAP_OPENFLAG_PROMISCUOUS,    // promiscuous mode
                              1000,             // read timeout
                              NULL,             // authentication on the remote machine
                              errbuf            // error buffer
                              ) ) == NULL)
	{
		exit(1);
	}

	unsigned char *desip = new unsigned char[4];
	unsigned char *srcip = new unsigned char[4];
	parseIP(desIp, desip);
	parseIP(srcIp, srcip);

	ARPFrame_t ARPFrame;

	//set Destination MAC address
	ARPFrame.FrameHeader.DesMAC[0] = 0xff;
	ARPFrame.FrameHeader.DesMAC[1] = 0xff;
	ARPFrame.FrameHeader.DesMAC[2] = 0xff;
	ARPFrame.FrameHeader.DesMAC[3] = 0xff;
	ARPFrame.FrameHeader.DesMAC[4] = 0xff;
	ARPFrame.FrameHeader.DesMAC[5] = 0xff;

	//set Source MAC address
	ARPFrame.FrameHeader.SrcMAC[0] = 0x00;
	ARPFrame.FrameHeader.SrcMAC[1] = 0x0c;
	ARPFrame.FrameHeader.SrcMAC[2] = 0x29;
	ARPFrame.FrameHeader.SrcMAC[3] = 0x73;
	ARPFrame.FrameHeader.SrcMAC[4] = 0x70;
	ARPFrame.FrameHeader.SrcMAC[5] = 0xdd;

	ARPFrame.FrameHeader.FramType = htons(0x0806);

	ARPFrame.HardwareType = htons(0x0001);

	ARPFrame.ProtocolType = htons(0x0800);
	ARPFrame.HLen = 6;
	ARPFrame.PLen = 4;

	ARPFrame.Operation = htons(0x0001);

	ARPFrame.SendHa[0] = 0x00;
	ARPFrame.SendHa[1] = 0x0c;
	ARPFrame.SendHa[2] = 0x29;
	ARPFrame.SendHa[3] = 0x73;
	ARPFrame.SendHa[4] = 0x70;
	ARPFrame.SendHa[5] = 0xdd;

	for(int i = 0; i<4; i++)
		ARPFrame.SendIP[i] = srcip[i];

	//ARPFrame.SendIP[0] = 0xc0;
	//ARPFrame.SendIP[1] = 0xa8;
	//ARPFrame.SendIP[2] = 0x8b;
	//ARPFrame.SendIP[3] = 0x81;

	for(int i = 0; i<6; i++)
		ARPFrame.RecvHa[i] = 0x00;

	for(int i = 0; i<4; i++)
	{
		ARPFrame.RecvIP[i] = desip[i];
	}

	if(pcap_sendpacket(adhandle, (u_char *)&ARPFrame, sizeof(ARPFrame_t)) != 0)
	{
		//err
	}
	else
	{

	}
}

#define IPTOSBUFFERS    12
char *iptos(u_long in)
{
    static char output[IPTOSBUFFERS][3*4+3+1];
    static short which;
    u_char *p;

    p = (u_char *)&in;
    which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
    _snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return output[which];
}

/* Print all the available information on the given interface */
std::string ifprint(pcap_if_t *d)
{
  pcap_addr_t *a;

  std::string adapterInfo;

  /* Name */
  //printf("%s\n",d->name);
  std::string name = d->name;
  adapterInfo = adapterInfo + name + "\n";

  /* Description */
  if (d->description)
    //printf("\tDescription: %s\n",d->description);
  {
	  std::string description = d->description;
	  adapterInfo = adapterInfo + "Description: " + description + "\n";
  }

  /* Loopback Address*/
  //printf("\tLoopback: %s\n",(d->flags & PCAP_IF_LOOPBACK)?"yes":"no");

  /* IP addresses */
  std::string addr;
  for(a=d->addresses;a;a=a->next) {
    //printf("\tAddress Family: #%d\n",a->addr->sa_family);
	//addr = addr + "\tAddress Family: ";
    switch(a->addr->sa_family)
    {
      case AF_INET:
        //printf("\tAddress Family Name: AF_INET\n");
		addr = addr + "\tAddress Family Name: AF_INET\n";
        if (a->addr)
          //printf("\tAddress: %s\n",iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
		{
			std::string address = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
			addr = addr + "\tAddress: " + address + "\n";
		}
        if (a->netmask)
          //printf("\tNetmask: %s\n",iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
		{
			std::string netmask = iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr);
			addr = addr + "\tNetmask: " + netmask + "\n";
		}
        if (a->broadaddr)
          //printf("\tBroadcast Address: %s\n",iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
		{
			std::string broadaddr = iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr);
			addr = addr + "\tBroadcast Address: " + broadaddr + "\n";
		}
        if (a->dstaddr)
          //printf("\tDestination Address: %s\n",iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
		{
			std::string dstaddr = iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr);
			addr = addr + "\tDestination Address: " + dstaddr + "\n";
		}
        break;
    }
  }
  adapterInfo = adapterInfo + addr + "\n";
  return adapterInfo;
}


string getAdapterip(pcap_if_t *d)
{
	//pcap_addr_t *a;
	//a = d->addresses;
	//std::string address;
	//for(a=d->addresses;a;a=a->next)
	//	if(a->addr)
	//	{
	//		std::string address = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
	//		return address;
	//	}
	pcap_addr_t *a;

  std::string adapterInfo;

  /* Name */
  //printf("%s\n",d->name);
  std::string name = d->name;
  adapterInfo = adapterInfo + name + "\n";

  /* Description */
  if (d->description)
    //printf("\tDescription: %s\n",d->description);
  {
	  std::string description = d->description;
	  adapterInfo = adapterInfo + "Description: " + description + "\n";
  }

  /* Loopback Address*/
  //printf("\tLoopback: %s\n",(d->flags & PCAP_IF_LOOPBACK)?"yes":"no");

  /* IP addresses */
  std::string addr;
  for(a=d->addresses;a;a=a->next) {
    //printf("\tAddress Family: #%d\n",a->addr->sa_family);
	//addr = addr + "\tAddress Family: ";
    switch(a->addr->sa_family)
    {
      case AF_INET:
        //printf("\tAddress Family Name: AF_INET\n");
		addr = addr + "\tAddress Family Name: AF_INET\n";
        if (a->addr)
          //printf("\tAddress: %s\n",iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
		{
			std::string address = iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr);
			return address;
			addr = addr + "\tAddress: " + address + "\n";
		}
        if (a->netmask)
          //printf("\tNetmask: %s\n",iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
		{
			std::string netmask = iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr);
			addr = addr + "\tNetmask: " + netmask + "\n";
		}
        if (a->broadaddr)
          //printf("\tBroadcast Address: %s\n",iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
		{
			std::string broadaddr = iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr);
			addr = addr + "\tBroadcast Address: " + broadaddr + "\n";
		}
        if (a->dstaddr)
          //printf("\tDestination Address: %s\n",iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
		{
			std::string dstaddr = iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr);
			addr = addr + "\tDestination Address: " + dstaddr + "\n";
		}
        break;
    }
  }
}


void NA_Qt_test2::on_add_button_clicked()
{
	QString Qnetwork = this->network_line->text();
	QString Qmask = this->mask_line->text();
	QString Qnext = this->next_line->text();
	this->capthread->route_table.add(
		Qnetwork.toStdString(),
		Qmask.toStdString(),
		Qnext.toStdString()
		);
}
void NA_Qt_test2::on_route_button_clicked()
{
	string network;
	string mask;
	string next;
	for(int i = 0; i < this->capthread->route_table.table.size(); i++)
	{
		network = this->capthread->route_table.table[i].network;
		mask = this->capthread->route_table.table[i].mask;
		next = this->capthread->route_table.table[i].next_interface;
		QString Qnetwork, Qmask, Qnext;
		Qnetwork = QString::fromStdString(network);
		Qmask = QString::fromStdString(mask);
		Qnext = QString::fromStdString(next);
		QString QMessage = "network: "+ Qnetwork + "mask: " + Qnetwork + "next: " + Qnext + "\n";
		this->route_browser->insertPlainText(QMessage);
	}
}