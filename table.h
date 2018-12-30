#include <string>
#include <vector>
using namespace std;
struct arpEntry {
	string IP;
	unsigned char MAC[6];
};

struct routeEntry{
	string network;
	string mask;
	string next_interface;
};

class arpTable{
private:
	vector<struct arpEntry> table;

public:
	void add(string IP, unsigned char *MAC);
	bool lookup(string IP, unsigned char *mac);
};

class routeTable{
public:
	vector<struct routeEntry> table;


	void add(string network, string mask, string next);
	bool lookup(string IP , string &next);

};