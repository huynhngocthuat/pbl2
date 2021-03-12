#include "DBHelper.h"
#include "SV.h"
#include "Diem.h"
#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>
#include "LopHocPhan.h"

using namespace std;

void DBHelper::init()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		closeDB();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		closeDB();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		closeDB();

	//output
	cout << "\t\tATTEMPTING CONNECTION TO SQL SERVER...";
	cout << "\n";
	switch (SQLDriverConnect(sqlConnHandle, NULL, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=ADMIN;DATABASE=Quan_Ly_Sinh_Vien;trusted = true;UID=sa;PWD=123456",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {

	case SQL_SUCCESS:
		cout << "\t\tSUCCESSFULLY CONNECTED TO SQL SERVER";
		cout << "\n";
		break;

	case SQL_SUCCESS_WITH_INFO:
		cout << "\t\tSUCCESSFULLY CONNECTED TO SQL SERVER";
		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "\t\tCOULD NOT CONNECT TO SQL SERVER";
		cout << "\n";
		closeDB();
		break;

	case SQL_ERROR:
		cout << "\t\tCOULD NOT CONNECT TO SQL SERVER";
		cout << "\n";
		closeDB();
		break;

	default:
		break;
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		closeDB();
}

void DBHelper::SelectDB(QLSV& db)
{

	//output
	db.Clear();
	cout << "\n";
	cout << "\t\tEXECUTING T-SQL QUERY...";
	cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT Sinh_Vien.MaSV, Ho_Ten, Nam_Sinh, Que_Quan, Dan_Toc, Sinh_Vien.Ma_Lop, Bao_Hiem, Ma_Khoa FROM Sinh_Vien INNER JOIN Lop ON Sinh_Vien.Ma_Lop = Lop.Ma_Lop", SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaSV[20];
		CHAR Ho_Ten[50];
		int Nam_Sinh;
		CHAR Que_Quan[20];
		CHAR Dan_Toc[10];
		CHAR Ma_Lop[20];
		CHAR Bao_Hiem[10];
		CHAR Ma_Khoa[20];
		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, Ho_Ten, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_DEFAULT, &Nam_Sinh, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, Que_Quan, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, Dan_Toc, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, Ma_Lop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, Bao_Hiem, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 8, SQL_CHAR, Ma_Khoa, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY RESULT : " << endl;
			}
			cout << j++ << ".  " <<  MaSV << setw(20) << Ho_Ten << setw(10) << Nam_Sinh << " " << setw(15) << Que_Quan
			     << setw(15) << Dan_Toc << setw(15) << Ma_Lop << setw(15) << Ma_Khoa << setw(15) << Bao_Hiem << endl;
			SV s1(MaSV, Ho_Ten, Ma_Khoa, Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);
			db.Add(s1);
			//cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::SelectClassDB(QLSV& db, string Ma_Lop)
{
	db.Clear();
	string s = "SELECT * FROM Sinh_Vien WHERE Ma_Lop = '" + Ma_Lop + "'";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	cout << "\n";
	cout << "\t\tExecuting T-SQL query...";
	cout << "\n";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaSV[20];
		CHAR Ho_Ten[50];
		int Nam_Sinh;
		CHAR Que_Quan[20];
		CHAR Dan_Toc[10];
		CHAR Ma_Lop[20];
		CHAR Bao_Hiem[10];
		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, Ho_Ten, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_DEFAULT, &Nam_Sinh, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, Que_Quan, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, Dan_Toc, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, Ma_Lop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, Bao_Hiem, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY RESULT : " << endl;
			}
			cout << j++ << ".  " << MaSV << setw(20) << Ho_Ten << setw(10) << Nam_Sinh << " " << setw(15) << Que_Quan
				<< setw(15) << Dan_Toc << setw(15) << Ma_Lop << setw(15) << Bao_Hiem << endl;
			SV s1(MaSV, Ho_Ten, "CNTT", Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);
			db.Add(s1);
			//cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::SelectFacultyDB(QLSV& db, string Ma_Khoa)
{
	db.Clear();
	string s1 = "SELECT Sinh_Vien.MaSV, Ho_Ten, Nam_Sinh, Que_Quan, Dan_Toc, Sinh_Vien.Ma_Lop, Bao_Hiem, Ma_Khoa FROM Sinh_Vien ";
	string s2 = "INNER JOIN Lop ON Sinh_Vien.Ma_Lop = Lop.Ma_Lop WHERE Lop.Ma_Khoa = '" + Ma_Khoa + "'";
	string s = s1 + s2;
	char m[500];
	snprintf(m, size(m), "%s", s.c_str());
	cout << "\n";
	cout << "\t\tExecuting T-SQL query...";
	cout << "\n";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaSV[20];
		CHAR Ho_Ten[50];
		int Nam_Sinh;
		CHAR Que_Quan[20];
		CHAR Dan_Toc[10];
		CHAR Ma_Lop[20];
		CHAR Bao_Hiem[10];
		CHAR Ma_Khoa[20];
		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, Ho_Ten, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_DEFAULT, &Nam_Sinh, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, Que_Quan, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, Dan_Toc, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, Ma_Lop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, Bao_Hiem, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 8, SQL_CHAR, Ma_Khoa, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY RESULT : " << endl;
			}
			cout << j++ << ".  " << MaSV << setw(20) << Ho_Ten << setw(10) << Nam_Sinh << " " << setw(15) << Que_Quan
				<< setw(15) << Dan_Toc << setw(15) << Ma_Lop << setw(15) << Ma_Khoa << setw(15) << Bao_Hiem << endl;
			SV s1(MaSV, Ho_Ten, Ma_Khoa, Nam_Sinh, Que_Quan, Dan_Toc, Ma_Lop, Bao_Hiem);
			db.Add(s1);
			//cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::SelectScoreDB()
{
	string s1 = "Select Sinh_Vien.MaSV, Ho_Ten, Ma_Lop, AVG(Diem_Thi) AS 'DTB' FROM Sinh_Vien ";
	string s2 = "INNER JOIN Ket_Qua ON Sinh_Vien.MaSV = Ket_Qua.MaSV ";
	string s3 = "GROUP BY Sinh_Vien.MaSV, Ho_Ten, Ma_Lop ORDER BY DTB ";
	string s = s1 + s2 + s3;
	char m[500];
	snprintf(m, size(m), "%s", s.c_str());
	cout << "\n";
	cout << "\t\tExecuting T-SQL query...";
	cout << "\n";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaSV[20];
		CHAR Ho_Ten[50];
		CHAR Ma_Lop[20];
		float DTB;
		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, Ho_Ten, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, Ma_Lop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_C_FLOAT, &DTB, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tDIEM TRUNG BINH  : " << endl;
				cout << setw(5) << "STT" << setw(15) << "MA SV" << setw(20) << "HO TEN" << setw(15) << "TEN LOP" << setw(10) << "DIEM TB" << endl;
			}
			cout << setw(5) << j++  << setw(15) << MaSV << setw(20) << Ho_Ten << setw(15) << Ma_Lop << setw(10) << DTB << endl;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}
void DBHelper::InsertDB()
{
	string MaSV;
	string HoTen;
	int Nam_Sinh;
	string Que_Quan;
	string Dan_Toc;
	string Ma_Lop;
	string Bao_Hiem;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien: ";
	getline(cin, MaSV);
	cout << "\t\tNhap ho ten sinh vien: ";
	getline(cin, HoTen);
	cout << "\t\tNhap nam sinh: ";
	cin >> Nam_Sinh;
	cin.ignore(100, '\n');
	cout << "\t\tNhap que quan sinh vien: ";
	getline(cin, Que_Quan);
	cout << "\t\tNhap dan toc: ";
	getline(cin, Dan_Toc);
	cout << "\t\tNhap lop: ";
	getline(cin, Ma_Lop);
	cout << "\t\tNhap so bao hiem: ";
	getline(cin, Bao_Hiem);
	ostringstream convert;
	convert << Nam_Sinh;
	string Nam_Sinh1;
	Nam_Sinh1 = convert.str();
	//string s = "INSERT INTO Sinh_Vien VALUES('" + sv.MaSV + "','" + sv.Ho_Ten + "','2001','" + sv.Que_Quan + "','" + sv.Dan_Toc
	//	+ "','" + sv.Ma_Lop + "','" + sv.Bao_Hiem + "')";
	string s = "INSERT INTO Sinh_Vien VALUES('" + MaSV + "','" + HoTen + "','" + Nam_Sinh1 + "','" + Que_Quan + "','" + Dan_Toc
		+ "','" + Ma_Lop + "','" + Bao_Hiem + "')";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	//char m[] = "INSERT INTO Sinh_Vien VALUES('102190333','Duc','2001','Hue','Kinh','19TCLC_DT2','BHYT66')";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {

		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		cout << "\n\t\tINSERT SUCCESS";
		cout << "\n";
		return;
	}
}

void DBHelper::UpdateDB()
{
	string MaSV;
	string Ho_Ten;
	int Nam_Sinh;
	string Que_Quan;
	string Dan_Toc;
	string Ma_Lop;
	string Bao_Hiem;
	cin.ignore(100, '\n');
	cout << "\t\tMASV cua SV can UPDATE : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ho ten sinh vien: ";
	getline(cin, Ho_Ten);
	cout << "\t\tNhap nam sinh: ";
	cin >> Nam_Sinh;
	cin.ignore(100, '\n');
	cout << "\t\tNhap que quan sinh vien: ";
	getline(cin, Que_Quan);
	cout << "\t\tNhap dan toc: ";
	getline(cin, Dan_Toc);
	cout << "\t\tNhap lop: ";
	getline(cin, Ma_Lop);
	cout << "\t\tNhap so bao hiem: ";
	getline(cin, Bao_Hiem);
	ostringstream convert;
	convert << Nam_Sinh;
	string Nam_Sinh1;
	Nam_Sinh1 = convert.str();
	string s = "UPDATE Sinh_Vien SET Ho_Ten = '" + Ho_Ten + "', Nam_Sinh = '" + Nam_Sinh1 + "', Que_Quan = '" + Que_Quan + "', Dan_Toc = '" + Dan_Toc
		+ "', Ma_Lop = '" + Ma_Lop + "', Bao_Hiem = '" + Bao_Hiem + "'WHERE MaSV = " + MaSV;
	char m[300];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		cout << "\n\t\tUPDATE SUCCESS";
		return;
	}
}

void DBHelper::DeleteDB(string masv)
{
	string s = "DELETE FROM Sinh_Vien WHERE MaSV = '" + masv + "' "; 
	char m[200];                                                     
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {

		cout << "\n\t\tDELETE SUCCESS";
		return;
	}
}

void DBHelper::SelectDiemDB(QLSV& db)
{

	//output
	for (int i = 0; i < db.GetN(); i++)
	{
		db[i].GetDanhSachDiem().Clear();
	}
	cout << "\n";
	cout << "\t\tExecuting T-SQL query...";
	cout << "\t\tEXECUTING T-SQL QUERY...";
	cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Ket_Qua", SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char MaSV[20];
		char MaMH[20];
		int Lan_Thi;
		float Diem_Thi;
		int i = 0;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, MaMH, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_DEFAULT, &Lan_Thi, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_C_FLOAT, &Diem_Thi, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY SUCCESS SCORE " << endl;
			}
			string MaSVstr;
			string MaMHstr;
			ostringstream convert;
			convert << MaSV;
			MaSVstr = convert.str();
			ostringstream convert2;
			convert2 << MaMH;
			MaMHstr = convert2.str();
			Diem d(MaMHstr, Lan_Thi, Diem_Thi);
			//cout << setw(10) << MaSV << setw(10) << MaMH << setw(3) << Lan_Thi << setw(5) << Diem_Thi << endl;
			for (int k = 0; k <= db.GetN(); k++) {
				if (db[k].GetMaSV() == MaSVstr) {
					db[k].GetDanhSachDiem().Add(d);
				}
			}
			
			i++;
		}
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::InsertDiemDB()
{
	string MaSV;
	string MaMH;
	int Lan_Thi;
	float Diem_Thi;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ma mon hoc : ";
	getline(cin, MaMH);
	cout << "\t\tNhap so lan thi : ";
	cin >> Lan_Thi;
	cout << "\t\tNhap diem thi : ";
	cin >> Diem_Thi;
	ostringstream convert;
	convert << Lan_Thi;
	ostringstream convert2;
	convert2 << Diem_Thi;
	string s = "INSERT INTO Ket_Qua VALUES('" + MaSV +"', '" + MaMH + "', '" + convert.str() + "','" + convert2.str() + "')";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	//char m[] = "INSERT INTO Ket_Qua VALUES('102190092', '19N11TRR', '1', '8')";
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) 
	{
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else 
	{
		cout << "\n\t\tINSERT SUCCESS";
		cout << "\n";
		return;
	}
}

void DBHelper::UpdateDiemDB()
{
	string MaSV;
	string MaMH;
	int Lan_Thi;
	float Diem_Thi;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ma mon hoc : ";
	getline(cin, MaMH);
	cout << "\t\tNhap so lan thi can thay doi : ";
	cin >> Lan_Thi;
	cout << "\t\tNhap diem thi can thay doi : ";
	cin >> Diem_Thi;
	ostringstream convert;
	convert << Lan_Thi;
	string lt = convert.str();
	ostringstream convert2;
	convert2 << Diem_Thi;
	string s = "UPDATE Ket_Qua SET Lan_Thi = " + convert.str() + ", Diem_Thi = " + convert2.str() 
		+  " WHERE MaSV = " + MaSV + "AND MaMH = '" + MaMH + "'";
	char m[500];
	//char m[] = "update Ket_Qua set Lan_Thi = 1, Diem_Thi = 9.6 where MaSV = 102190093 and MaMH = 19N11JAVA"
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {

		cout << "\n\t\tUPDATE SUCCESS";
		return;
	}
}

void DBHelper::DeleteDiemDB()
{
	string masv;
	string mamh;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien can xoa : ";
	getline(cin, masv);
	cout << "\t\tNhap ma mon hoc can xoa : ";
	getline(cin, mamh);
	string s = "DELETE FROM Ket_Qua WHERE MaSV = '" + masv + "' AND MaMH = '" + mamh + "'";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		cout << "\n\t\tDELETE SUCCESS";
		return;
	}
}

void DBHelper::DeleteAllDiemDB(string masv)
{
	string s = "DELETE FROM Ket_Qua WHERE MaSV = '" + masv + "'";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tTOAN BO DIEM DA DUOC XOA ";
		cout << "\n";
	}
	else {
		cout << "\n\t\tDELETE SUCCESS BANG DIEM";
		return;
	}
}

void DBHelper::SelectTKBDB(QLSV& db)
{

	//output
	for (int i = 0; i < db.GetN(); i++)
	{
		db[i].GetTKB().Clear();
	}
	cout << "\n";
	cout << "\t\tEXECUTING T-SQL QUERY...TABLE Thoi_Khoa_Bieu";
	cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT LopHocPhan.MaLopHocPhan,MaMH, MaSV, Giang_Vien, Thu, TietHoc_Gio, PhongHoc, TuanHoc FROM LopHocPhan INNER JOIN Thoi_Khoa_Bieu ON Thoi_Khoa_Bieu.MaLopHocPhan = LopHocPhan.MaLopHocPhan", SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char MaLopHocPhan[30];
		char MaMH[20];
		char MaSV[20];
		char Giang_Vien[50];
		int Thu;
		char TietHoc_Gio[20];
		char PhongHoc[20];
		char TuanHoc[20];
		int i = 0;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaLopHocPhan, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, MaMH, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, MaSV, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, Giang_Vien, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_DEFAULT, &Thu, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, TietHoc_Gio, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, PhongHoc, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 8, SQL_CHAR, TuanHoc, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY SUCCESS TKB " << endl;
			}
			string MaLopHocPhanstr;
			string MaMHstr;
			string MaSVstr;
			string Giang_Vienstr;
			string TietHoc_Giostr;
			string PhongHocstr;
			string TuanHocstr;
			ostringstream convert1;
			ostringstream convert2;
			ostringstream convert3;
			ostringstream convert4;
			ostringstream convert5;
			ostringstream convert6;
			ostringstream convert7;
			convert1 << MaLopHocPhan;
			convert2 << MaMH;
			convert3 << MaSV;
			convert4 << Giang_Vien;
			convert5 << TietHoc_Gio;
			convert6 << PhongHoc;
			convert7 << TuanHoc;
			MaLopHocPhanstr = convert1.str();
			MaMHstr = convert2.str();
			MaSVstr = convert3.str();
			Giang_Vienstr = convert4.str();
			TietHoc_Giostr = convert5.str();
			PhongHocstr = convert6.str();
			TuanHocstr = convert7.str();
			LopHocPhan t(MaLopHocPhanstr, MaMHstr, Giang_Vienstr, Thu, TietHoc_Giostr, PhongHocstr, TuanHocstr);
			for (int k = 0; k < db.n; k++) {
				if (db[k].GetMaSV() == MaSVstr) {
				   db[k].GetTKB().Add(t);
				}
			}
			i++;
		}
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::SelectLHPDB(TKB& listLHP)
{

	cout << "\n";
	cout << "\t\tQUERY CAC LOP HOC PHAN";
	cout << "\n";
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM LopHocPhan", SQL_NTS)) {
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		char MaLopHocPhan[30];
		char MaMH[20];
		char Giang_Vien[50];
		int Thu;
		char TietHoc_Gio[20];
		char PhongHoc[20];
		char TuanHoc[20];
		int i = 0;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaLopHocPhan, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, MaMH, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, Giang_Vien, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_DEFAULT, &Thu, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, TietHoc_Gio, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, PhongHoc, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, TuanHoc, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				cout << "\n\t\tQUERY SUCCESS LHP " << endl;
			}
			string MaLopHocPhanstr;
			string MaMHstr;
			string Giang_Vienstr;
			string TietHoc_Giostr;
			string PhongHocstr;
			string TuanHocstr;
			ostringstream convert1;
			ostringstream convert2;
			ostringstream convert3;
			ostringstream convert4;
			ostringstream convert5;
			ostringstream convert6;
			convert1 << MaLopHocPhan;
			convert2 << MaMH;
			convert3 << Giang_Vien;
			convert4 << TietHoc_Gio;
			convert5 << PhongHoc;
			convert6 << TuanHoc;
			MaLopHocPhanstr = convert1.str();
			MaMHstr = convert2.str();
			Giang_Vienstr = convert3.str();
			TietHoc_Giostr = convert4.str();
			PhongHocstr = convert5.str();
			TuanHocstr = convert6.str();
			LopHocPhan t(MaLopHocPhanstr, MaMHstr, Giang_Vienstr, Thu, TietHoc_Giostr, PhongHocstr, TuanHocstr);
			listLHP.Add(t);
			i++;
		}
	}
	SQLCancel(sqlStmtHandle);
}

void DBHelper::InsertTKBDB()
{
	string MaSV;
	string MaLopHocPhan;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ma lop hoc phan : ";
	getline(cin, MaLopHocPhan);
	string s = "INSERT INTO Thoi_Khoa_Bieu VALUES('" + MaSV + "','" + MaLopHocPhan + "','19-20')";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	//char m[] = "INSERT INTO Thoi_Khoa_Bieu VALUES('102190093', 'CTMT11', '19-20')";
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS))
	{
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else
	{
		cout << "\n\t\tINSERT SUCCESS";
		cout << "\n";
		return;
	}
}

void DBHelper::UpdateTKBDB()
{
	string MaSV;
	string MaLopHocPhanold;
	string MaLopHocPhannew;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ma lop hoc phan cu : ";
	getline(cin, MaLopHocPhanold);
	cout << "\t\tNhap ma lop hoc phan moi : ";
	getline(cin, MaLopHocPhannew);
	string s = "UPDATE Thoi_Khoa_Bieu  SET MaLopHocPhan = '" + MaLopHocPhannew + "' WHERE MaSV = '" + MaSV + "' AND MaLopHocPhan = '"
		+ MaLopHocPhanold + "'";
	char m[500];
	//char m[] = "update Ket_Qua set Lan_Thi = 1, Diem_Thi = 9.6 where MaSV = 102190093 and MaMH = 19N11JAVA"
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {

		cout << "\n\t\tUPDATE SUCCESS";
		return;
	}
}

void DBHelper::DeleteTKBDB()
{
	string MaSV;
	string MaLopHocPhan;
	cin.ignore(100, '\n');
	cout << "\t\tNhap ma sinh vien can xoa : ";
	getline(cin, MaSV);
	cout << "\t\tNhap ma lop hoc phan can xoa : ";
	getline(cin, MaLopHocPhan);
	string s = "DELETE FROM Thoi_Khoa_Bieu WHERE MaSV = '" + MaSV + "' AND MaLopHocPhan = '" + MaLopHocPhan + "'";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tERROR QUERYING SQL SERVER";
		cout << "\n";
		closeDB();
	}
	else {
		cout << "\n\t\tDELETE SUCCESS";
		return;
	}
}

void DBHelper::DeleteAllTKBDB(string masv)
{
	
	string s = "DELETE FROM Thoi_Khoa_Bieu WHERE MaSV = '" + masv + "'";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		cout << "\n";
		cout << "\t\tTOAN BO TKB DA DUOC XOA";
		cout << "\n";
	}
	else {
		cout << "\n\t\tDELETE SUCCESS LIST TKB";
		return;
	}
}

void DBHelper::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
