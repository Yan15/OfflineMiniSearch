#include "Configuration.cpp"
#include "PageLib.cpp"
using namespace std;

namespace ws{
PageLib::PageLib(Configuration &conf
								,DirScanner &dirScanner
								,FileProcessor &fileProcessor)
				:_conf(conf),_dirScanner(dirScanner)
				,_fileProcessor(fileProcessor){}

void PageLib::create()
{
	vector<string>& _vecFiles=_dirScanner.files();
	for(size_t idx=0;idx!=vecFiles.size();++idx)
	{
		string page = _fileProcessor.process(idx,vecFiles[idx])
		_vecFiles.push_back(page);
	}
}

void PageLib::store()
{
	std::map<std::string, std::string> & confMap = _conf.getConfigMap();
	std::string pageLibPath = confMap[RIPEPAGELIB_KEY];
	std::string offsetLibPath = confMap[OFFSETLIB_KEY];

	std::ofstream ofsPage(pageLibPath.c_str());
	std::ofstream ofsOffset(offsetLibPath.c_str());
	if(!(ofsPage.good() && ofsOffset.good()))
	{
		std::cout << "ofstream open error!" << std::endl;
		return;
	}

	for(size_t idx = 0; idx != _vecPages.size(); ++idx)
	{
		int id = idx + 1;
		int length = _vecPages[idx].size();
		std::ofstream::pos_type offset = ofsPage.tellp();
		ofsPage << _vecPages[idx];

		ofsOffset << id << '\t' << offset << '\t' << length << '\n';
	}

	ofsPage.close();
	ofsOffset.close();
}


}
