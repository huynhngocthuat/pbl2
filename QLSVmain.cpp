#include "QLSV.h"
#include "DBHelper.h"
#include <iostream>

using namespace std;
string Ma_Lop;
string Ma_Khoa;
int CHECK;
TKB listLHP;
void ShowMainMenu() 
{
    cout << "\n";
    cout << "\t\t--------------------------------MENU----------------------------------" << endl;
    cout << "\t\t\t\t" << setw(5) << "I." << "  TRUY VAN DU LIEU TU DATABASE " << endl;
    cout << "\t\t\t\t" << setw(5) << "II." << "  HIEN THI THONG TIN SINH VIEN" << endl;
    cout << "\t\t\t\t" << setw(5) << "III." << "  THEM DU LIEU VAO HE THONG" << endl; // SINH VIEN
    cout << "\t\t\t\t" << setw(5) << "IV." << "  SUA DOI DU LIEU TRONG HE THONG" << endl; // SINH VIEN, TKB
    cout << "\t\t\t\t" << setw(5) << "V." << "  XOA DU LIEU TRONG HE THONG" << endl;// SINH VIEN, TKB, DIEM
    cout << "\t\t\t\t" << setw(5) << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowSelectMenu()
{
    cout << "\n";
    cout << "\t\t-------------------------------QUERY DATABASE------------------------------------" << endl;
    cout << "\t\t\t\t" << "   1.  TRUY VAN SINH VIEN THEO LOP" << endl;
    cout << "\t\t\t\t" << "   2.  TRUY VAN SINH VIEN THEO KHOA" << endl;
    cout << "\t\t\t\t" << "   3.  TRUY VAN SINH VIEN THEO DIEM" << endl;
    cout << "\t\t\t\t" << "   4.  TRUY VAN TOAN BO SINH VIEN" << endl;
    cout << "\t\t\t\t" << "   5.  TRUY VAN DIEM CUA SINH VIEN" << endl;
    cout << "\t\t\t\t" << "   6.  TRUY VAN TKB CUA SINH VIEN" << endl;
    cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}
void ShowDisplayMenu()
{
    cout << "\n";
    cout << "\t\t----------------------------------DISPLAY DATA------------------------------------" << endl;
    cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA SINH VIEN" << endl;
    cout << "\t\t\t\t" << "   2.  HIEN THI DIEM CUA MOT SINH VIEN" << endl;
    cout << "\t\t\t\t" << "   3.  HIEN THI TKB CUA MOT SINH VIEN" << endl;
    cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}
void ShowAddMenu() 
{
    cout << "\n";
    cout << "\t\t----------------------------THEM DU LIEU VAO HE THONG------------------------------" << endl;
    cout << "\t\t\t\t" << "   1.  THEM MOT DOI TUONG SINH VIEN " << endl;
    cout << "\t\t\t\t" << "   2.  THEM MOT DOI TUONG DIEM" << endl;
    cout << "\t\t\t\t" << "   3.  THEM MOT DOT TUONG THOI KHOA BIEU" << endl;
    cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowUpdateMenu() 
{
    cout << "\n";
    cout << "\t\t---------------------------SUA DOI DU LIEU TRONG HE THONG----------------------------" << endl;
    cout << "\t\t\t\t" << "   1.  SUA DOI THONG TIN CUA SINH VIEN " << endl;
    cout << "\t\t\t\t" << "   2.  SUA DOI DU LIEU DIEM " << endl;
    cout << "\t\t\t\t" << "   3.  SUA DOI DU LIEU TKB " << endl;
    cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowDeleteMenu() 
{
    cout << "\n";
    cout << "\t\t--------------------------XOA DU LIEU TRONG HE THONG---------------------------------" << endl;
    cout << "\t\t\t\t" << "   1.  XOA TOAN BO THONG TIN CUA SINH VIEN " << endl;
    cout << "\t\t\t\t" << "   2.  XOA DU LIEU DIEM CUA SINH VIEN" << endl;
    cout << "\t\t\t\t" << "   3.  XOA DU LIEU MON HOC CUA SINH VIEN" << endl;
    cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void SelectInform(QLSV &db, DBHelper database, TKB& listLHP) 
{
    int temp = 1;
    while (temp) 
    {
        int k;
        ShowSelectMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : "; 
        cin >> k;
        if (k > 0 && k < 5) CHECK = k;
        switch (k)
        {
        case 1:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma lop : ";
            getline(cin, Ma_Lop);
            database.SelectClassDB(db, Ma_Lop);
            //cout << db;
            db.SortAZ();
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma khoa : ";
            getline(cin, Ma_Khoa);
            database.SelectFacultyDB(db, Ma_Khoa);
           // cout << db;
            db.SortAZ();
            break;
        case 3:
            database.SelectScoreDB();
            db.SortAZ();
            break;
        case 4: 
            database.SelectDB(db);
           // cout << db;
            db.SortAZ();
            break;
        case 5:
            database.SelectDiemDB(db);
            break;
        case 6:
            database.SelectTKBDB(db);
            database.SelectLHPDB(listLHP);
            //cout << listLHP;
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void DisplayInform(QLSV& db, DBHelper database)
{
    int temp = 1;
    string MaSV;
    int i;
    while (temp)
    {
        int m;
        ShowDisplayMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            cout << db << endl;
            break;
        case 2:
            cout << "\t\tNhap ma sinh vien : ";
            getline(cin, MaSV);
            i = db.IndexOf(MaSV) - 1;
            cout << db[i].GetDanhSachDiem();
            break;
        case 3:
            cout << "\t\tNhap ma sinh vien : ";
            getline(cin, MaSV);
            i = db.IndexOf(MaSV)-1;
            cout << db[i].GetTKB();
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void UpdateDBSelect(QLSV& db, DBHelper database, TKB listLHP)
{
        switch (CHECK)
        {
        case 1:
            database.SelectClassDB(db, Ma_Lop);
            //db.SortAZ();
            break;
        case 2:
            database.SelectFacultyDB(db, Ma_Khoa);
            //db.SortAZ();
            break;
        case 3:
            database.SelectScoreDB();
            //db.SortAZ();
            break;
        case 4:
            database.SelectDB(db);
            //db.SortAZ();
            break;
        default:
            break;
        }
}


void AddInform(QLSV &db, DBHelper &database, TKB listLHP) 
{
    int temp = 1;
    while (temp) 
    {
        int n;
        ShowAddMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : "; 
        cin >> n;
        switch (n)
        {
        case 1:
            database.InsertDB();
            UpdateDBSelect(db, database, listLHP);
            //database.SelectDiemDB(db);
            //database.SelectTKBDB(db);
            break;
        case 2:
            database.InsertDiemDB();
            database.SelectDiemDB(db);
            break;
        case 3:
            database.InsertTKBDB();
            database.SelectTKBDB(db);
            break;
        default:
            temp = 0;
            break;
        }
    }
}


void UpdateInform(QLSV& db, DBHelper& database, TKB listLHP)
{
    int temp = 1;
    while (temp)
    {
        int n;
        ShowUpdateMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> n;
        switch (n)
        {
        case 1:
            database.UpdateDB();
            UpdateDBSelect(db, database, listLHP);
            //database.SelectDiemDB(db);
           // database.SelectTKBDB(db);
            break;
        case 2:
            database.UpdateDiemDB();
            database.SelectDiemDB(db);
            break;
        case 3:
            database.UpdateTKBDB();
            database.SelectTKBDB(db);
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void DeleteInform(QLSV& db, DBHelper& database, TKB listLHP)
{
    int temp = 1;
    string masv;
    while (temp)
    {
        int n;
        ShowDeleteMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> n;
        switch (n)
        {
        case 1:
            cin.ignore(100, '\n');
            cout << "\t\tNhap MaSV can xoa : ";
            getline(cin, masv);
            database.DeleteAllDiemDB(masv);
            database.DeleteAllTKBDB(masv);
            database.DeleteDB(masv);
            //db.Remove(masv);
            //UpdateDBSelect(db, database, listLHP);
            //database.SelectDiemDB(db);
            //database.SelectTKBDB(db);
            break;
        case 2:
            database.DeleteDiemDB();
            //database.SelectDiemDB(db);
            break;
        case 3:
            database.DeleteTKBDB();
            //database.SelectTKBDB(db);
            break;
        default:
            temp = 0;
            break;
        }
    }
}
int main()
{
    QLSV db;
    DBHelper database;
    //SV sv("102190092", "HUYNH THUAT", "CNTT", 2001, "TAM KY", "KINH", "19T2", "BHYT");
    /*TKB listLHP;
    LopHocPhan l1("TRR11", "TRR", "NGUYEN VAN HIEU", 2, "2-4", "F201", "3-18");
    LopHocPhan l2("TRR12", "TRR", "NGUYEN VAN HIEU", 2, "4-5", "F201", "3-18");
    listLHP.Add(l1);
    cout << listLHP;*/
    //db.Add(sv);
    //db.AddDiem();
   // listLHP.Update(l2);
    //cout << listLHP;*/
    database.init();
    int k = 1;
    while (k) {
        int temp;
        ShowMainMenu();
        cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> temp;
        switch (temp)
        {
        case 1:
            SelectInform(db, database, listLHP);
            break;
        case 2:
            DisplayInform(db, database);
            break;
        case 3:
            AddInform(db, database, listLHP);
            break;
        case 4:
            UpdateInform(db, database, listLHP);
            break;
        case 5:
            DeleteInform(db, database, listLHP);
            break;
        default:
            k = 0;
            break;
        }
    }
    return 0;
}