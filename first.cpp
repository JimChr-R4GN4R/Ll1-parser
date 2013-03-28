#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<string>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include"header.h"

using namespace std;

int main(int argc,char* argv[]){
	cout << "-------------------------------left recursion------------------------------" << endl;
	left();
	/*vector<string>::iterator iter;
	for(iter = nonTerminals_vector.begin();iter != nonTerminals_vector.end();iter++){
		cout << *iter << "-->" << longest_subsequence(*iter)<< endl;
	}*/
	cout << "-------------------------------left factoring------------------------------" << endl;
	left_fac();
	cout << "-------------------------------first------------------------------" << endl;
	first();
	cout << "-------------------------------follow------------------------------" << endl;
	follow();
	cout << "-------------------------------table------------------------------" << endl;
	parse();
	cout << "-------------------------------stack------------------------------" << endl;
	stack_parsing();
	return 0;
}


