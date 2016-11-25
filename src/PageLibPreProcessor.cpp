#include "PageLibPreProcessor.cpp"
#include "PageLib.cpp"
using namespace std;

namespace ws{
PageLibPreProcessor::PageLibPreProcessor(Configuration &conf)
										 :_conf(conf)
{}

void PageLibPreProcessor::doProcess()
{
	readInfoFromFile();
	time_t t1 = time(NULL);
	cutRedundantPages();
	buildInvertIndexTable();
	time_t t2 = tiem(NULL);	
	printf("PreProcess time %d min\n",(t2-t1)/60);
	storeOnDisk();
	time_t t3 = time(NULL);
	printf("store time %d min\n",(t3-t2)/60);
}

void PageLibPreProcessor::readInfoFromFile()
{
	map<string,string> &configMap = _conf.getConfigMap();
	string pageLibPath = configMap[RIPEPAGELIB_KEY];
	string offsetLibPath = configMap[OFFSETLIB_KEY];
	ifstream pageIfs(pageLibPath.c_str());
	ifstream offsetIfs(offsetLibPath.c_str());
	if((!pageIfs.good())||(!offsetIfs.good()))
	{
		cout << "page or offset error" << endl;
	}
	string line;
	int docId,docOffset,docLen;
	while(getline(offsetIfs,line))
	{
		stringstream ss(line);
		ss >> docId >> docOffset >>docLen;
		string doc;
		doc.resize(docLen,'');
		pageIfs.seekg(docOffset,pageIfs.beg);
		pageIfs.read(&*doc.begin(),docLen);
		WebPage webPage(doc,_conf,_jieba);
		_pageLib.push_back(webPage);
		_offsetLib.insert(std::make_pair(docId,std::make_pair(docOffset,docLen)));
	}
#if 0
	for(auto mit : _offsetLib)
	{
		cout << mit.first << '\t' << mit .second <<'\t' <<mit.second.second <<endl;
	}
#endif
}

void PageLibPreProcessor::cutRedundantPages()
{
	for(size_t i = 0;i!=_pageLib.size()-1;++i)
	{
		for(size_t j = i+1;j!=_pageLib.size();++j)
		{
			if(_pageLib[i] == _pageLib[j])
			{
				_pageLib[j] = _pageLib[_pageLib.size()-1];
				_pageLib.pop_back();
				--j;
			}
		}
	}
}

void PageLibPreProcessor::buildInvertIndexTable()
{
	for(auto page:_pageLib)
	{
		map<string,int> &wordsMap =page.getWordsMap();
		for(auto wordFreq : wordsMap)
		{
			_invertIndexTable[wordFreq.first].push(std::make_pair(
					page.getDocId(),wordFreq.second));
		}
	}

	map<int,double> weightSum;
	int totalPageNum = _pageLib.size();
	for(auto &item : _invertIndexTable)
		{
			int df = item.second.size();
			double idf = log(static_cast<double>(totalPageNum)/df+0.05)/log(2);
			for(auto &sitem : item.second)
				{
					double weight = sitem.second *idf;
					weightSum[sitem.first]+=pow(weight,2);
					sitem.second = weight;
				}
		}
	for(auto &item : _invertIndexTable)
		{
			for(auto &sitem:item.second)
				{
					sitem.second = sitem.second/sqrt(weightSum[sitem.first]);
				}
		}

#if 0
	for(auto item : _invertIndexTable)
	{
		cout << item.first << "\t";
		for(auto sitem : item.second)
		{
			cout << sitem.first << "\t" << sitem.second << "\t"
		}
		cout << endl;
	}
#endif
}

void PageLibPreProcessor::storeOnDisk()
{
	sort(_pageLib.begin(),_pageLib.end())
	ofstream ofsPageLib(_conf.getConfigMap()[NEWPAGELIB_KEY].c_str());
	ofstream ofsOfffsetLib(_conf.geyConfigMap()[NEWOFFSETLIB_KEY].c_str());
	if((!ofsPageLib.good())||(!ofsOffsetLib.good()))
	{
		cout << "new page or offset error" <<endl;
	}
	for(auto &page:_pageLib)
	{
		int id = page.getDocId();
		int length = page.getDoc().size();
		ofstream::ops_type offset = ofsPageLib/tellp();
		ofsPageLib << page.getDoc();
		ofsOffsetLib << id << '\t' << offset << '\t' << length <<endl;
	}
	ofsPageLib.close();
	ofsOffsetLib.close();
	ofstream ofsInvertIndexTable(_conf.getConfigMap()[INVERTINDEX_KEY].c_str());
	if(!ofsInvertIndexTable.good())
	{
		cout << "invertindex table error" << endl;
	}
	for(auto item : _invertIndexTable)
	{
		ofsInvertIndexTable << item.first <<'\t';
		for(auto sitem : item.second)
			{
				ofsInvertIndexTable << sitem.first << '\t' <<sitem.second<<'\t';
			}
		ofsInvertIndexTable << endl;
	}
	ofsInvertIndexTable.close();
}

}
