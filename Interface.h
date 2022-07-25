#pragma once
#include <string>
#include <fstream>
enum type{rect,cir,tri};
struct triangle
{
	type key;
	int first[2];
	int second[2];
	int third[2];
	std::string color;
};
struct rectangle
{
	type key;
	int leftUp[2];
	int rightDown[2];
	std::string color;
};
struct circle
{
	type key;
	int center[2];
	int radius;
	std::string color;
};
struct figure
{
	type key;
	std::string color;
};

struct element
{
	figure* itFigure;
	element* next;
	element* prev;
};


struct list
{
	int size = 0;
	element* head;
	element* tail;
};

void pushBack(list* oldList, element* newElement);
void pushFirst(list* oldList, element* newElement);
void init(list* curList);
void clear(list* oldList);
void readList(list*& readList, std::ifstream& stream);
int readElement(element*& readElement, std::ifstream& stream);
rectangle* readRectangle(std::ifstream& stream);
circle* readCircle(std::ifstream& stream);
triangle* readTriangle(std::ifstream& stream);
void writeList(list*& readList, std::ofstream& stream);
void writeElement(element*& readElement, std::ofstream& stream);
void writeRectangle(rectangle* rect, std::ofstream& stream);
void writeCircle(circle* cir, std::ofstream& stream);
void writeTriangle(triangle* tri, std::ofstream& stream);
