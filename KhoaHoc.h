#pragma once
#include<iostream>
#include<string>
using namespace std;

class KhoaHoc {
private:
    string maKhoaHoc;
    int namBatDau;
    int namKetThuc;
public:
    KhoaHoc(string = "", int = 0, int = 0);
    ~KhoaHoc();
    string getMaKhoaHoc();
};