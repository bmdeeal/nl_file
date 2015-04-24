#ifndef NL_FILE_H
#define NL_FILE_H
using namespace std;

struct nl_File {
	string filename; //the file to load/save from/to
	vector<string> data; //vector of each line -- would use a list, but random access seems to be a more likely use case, although insertions might be pretty common as well... still, this library is expected to be used for things like configuration files, with few line inserts
	//save -- write file to disk
	int save();
	//load -- read file from disk
	int load();
	//constructors -- they don't need to do much in the slightest at the moment, if ever
	nl_File();
	nl_File(const char *f);
};
#endif