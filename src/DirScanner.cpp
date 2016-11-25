#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "GlobalDefine.hpp"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
using namespace std;

namespace ws{
DirScanner(Configuration &conf)
	:_conf(conf)
{
	_vecFiles.reserve(FileNo);
}

void DirScanner::operator()()
{
	map<string,string> & confMap = _conf.getConfigMap();
	string dirName = confMap[YULIAO_KEY];
	traverse(dirName);
}

vector <string> &DirScanner::files()
{
	return _vecFiles;
}

void DirScanner::traverse(const string & dirName)
{
	DIR *pdir = ::opendir(dirName.c_str());
	if (NULL ==pdir)
	{
		printf("dir open error");
		exit(EIXT_FAILURE);
	}

	::chdir(dirName.c_str());
	struct dirent * mydirent;
	struct stat mystat;
	while(NULL!=(mydirent=readdir(pdir)))
	{
		::stat(mydirent->d_name,&mystat);
	if(S_ISDIR(mystat.st_mode))
	{
		if(0==strncmp(mydirent->d_name,".",1)
				||strncmp(mydirent->d_name,"..",2))
		{
			continue;
		}
		else{
					traverse(mydirent->d_name);
				}
		else{
					string fileName;
					fileName.append(getcwd(NULL,0))
									.append("/")
									.append(mydirent->d_name);
					_vecFiles.push_back(fileName);
				}
	}
	::chdir("..");
	::closedir(pdir);
	}
}
}
