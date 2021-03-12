#pragma once
#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "DanhSachDiem.h"
#include "TKB.h"
#include "Person.h"
using namespace std;
class SV : public Person
{
	friend class DBHelper;
private:
	string MaSV;
	string Khoa;
	string Ma_Lop;
	DanhSachDiem ListDiem;
	TKB ListTKB;
public:
	SV(string = "", string = "", string = "CNTT", int = 2001, string = "", string = "", string = "", string = "");
	~SV();
	string GetMaSV();
	string GetTen();
	DanhSachDiem& GetDanhSachDiem();
	TKB& GetTKB();
	friend ostream& operator<<(ostream&, const SV&);
	const SV& operator=(const SV&);
	SV& Update(string,string, int, string, string, string, string);
};