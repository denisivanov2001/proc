#include <iostream>
#include <fstream>
#include "Interface.h"
using namespace std;
int main()
{
	ifstream read;
	ofstream write;
	read.open("1.txt");
	write.open("2.txt");
	list* clientList=new list;
	init(clientList);
	readList(clientList, read);
	write << "List:\n";
	writeList(clientList, write);
	write << "Rectangle:\n";
	writeRect(clientList, write);
	write << "Circle:\n";
	writeCir(clientList, write);
	write << "Triangle:\n";
	writeTri(clientList, write);
	write << "Delete list:\n";
	clear(clientList);
	writeList(clientList, write);
	read.close();
	write.close();
	return 1;
}