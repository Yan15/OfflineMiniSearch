#ifndef __MY_PAGELIBPREPROCESSOR_H_
#define __MY_PAGELIBPREPROCESSOR_H_

#include "WebPage.hpp"
#include "WordSegmentation.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

namespace ws{
class Configuration;
class PageLibPreProcessor
{
public:
	PageLibPreProcessor(Configuration &conf);
	void doProcess();
private:
	void readInfoFromPages();
	void cutRedundentPages();
	void buildInverstIndexTable();
	void storeonDisk();
private:
	Configuration &_conf;
	WordSegmentation &_jieba;
	vector<WebPage> _pagelib;
	unordered_map<int,pair<int,int>> _offsetlib;
	unordered_map<string,vector<pair<int,double>>> _invertIndexTable;
};
}
#endif
