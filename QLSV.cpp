#include "QLSV.h"
#include <iostream>
using namespace std;
string tachten(string Ho_Ten, int k) {
    int count = 0;
    int temp = k;
    for (int i = Ho_Ten.length() - 1; i >= 0; i--) {
        if (Ho_Ten[i] == ' ') {
            if (temp == 1) {
                count = i;
                break;
            }
            else {
                temp -= 1;
            }
        }
    }
    string ten = "";
    for (unsigned int j = count + 1; j < Ho_Ten.length(); j++) {
        ten += Ho_Ten[j];
    }
    return ten;
}

int CompareTen(string L, string R) {
    int count = 1;
    while (tachten(L, count) == tachten(R, count)) {
        count++;
    }
    if (tachten(L, count) <= tachten(R, count)) {
        return 1;
    }
    return 0;
}

void mergeTen(QLSV& db, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    QLSV L, R;

    for (i = 0; i < n1; i++)
        L.Add(db[l + i]);
    for (j = 0; j < n2; j++)
        R.Add(db[m + 1 + j]);

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (CompareTen(L[i].GetHoTen(), R[j].GetHoTen())) {
            db[k] = L[i];
            i++;
        }
        else {
            db[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        (db)[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        (db)[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortTen(QLSV& db, int l, int r)
{
    if (l < r)
    {
        int m = (r + l) / 2;
        mergeSortTen(db, l, m);
        mergeSortTen(db, m + 1, r);
        mergeTen(db, l, m, r);
    }
}

void merge(QLSV& db, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    QLSV L, R;

    for (i = 0; i < n1; i++)
        L.Add((db)[l + i]);
    for (j = 0; j < n2; j++)
        R.Add((db)[m + 1 + j]);

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {

        if ((L[i].GetDanhSachDiem()).TinhTB() >= (R[j].GetDanhSachDiem()).TinhTB()) {
            (db)[k] = L[i];
            i++;
        }
        else {
            (db)[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        (db)[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        (db)[k] = R[j];
        j++;
        k++;
    }
}

void mergeSortDiem(QLSV& db, int l, int r)
{
    if (l < r)
    {
        int m = (r + l) / 2;
        mergeSortDiem(db, l, m);
        mergeSortDiem(db, m + 1, r);
        merge(db, l, m, r);
    }
}

QLSV::QLSV()
{
    this->n = 0;
    this->data = nullptr;
}

QLSV::~QLSV()
{
    delete[] this->data;
}

ostream& operator<<(ostream& o, const QLSV& db) 
{
    cout << setw(5) << "STT" << setw(15) << "MA SINH VIEN" << setw(20) << "HO TEN" << setw(15) << "NAM SINH" << setw(15) 
        << "QUE QUAN" << setw(15) << "DAN TOC" << setw(15) << "KHOA" << setw(15) << "MA LOP" << setw(15) << "BHYT" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.data + i) << endl << endl;
    }
    return o;
}

void QLSV::ShowDiem() {
    cout << setw(5) << "STT" << setw(20) << "MA SINH VIEN" << setw(30) << "HO TEN" << setw(20) << "DIEM TRUNG BINH" << endl;
    for (int i = 1; i < this->n; i++) {
        //cout<<(*this)[i].getHoTen()<<"   diem trung binh:  "<<(*this)[i].getListDiem().tinhTB()<<endl;
        cout << setw(5) << i + 1 << setw(20) << (*this)[i].GetMaSV() << setw(30) << (*this)[i].GetHoTen() << setw(20) << (*this)[i].GetDanhSachDiem().TinhTB() << endl;
    }
}

SV& QLSV::operator[](const int& s)
{
    static SV error;
    return ((s >= 0) && (s < this->n)) ? *(this->data + s) : error;
}


int  QLSV::GetN()
{
    return this->n;
}
void QLSV::Clear()
{
    this->n = 0;
    delete[] this->data;
}
void QLSV::Add(SV newSv) {

    if (this->n == 0) {
        this->data = new SV[this->n + 1];
        this->data[this->n] = newSv;
    }
    else {
        QLSV temp;
        temp.data = new SV[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.data + i) = *(this->data + i);
        }
        delete[] this->data;
        this->data = new SV[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->data + j) = *(temp.data + j);
        }
        *(this->data + this->n) = newSv;
    }
    this->n++;
}
void QLSV::AddSV() {
   
    string MaSV;
    string Ho_Ten;
    int Nam_Sinh;
    string Que_Quan;
    string Dan_Toc;
    string Ma_Lop;
    string Bao_Hiem;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien: "; 
    getline(cin, MaSV);
    cout << "Nhap ten: "; 
    getline(cin, Ho_Ten);
    cout << "Nhap nam sinh: "; 
    cin >> Nam_Sinh;
    cin.ignore(100, '\n');
    cout << "Nhap que  quan: "; ; 
    getline(cin, Que_Quan);
    cout << "Nhap dan toc: "; 
    getline(cin, Dan_Toc);
    cout << "nhap ma lop: "; 
    getline(cin, Ma_Lop);
    cout << "Nhap ma BHYT: "; 
    getline(cin, Bao_Hiem);
    SV newSv(MaSV, Ho_Ten,"CNTT", Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);
    cout << newSv;
    this->Add(newSv);
}

void QLSV::AddDiem()
{

    string MaSV;
    string MaMH;
    int Lan_Thi;
    float Diem_Thi;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien : ";
    getline(cin, MaSV);
    cout << "Nhap ma mon hoc : ";
    getline(cin, MaMH);
    cout << "Nhap so lan thi : ";
    cin >> Lan_Thi;
    cout << "Nhap diem thi : ";
    cin >> Diem_Thi;
    Diem d1(MaMH, Lan_Thi, Diem_Thi);
    for (int i = 0; i < this->n; i++) {
        if (this->data[i].GetMaSV() == MaSV) {
            this->data[i].GetDanhSachDiem().Add(d1);
        }
    }
}

void QLSV::AddTKB(TKB listLHP)
{
    string MaLopHocPhan;
    string MaSV;
    LopHocPhan lhp;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien : ";
    getline(cin, MaSV);
    cout << "Nhap ma lop hoc phan : ";
    getline(cin, MaLopHocPhan);
    for (int i = 0; i < listLHP.Getn(); i++) {
        if (listLHP[i].getMaLopHp() == MaLopHocPhan) {
            lhp = listLHP[i];
        }
    }
    for (int i = 0; i < this->n; i++) {
        if (data[i].GetMaSV() == MaSV) {
            data[i].GetTKB().Add(lhp);
        }
    }
  
}

void QLSV::Insert(const int& k) {
    string MaSV;
    string HoTen;
    int Nam_Sinh;
    string Que_Quan;
    string Dan_Toc;
    string Ma_Lop;
    string Bao_Hiem;
    cout << "Nhap ma sinh vien: ";
    getline(cin, MaSV);
    cout << "Nhap ho ten sinh vien: ";
    getline(cin, HoTen);
    cout << "Nhap nam sinh: ";
    cin >> Nam_Sinh; 
    cin.ignore(100, '\n');
    cout << "Nhap que quan sinh vien: ";
    getline(cin, Que_Quan);
    cout << "Nhap dan toc: ";
    getline(cin, Dan_Toc);
    cout << "Nhap lop: ";
    getline(cin, Ma_Lop);
    cout << "Nhap so bao hiem: ";
    getline(cin, Bao_Hiem);
    SV newSv(MaSV, HoTen,"CNTT", Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);

    QLSV temp;
    temp.data = new SV[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.data + i) = *(this->data + i);
    }
    delete[] this->data;
    this->data = new SV[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->data + i) = *(temp.data + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->data + i) = *(this->data + i - 1);
        }
        *(this->data + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->data + i) = *(temp.data + i);
        }
        *(this->data + this->n) = newSv;
    }
    this->n++;
}

int QLSV::IndexOf(string maSv) {
    for (int i = 0; i < this->n; i++) {

        if (maSv == (*this)[i].GetMaSV()) {
            return i+1;
            break;
        }
    }
    return -1;
}

void QLSV::Remove(string MaSV) 
{
    int k = this->IndexOf(MaSV)-1;
    QLSV temp;
    if (k == -2) {
        cout << "Nhap sai MaSV!!!" << endl;
    }
    else {
        temp.data = new SV[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.data + i) = *(this->data + i);
        }
        delete[] this->data;
        this->data = new SV[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->data + i) = *(temp.data + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->data + i) = *(temp.data + i + 1);
        }
        this->n--;
    }
}
void QLSV::RemoveDiem()
{
    string masv;
    string mamh;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien can xoa : ";
    getline(cin, masv);
    cout << "Nhap ma mon hoc can xoa : ";
    getline(cin, mamh);
    for (int i = 0; i < this->n; i++) {
        if (this->data[i].GetMaSV() == masv) {
            this->data[i].GetDanhSachDiem().Remove(mamh);
        }
    }
}

void QLSV::RemoveTKB()
{
    string MaSV;
    string MaLopHocPhan;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien can xoa : ";
    getline(cin, MaSV);
    cout << "Nhap ma lop hoc phan can xoa : ";
    getline(cin, MaLopHocPhan);
    for (int i = 0; i < this->n; i++) {
        if (this->data[i].GetMaSV() == MaSV) {
            this->data[i].GetTKB().Remove(MaLopHocPhan);
        }
    }
}
void QLSV::Search() {
    QLSV dbSearch;
    string tenSv;
    cout << "Nhap ten sinh vien can tim: ";
    getline(cin, tenSv);
    for (int i = 0; i < this->n; i++) {
        string ten = (*this)[i].GetTen();
        if (ten.find(tenSv) != -1) {
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QLSV::Update() {
    string MaSV;
    string Ho_Ten;
    string Ma_Khoa;
    int Nam_Sinh;
    string Que_Quan;
    string Dan_Toc;
    string Ma_Lop;
    string Bao_Hiem;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien cua sinh vien can update: "; 
    getline(cin, MaSV);
    cout << "Nhap ten can sua: "; 
    getline(cin, Ho_Ten);
    cout << "Nhap nam sinh can sua: "; 
    cin >> Nam_Sinh;
    cin.ignore(100, '\n');
    cout << "Nhap que  quan  can sua: "; 
    getline(cin, Que_Quan);
    cout << "Nhap dan toc can sua: "; 
    getline(cin, Dan_Toc);
    cout << "Nhap ma khoa can sua : ";
    getline(cin, Ma_Khoa);
    cout << "Nhap ma lop can sua: "; 
    getline(cin, Ma_Lop); 
    cout << "Nhap ma BHYT can sua: "; 
    getline(cin, Bao_Hiem);
    int k = this->IndexOf(MaSV)-1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(Ho_Ten, Ma_Khoa, Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);
            break;
        }
    }
}

void QLSV::UpdateDiem()
{
    string MaSV;
    string MaMH;
    int Lan_Thi;
    float Diem_Thi;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien : ";
    getline(cin, MaSV);
    cout << "Nhap ma mon hoc : ";
    getline(cin, MaMH);
    cout << "Nhap so lan thi can thay doi : ";
    cin >> Lan_Thi;
    cout << "Nhap diem thi can thay doi : ";
    cin >> Diem_Thi;
    for (int i = 0; i < this->n; i++) {
        if (this->data[i].GetMaSV() == MaSV) {
            for (int j = 0; j < this->data[i].GetDanhSachDiem().Getn(); j++) {
                if (this->data[i].GetDanhSachDiem()[j].GetMaMH() == MaMH) {
                    this->data[i].GetDanhSachDiem()[j].Update(Lan_Thi, Diem_Thi);
                }
            }
        }
    }
    

}

void QLSV::UpdateTKB(TKB listLHP)
{
    string MaSV;
    string MaLopHocPhanold;
    string MaLopHocPhannew;
    LopHocPhan lhpnew;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien : ";
    getline(cin, MaSV);
    cout << "Nhap ma lop hoc phan cu : ";
    getline(cin, MaLopHocPhanold);
    cout << "Nhap ma lop hoc phan moi : ";
    getline(cin, MaLopHocPhannew);
    for (int k = 0; k < listLHP.Getn(); k++) {
        if (listLHP[k].getMaLopHp() == MaLopHocPhannew) {
            lhpnew = listLHP[k];
            cout << lhpnew;
        }
    }
    for (int i = 0; i < this->n; i++)
    {
        if (this->data[i].GetMaSV() == MaSV) {
            for (int j = 0; j < this->data[i].GetTKB().Getn(); j++) {
                if (this->data[i].GetTKB()[j].getMaLopHp() == MaLopHocPhanold) {
                    this->data[i].GetTKB()[j].Update(lhpnew);
                }
            }
        }
    }

}

void QLSV::SortAZ() {
    /*for (int i = 0; i < this->n - 1; i++) {
        for (int j = i + 1; j < this->n; j++) {
            int count = 1;
            string ten1 = ((*this)[i]).GetTen();
            string ten2 = ((*this)[j]).GetTen();
            while (tachten(ten1, count) == tachten(ten2, count)) {
                count++;
            }
            if (tachten(ten1, count) > tachten(ten2, count)) {
                swap((*this)[i], (*this)[j]);
            }
        }
    }*/
    mergeSortTen((*this), 0, this->n - 1);
}


void QLSV::SortDiem() {
    mergeSortDiem((*this), 0, this->n - 1);
} 

