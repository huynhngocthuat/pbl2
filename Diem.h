#pragma once
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Diem 
{
  //  friend class DBHelper;
private:
    string MaMH;
    int Lan_Thi;
    float Diem_Thi;
public:
    Diem(string = "", int = 1, float = 0);
    ~Diem();
    string GetMaMH();
    int GetLan_Thi();
    float GetDiem_Thi();
    friend ostream& operator<<(ostream&, const Diem&);
    friend istream& operator>>(istream&, Diem&);
    Diem& Update(int, float);

};