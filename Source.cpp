//Read Readme for instructions, Github version
//Michael Karlsson, 1601924, Ti16SPeli, Programming and algorithms, Syksy 2018 HARJOITUSTYÖ
// A* Toteutus
#include<iostream>
#include<vector>
#include<string>
#include <fstream> //read file
#include <stdio.h>
#include <stdlib.h> //abs
using namespace std;

void printMap(int *map, int w, int h) // print map to console
{
	cout << "Map width is:" << w << ", height is:" << h << endl;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			cout << map[w*y + x] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int* readFile(int &w, int &h,int *map,string Path) // Read Map file, Return map as integer array
{
	int sum = 0;
	string line;
	ifstream inFile(Path);

	if (!inFile)
	{
		cout << "Unable to open file";
		exit(1);   // call system to stop
	}

	if (inFile.is_open()) 
	{
		if (getline(inFile, line)) //read h and w
		{
			unsigned long index = line.find_first_of(",");
			w = stoi(line.substr(0, index));
			h = stoi(line.substr(index + 1));
			map = new int[w*h];
		}
		for (int y = 0; y<h; y++) { //read the map
			if (getline(inFile, line)) {
				for (int x = 0; x < w; x++) {
					map[y*w + x] = stoi(line.substr(2 * x, 1));
				}
			}
			else {
				std::cout << "Error reading file!\n";
				return map;
			}
		}
	}
	inFile.close();
	printMap(map,w,h);
	return map;
}

class Node
{
public:
	Node* pBack=nullptr; //Node thats next in queue
	Node* pFront=nullptr; //Node thats in front in queue
	
	int disTravelled; //distance travelled to get to this node
	Node* route; // previous Location, from which this node was entered
	int location; // location in map = index in map array
	int priority; //priority in queue, smallest get in front of the line =distance travelled + cost to move to node + 
	//min distance to goal = differences in x or y-coordinates, whichever is larger.

Node(int location, int weight, int travelled,int priority ,Node* prev)
	{
	route = prev;
	this->location = location;
	this->priority = priority;
	disTravelled = travelled + weight;
	}
};

class PriorityQueue
{
public:

	Node*pFirst = nullptr;
	Node*pLast = nullptr;
	int startI;
	int goalI;
	int width;
	int height;
	int goalX;
	int goalY;
	int *map;

	PriorityQueue(int startI, int goalI, int width, int height, int *map)
	{
		this->map=map;
		this->startI = startI;
		this->goalI = goalI;
		this->width = width;
		this->height = height;
		goalY= goalI / width + 1;
		goalX = goalI - width*(goalY - 1) + 1;

		enqueuePriority(startI,0,0,nullptr); // add startnode to queue 

	}

	int calculatePriority(int weight, int travelled, int location) //calculates and returns priority of node
	{

		int localY = location / width + 1;
		int localX = location - width*(localY - 1) + 1;
		// Estimate is whichever is bigger, differences in X or Y coordinates
		if (abs(localY-goalY) > abs(localX-goalX))
		{
			return  weight + travelled + abs(localY - goalY);
		}
		else
		{
			return  weight + travelled + abs(localX - goalX);
		}
	}

	bool isEmpty() //returns true if queue is empty
	{
		if (nullptr == pFirst)
			return true;
		else return false;
	}
	void enqueuePriority(int location, int weight, int travelled, Node* prev) // Queues node with priority to correct position
	{
		if (nullptr != pFirst) // See if node is already in the queue
		{
			Node *pTemp = pFirst;
			do
			{
				if (pTemp->location == location)
				{
					int priority = calculatePriority(weight, travelled, location);

					// This might not be possible to happen because it't always the same cost to move to a node
					// might happen if there is no path 
					if (priority < pTemp->priority) // Remove the node with old priority and try adding again
					{
						if (nullptr == pTemp->pBack) //Last node
						{
							pLast = pTemp->pFront;
							pTemp->pFront->pBack = nullptr;
							pTemp->pBack = nullptr;
							pTemp->pFront = nullptr;
							
							enqueuePriority(location, weight, travelled, prev);

						}
						else if (nullptr == pTemp->pFront) //First node
						{
							dequeue();
							enqueuePriority(location, weight, travelled, prev);
						}
						else //middle node
						{
							pTemp->pFront->pBack = pTemp->pBack;
							pTemp->pBack->pFront = pTemp->pFront;

							pTemp->pBack = nullptr;
							pTemp->pFront = nullptr;

							enqueuePriority(location, weight, travelled, prev);
						}

					}
					return;
				}
				pTemp = pTemp->pBack;
			} while (nullptr != pTemp);
		}
		int priority = calculatePriority(weight, travelled, location);
		Node*pNew = new Node(location,weight,travelled,priority,prev);
		//cout << "Enqueue location:" << pNew->location << endl;

		if (nullptr == pFirst) // if inserted to empty queue
		{
			pFirst = pNew;
			pLast = pNew;
		}
		else
		{
			Node*pTMP = pFirst;
			bool inserted = false;
			do 
			{
				if (pTMP->priority > pNew->priority) //Add node before pTMP
				{
					if (pTMP == pFirst) // if new node has smallest priority = presumed distance-> first in line
					{
						pNew->pBack = pFirst;
						pFirst->pFront = pNew;
						pFirst = pNew;
					}
					else
					{
						pNew->pFront = pTMP->pFront;
						pNew->pBack = pTMP;
						pNew->pFront->pBack = pNew;
						pTMP->pFront = pNew;
					}
					inserted = true;
				}
				else
				{
					pTMP = pTMP->pBack;
				}
			} while (nullptr!=pTMP && !inserted);
			if (!inserted) //Highest priority number -> add to the back of the queue
			{
				pLast->pBack = pNew;
				pNew->pBack = nullptr;
				pNew->pFront = pLast;
				pLast = pNew;
			}
		} 
	}
	Node* dequeue() //Returns first item (Node) from queue
	{
		if (nullptr == pFirst)
			return NULL;
		Node* pTmp = pFirst;
		pFirst = pFirst->pBack;

		if (nullptr != pFirst) // Error handling
		{
			pFirst->pFront = nullptr;
		}
		else
		{
			pLast = nullptr;
		}
		
		//cout << "return location:" << pTmp->location << endl;
		map[pTmp->location] = -1; // Marks node to map as visited to not to enter it again
		pTmp->pBack = nullptr;
		pTmp->pFront = nullptr;
		return pTmp;
	}

	void clear() //clears queue
	{
		while (nullptr != pFirst)
		{
			Node* pTmp = pFirst;
			pFirst = pFirst->pBack;
			delete pTmp;
		}
		pLast = nullptr;
	}
	void print() //Print queue for debugging
	{
		if (nullptr != pFirst)
		{
			Node *pTMP = pFirst;
			cout << "Queue:" << endl;
			do
			{
				cout << pTMP->location << endl;
				pTMP = pTMP->pBack;
			} while (nullptr!=pTMP);
		}
	}
	void printRoute(Node *node)
	{
		Node*pTmp = node;
		int X;
		int Y;
		int location;
		int *path = new int[width*height];
		for (int i = 0; i < width*height; i++)
		{
			path[i] = 0;
		}
		cout << "Route from goal to start is:" << endl;
		do
		{
			location = pTmp->location;
			if(location==startI)
				path[location] = 5;
			else if (location==goalI)
				path[location] = 6;
			else
				path[location] = 1;

			Y = location / width + 1;
			X = location - width*(Y - 1) + 1;
			cout << "X:" << X << ", Y:" << Y << ", Distance travelled:"<<pTmp->disTravelled << endl;

			pTmp = pTmp->route;

		} while (nullptr!=pTmp);
		printMap(path,width,height);
	}
	void AStar() // queues and dequeues nodes
	{
		Node *node = dequeue();
		if (nullptr == node) //No path to node exists
		{
			cout << "No path to node exists" << endl;
			return;
		}
		int location = node->location;

		if (location==goalI) //Found goal
		{
			cout << "goal found, distance travelled :" <<node->disTravelled <<endl;
			printRoute(node);
			return;
		}

		int Y = location / width + 1;
		int X = location - width*(Y - 1) + 1; // Different situations if node is on the edge of the map
		// Test that you stay on map and test that map value is not 0
		if (Y != 1) //Not top row
		{
			if (map[location-width]>0) //North
			{
				enqueuePriority(location - width, map[location - width], node->disTravelled, node);
			}
		}
		if (X != width && Y != 1) //Not top row or right edge
		{
			if (map[location - width+1]>0) //NorthEast
			{
				enqueuePriority(location - width + 1, map[location - width + 1], node->disTravelled, node);
			}
		}
		if (X != width) //Not right edge
		{
			if (map[location + 1]>0) //East
			{
				enqueuePriority(location + 1, map[location + 1], node->disTravelled, node);
			}
		}
		if (X != width && Y!=height) //Not right edge, not bottom edge
		{
			if (map[location + width + 1]>0) //SouthEast
			{
				enqueuePriority(location + width + 1, map[location + width + 1], node->disTravelled, node);
			}
		}
		if (Y != height) //Not bottom row
		{
			if (map[location + width]>0) //South
			{
				enqueuePriority(location + width, map[location + width], node->disTravelled, node);
			}
		}
		if (Y != height && X!=1) //Not left edge, not bottom row
		{
			if (map[location - 1 + width]>0) //SouthWest
			{
				enqueuePriority(location - 1 + width, map[location - 1 + width], node->disTravelled, node);
			}
		}
		if (X != 1) //Not left edge
		{
			if (map[location - 1]>0) //West
			{
				enqueuePriority(location - 1, map[location - 1], node->disTravelled, node);
			}
		}
		if (X != 1 && Y!=1) //Not left edge, not top row
		{
			if (map[location - 1 -width]>0) //NorthWest
			{
				enqueuePriority(location - 1 - width, map[location - 1 - width], node->disTravelled, node);
			}
		}
		AStar();
	}

};



int main()
{
	int width = 99;
	int height = 99;
	int* MapInt=new int;
	string path = "Map.txt";
	
	int goalX = -1;
	int goalY = -1;
	int startX = -1;
	int startY = -1;

	int startI;//start index in MapInt
	int goalI; //goal index in MapInt
	MapInt = readFile(width, height, MapInt, path);


	
	do // Ask start and goal
	{
		cout << "Give start x:";
		cin >> startX;
		cout << "Give start y:";
		cin >> startY;
		cout << "Give goal x:";
		cin >> goalX;
		cout << "Give goal y:";
		cin >> goalY;
		if (!(startX > 0 && startX <= width && goalX > 0 && goalX <= width && startY > 0 && startY <= height && goalY > 0 && goalY <= height))
		{
			cout << "Invalid input, read Readme file for instructions" << endl;
		}
	} while (!(startX > 0 && startX <= width && goalX > 0 && goalX <= width && startY > 0 && startY <= height && goalY > 0 && goalY <= height));
	
	//count indexes
	startI = width*(startY - 1) + (startX - 1);
	goalI = width*(goalY - 1) + (goalX - 1);

	PriorityQueue PQ(startI,goalI,width,height,MapInt);
	PQ.AStar();

	//PQ.print(); //Debuging
	PQ.clear();
	cout << "FINISHED" << endl;
	return 0;
}