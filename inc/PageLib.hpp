#ifndef __MY_PAGELIB_H_
#define __MY_PAGELIB_H_

#include <string>
#include <vector>
namespace ws{
class Configuration;
class DirScanner;
class FileProcessor;
class PageLib
{
public:
	PageLib(const string &conf
					,const string &dirScanner
					,const string &fileProcessor);
	void create();
	void store();
private:
	Configuration & _conf;
	DirScanner & _dirScanner;
	FileProcessor & _fileProcessor;
	std::vector<string> _vecPages;
};
}
#endif
