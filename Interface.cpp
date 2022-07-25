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

void writeRect(list*& writeList, std::ofstream& stream)
{
	
	auto curEl = writeList->head;
	for (int i = 0; i < writeList->size; i++)
	{
		if(curEl->itFigure->key==rect)
		writeElement(curEl, stream);
		curEl = curEl->next;
	}
}

void writeCir(list*& writeList, std::ofstream& stream)
{
	auto curEl = writeList->head;
	for (int i = 0; i < writeList->size; i++)
	{
		if (curEl->itFigure->key == cir)
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
