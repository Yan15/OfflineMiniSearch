#ifndef __MY_CONFIGURATION_H_
#define __MY_CONFIGURATION_H_

#include <string>
#include <set>
#include <map>
using namespace std;

namespace ws{
class Configuration
{
public:
	Configuration(const std::string &filepath);
	std::map<std::string,std::string>&getConfigMap;
	std::set<std::string>&getStopWordList;
private:
	void readConfiguration();
private:
	string _filepath;
	map<std::string,std::string> _configMap;
	set<std::string> _stopWordList;
};
}
#endif
