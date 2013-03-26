#include <iostream>
#include<vector>
#include<map>
#include<cstring>
#include<fstream>
#include <cstdlib>
using namespace std;

vector<string> nonTerminals_vector;
map< string,vector<string> > grammar;

string getNonterminal(string line,int &linePos)
{
	int i=0;
	string str="";
	while(line[i]!='-')
	{
		str+=line[i];
		i++;
	}
	linePos=i+2;
	return str;
}

string getRHS(string line,int &linePos)
{
	int i=linePos;
	int len=line.length();
	string str="";
	while(i!=len && line[i]!='|')
	{
		str+=line[i];
		i++;
	}
	if(i!=len)
		linePos=i+1;
	else
		linePos=i;
	return str;
}

bool nonTerminal_notExist(string nonTerminal)
{
	int vec_size=nonTerminals_vector.size();
	for(int i=0;i<vec_size;i++)
	{
		if(nonTerminals_vector[i]==nonTerminal)
			return 0;
	}
	return 1;
}

bool str_match(int j,int i,int k)
{
	string str2=grammar[nonTerminals_vector[i]][k];
	if(str2.compare(0,nonTerminals_vector[j].length(),nonTerminals_vector[j]) == 0)
	{
		//cout << nonTerminals_vector[j]<<"\t"<<str2<<endl;
		return 1;
	}
	return 0;
}

bool check_direct_recursion(int i)
{
	int vec_size=grammar[nonTerminals_vector[i]].size();
	for(int j=0;j<vec_size;j++)
	{
		if(str_match(i,i,j))
		{
			return 1;
		}
	}
	return 0;
}

void direct_recursion(int i)
{
	int vec_size=grammar[nonTerminals_vector[i]].size();
	
	if(check_direct_recursion(i))
	{
		
		string newNonTerminal=nonTerminals_vector[i]+"_dash";
		nonTerminals_vector.push_back(newNonTerminal);
		vector<string> temp_vec;
		for(int j=0;j<vec_size;j++)
		{
			string originalRHS=grammar[nonTerminals_vector[i]][j];
			if(str_match(i,i,j))
			{
				string changedRHS=originalRHS.substr(nonTerminals_vector[i].length(),originalRHS.length());	//alpha1
				grammar[newNonTerminal].push_back(changedRHS+" "+newNonTerminal);
				//grammar[nonTerminals_vector[i]].erase(grammar[nonTerminals_vector[i]].begin()+j);
			}
			else
			{
				//cout << originalRHS+newNonTerminal<<endl;
				temp_vec.push_back(originalRHS+" "+newNonTerminal);
				//grammar[nonTerminals_vector[i]][j]=originalRHS+newNonTerminal;
			}
		}
		grammar[nonTerminals_vector[i]].erase(grammar[nonTerminals_vector[i]].begin(),grammar[nonTerminals_vector[i]].end());
		grammar[nonTerminals_vector[i]].insert(grammar[nonTerminals_vector[i]].begin(),temp_vec.begin(),temp_vec.end());
		temp_vec.erase(temp_vec.begin(),temp_vec.end());
		//cout << newNonTerminal<<endl;
		grammar[newNonTerminal].push_back("#");
		//for(int l=0;l<grammar[newNonTerminal].size();l++)
		//	cout << grammar[newNonTerminal][l]<<"\t";
		//exit(1);
		
	}
}

void indirect_recursion()
{
	int i,j,k,l;
	int vec_size=nonTerminals_vector.size();
	for(i=0;i<vec_size;i++)
	{
		for(j=0;j<i;j++)
		{
			int tmp=grammar[nonTerminals_vector[i]].size();
			for(k=0;k<tmp;k++)
			{
				if(str_match(j,i,k))
				{
					//cout <<grammar[nonTerminals_vector[i]][k]<<"\t : \t";
					string originalRHS=grammar[nonTerminals_vector[i]][k];
					string changedRHS;
					changedRHS=originalRHS.substr(nonTerminals_vector[j].length(),originalRHS.length());
					grammar[nonTerminals_vector[i]].erase(grammar[nonTerminals_vector[i]].begin()+k);
					int tmp1=grammar[nonTerminals_vector[j]].size();
					
					for(l=0;l<tmp1;l++)
					{
						grammar[nonTerminals_vector[i]].push_back(grammar[nonTerminals_vector[j]][l]+changedRHS);
						//cout << grammar[nonTerminals_vector[j]][l]+changedRHS<<"\t";
					}
					//cout<<endl;
				}
			}
		}
		direct_recursion(i);
	}
}



void left()
{
	string line;
	ifstream fp;
	fp.open("in");
	int linePos;
	while(getline (fp,line))
	{
		linePos=0;
		string nonTerminal=getNonterminal(line,linePos);
		if(nonTerminal_notExist)
		{
			nonTerminals_vector.push_back(nonTerminal);
		}
		string RHS;
		int len=line.length();
		while(linePos!=len)
		{
			RHS=getRHS(line,linePos);
			grammar[nonTerminal].push_back(RHS);
		}
		/*
		for(int j=0;j<grammar[nonTerminal].size();j++)
		{
			if(str_match(nonTerminal,grammar[nonTerminal][j]))
			{
				grammar[nonTerminal+"_dash"].push_back()
			}
		}
		*/
	}
	indirect_recursion();
	//direct_recursion(0);
	//cout << nonTerminals_vector.size()<<endl;
	
	for(int i=0;i<nonTerminals_vector.size();i++)
	{
		cout <<nonTerminals_vector[i]<<"\t : \t";
		int len=grammar[nonTerminals_vector[i]].size();
		//cout << len<<endl;
		for(int j=0;j<len;j++)
		{
			cout << grammar[nonTerminals_vector[i]][j]<<"\t|\t";
		}
		cout << endl;
	}
	//exit(1);
	fp.close();
}
