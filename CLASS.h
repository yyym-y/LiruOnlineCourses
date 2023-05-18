#ifndef LIRUONLINECOURSES_CLASS_H
#define LIRUONLINECOURSES_CLASS_H
#include<vector>
#include<string>
#include<iostream>
#include<tuple>

using namespace std;

class GetPath{
protected:
    string PATH;
public:
    GetPath(){queryPath();};
    void queryPath();
};

class EditContent : public GetPath{
protected:
    int type;
    vector<string> info;
public:
    EditContent(int type_, vector<string> info_) : GetPath(), type(type_), info(info_){};
    EditContent(){};
    bool Action();
};

class LogCheck : public EditContent{
public:
    LogCheck()=default;
    LogCheck(string ID, string password);
};

class Creat : GetPath{
public:
    Creat()=default;
    Creat(string ID, string name, string nickname, string password);
};

class Change : public EditContent{
public:
    Change()=default;
    Change(string ID, int index, string content);
};

class Delete : public EditContent{
public:
    Delete() = default;
    Delete(string ID);
};

class ExportData : public EditContent{
public:
    ExportData(){type=4;};
    ExportData(int up){type=4;}
};
#endif //LIRUONLINECOURSES_CLASS_H
