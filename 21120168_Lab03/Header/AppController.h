#pragma once
#define HARRIS "harris"
#define BLOB "blob"
#define DOG "dog"

#include "ImageHelper.h"
#include "HarrisDetector.h"
#include "BlobDetector.h"
#include "DoGDetector.h"
#include "ImagesMatcher.h"

#include <string.h>
#include <iostream>

using namespace std;

class AppController
{
private:

public:
	void run(int argc, char** argv);
	void showHelp();
private:
	bool checkDetector(char* detector);
};

