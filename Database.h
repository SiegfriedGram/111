#pragma once

#include"sqlite3.h"
#include<vector>
#include<iostream>

using namespace std;

class Database {
public:
	Database();
	~Database();
	bool initDatabase();
	bool insertDataToPD(string patient_id, string device_id);
	bool queryPatient();
	bool queryDevice();
	//void findDeviceByPatient();
	void findPatientById(string patient_id);
	//bool insertDevice();

private:
	sqlite3* db;
	sqlite3_stmt* stmt;
};

static int callback(void* data, int argc, char** argv, char** azColName);

/*
	ʹ�ã�
	//����ʵ��
	Database* db = new Database();
	//���÷���
	db->initDatabase();
*/