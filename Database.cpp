#pragma once

#include "Database.h"

vector<string> vstr;
vector<string> vnumber;

static int callback(void* data, int argc, char** argv, char** azColName) {
 for (int i = 0; i < argc; i++) {
	 switch (i + 1) {
	 case 0:
		 break;//id������
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

	//���в�ѯǰ��׼����������������Ϸ���
	//-1����ϵͳ���Զ�����SQL���ĳ���
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "��ѯ���OK";
		// ÿ��һ��sqlite3_step()������stmt������ͻ�ָ����һ����¼
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// ȡ����0���ֶε�ֵ
			int patientId = sqlite3_column_text(stmt, 0);
			// ȡ����1���ֶε�ֵ
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			// ȡ����2���ֶε�ֵ
			const unsigned char *sex = sqlite3_column_text(stmt, 2);
			// ȡ����3���ֶε�ֵ
			int age = sqlite3_column_int(stmt, 3);
			//�����ز�ѯ������
			std::cout << "patientId = " << patientId << ", name = " << name
				<< ", sex = " << sex << ", age = " << age;
		}
	}
	else {
		std::clog << "��ѯ���������";
	}
	//�����������׼��ִ����һ�����
	sqlite3_finalize(stmt);

	return true;
}
bool Database::queryDevice() {
	string sql = "SELECT* FROM device";
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "��ѯ���OK";
		// ÿ��һ��sqlite3_step()������stmt������ͻ�ָ����һ����¼
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// ȡ����0���ֶε�ֵ
			int deviceId = sqlite3_column_text(stmt, 0);
			// ȡ����1���ֶε�ֵ
			const unsigned char *dev_serial = sqlite3_column_text(stmt, 1);
			// ȡ����2���ֶε�ֵ
			const unsigned char *refresh = sqlite3_column_text(stmt, 2);

			//�����ز�ѯ������
			std::cout << "deviceID = " << deviceId << ", dev_serial = " << dev_serial
				<< ", refresh = " << refresh ;
		}
	}
	else {
		std::clog << "��ѯ���������";
	}
	//�����������׼��ִ����һ�����
	sqlite3_finalize(stmt);

	return true;
}

void Database::findPatientById(string patient_id) {
	string sql = "SELECT* FROM patient where patientId = '"+patient_id+"';";
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), -1, &stmt, &zErrMsg);

	if (rc == SQLITE_OK) {
		std::cout << "��ѯ���OK";
		// ÿ��һ��sqlite3_step()������stmt������ͻ�ָ����һ����¼
		while (sqlite3_step(stmt) == SQLITE_ROW) {
			// ȡ����0���ֶε�ֵ
			int patientId = sqlite3_column_text(stmt, 0);
			// ȡ����1���ֶε�ֵ
			const unsigned char *name = sqlite3_column_text(stmt, 1);
			// ȡ����2���ֶε�ֵ
			const unsigned char *sex = sqlite3_column_text(stmt, 2);
			// ȡ����3���ֶε�ֵ
			int age = sqlite3_column_int(stmt, 3);
			//�����ز�ѯ������
			std::cout << "patientId = " << patientId << ", name = " << name
				<< ", sex = " << sex << ", age = " << age;
		}
	}
	else {
		std::clog << "��ѯ���������";
	}
	//�����������׼��ִ����һ�����
	sqlite3_finalize(stmt);

}
