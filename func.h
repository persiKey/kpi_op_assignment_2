#pragma once
#include "structs.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

void GetFileLocations(vector<string>& file_paths);
void ProcedeFiles(vector<string>& names, vector<STUD_TABLE_DATA>& Table);
