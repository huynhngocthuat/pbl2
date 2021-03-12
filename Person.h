#include<iostream>
#include<string>
using namespace std;

class Person {
protected:
    string Ho_Ten;
    int Nam_Sinh;
    string Que_Quan;
    string Dan_Toc;
    string Bao_Hiem;
public:
    Person(string, int, string, string, string);
    virtual ~Person();
    string GetHoTen();
};