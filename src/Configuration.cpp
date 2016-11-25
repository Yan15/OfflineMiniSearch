#include "Configuration.hpp"
#include "GlobalDefine.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

namespace ws{
Configuration::Configuration(const std::string &filepath)
	:_filepath(filepath)
{
	readConfiguration();
}

void Configuration::readConfiguration()
{
	std::ifstream ifs(_filepath.c_str());
	if(ifs.good())
	{
		std::string line;
		while(getline(ifs,line))
		{
			std::istringstream iss(line);
			std::string key;
			std::string value;
			iss>>key>>value;
			_configMap[key] = value;
		}
		std::cout << "read configuration is over."<<std::endl;
	}
	else
	{
		std::cout << "ifstream open error."<< std::endl;
	}
}

std::map<string,string> &Configuration::getConfiguration()
{
	return _configMap;
}

std::set<string> &Configuration::getStopWordList()
{
	if(_stopWordList.size()>0)
		{
			return _stopWordList;
		}
	string stopWorldFilePath = _configMap[STOP_WORD_KEY];
	ifstream ifs(stopWordFilePath.c_str());
	if(!ifs)
	{
		cout<<"StopWord ifstream open error."<<endl;
	}
	string wordl;
	while(getline(ifs,word))
	{
		_stopWordList.insert(word);
	}
	return _stopWordList;
}

}
