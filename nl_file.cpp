#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "nl_file.h"

/*
 nl_File -- simple line based file library
 it's extremely simple, but makes text file loading/writing pretty much trivial
*/

/*
 Copyright (c) 2015 Brenden Deeal
 
 Permission is hereby granted, free of charge, to any person obtaining
 a copy of this software and associated documentation files (the
 "Software"), to deal in the Software without restriction, including
 without limitation the rights to use, copy, modify, merge, publish,
 distribute, sublicense, and/or sell copies of the Software, and to
 permit persons to whom the Software is furnished to do so, subject to
 the following conditions:
 
 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

//it works!
//todo: error handling of some kind, this doesn't really handle things like full disk or disk removed, etc
//also, it doesn't check if the file exists when loading

using namespace std;


//save -- write file to disk
int nl_File::save() {
	int pos; //number of lines written
	ofstream out_file; //file to write
	//open the file for writing
	out_file.open(filename.c_str());
	//if there's ANY issue at all, abort
	if (!out_file.good()) {
		cout << "error opening \"" << filename << "\"!\n";
		out_file.close();
		return 0;
	}
	//write each line out
	//todo: do some kind of error checking, in case of something like full disk
	for (pos=0; pos < data.size(); ++pos) {
		out_file << data[pos] << "\n";
	}
	//and we're done
	out_file.close();
	return 1;
}
//load -- read file from disk
//todo: check if there are any issues reading that aren't EOF
int nl_File::load() {
	ifstream in_file; //file to read
	string temp; //temporary string to load to
	//open the file for reading
	in_file.open(filename.c_str());
	//empty anything that was previously loaded
	data.clear();
	//load each line in
	while (in_file.good()) {
		getline(in_file, temp);
		//strip blank lines
		if (temp != "") { data.push_back(temp); }
	}
	//and we're done
	in_file.close();
	return 1;
}
//constructors -- they don't need to do much in the slightest
nl_File::nl_File() {
}
nl_File::nl_File(const char *f) {
	filename=f;
}


//test program
//todo: replace with a set of unit tests that write a file, read that file back, that sort of thing -- might be overkill for such a trivial library though
int main() {
	nl_File test_file ("test.txt");
	cout << "load\n";
	test_file.load();
	test_file.data[2]="asdf!";
	cout << "save\n";
	test_file.save();
}