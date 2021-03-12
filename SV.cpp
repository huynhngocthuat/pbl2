#include "SV.h"
#include <iomanip>

SV::SV(string MaSV, string Ho_Ten, string Khoa, int Nam_Sinh, string Que_Quan, string Dan_Toc, string Ma_Lop, string Bao_Hiem)
	: MaSV(MaSV), Khoa(Khoa), Person(Ho_Ten, Nam_Sinh, Que_Quan, Dan_Toc,Bao_Hiem), Ma_Lop(Ma_Lop)
{
}
SV::~SV()
{
}
string SV::GetMaSV()
{
	return this->MaSV;
}
string SV::GetTen()
{
	return this->Ho_Ten;
}
ostream& operator<<(ostream& o, const SV& sv)
{
	cout << setw(15) << sv.MaSV <<  setw(20) << sv.Ho_Ten << setw(15) << sv.Nam_Sinh << setw(15) << sv.Que_Quan
		  << setw(15) << sv.Dan_Toc << setw(15) << sv.Khoa << setw(15) << sv.Ma_Lop << setw(15) << sv.Bao_Hiem << endl;
	return o;
}
const SV& SV::operator=(const SV& sv)
{
	this->MaSV = sv.MaSV;
	this->Ho_Ten = sv.Ho_Ten;
	this->Nam_Sinh = sv.Nam_Sinh;
	this->Que_Quan = sv.Que_Quan;
	this->Dan_Toc = sv.Dan_Toc;
	this->Khoa = sv.Khoa;
	this->Ma_Lop = sv.Ma_Lop;
	this->Bao_Hiem = sv.Bao_Hiem;
	return (*this);
}
SV& SV::Update(string Ho_Ten, string Ma_Khoa, int Nam_Sinh, string Que_Quan, string Dan_Toc, string Ma_Lop, string Bao_Hiem)
{
	this->Ho_Ten = Ho_Ten;
	this->Khoa = Ma_Khoa;
	this->Nam_Sinh = Nam_Sinh;
	this->Que_Quan = Que_Quan;
	this->Dan_Toc = Dan_Toc;
	this->Ma_Lop = Ma_Lop;
	this->Bao_Hiem = Bao_Hiem;
	return *this;
}
DanhSachDiem& SV::GetDanhSachDiem() 
{
	return this->ListDiem;
}
TKB& SV::GetTKB() {
	return this->ListTKB;
}