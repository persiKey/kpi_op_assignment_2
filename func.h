#pragma once
#include "structs.h"
#include <vector>
#include <string>

using std::string;
using std::vector;

void GetFileLocations(vector<string>& file_paths);
void ProcedeFiles(const vector<string>& file_paths, vector<STUD_TABLE_DATA>& Table);

void PrintTable(const vector<STUD_TABLE_DATA>& Table);

void SortTable(vector<STUD_TABLE_DATA>& Table);

void GetBudgetRating(const vector<STUD_TABLE_DATA>& Table, vector<STUD_TABLE_DATA>& BudgetTable);

void PrintTableToFile(const vector<STUD_TABLE_DATA>& Table, int persents= PESENT_OF_SCHOLARHSIP);

float GetMinScholarGPA(const vector<STUD_TABLE_DATA>& Table);