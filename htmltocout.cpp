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
		stringDump = new string[charDumpCount+1];
		for(int i = 0; i < charDumpCount; i++){
				stringDump[i] += ' ';
			for(int j = 0; j < 1000; j++){
				if(charDump[i][j] == '/' || 
					charDump[i][j] == '"' ||
					charDump[i][j] == '\0')
					stringDump[i] += '\\';
					

				stringDump[i] += charDump[i][j];
					
					
			}
		}
	}

	Process(string c, string h, string orig){
		//pull in file names
		currentFile = c;
		headerFile = h;
		
		dumpFile();
		checkSensetive();
		
		
		ofstream head;
		head.open(headerFile.c_str(), ios::out);
		
		head << "\n void print" << orig << "(){ \n\n cout << \" ";
		
		 for(int i = 0; i < charDumpCount; i++){
			head << stringDump[i].c_str() << endl;
		}
		head << "\";\n\n}";
		
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
		
		Process process(currentFile, headerFile, (currentFile.substr(0, lastindex)));
		
			
	}

	return 0;
}
