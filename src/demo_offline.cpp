#include "GlobalDefine.hpp"
#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "FileProcessor.hpp"
#include "PageLib.hpp"
#include "WordSegmentation.hpp"
#include "WebPage.hpp"
#include "PageLibPreprocessor.hpp"
#include <stdio.h>
#include <time.h>

int main(void)
{
	ws::Configuration conf("conf/my.conf");
	ws::DirScanner dirScanner(conf);
	dirScanner();
	ws::FileProcessor fileProcessor(conf);
	ws::PageLib pagelib(conf, dirScanner, fileProcessor);
	time_t t1 = time(NULL);
	pagelib.create();
	pagelib.store();
	time_t t2 = time(NULL);
	printf("raw lib create and store time: %d min\n", (t2 - t1));

	ws::PageLibPreprocessor libPreprocessor(conf);
	libPreprocessor.doProcess();
	return 0;
}
