#include <iostream>
#include "graph.h"
using namespace std;

int main() 
{
	Graph<int,int,false> graph = Graph<int,int,false>();
	for(int i = 0; i < 10; ++i) {
		graph.add(i);
	}
	for(int i = 0; i < 9; ++i) {
		graph.add(i,i+1,i+2);
	}
	graph.print();
	
	
	
	return 0;
}
