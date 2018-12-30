#include "table.h"
#include "func.h"
void arpTable::add(string IP, unsigned char *MAC)
{
	struct arpEntry new_entry;
	new_entry.IP = IP;
	for(int i =0;i<6;i++)
		new_entry.MAC[i] = MAC[i];
	bool exist = false;
	for(int i=0; i<this->table.size();i++)
		if(table[i].IP == IP)
			exist = true;
	if(!exist)
		this->table.push_back(new_entry);
}

bool arpTable::lookup(string IP, unsigned char * mac)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i].IP == IP) {
			for (int j = 0; j < 6; j++)
				mac[j] = table[i].MAC[j];
			return true;
		}
	}
	return false;
}
void routeTable::add(string network, string mask, string next)
{
	routeEntry entry;
	entry.network = network;
	entry.mask = mask;
	entry.next_interface = next;
	this->table.push_back(entry);
}

bool routeTable::lookup(string IP , string &next)
{
	unsigned char ip[4];
	parseIP(IP, ip);

	for (int i = 0; i < table.size(); i++)
	{
		struct routeEntry entry = table[i];
		unsigned char network[4];
		unsigned char mask[4];
		parseIP(entry.network, network);
		parseIP(entry.mask, mask);
		if (((ip[0] & mask[0]) == network[0]) &&
			((ip[1] & mask[1]) == network[1]) &&
			((ip[2] & mask[2]) == network[2]) &&
			((ip[3] & mask[3]) == network[3]))
		{
			next = entry.next_interface;
			return true;
		}
	}
	return false;
}