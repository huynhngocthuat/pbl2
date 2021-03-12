#pragma once
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>
#include "SV.h"
#include "QLSV.h"
#include "Diem.h"
class DBHelper 
{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1024
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	void init();
	void InsertDB();
	void SelectDB(QLSV&);
	void SelectClassDB(QLSV&, string);
	void SelectFacultyDB(QLSV&, string);
	void SelectScoreDB();
	void UpdateDB();
	void DeleteDB(string);

	void SelectDiemDB(QLSV&);
	void InsertDiemDB();
	void UpdateDiemDB();
	void DeleteDiemDB();
	void DeleteAllDiemDB(string);

	void SelectTKBDB(QLSV&);
	void SelectLHPDB(TKB&);
	void InsertTKBDB();
	void UpdateTKBDB();
	void DeleteTKBDB();
	void DeleteAllTKBDB(string);
	void closeDB();
};