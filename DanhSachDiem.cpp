#include "DanhSachDiem.h"

DanhSachDiem::DanhSachDiem() 
{
    this->n = 0;
    this->data = nullptr;
}

DanhSachDiem::~DanhSachDiem() 
{
    delete[] this->data;
}

const DanhSachDiem& DanhSachDiem::operator=(const DanhSachDiem& list) 
{
    this->n = list.n;
    this->data = new Diem[this->n];

    for (int i = 0; i < this->n; i++) {
        (*this)[i] = *(list.data + i);
    }
    return *this;
}

ostream& operator<<(ostream& o, const DanhSachDiem& db) 
{
    cout << setw(5) << "STT" << setw(15) << "MA MON HOC" << setw(10) << "LAN THI" << setw(12) << "DIEM SO" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.data + i) << endl;
    }
    return o;
}

Diem& DanhSachDiem::operator[](const int& k) 
{
    return *(this->data + k);
}

int DanhSachDiem::Getn()
{
    return this->n;
}
void DanhSachDiem::Clear()
{
    this->n = 0;
    delete[] this->data;
}
void DanhSachDiem::Add(const Diem& newDiem) 
{
    if (this->n == 0) {
        this->data = new Diem[this->n + 1];
        this->data[this->n] = newDiem;
    }
    else {
        DanhSachDiem temp;
        temp.data = new Diem[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.data + i) = *(this->data + i);
        }
        delete[] this->data;
        this->data = new Diem[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->data + j) = *(temp.data + j);
        }
        *(this->data + this->n) = newDiem;
    }
    this->n++;
}

int DanhSachDiem::IndexOf(string maMh) 
{
    for (int i = 0; i < this->n; i++) {
        if (maMh == (*this)[i].GetMaMH()) {
            return i;
        }
    }
    return -1;
}

void DanhSachDiem::Remove(string MaMH) 
{
    int k = this->IndexOf(MaMH);
    DanhSachDiem temp;
    temp.data = new Diem[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.data + i) = *(this->data + i);
    }
    delete[] this->data;
    this->data = new Diem[this->n - 1];
    for (int i = 0; i < k; i++) {
        *(this->data + i) = *(temp.data + i);
    }
    for (int i = k; i < (this->n - 1); i++) {
        *(this->data + i) = *(temp.data + i + 1);
    }
    this->n--;
}

DanhSachDiem DanhSachDiem::Search(string MaMH) 
{
    DanhSachDiem dbSearch;
    for (int i = 0; i < this->n; i++) {
        if (MaMH == (*this)[i].GetMaMH()) {
            dbSearch.Add((*this)[i]);
        }
    }
    return dbSearch;
}

void DanhSachDiem::Update() 
{
    string MaMH;
    int Lan_Thi;
    float Diem_Thi;
    cout << "Nhap ma mon hoc can update: "; cin >> MaMH;
    cout << "Nhap lan thi can update: "; cin >> Lan_Thi;
    cout << "Nhap diem: "; cin >> Diem_Thi;


    int k = this->IndexOf(MaMH);

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(Lan_Thi,Diem_Thi);
            break;
        }
    }
}

float DanhSachDiem::TinhTB() 
{
    int check[100];
    for (int i = 0; i < this->n; i++) {
        check[i] = 1;
    }
    DanhSachDiem temp;
    float sum = 0;

    for (int i = 0; i < this->n; i++) {
        if (check[i] == 1) {
            DanhSachDiem dbSearch = this->Search(((*this)[i]).GetMaMH());
            if (dbSearch.n == 2) {
                Diem data = dbSearch[1];
                temp.Add(data);
                check[this->IndexOf(data.GetMaMH())] = 0;
            }
            else {
                temp.Add(dbSearch[0]);
            }
        }
    }
    for (int i = 0; i < temp.n; i++) {
        //sum += temp[i].GetDiem_Thi();
        cout << temp[i].GetDiem_Thi();
    }
    return 1.0;
}