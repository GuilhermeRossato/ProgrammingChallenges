// UriChallenges.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "Glue.h"
#include <iostream>
#include <fstream>
#include <chrono>

#define USE_INPUT_FILE	true
#define USE_OUTPUT_FILE	true
#define INPUT_FILENAME	"input.txt"
#define OUTPUT_FILENAME	"output.txt"
#define CURRENT_FUNCTION mainObi2012();

using namespace std;

int main()
{
	ifstream *in;
	ofstream *out;
	streambuf *cinbuf = std::cin.rdbuf();
	streambuf *coutbuf = std::cout.rdbuf();
	if (USE_INPUT_FILE) {
		in = new ifstream(INPUT_FILENAME);
		if (!in->is_open()) {
			cout << "Error: Unable to open input file" << endl << "Filename: " << INPUT_FILENAME;
			return 0;
		}
		cin.rdbuf(in->rdbuf());
	}
	if (USE_OUTPUT_FILE) {
		out = new ofstream(OUTPUT_FILENAME);
		if (!out->is_open()) {
			cout << "Error: Unable to open output file" << endl << "Filename: " << OUTPUT_FILENAME;
			return 0;
		}
		cout.rdbuf(out->rdbuf());
	}

	auto start = chrono::high_resolution_clock::now();
	CURRENT_FUNCTION;
	auto finish = chrono::high_resolution_clock::now();
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);
	if (USE_INPUT_FILE)
		in->close();
	if (USE_OUTPUT_FILE)
		out->close();
	cout << (chrono::duration_cast<chrono::nanoseconds>(finish-start).count())-1330 << "ns" << endl;
	return 0;
}