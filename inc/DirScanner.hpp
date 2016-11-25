#ifndef __MY_DIRSCANNER_H_
#define __MY_DIRSCANNER_H_

#include <string>
#include <set>
using namespace std;

namespace ws{
const int FileNo=1000;
class Configuration;
class DirScanner
{
public:
	DirScanner(Configuration &conf);
	void operator()();
	std::vector<std::string>$files();
private:
	void traverse(const std::string &dirName);
	Configuration & _conf;
	vector<string> _vecFiles;
};

}
#endif
