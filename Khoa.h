#pragma once
#include<iostream>
#include<string>
using namespace std;

class Khoa {
private:
    string maKhoa;
    string tenKhoa;
    int namThanhLap;
public:
    Khoa(string = "", string = "", int = 0);
    ~Khoa();

};
