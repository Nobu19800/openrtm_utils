/*!
* @file  FileStreamFunc.cpp
* @brief ファイル操作関連の関数
*
*/

#include <coil/File.h>

#include "FileStreamFunc.h"


using namespace RTC;
using namespace std;



/**
*@brief バイナリファイルに文字保存する関数
* @param a 文字列
* @param ofs ファイルストリーム
*/
void WriteString(string a, ofstream &ofs)
{
	int s = a.size()+1;
	ofs.write( (char*)&s, sizeof(s) );
	ofs.write( a.c_str(), s );
}


/**
*@brief バイナリファイルより文字読み込みする関数
* @param ifs ファイルストリーム
* @return 文字列
*/
string ReadString(ifstream &ifs)
{
	string a;
	int s;
	ifs.read( (char*)&s, sizeof(s) );

	char *st = new char[s];
	ifs.read( st, s );

	a = st;

	delete st;

	return a;
}

/**
*@brief ファイルパスからファイル名、本体名、拡張子、ディレクトリパスを出力するクラスのコンストラクタ
* @param path ファイルパス
*/
PathList::PathList(std::string path)
{
	fname = coil::basename(path.c_str());
	std::vector<std::string> sl = coil::split(fname,".");
	name = sl[0];
	
	if(sl.size() > 1)
	{
		cxt = sl[1];
	}
	else
	{
		cxt = "";
	}
	
	char* repath = const_cast<char*>(path.c_str());
	dname = coil::dirname(repath);
}