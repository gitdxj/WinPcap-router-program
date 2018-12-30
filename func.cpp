#include "func.h"

using namespace std;

void parseIP(string IP_addr, unsigned char *ip)
{
	int position1 = IP_addr.find('.');
	int position2 = IP_addr.find('.', position1 + 1);
	int position3 = IP_addr.find('.', position2 + 1);

	string sub1 = IP_addr.substr(0, position1);
	string sub2 = IP_addr.substr(position1+1, position2 - position1 - 1);
	string sub3 = IP_addr.substr(position2+1, position3 - position2 - 1);
	string sub4 = IP_addr.substr(position3+1, IP_addr.length());
	/*cout<<sub1<<endl
		<<sub2<<endl
		<<sub3<<endl
		<<sub4<<endl;*/
	int byte1 = atoi(sub1.c_str());
	int byte2 = atoi(sub2.c_str());
	int byte3 = atoi(sub3.c_str());
	int byte4 = atoi(sub4.c_str());
	
	if(ip == NULL)
		return;
	else{
		*(ip) = unsigned char(byte1);
		*(ip+1) = unsigned char(byte2);
		*(ip+2) = unsigned char(byte3);
		*(ip+3) = unsigned char(byte4);
	}
}

//void sendARPFrame(pcap_if_t *d, std::string IP_addr)
//{
//	char errbuf[PCAP_ERRBUF_SIZE];
//	pcap_t *adhandle;
//	if ( (adhandle= pcap_open(d->name,          // name of the device
//                              65536,            // portion of the packet to capture. 
//                                                // 65536 guarantees that the whole packet will be captured on all the link layers
//                              PCAP_OPENFLAG_PROMISCUOUS,    // promiscuous mode
//                              1000,             // read timeout
//                              NULL,             // authentication on the remote machine
//                              errbuf            // error buffer
//                              ) ) == NULL)
//	{
//		exit(1);
//	}
//
//	unsigned char *ip = new unsigned char[4];
//	parseIP(IP_addr, ip);
//
//	ARPFrame_t ARPFrame;
//
//	//set Destination MAC address
//	ARPFrame.FrameHeader.DesMAC[0] = 0xff;
//	ARPFrame.FrameHeader.DesMAC[1] = 0xff;
//	ARPFrame.FrameHeader.DesMAC[2] = 0xff;
//	ARPFrame.FrameHeader.DesMAC[3] = 0xff;
//	ARPFrame.FrameHeader.DesMAC[4] = 0xff;
//	ARPFrame.FrameHeader.DesMAC[5] = 0xff;
//
//	//set Source MAC address
//	ARPFrame.FrameHeader.SrcMAC[0] = 0x00;
//	ARPFrame.FrameHeader.SrcMAC[1] = 0x0c;
//	ARPFrame.FrameHeader.SrcMAC[2] = 0x29;
//	ARPFrame.FrameHeader.SrcMAC[3] = 0x73;
//	ARPFrame.FrameHeader.SrcMAC[4] = 0x70;
//	ARPFrame.FrameHeader.SrcMAC[5] = 0xdd;
//
//	ARPFrame.FrameHeader.FramType = htons(0x0806);
//
//	ARPFrame.HardwareType = htons(0x0001);
//
//	ARPFrame.ProtocolType = htons(0x0800);
//	ARPFrame.HLen = 6;
//	ARPFrame.PLen = 4;
//
//	ARPFrame.Operation = htons(0x0001);
//
//	ARPFrame.SendHa[0] = 0x00;
//	ARPFrame.SendHa[1] = 0x0c;
//	ARPFrame.SendHa[2] = 0x29;
//	ARPFrame.SendHa[3] = 0x73;
//	ARPFrame.SendHa[4] = 0x70;
//	ARPFrame.SendHa[5] = 0xdd;
//
//	ARPFrame.SendIP[0] = 0xc0;
//	ARPFrame.SendIP[1] = 0xa8;
//	ARPFrame.SendIP[2] = 0x8b;
//	ARPFrame.SendIP[3] = 0x81;
//
//	for(int i = 0; i<6; i++)
//		ARPFrame.RecvHa[i] = 0x00;
//
//	for(int i = 0; i<4; i++)
//	{
//		ARPFrame.RecvIP[i] = ip[i];
//	}
//
//	if(pcap_sendpacket(adhandle, (u_char *)&ARPFrame, sizeof(ARPFrame_t)) != 0)
//	{
//		//err
//	}
//	else
//	{
//
//	}
//}