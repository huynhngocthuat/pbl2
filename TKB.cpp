#include "TKB.h"

TKB::TKB() {
    this->n = 0;
    this->data = nullptr;
}

TKB::~TKB() 
{
    delete[] this->data;

}

int TKB::Getn()
{
    return this->n;
}
LopHocPhan& TKB::operator[](int i) {
    return *(this->data + i);
}

ostream& operator<<(ostream& o, const TKB& tkb) {
    cout << setw(5) << "STT" << setw(15) << "MA LOP" << setw(30) << "TEN GIANG VIEN" << setw(10) << "THU" << setw(15) << "TIET HOC" << setw(15) << "PHONG HOC" << setw(15) << "TUAN" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < tkb.n; i++) {
        o << setw(5) << i + 1 << *(tkb.data + i) << endl;
    }
    return o;
}

int TKB::IndexOf(string maLopHp) {
    for (int i = 0; i < this->n; i++) {
        if (maLopHp == (*this)[i].getMaLopHp()) {
            return i;
            break;
        }
    }
    return -1;
}

void TKB::Clear()
{
    this->n = 0;
    delete[] this->data;
}
void TKB::Add(const LopHocPhan& newLopHp) {
    if (this->n == 0) {
        this->data = new LopHocPhan[this->n + 1];
        (*this)[this->n] = newLopHp;
    }
    else {
        TKB temp;
        temp.data = new LopHocPhan[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.data + i) = *(this->data + i);
        }
        delete[] this->data;
        this->data = new LopHocPhan[this->n + 1];
        for (int i = 0; i < this->n; i++) {
            *(this->data + i) = *(temp.data + i);
        }
        *(this->data + this->n) = newLopHp;
    }
    this->n++;
}

void TKB::Remove(string maLopHp) {
    int index = this->IndexOf(maLopHp);
    if (index != -1) {
        TKB temp;
        temp.data = new LopHocPhan[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.data + i) = (*this)[i];
        }
        delete[] this->data;
        this->data = new LopHocPhan[this->n - 1];
        for (int i = 0; i < index; i++) {
            (*this)[i] = *(temp.data + i);
        }
        for (int i = index; i < this->n - 1; i++) {
            (*this)[i] = *(temp.data + i);
        }
    }
    this->n--;
}
