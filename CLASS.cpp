#include "CLASS.h"
#include<string>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<tuple>
using namespace std;

// password encryption
string passwordEncryption(string password){
    unsigned long long Out = 0, key = 131, Mul = 1;
    for(int temp = 0 ; temp < password.size() ; temp++, Mul *= key)
        Out += password[temp] * Mul;
    string FIN = to_string(Out);
    return  FIN;
}

// account keys
char key1[27] = "QASWZXDECVFRBNGTHYJUMKIOLP";
char key2[27] = "plijkomnhutybvfgcxerdwsqza";
char key3[11] = "7563890412";
//Encryption account
string accountEncryption(string put){
    int one = 90, two = 33, there = 62;
    string FIN;
    for(char temp : put){
        if(temp >= 'A' && temp <= 'Z')
            FIN += char(one + key1[temp - 'A'] - 'A');
        else if(temp >= 'a' && temp <= 'z')
            FIN += char(two + key2[temp - 'a'] - 'a');
        else{
            FIN += char(there + key3[temp - '0'] - '0');
        }
    }
    return FIN;
}
//Decode account
string accountDecode(string put){
    auto Find = [](char* key, int Length, char findChar){
        for(int temp = 0 ; temp < Length ; temp++){
            if(*(key + temp) == findChar)
                return temp;
        }
        return -1;
    };
    int one = 90, two = 33, there = 62;
    string FIN;
    for(char temp : put){
        char ch = temp;
        if(temp >= 90 && temp <= 116)
            FIN +=  char('A' + Find(key1, 26, char(ch + 'A'  - one)));
        else if(temp >= 33 && temp <= 59)
            FIN += char('a' + Find(key2, 26, char(ch + 'a' - two)));
        else
            FIN += char('0' + Find(key3, 10, char(ch + '0' - there)));
    }
    return FIN;
}

// query the path of the running .exe
string currentPath(){
    char buffer[512] = {0};
    GetCurrentDirectory(sizeof(buffer), buffer);
    string Road = buffer;
    return Road;
}

// Check if the file exist
void GetPath::queryPath(){
    string Road = currentPath();
    Road += "\\logInfo";
    ofstream ff;
    ff.open(Road, ios::in);
    if(ff.is_open()){
        ff.close();
    }else{
        ofstream new_ff(Road.c_str());
        new_ff << "0*\"(6 0*\"(6 0*\"(6 2099018719509\n"; //Init Admin account : admin : 123456
        new_ff.close();
    }
    PATH = Road;
}

// Edit Content
bool EditContent::Action(){ // type : 1-Check exist 2-Delete 3-Change 4-export
    // info content : 1- ID+password   2- ID   3-ID+index+content   4-none

    //Function below is to divide content into three parts
    auto Fun = [](string put){
        vector<string> info; int index = 0;
        while(info.size() != 4){
            string Use;
            while(index < put.size() && put[index] != ' '){
                Use += put[index]; index++;
            }
            info.push_back(Use); index++;
        }
        return info;
    };

    ifstream ff;
    ff.open(PATH, ios::in);
    //ch is to save read content, Content is to save new content, Origin is to save final info;
    string ch, Content, Origin;
    if(ff.is_open()){
        int flag = 0; //Check ID if exist
        string Change;
        while(getline(ff, ch)){
            vector<string> fin = Fun(ch);
            if(type == 4){
                //decode the content
                Origin += accountDecode(fin[0]) + "\t\t";
                Origin += accountDecode(fin[1]) + "\t\t";
                Origin += accountDecode(fin[2]) + "\t\t";
                Origin += "\n";
                continue;
            }
            if(fin[0] == info[0]){
                flag = 1;
                if(type == 1){
                    if(fin[3] == info[1]) return true;
                    else return false;
                }else if(type == 2) continue;
                else if(type == 3){
                    fin[info[1][0] - '0'] = info[2];
                    for(auto pr : fin) Change += (pr + " ");
                    Change += "\n";
                }
            }else Change += (ch + "\n");
        }

        ff.close();
        if(type == 1) return false;
        // Check if the DATA.txt exist and write the content
        if(type == 4){
            string Road = currentPath();
            Road += "./DATA.txt";
            ofstream new_ff(Road.c_str());
            new_ff << "ID\t\tname\t\tnickname\t\t\n\n";
            new_ff << Origin; new_ff.close();
            return true;
        }

        ofstream ofs;
        ofs.open(PATH, ofstream::out | ofstream::trunc);
        ofs.flush(); ofs << Change;
        ofs.close();
        if(flag) return true;
        else return false;
    }
    return false;
}


LogCheck::LogCheck(string ID, string password) {
    ID = accountEncryption(ID); password = passwordEncryption(password);
    queryPath();
    info.push_back(ID); info.push_back(password); type = 1;
}

Creat::Creat(string ID, string name, string nickname, string password){
    ID = accountEncryption(ID); name = accountEncryption(name);
    nickname = accountEncryption(nickname); password = passwordEncryption(password);
    string put = ID + " " + name + " " + nickname + " " + password + "\n\n";
    ofstream ff;
    ff.open(PATH, ios::app);
    ff << put;
    ff.close();
}

Change::Change(string ID, int index, string content) {
    queryPath();
    ID = accountEncryption(ID);
    if(index == 3) content = passwordEncryption(content);
    else content = accountEncryption(content);
    info.push_back(ID), info.push_back(to_string(index)), info.push_back(content);
    type = 3;
}

Delete::Delete(string ID) {
    queryPath();
    ID = accountEncryption(ID);
    info.push_back(ID); type = 2;
}
