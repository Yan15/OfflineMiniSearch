#ifndef __MY_WEBPAGE_H_
#define __MY_WEBPAGE_H_

#include "Configuration.hpp"
#include "WordSegmentation.hpp"
#include <iostream>
#include <map>
#include <set>
#include <vector>

using std::string;
using std::map;
using std:;set;
using std::vector;

namespace ws{
class PageLibPreProcessor;
class WebPage
{
public:
	friend bool operator == (const WebPage &lhs,const WebPage &rhs);
	friend bool operator < (const WebPage &lhs,const WebPage &rhs);
	const static int TOPK_NUMBER = 20;
	WebPage(string &doc,Configuration &config,WordSegmention &jieba);
	int getDocId()
	{
		return _docId;
	}
	map<string ,int>&getWordMap()
	{
		return _wordMap;
	}
	string getDoc()
	{
		return _doc;
	}
private:
	string _doc;
	int _docId;
	string _docTitle;
	string _docUrl;
	string _docContent;
	string _docSummary;
	vector<string> _topWords;
	map<string,int> _wordMap;
};
}
#endif
