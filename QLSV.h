#pragma once
#include "SV.h"
class QLSV 
{
    friend class DBHelper;
private:
	SV* data;
	int n;
public:
	QLSV();
	~QLSV();
	friend ostream& operator<<(ostream&, const QLSV&);
    void ShowDiem();
    int GetN();
    void Clear();
    void AddSV();
    void AddDiem();
    void AddTKB(TKB);
    void Add(SV);
    void Insert(const int&);
    SV& operator[](const int&);
    int IndexOf(string);
    void Remove(string);
    void RemoveDiem();
    void RemoveTKB();
    void Search();
    void Update();
    void UpdateDiem();
    void UpdateTKB(TKB);
    void SortAZ();
    void SortDiem();
};