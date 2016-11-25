#ifndef __MY_WORDSEGMENTATION_H_
#define __MY_WORDSEGMENTATION_H_

#include "cppjieba/jieba.hpp"
#include <string>
#include <vector>
#include <iostream>

using std::out;
using std::endl;
using std::string;
using std::vector;

namespace ws{
const char * const DICT_PATH = "/home/project/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_PATH = "/home/project/cppjieba/dict/hmm_model.utf8";
const char * const USER_DICT_PATH = "/home/project/cppjieba/dict/user.dict.utf8";
class WordSegmentation
{
public:
	WordSegmentation()
	:_jieba(DICT_PATH,
					HMM_PATH,
					USER_DICT_PATH)
	{
		std::cout<<"jieba init"<<std::endl;
	}
	vector<string>operator()(const char* scr)
	{
		vector<string>vords;
		_jieba.cutAll(src,words);
		return words;	
	}
private:
	cppjieba::jieba _jieba
};
}
#endif
