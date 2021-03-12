#pragma once
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class LopHocPhan 
{
private:
    string MaLopHocPhan;
    string MaMH;
    string Giang_Vien;
    int Thu;
    string TietHoc_Gio;
    string PhongHoc;
    string TuanHoc;
public:
    LopHocPhan(string = "", string = "", string = "", int = 2, string = "", string = "", string = "");
    ~LopHocPhan();
    const LopHocPhan& operator=(const LopHocPhan&);
    friend ostream& operator<<(ostream&, const LopHocPhan&);
    string getMaLopHp();
    string getMaMH();
    string getTenGiangVien();
    LopHocPhan& Update(LopHocPhan);
};