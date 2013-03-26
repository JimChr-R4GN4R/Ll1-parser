#include "header.h"
using namespace std;

int main()
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
	return 0;
}
