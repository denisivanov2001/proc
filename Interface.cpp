#include "Interface.h"



void pushBack(list* oldList, element* newElement)
{
    newElement->prev = oldList->tail;
    newElement->next = nullptr;
    if (oldList->size)
    {
        oldList->tail->next = newElement;
        oldList->tail = newElement;
    }
    else
    {
        oldList->tail = newElement;
        oldList->head = newElement;
    }
    oldList->size++;
    return ;
}

void pushFirst(list* oldList, element* newElement)
{
    newElement->next = oldList->head;
    newElement->prev = nullptr;
    oldList->head->prev = newElement;
    oldList->size++;
    return;
}

void init(list* curList)
{
    
    curList->head = nullptr;
    curList->tail = nullptr;
    return ;
}

void clear(list* oldList)
{
    auto curEl = oldList->head;
    while (curEl!=nullptr)
    {
        oldList->head->prev = nullptr;
        oldList->head = oldList->head->next;
        
        
       delete curEl;
        curEl = oldList->head;
    }
    oldList->size = 0;
}
void readList(list*& readList, std::ifstream& stream)
{
	while (!stream.eof())
	{
		element* newElement = new element;
		if (readElement(newElement, stream))
		{
			pushBack(readList, newElement);
		}
	}
}

int readElement(element*& readElement, std::ifstream& stream)
{
	readElement->itFigure = new figure;
	char type;
	stream >> type;
	switch (type)
	{
	case 'r':
	{
		readElement->itFigure = (figure*)readRectangle(stream);
		stream >> ((rectangle*)readElement->itFigure)->color;
		return 1;
	}
	case 'c':
	{
		readElement->itFigure = (figure*)readCircle(stream);
		stream >> ((circle*)readElement->itFigure)->color;
		return 1;
	}
	default:
		break;
	}
	return 0;
}

rectangle* readRectangle(std::ifstream& stream)
{
	rectangle* newRect = new rectangle();
	newRect->key = rect;
	stream >> newRect->leftUp[0];
	stream >> newRect->leftUp[1];
	stream >> newRect->rightDown[0];
	stream >> newRect->rightDown[1];
	return newRect;
}

circle* readCircle(std::ifstream& stream)
{
	circle* newCir = new circle();
	newCir->key = cir;
	stream >> newCir->center[0];
	stream >> newCir->center[1];
	stream >> newCir->radius;
	return newCir;
}

void writeList(list*& writeList, std::ofstream& stream)
{
	stream << "Num " << writeList->size << "\n";
	auto curEl = writeList->head;
	for (int i = 0; i < writeList->size; i++)
	{
		stream << i << ": ";
		writeElement(curEl, stream);
		curEl = curEl->next;
	}
}

void writeElement(element*& writeElement, std::ofstream& stream)
{
	switch (writeElement->itFigure->key)
	{
	case rect:
	{
		writeRectangle((rectangle*)writeElement->itFigure, stream);
		break;
	}
	case cir:
	{
		writeCircle((circle*)writeElement->itFigure, stream);
		break;
	}
	default:
		break;
	}
	stream << "Perimetr " << perimetr(writeElement)<<"\n";
	return;
}

void writeRectangle(rectangle* rect, std::ofstream& stream)
{
	stream << "Left up x: " << rect->leftUp[0] << " Left up y: " << rect->leftUp[1] << "\n";
	stream << "Right down x: " << rect->rightDown[0] << " Right down y: " << rect->rightDown[1] << "\n";
	stream << "Color " << rect->color << "\n";
	return;
}

void writeCircle(circle* cir, std::ofstream& stream)
{
	stream << "Center: " << cir->center[0] << " " << cir->center[1] << "\n";
	stream << "Radius " << cir->radius << "\n";
	stream << "Color " << cir->color << "\n";
}

double perimetr(element* el)
{
	switch (el->itFigure->key)
	{
	case rect:
	{
		return (((rectangle*)el->itFigure)->leftUp[0] - ((rectangle*)el->itFigure)->rightDown[0]) *
			(((rectangle*)el->itFigure)->rightDown[1] - ((rectangle*)el->itFigure)->leftUp[1]);
		
	}
	case cir:
	{
		return 2.0 * M_PI * (double)((circle*)el->itFigure)->radius;
	}
	default:
		break;
	}
	return -1;
}

int equ(element* first, element* second)
{
	if (perimetr(first) > perimetr(second))
		return 1;
	else if (perimetr(first) < perimetr(second))
		return -1;
	else
		return 0;
}

list* sort(list* sortingList)
{
	list* newList = new list;
	init(newList);
while(sortingList->size!=0)
	{
		element* min = sortingList->head;
		element* cur = sortingList->head;
		while (cur!=nullptr)
		{
			if (equ(cur, min) == -1)
				min = cur;
			cur = cur->next;
		}
		if(min->prev!=nullptr)
		min->prev->next = min->next;
		if(min->next!=nullptr)
		min->next->prev = min->prev;
		if (min == sortingList->head)
			sortingList->head = min->next;
		if (min == sortingList->tail)
			sortingList->tail = min->prev;
		sortingList->size--;
		pushBack(newList, min);
	}
	return newList;
}
