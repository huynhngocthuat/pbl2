#include "Person.h"

Person::Person(string Ho_Ten, int Nam_Sinh, string Que_Quan, string Dan_Toc, string Bao_Hiem)
    :Ho_Ten(Ho_Ten), Nam_Sinh(Nam_Sinh), Que_Quan(Que_Quan), Dan_Toc(Dan_Toc), Bao_Hiem(Bao_Hiem)
{}

Person::~Person() {}

string Person::GetHoTen() {
    return this->Ho_Ten;
}