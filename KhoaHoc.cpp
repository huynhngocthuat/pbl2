#include "KhoaHoc.h"

KhoaHoc::KhoaHoc(string maKhoaHoc, int namBatDau, int namKetThuc)
    :maKhoaHoc(maKhoaHoc), namBatDau(namBatDau), namKetThuc(namKetThuc)
{}
KhoaHoc::~KhoaHoc() {}

string KhoaHoc::getMaKhoaHoc() {
    return this->maKhoaHoc;
}