#include "Configuration.hpp"
#include "FileProcessor.hpp"
#include <iostream>
#include <string>
using namespace std;

namespace ws{
FileProcessor::FileProcessor(Configuration &conf)
								:_conf(conf)
{
	map<string,string>&confMap = _conf.getConfigMap();
	string titleFeatureFilePath = confMap[TITLEFEATURE_KRY];
	ifstream ifs(titleFeatureFilePath.c_str());
	if(ifs)
	{
		getline(ifs,_titleFeature);
	}
	cout<<"_titleFeature="<<_titleFeature<<endl;
}

string FileProcessot::process(int idx,const string &filename)
{
	string page,id,url,title,content;
	ostringstream oss;
	oss<<(idx+1);
	id=oss.str();
	url=filename
	readfile(filename,title,content);
	page.append("<doc>\n<docid>")
		.append(id).append("</docid>\n<docurl>")
		.append(url).append("</docurl>\n<doctitle>\n")
		.append(title).append("\n</doctitle>\n<doccontent>\n")
		.append(content).append("\n</doccontent>\n</doc>\n");
	return page;
}

void FileProcessor::readfile(const string &filename
															,const string &title
															,const string &content)
ifstream ifs(filename.c_str());
	if(!ifs)
	{
		cout << "ifstream open error!" << endl;
	}
	else
	{
		ifs.seekg(0, ifs.end);
		int length = ifs.tellg();
		ifs.seekg(0, ifs.beg);
		content.resize(length, ' ');
		ifs.read(&*content.begin(), length);
		ifs.seekg(0, ifs.beg);
		title.resize(1024, ' ');
		int count = 11;
		bool flag = false;
		while(getline(ifs, title) && count > 0)
		{
			std::string::size_type pos = title.find(_titleFeature);
			if(pos != std::string::npos)
			{
				pos += _titleFeature.size();
				title = title.substr(pos);
				flag = true;
				break;
			}
			--count;
		}
		if(count > 0&& flag == false)
		{
			ifs.seekg(0,ifs.beg);
			getline(ifs,title);
		}
		else if(count == 0&& flag == false)
						{
							getline(ifs,title);
						}
		size_t sz = title.size();
		if(title[sz-1]=='\n')
		{
			title[sz-1]='\0';
		}
	}
}
