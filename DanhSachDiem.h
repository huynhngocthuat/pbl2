#pragma once
#include "Diem.h"
class DanhSachDiem {
private:
    Diem* data;
    int n;
public:
    DanhSachDiem();
    ~DanhSachDiem();
    const DanhSachDiem& operator =(const DanhSachDiem&);
    friend ostream& operator<<(ostream&, const DanhSachDiem&);
    Diem& operator[](const int&);
    int Getn();
    int IndexOf(string);
    void Clear();
    void Add(const Diem&);
    DanhSachDiem Search(string);
    void Update();
    void Remove(string);
    float TinhTB();

};
