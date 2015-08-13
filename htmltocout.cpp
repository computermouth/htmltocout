#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;


class Process{
	string currentFile;
	string headerFile;
	char** charDump;
	int charDumpCount;
	string* stringDump;
  public:

	void dumpFile(){
		ifstream html;
		html.open(currentFile.c_str());
		
		int count = 0;
		
		while(!html.eof()){
			char buf[1000];
			html.getline(buf, 1000);
			
			count++;
		}
			
		charDumpCount = count;
		
		charDump = new char*[count];
		for(int i = 0; i < count; i++)
			charDump[i] = new char[1000];
			
		for(int i = 0; i < count; i++)
			for(int j = 0; j < 1000; j++)
				charDump[i][j] = ' ';
			
		html.clear();
		html.seekg(0, ios::beg);
		
		for(int i = 0; i < count; i++){
			html.getline(charDump[i], 1000);
		}
		
		html.close();
	}
	
	void checkSensetive(){
	
		cout << charDumpCount;
		stringDump = new string[charDumpCount];
		for(int i = 0; i < charDumpCount; i++){
			for(int j = 0; j < 995; j++){
				if(charDump[i][j] == '/')
					stringDump[i] += "\\";

				stringDump[i] += charDump[i][j];
					
					
			}
				stringDump[i]+= "\\\n";
				cout << stringDump[i] << endl;
		}
	}

	Process(string c, string h){
		//pull in file names
		currentFile = c;
		headerFile = h;
		
		dumpFile();
		checkSensetive();
		
		cout << "\n";
		
		ofstream head;
		head.open(headerFile.c_str());
		head << "\n\n";
		
		for(int i = 0; i < charDumpCount; i++){
			head << stringDump[i] << endl;
			cout << stringDump[i];
		}
		
		head.close();
		
		
	}
	
	~Process(){
		for(int i = 0; i < charDumpCount; i++)
			delete [] charDump[i];
		delete [] charDump;
		delete [] stringDump;
	}
	
};

int main(int argc, char* argv[]){

	cout << "\n" << argv[ 0 ] << " is converting the following files: \n\n";
       
	for (int n = 1; n < argc; n++){
		cout << setw( 2 ) << n << ": " << argv[ n ] << " ==> ";
		
		string currentFile = argv[n];
		int lastindex = currentFile.find_last_of(".");
		string headerFile = (currentFile.substr(0, lastindex) + ".h");
		cout << headerFile << '\n';
		
		Process process(currentFile, headerFile);
		
			
	}

	return 0;
}
