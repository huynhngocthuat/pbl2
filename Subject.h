#pragma once
#include<iostream>
#include<string>
using namespace std;

class Subject {
private:
    string maMh;
    string maKhoa;
    string tenMh;
public:
    Subject(string = "", string = "", string = "");
    ~Subject();
    string getMaMh();
    string getMaKhoa();
    string getTenMh();
};