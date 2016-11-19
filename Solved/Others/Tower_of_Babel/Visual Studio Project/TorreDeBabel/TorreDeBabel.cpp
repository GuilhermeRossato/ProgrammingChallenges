#include <iostream>
#include <fstream>
#include <chrono>
#include "stdafx.h"
#pragma region DEFINITIONS
#ifndef NULL
#define NULL 0
#endif // !NULL

struct Elevator {
	unsigned int base;
	unsigned int step;
};

struct Trail {
	unsigned int floor;
	Trail * past;
};

#pragma endregion DEFINITIONS
#pragma region TREE_NODE

////////////////////////////////////////
// BINARY TREE OF UNIQUE unsigned int //
////////////////////////////////////////

struct TreeNode {
	TreeNode * left;
	TreeNode * right;
	unsigned int id;
};

TreeNode * new_TreeNode();
void delete_TreeNode(TreeNode *);

TreeNode * Tree_create(unsigned int id) {
	TreeNode * root = new_TreeNode();
	root->id = id;
	root->left = NULL;
	root->right = NULL;
	return root;
}

TreeNode * Tree_add(TreeNode * root, unsigned int id) {
	if (root == NULL) {
		return Tree_create(id);
	} else if (root->id > id) {
		if (root->left != NULL)
			return Tree_add(root->left, id);
		else {
			TreeNode * o = Tree_create(id);
			root->left = o;
			return o;
		}
	} else if (root->id < id) {
		if (root->right != NULL)
			return Tree_add(root->right, id);
		else {
			TreeNode * o = Tree_create(id);
			root->right = o;
			return o;
		}
	} else
		return root; // No duplicates
}

TreeNode * Tree_add_LOOP(TreeNode * root, unsigned int id) {
	while (true) {
		if (root == NULL) {
			return Tree_create(id);
		} else if (root->id > id) {
			if (root->left != NULL)
				root = root->left;
			else {
				TreeNode * fill = Tree_create(id);
				root->left = fill;
				return fill;
			}
		} else if (root->id < id) {
			if (root->right != NULL)
				root = root->right;
			else {
				TreeNode * fill = Tree_create(id);
				root->right = fill;
				return fill;
			}
		} else
			return root;
	}
}

// Returns what it found or the leaf before it.
TreeNode * Tree_smartSearch_REC(TreeNode * root, unsigned int id) {
	if (root == NULL)
		return NULL;
	else if (root->id < id)
		if (root->right == NULL)
			return root;
		else
			return Tree_smartSearch_REC(root->right, id);
	else if (root->id > id)
		if (root->left == NULL)
			return root;
		else
			return Tree_smartSearch_REC(root->left, id);
	else
		return root;
}

TreeNode * Tree_smartSearch_LOOP(TreeNode * root, unsigned int id) {
	while (true) {
		if (root->id < id)
			if (root->right == NULL)
				return root;
			else
				root = root->right;
		else if (root->id > id)
			if (root->left == NULL)
				return root;
			else
				root = root->left;
		else
			return root;
	}
}

void Tree_destroy_REC(TreeNode * root) {
	if (root != NULL) {
		Tree_destroy_REC(root->left);
		Tree_destroy_REC(root->right);
		delete_TreeNode(root);
	}
}

#define TREE_DEPTH_GUESS	10

extern unsigned int memUsage;
void updatePeak();

void Tree_destroy_LOOP(TreeNode * root) {
	TreeNode * head = root;
	TreeNode * * past = new TreeNode *[TREE_DEPTH_GUESS];
	memUsage += TREE_DEPTH_GUESS*sizeof(TreeNode *);
	updatePeak();
	for (int i = 0; i < TREE_DEPTH_GUESS; i++)
		past[i] = NULL;
	bool hasLeft, hasRight;
	while (true) {
		if (head == NULL) {
			if (past[0] == NULL) {
				if (root == NULL)
					break;
				else
					head = root; // Lost Trail, restart
			} else {
				head = past[0];
				for (int i = 0; i < TREE_DEPTH_GUESS-1; i++)
					past[i] = past[i+1];
				past[TREE_DEPTH_GUESS - 1] = NULL;
			}
		} else {
			hasLeft = (head->left != NULL);
			hasRight = (head->right != NULL);
			if (!hasLeft && !hasRight) {
				if (head == root) {
					delete_TreeNode(head);
					break;
				} else {
					head = NULL;
				}
			} else if (!hasLeft && hasRight) {
				if (head->right->left == NULL && head->right->right == NULL) {
					delete_TreeNode(head->right);
					head->right = NULL;
				} else {
					for (int i = TREE_DEPTH_GUESS-1; i > 0; i--)
						past[i] = past[i-1];
					past[0] = head;
					head = head->right;
				}
			} else if (hasLeft && !hasRight) {
				if (head->left->left == NULL && head->left->right == NULL) {
					delete_TreeNode(head->left);
					head->left = NULL;
				} else {
					for (int i = TREE_DEPTH_GUESS - 1; i > 0; i--)
						past[i] = past[i - 1];
					past[0] = head;
					head = head->left;
				}
			} else {
				if (head->left->left == NULL && head->left->right == NULL) {
					delete_TreeNode(head->left);
					head->left = NULL;
				} else if (head->right->left == NULL && head->right->right == NULL) {
					delete_TreeNode(head->right);
					head->right = NULL;
				} else {
					for (int i = TREE_DEPTH_GUESS - 1; i > 0; i--)
						past[i] = past[i - 1];
					past[0] = head;
					head = head->left;
				}
			}
		}
	}
	memUsage -= TREE_DEPTH_GUESS*sizeof(TreeNode *);
}
#pragma endregion TREE_NODE
#pragma region MEMORY_HANDLER
unsigned int memUsage = 0;
unsigned int peak = 0;
unsigned int getAllocatedBytes() {
	return memUsage;
}
void updatePeak() {
	if (memUsage > peak)
		peak = memUsage;
}
#pragma region INT
unsigned int * new_int() {
	memUsage += sizeof(unsigned int);
	updatePeak();
	return new unsigned int;
}
unsigned int * new_int(unsigned int quantity) {
	memUsage += quantity*sizeof(unsigned int);
	updatePeak();
	return new unsigned int[quantity];
}
void delete_int(unsigned int * object) {
	memUsage -= sizeof(unsigned int);
	delete[] object;
}
void delete_int(unsigned int * object, unsigned int size) {
	memUsage -= size*sizeof(unsigned int);
	delete[] object;
}
#pragma endregion
#pragma region TREE_NODE
TreeNode * new_TreeNode() {
	memUsage += sizeof(TreeNode);
	updatePeak();
	return new TreeNode;
}
void delete_TreeNode(TreeNode * object) {
	memUsage -= sizeof(TreeNode);
	delete[] object;
}
#pragma endregion
#pragma region ELEVATOR
Elevator * new_elevator(unsigned int quantity) {
	memUsage += quantity*sizeof(Elevator);
	updatePeak();
	return new Elevator[quantity];
}
void delete_elevator(Elevator * object, unsigned int quantity) {
	memUsage -= quantity*sizeof(Elevator);
	delete[] object;
}
#pragma endregion
#pragma region TRAIL
Trail * new_Trail(Trail * past, unsigned int floor) {
	memUsage += sizeof(Trail);
	updatePeak();
	Trail * n = new Trail;
	n->past = past;
	n->floor = floor;
	return n;
}
void delete_Trail_All(Trail * object) {
	while (object != NULL) {
		memUsage -= sizeof(Trail);
		Trail * past = object->past;
		delete[] object;
		object = past;
	}
}
void delete_Trail_One(Trail * object) {
	if (object != NULL) {
		memUsage -= sizeof(Trail);
		delete[] object;
	}
}
#pragma endregion

#pragma endregion MEMORY HANDLER

#define	SHOW_FINAL_PATH			true
#define SHOW_VISITED			false
#define SHOW_TRAIL				false
#define SHOW_DELETION			false
#define TRY_USING_NANOSECONDS	true
#define SHOW_EVERY				100000
#define MAX_MEMORY_USAGE		200000
#define SEARCH_FUNCTION			search_LOOP
#define TREE_SEARCH_FUNCTION	Tree_smartSearch_LOOP
#define TREE_ADD_FUNCTION		Tree_add_LOOP
#define TREE_DESTROY_FUNCTION	Tree_destroy_LOOP

unsigned int maxHeight, elevCount, floorOrigin, floorTarget;

Elevator * elevators = NULL;
TreeNode * visited = NULL;

using namespace std;

unsigned int myAbs(int value) {
	if (value >= 0)
		return value;
	return -value;
}

unsigned int getUnvisitedFloor(unsigned int at) {
	TreeNode * result;
	TreeNode * result_smallest = NULL;
	unsigned int closestFloor = 0;
	for (unsigned int i = 0; i < elevCount; i++) {
		unsigned int base = elevators[i].base;
		unsigned int step = elevators[i].step;
		unsigned int up = at + step;
		unsigned int down = at - step;
		unsigned int up_distance = myAbs(up - floorTarget);
		unsigned int down_distance = myAbs(down - floorTarget);

		if (base == at && up < maxHeight) {
			result = Tree_smartSearch_LOOP(visited, up);
			if (result->id != up) {
				if ((up_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
					closestFloor = up;
					result_smallest = result;
				}
			}
		} else if ((at > base) && ((at - base) % step == 0)) { // Elevator reaches
			if (up < maxHeight) {
				if (up_distance > down_distance) {
					result = Tree_smartSearch_LOOP(visited, down);
					if (result->id != down) {
						if ((down_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
							closestFloor = down;
							result_smallest = result;
						}
					} else {
						result = Tree_smartSearch_LOOP(visited, up);
						if (result->id != up) {
							if ((up_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
								closestFloor = up;
								result_smallest = result;
							}
						}
					}
				} else {
					result = Tree_smartSearch_LOOP(visited, up);
					if (result->id != up) {
						if ((up_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
							closestFloor = up;
							result_smallest = result;
						}
					} else {
						result = Tree_smartSearch_LOOP(visited, down);
						if (result->id != down) {
							if ((down_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
								closestFloor = down;
								result_smallest = result;
							}
						}
					}
				}
			} else {
				result = Tree_smartSearch_LOOP(visited, down);
				if (result->id != down) {
					if ((down_distance < myAbs(closestFloor - floorTarget)) || (result_smallest == NULL)) {
						closestFloor = down;
						result_smallest = result;
					}
				}
			}
		}
	}
	if (result_smallest == NULL)
		return -1;
	else {
		Tree_add_LOOP(result_smallest, closestFloor);
		return closestFloor;
	}
}

void percorrePrint(TreeNode * node) {
	if (node != NULL) {
		percorrePrint(node->left);
		cout << node->id << " ";
		percorrePrint(node->right);
	}
}

void showVisitedSoFar() {
	cout << "Visited: ";
	percorrePrint(visited);
	cout << endl;
}

bool search_REC(unsigned int at) {
	if (at == floorTarget)
		return true;
	unsigned int next = getUnvisitedFloor(at);
	while (next != -1) {
		if (SHOW_VISITED) {
			system("cls");
			showVisitedSoFar();
		}
		if (search_REC(next)) {
			if (SHOW_FINAL_PATH)
				cout << next << " < ";
			if (at == floorOrigin)
				cout << at << endl;
			return true;
		} else
			next = getUnvisitedFloor(at);
		if (peak >= MAX_MEMORY_USAGE) {
			if (at == floorOrigin)
				cout << "Educated stop" << endl;
			break;
		}
	}
	return false;
}

// Only useful if: SHOW_TRAIL and SEARCH_LOOP
void showTrailStep(Trail * node) {
	while (node != NULL) {
		if (node->past == NULL)
			cout << node->floor;
		else
			cout << node->floor << " < ";
		node = node->past;
	}
}

void showTrail(char * title, Trail * node) {
	cout << title;
	showTrailStep(node);
	cout << endl;
}

int show_count = 0;

bool search_LOOP(unsigned int start) {
	Trail * trailHead = new_Trail(NULL, start);
	while (trailHead != NULL) {
		if (SHOW_VISITED || SHOW_TRAIL) {
			show_count++;
			if (SHOW_EVERY == 1 || show_count > SHOW_EVERY) {
				show_count = 0;
				system("cls");
				if (SHOW_VISITED)
					showVisitedSoFar();
				if (SHOW_TRAIL)
					showTrail((char *)"Trail: ", trailHead);
			}
		}
		if (trailHead->floor == floorTarget) {
			//if (!SHOW_TRAIL && SHOW_FINAL_PATH)
				showTrail((char *)"Final: ", trailHead);
			delete_Trail_All(trailHead);
			return true;
		}
		unsigned int next = getUnvisitedFloor(trailHead->floor);
		if (next == -1) {
			if (peak >= MAX_MEMORY_USAGE) {
				cout << "Educated stop" << endl;
				delete_Trail_All(trailHead);
				return false;
			}
			Trail * hold = trailHead->past;
			delete_Trail_One(trailHead);
			trailHead = hold;
		} else {
			Trail * t = new_Trail(trailHead, next);
			trailHead = t;
		}
	}
	return false;
}

void solve() {
	cin >> maxHeight >> elevCount >> floorOrigin >> floorTarget;
	elevators = new_elevator(elevCount);

	for (unsigned int i = 0; i < elevCount; i++)
		cin >> elevators[i].base >> elevators[i].step;

	visited = Tree_add_LOOP(visited, floorOrigin);
	if (SEARCH_FUNCTION(floorOrigin)) {
		cout << "Path found" << endl;
	} else {
		cout << "No path found" << endl;
	}

	if (peak != memUsage)
		cout << "Finished with " << memUsage << ", Peaked at " << peak << " bytes" << endl;
	else
		cout << "Used " << memUsage << " bytes" << endl;
	TREE_DESTROY_FUNCTION(visited);
	delete_elevator(elevators, elevCount);
}

#pragma region IOFILES

#define USE_INPUT_FILE	true
#define USE_OUTPUT_FILE	false
#define INPUT_FILENAME	"input.txt"
#define OUTPUT_FILENAME	"output.txt"
#define DATA_FILENAME "data.txt"
#define CURRENT_FUNCTION solve()

void showFormatted(long long diff, const char * unit, unsigned int s, char start);

extern void solve();

int main() {
	ifstream *in;
	in = new ifstream(DATA_FILENAME);
	long long diffAnterior = 0;
	if (in->is_open()) {
		(*in) >> diffAnterior;
		in->close();
		in = NULL;
	}
	ofstream *out = NULL;
	streambuf *cinbuf = std::cin.rdbuf();
	streambuf *coutbuf = std::cout.rdbuf();
	if (USE_INPUT_FILE) {
		in = new ifstream(INPUT_FILENAME);
		if (!in->is_open()) {
			cout << "Error: Unable to open input file" << endl << "Filename: " << INPUT_FILENAME << endl;
			system("pause");
			return 0;
		}
		cin.rdbuf(in->rdbuf());
	}
	if (USE_OUTPUT_FILE) {
		out = new ofstream(OUTPUT_FILENAME);
		if (!out->is_open()) {
			cout << "Error: Unable to open output file" << endl << "Filename: " << OUTPUT_FILENAME << endl;
			system("pause");
			return 0;
		}
		cout.rdbuf(out->rdbuf());
	}

	auto start = chrono::high_resolution_clock::now();
	CURRENT_FUNCTION;
	long long diff;
	if (TRY_USING_NANOSECONDS) {
		diff = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
	} else  {
		diff = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count();
	}
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);
	if (USE_INPUT_FILE)
		in->close();
	if (USE_OUTPUT_FILE)
		out->close();

	out = new ofstream(DATA_FILENAME);
	if (out->is_open()) {
		if (diff == 0)
			(*out) << '0';
		else
			(*out) << diff;
		out->close();
	}
	cout << "----------------------------------------------" << endl;

	if (TRY_USING_NANOSECONDS) {
		if (diffAnterior != 0) {
			cout << "Last timestamp:";
			if (diffAnterior >= (long)1000000000) {
				showFormatted(diffAnterior / (long)1000000.0, (char *)"ms", 10, 48 + 3);
			} else if (diffAnterior >= (long)1000000.0) {
				showFormatted(diffAnterior / (long)1000.0, (char *)"us", 20, 48 + 6);
			} else {
				showFormatted(diffAnterior, (char *)"ns", 30, 48 + 9);
			}
		}
		cout << "This timestamp:";
		if (diff >= (long)1000000000) {
			showFormatted((long)diff / (long)1000000.0, (char *)"ms", 10, 48 + 3);
		} else if (diff >= (long)1000000.0) {
			showFormatted((long)diff / (long)1000.0, (char *)"us", 20, 48 + 6);
		} else if (diff == 0) {
			cout << "3       <1ms" << endl;
		} else {
			showFormatted((long)diff, (char *)"ns", 30, 48 + 9);
		}
	} else {
		cout << "Last timestamp:";
		if (diffAnterior == 0)
			cout << "3       <1ms" << endl;
		else
			showFormatted((long)diffAnterior, (char *)"ms", 10, 48 + 3);
		cout << "This timestamp:";
		if (diff == 0)
			cout << "3       <1ms" << endl;
		else
			showFormatted((long)diff, (char *)"ms", 10, 48 + 3);
	}
	if (getAllocatedBytes() != 0)
		cout << "Memory left unallocated:" << getAllocatedBytes() << " bytes" << endl;
	else
		cout << "No memory has been left behind" << endl;
	system("pause");
	return 0;
}
void showFormatted(long long diff, const char * unit, unsigned int s, char start) {
	char * x = new char[s + 1];
	x[s] = '\0';
	unsigned int i = 0, separatorCount = 0;
	while ((diff > 0) && (i < s)) {
		x[(s - 1) - i] = (diff % 10) + 48;
		diff = diff / 10;
		i++;
		separatorCount++;
		if (separatorCount == 3 && i != s - 1 && i + 1 < s && (diff > 0)) {
			separatorCount = 0;
			x[s - 1 - i] = '\'';
			i++;
		}
	}
	while (i + 1 < s) {
		x[s - 1 - i] = ' ';
		i++;
	}
	x[0] = start;
	cout << x << unit << endl;
	delete[] x;
}
#pragma endregion IOFILES
