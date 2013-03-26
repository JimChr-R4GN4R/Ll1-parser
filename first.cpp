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

extern vector<string> nonTertminals_vector;
extern map< string,vector<string> > grammar;

vector<string> split(string s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while(getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

bool is_nonTerminal(string nonT){
	vector<string>::iterator iter;
	for(iter = nonTerminals_vector.begin();iter != nonTerminals_vector.end();iter++){
		if(*iter == nonT)
			return 1;
	}
	return 0;
}

bool has_ep(string nonT){
	vector<string>::iterator iter_v;
	for(iter_v = grammar[nonT].begin();iter_v != grammar[nonT].end();iter_v++){
		if(*iter_v == "#"){
			return 1;
		}
		else{
			vector<string> temp;
			vector<string>::iterator it_temp;
			split(*iter_v,' ',temp);
			for(it_temp = temp.begin();it_temp != temp.end();it_temp++){
				if(is_nonTerminal(*it_temp)){
					if(!has_ep(*it_temp)){
						return 0;
					}
				}
				else
					return 0;
			}
			return 1;
		}
	}
}

int main(int argc,char* argv[]){
	left();
	vector<string>::iterator iter;
	vector<string>::iterator iter_v;
	map<string,set<string> > first_set;
	int flag_i = 1;
	while(flag_i){
		flag_i = 0;
		for(iter = nonTerminals_vector.begin();iter != nonTerminals_vector.end();iter++){
			if(has_ep(*iter)){
				first_set[*iter].insert("#");
				flag_i = 1;
			}
			else{
				for(iter_v = grammar[*iter].begin();iter_v != grammar[*iter].end();iter_v++){
					vector<string> temp;
					vector<string>::iterator it_temp;
					split(*iter_v,' ',temp);
					for(it_temp = temp.begin();it_temp != temp.end();it_temp++){
						if(is_nonTerminal(*it_temp)){
							if(!has_ep(*it_temp)){
								set<char>::iterator it_s;
								if(first_set.find(*it_temp)!=first_set.end()){
									for(it_s = first_set[*it_temp].begin();it_s != first_set[*it_temp].end();it_s++){
										first_set[*iter].insert(*it_s);
									}
									flag_i = 1;
									break;
								}
							}
						}
						else{
							first_set[*iter].insert(*it_temp);
							break;
						}
					}
				}
			}
		}
	}
	for(iter = nonTerminals_vector.begin();iter != nonTerminals_vector.end();iter++){

	return 0;
}
