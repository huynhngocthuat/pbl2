#include "LopHocPhan.h"

LopHocPhan::LopHocPhan(string MaLopHocPhan, string MaMH, string Giang_Vien, int Thu, string TietHoc_Gio, string PhongHoc, string TuanHoc)
        : MaLopHocPhan(MaLopHocPhan), MaMH(MaMH), Giang_Vien(Giang_Vien), Thu(Thu), TietHoc_Gio(TietHoc_Gio), PhongHoc(PhongHoc), TuanHoc(TuanHoc)
{}

LopHocPhan::~LopHocPhan() 
{
   
}

const LopHocPhan& LopHocPhan::operator=(const LopHocPhan& lhp)
{
    this->MaLopHocPhan = lhp.MaLopHocPhan;
    this->MaMH = lhp.MaMH;
    this->Giang_Vien = lhp.Giang_Vien;
    this->Thu = lhp.Thu;
    this->TietHoc_Gio = lhp.TietHoc_Gio;
    this->PhongHoc = lhp.PhongHoc;
    this->TuanHoc = lhp.TuanHoc;
    return (*this);
}

ostream& operator<<(ostream& o, const LopHocPhan& lopHocPhan) {
    o << setw(15) << lopHocPhan.MaLopHocPhan << setw(30) << lopHocPhan.Giang_Vien << setw(10) << lopHocPhan.Thu << setw(15) << lopHocPhan.TietHoc_Gio
        << setw(15) << lopHocPhan.PhongHoc << setw(15) << lopHocPhan.TuanHoc << endl;
    return o;
}

string LopHocPhan::getMaLopHp() {
    return this->MaLopHocPhan;
}

string LopHocPhan::getMaMH() {
    return this->MaMH;
}

string LopHocPhan::getTenGiangVien() {
    return this->Giang_Vien;
}
LopHocPhan& LopHocPhan::Update(LopHocPhan lhp)
{
    this->MaLopHocPhan = lhp.MaLopHocPhan;
    this->MaMH = lhp.MaMH;
    this->Giang_Vien = lhp.Giang_Vien;
    this->Thu = lhp.Thu;
    this->TietHoc_Gio = lhp.TietHoc_Gio;
    this->PhongHoc = lhp.PhongHoc;
    this->TuanHoc = lhp.TuanHoc;
    return (*this);
}