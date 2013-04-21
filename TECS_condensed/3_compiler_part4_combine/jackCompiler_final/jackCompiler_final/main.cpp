//
//  main.cpp
//  jackCompiler_final
//
//  Created by Derrick Ho on 3/15/13.
//  Copyright (c) 2013 Derrick Ho. All rights reserved.
//

#include <iostream>
#include <dirent.h>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;
const string token_exe= "/Users/derrickho/Dropbox/Documents/XcodeProjects/jackTokenizerModule/jackTokenizer.py";
const string parser_exe= "/Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py";
const string jack_compiler_c_exe = "/Users/derrickho/Library/Developer/Xcode/DerivedData/jackCompilerPart2_cpp-bkabdqmvlbfvaiadukccqvsorndr/Build/Products/Debug/jackCompilerPart2_cpp";
const string python_exe = "/usr/bin/python";
void handleJackFile(const string & filename,const string & directory, const int &num);
void do_tokenize(string filename, string directory, int num);
void do_parser(string filename, string directory, int num);
void do_vm(string filename, string directory, int num);
/*
Breif : take away the directory and ext
i.e.  "/path/to/fileName.jack" becomes "fileName"
@param "path" : a path to a file with an extention
@return a name without the path nor the ext
*/
string extractDirectoryAndExt(string path);
int main(int argc, const char * argv[])
{
	vector<string> arr_of_jack_files;
	string directory_of_jack_files;
	if (argc == 1) {
		cout << "This program accepts either a <.jack> file or \n";
		cout << "a directory as a command line argument\n\n";
		cout << "will convert a .jack file into a .vm file\n";
		cout << "if its a directory it will convert each .jack file in\n";
		cout << "it into a .vm file\n";
		cout << "./jackCompiler_final <.jack/directory>\n";
		return 0;
	}
	if(strstr(argv[1], ".jack")){
		cout << "is jack file" << endl;
		directory_of_jack_files = argv[1];
		directory_of_jack_files = directory_of_jack_files.substr(0,1 +directory_of_jack_files.rfind("/"));
		arr_of_jack_files.push_back(argv[1]);
	}else{
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir (argv[1])) != NULL) {
			/* print all the files and directories within directory */
			while ((ent = readdir (dir)) != NULL) {
				if (strstr(ent->d_name, ".jack")) {
					//printf ("%s\n", ent->d_name);
					string path2file = string(argv[1]) + "/";
					directory_of_jack_files = path2file;
					path2file += ent->d_name;
					FILE* f = fopen(path2file.c_str(), "r");

					if(!f){cerr << "can't open file\n"; exit(1);}//verify that file can be opened
					arr_of_jack_files.push_back(path2file); // add path/to/file to an array to open up later
					fclose(f);
				}
			}
			closedir (dir);
		} else {
			/* could not open directory */
			perror ("");
			return EXIT_FAILURE;
		}
	}
	for (int i = 0;  i < arr_of_jack_files.size(); ++i) {
		pid_t pid ;
		if( (pid= fork()) == -1) {cerr << " couldn't bare a child\n"; return 1;};
		if (!pid ) {//child
			handleJackFile(arr_of_jack_files[i], directory_of_jack_files, i);
			return 0; //kill kid here.
		}
		sleep(1);
	}
    return 0;
}

typedef enum {TOKEN, PARSER, COMPILER}enum_fn;
void pick_Prog(const string &destination, const string & source, const enum_fn & name );

void handleJackFile(const string & filename, const string & directory, const int &num){
	string token_vm =string(directory) + (extractDirectoryAndExt(filename)) + "_T";
	string parser_vm =string(directory) + (extractDirectoryAndExt(filename)) + "_P";
	string compiler_vm =string(directory) + (extractDirectoryAndExt(filename)) + ".vm";
	
	pick_Prog(token_vm, filename , TOKEN);//do_tokenize(filename, directory, num);
	cout << token_vm << string(" [done]") << endl;
	pick_Prog(parser_vm, token_vm , PARSER);//do_parser(filename, directory, num);
	cout << parser_vm << string(" [done]") << endl;
	pick_Prog(compiler_vm, parser_vm , COMPILER);//do_vm(filename, directory, num);
	cout << compiler_vm << string(" [done]") << endl;
}
void pick_Prog(const string& destination, const string& source, const enum_fn& name){
	FILE* f = fopen(destination.c_str(), "w");
	if(!f){cerr<< "couldn't open\n"; exit(1);}
	
	pid_t pid = fork();//make another child
	if( pid== -1) {cerr << " couldn't bare a child\n"; exit(1);};
	if(!pid) {//is child
		//redirect std output to destination
		if(-1==  dup2(fileno(f), 1)   ){	cerr<< "couldn't redirect STD output\n";	exit(1);}
		switch (name) {
			case TOKEN:{
				if (-1== execl(python_exe.c_str(), python_exe.c_str(),
							   token_exe.c_str(), source.c_str(),
							   NULL)
					){	cerr << "can't run program\n";	exit(1);}
			}break;
			case PARSER:	{
				if (-1== execl(python_exe.c_str(), python_exe.c_str(),
							   parser_exe.c_str(), source.c_str(),
							   NULL)
					){	cerr << "can't run program\n";	exit(1);}
			}break;
			case COMPILER:{
				if (-1== execl(jack_compiler_c_exe.c_str(), jack_compiler_c_exe.c_str(),
							   source.c_str(),
							   NULL)
					){	cerr << "can't run program\n";	exit(1);}
			}break;
			default:
				cerr << "Unknown function to call" << endl; exit(1);
		}
	}
	//wait for child to finish then exterminate it
	int pid_status;
	if(waitpid(pid, &pid_status, 0) == -1){cerr << " error waiting for child process "<<endl; exit(0);	}
	
	fclose(f);
	return;
}

void do_tokenize(string filename, string directory, int num){
	FILE * f;
	cout << filename << " token[" << num <<"] "<< endl;
	//make another child
	pid_t pid = fork();
	if( pid== -1) {cerr << " couldn't bare a child\n"; exit(1);};
	//do the tokenizing
	char token_vm[1024];
	sprintf(token_vm, "%s/%s_%d.txt", directory.c_str(), "token", num);
	
	f = fopen(token_vm, "w");//open file for writing
	if(!f){cerr<< "couldn't open token.txt\n"; exit(1);}
	if(!pid) {
		//redirect std output to token.txt
		if(-1==
		   dup2(fileno(f), 1)
		   ){
			cerr<< "couldn't redirect STD output\n";
			exit(1);
		}
		if (-1==
			execl(python_exe.c_str(), python_exe.c_str(),
				  token_exe.c_str(), filename.c_str(),
				  NULL)
			)
		{
			cerr << "can't run program\n";
			exit(1);
		}
	}
	//wait for child to finish then exterminate it
	int pid_status;
	if(waitpid(pid, &pid_status, 0) == -1){
		cerr << " error waiting for child process "<<endl;
	}
	fclose(f);
	return;
}
void do_parser(string filename, string directory, int num){
	FILE * f;
	cout << filename << " parser[" << num <<"] "<< endl;
	//make another child
	pid_t pid = fork();
	if( pid== -1) {cerr << " couldn't bare a child\n"; exit(1);};
	//do the tokenizing
	char parser_vm[1024];
	sprintf(parser_vm, "%s/%s_%d.txt", directory.c_str(), "parser", num);
	char token_vm[1024];
	sprintf(token_vm, "%s/%s_%d.txt", directory.c_str(), "token", num);
	f = fopen(parser_vm, "w");//open file for writing
	if(!f){cerr<< "couldn't open token.txt\n"; exit(1);}
	if(!pid) {
		//redirect std output to token.txt
		if(-1==  dup2(fileno(f), 1)	   ){cerr<< "couldn't redirect STD output\n";	exit(1);	}
		if (-1==	execl(python_exe.c_str(), python_exe.c_str(),
				  parser_exe.c_str(), token_vm,
				  NULL)
			){	cerr << "can't run program\n";	exit(1);	}
	}
	//wait for child to finish then exterminate it
	int pid_status;
	if(waitpid(pid, &pid_status, 0) == -1){
		cerr << " error waiting for child process "<<endl;
	}
	fclose(f);
	return;
}
void do_vm(string filename, string directory, int num){
	FILE * f;
	cout << filename << " vm[" << num <<"] "<< endl;
	//make another child
	pid_t pid = fork();
	if( pid== -1) {cerr << " couldn't bare a child\n"; exit(1);};
	//do the tokenizing
	char vm_vm[1024];
	sprintf(vm_vm, "%s/%s_%d.txt", directory.c_str(), "vm", num);
	char parser_vm[1024];
	sprintf(parser_vm, "%s/%s_%d.txt", directory.c_str(), "parser", num);
	f = fopen(vm_vm, "w");//open file for writing
	if(!f){cerr<< "couldn't open token.txt\n"; exit(1);}
	if(!pid) {
		//redirect std output to token.txt
		if(-1==  dup2(fileno(f), 1)	   ){cerr<< "couldn't redirect STD output\n";	exit(1);	}
		if (-1==	execl(	jack_compiler_c_exe.c_str(),  jack_compiler_c_exe.c_str(), parser_vm,
						  NULL)
			){	cerr << "can't run program\n";	exit(1);	}
	}
	//wait for child to finish then exterminate it
	int pid_status;
	if(waitpid(pid, &pid_status, 0) == -1){
		cerr << " error waiting for child process "<<endl;
	}
	fclose(f);
	return;

}

string extractDirectoryAndExt(string path){
	int start =(int)path.rfind("/")+1;
	int dot = (int)path.rfind(".jack");
	if (dot == string::npos) {
		cerr<< "expected a file with a .jack ext\n";
		exit(1);
	}
	return path.substr(start, dot-start);
}