#ifndef __MY_FILEPROCESSOR_H_
#define __MY_FILEPROCESSOR_H_

#include <string>
namespace ws{
class Configuration;
class FileProcessor
{
public:
	FileProcessor(Configuration &conf);
	std::string process(int idx,const string &fileName);
	
private:
	void readfile(const std::string &fileName
								, std::string &title
								, std::string &content);
private:
	std::string _titleFeature;
	Configuration & _conf;
};
}
#endif
