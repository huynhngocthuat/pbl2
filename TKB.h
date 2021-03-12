#pragma once
#include "LopHocPhan.h"

class TKB {
private:
    int n;
    LopHocPhan* data;
public:
    TKB();
    ~TKB();
    int Getn();
    void Clear();
    void Add(const LopHocPhan&);
    void Remove(string);
    void Update(LopHocPhan);
    LopHocPhan& operator[](int);
    int IndexOf(string);
    friend ostream& operator<<(ostream&, const TKB&);
};