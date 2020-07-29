#pragma once

#include "Database.h"

vector<string> vstr;
vector<string> vnumber;

static int callback(void* data, int argc, char** argv, char** azColName) {
 for (int i = 0; i < argc; i++) {
	 switch (i + 1) {
	 case 0:
		 break;//id已弃用
	 case 1:
		 vstr.push_back(string(argv[i])); break;
	 case 2:
		 vnumber.push_back(string(argv[i])); break;
	 default:
		 break;

		}
	}
return 0;

}

Database::Database() {

}

Database::~Database() {

}

bool Database::initDatabase() {
	int rc = sqlite3_open("monitor-cloude.db", &db);
	if (rc) {
		sqlite3_close(db);
		return false;
	}
	return true;
}

bool Database::insertDataToPD(string patient_id,string device_id) {
	string sql = "INSERT INTO patient_device (ID,DEVID,PATIENTID) VALUES('"+
		patient_id+"','"+
		device_id+"','"+
		patient_id + "');";
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		return false;
	}
	return true;
}

bool Database::queryPatient() {
	string sql = "SELECT* FROM patient";
	char* zErrMsg = 0;

	//进行查询前的准备工作——检查语句合法性
	//-1代表系统会自动计算SQL语句的长度
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "查询语句OK";
		// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// 取出第0列字段的值
			int patientId = sqlite3_column_text(stmt, 0);
			// 取出第1列字段的值
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			// 取出第2列字段的值
			const unsigned char *sex = sqlite3_column_text(stmt, 2);
			// 取出第3列字段的值
			int age = sqlite3_column_int(stmt, 3);
			//输出相关查询的数据
			std::cout << "patientId = " << patientId << ", name = " << name
				<< ", sex = " << sex << ", age = " << age;
		}
	}
	else {
		std::clog << "查询语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);

	return true;
}
bool Database::queryDevice() {
	string sql = "SELECT* FROM device";
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "查询语句OK";
		// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// 取出第0列字段的值
			int deviceId = sqlite3_column_text(stmt, 0);
			// 取出第1列字段的值
			const unsigned char *dev_serial = sqlite3_column_text(stmt, 1);
			// 取出第2列字段的值
			const unsigned char *refresh = sqlite3_column_text(stmt, 2);

			//输出相关查询的数据
			std::cout << "deviceID = " << deviceId << ", dev_serial = " << dev_serial
				<< ", refresh = " << refresh ;
		}
	}
	else {
		std::clog << "查询语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);

	return true;
}

void Database::findPatientById(string patient_id) {
	string sql = "SELECT* FROM patient where patientId = '"+patient_id+"';";
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "查询语句OK";
		// 每调一次sqlite3_step()函数，stmt语句句柄就会指向下一条记录
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// 取出第0列字段的值
			int patientId = sqlite3_column_text(stmt, 0);
			// 取出第1列字段的值
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			// 取出第2列字段的值
			const unsigned char *sex = sqlite3_column_text(stmt, 2);
			// 取出第3列字段的值
			int age = sqlite3_column_int(stmt, 3);
			//输出相关查询的数据
			std::cout << "patientId = " << patientId << ", name = " << name
				<< ", sex = " << sex << ", age = " << age;
		}
	}
	else {
		std::clog << "查询语句有问题";
	}
	//清理语句句柄，准备执行下一个语句
	sqlite3_finalize(stmt);

}
