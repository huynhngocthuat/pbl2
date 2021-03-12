#include "Diem.h"

Diem::Diem(string MaMH, int Lan_Thi, float Diem_Thi)
    : MaMH(MaMH), Lan_Thi(Lan_Thi), Diem_Thi(Diem_Thi)
{}

Diem::~Diem() 
{

}

float Diem::GetDiem_Thi()
{
    return this->Diem_Thi;
}

string Diem::GetMaMH() 
{
    return this->MaMH;
}

int Diem::GetLan_Thi() 
{
    return this->Lan_Thi;
}

ostream& operator<<(ostream& o, const Diem& Diem) 
{
    o << setw(15) << Diem.MaMH << setw(10) << Diem.Lan_Thi << setw(12) << Diem.Diem_Thi << endl;
    return o;
}

istream& operator>>(istream& i, Diem& Diem)
{
    cin.ignore(100, '\n');
    cout << "Nhap ma mon hoc : ";
    getline(cin, Diem.MaMH);
    cout << "Nhap lan thi : ";
    i >> Diem.Lan_Thi;
    cout << "Nhap diem thi : ";
    i >> Diem.Diem_Thi;
    return i;
}
Diem& Diem::Update(int Lan_Thi, float Diem_Thi) 
{
    this->Diem_Thi = Diem_Thi;
    this->Lan_Thi = Lan_Thi;
    return *this;
}