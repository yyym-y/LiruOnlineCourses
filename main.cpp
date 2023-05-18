#include <iostream>
#include <map>
#include <conio.h>
#include <windows.h>
#include "CLASS.h"

using namespace std;

bool Check(string ID, string password){
    LogCheck Use(ID, password);
    return Use.Action();
}

void add(){
    cout << "\tpleased inter there infos, divide by space:\n\n";
    cout << "\t1: ID  2:name  3:  nickname    4:password\n\n\t";
    string ID, name, nickname, password;
    cin >> ID >> name >> nickname >> password;
    Creat Use(ID, name, nickname, password);
    cout << "\n\tCreate Success\n";
}

void change(){
    string UID, content; int index;
    cout << "\n   Please inter the UID of the account you want to change : \n\n\t";
    cin >> UID;
    cout << "\tPlease inter which info you want to change : \n\n";
    cout << "\t1: ID  2:name  3:  nickname    4:password\n\n\t";
    cin >> index; index--;
    cout << "\n\tPlease inter the content that changed : \n\n\t";
    cin >> content;
    Change Use(UID, index, content);
    bool result = Use.Action();
    if(result)
        cout << "\n\tChange Success\n";
    else cout << "\n\tID is wrong\n";
}

void delete_(){
    cout << "   Please inter the UID of the account you want to delete : \n\n\t";
    string UID; cin >> UID;
    Delete Use(UID);
    bool result = Use.Action();
    if(result)
        cout << "\n\tdelete Success\n\n";
    else cout << "\n\tID is wrong\n";
}

void exportData(){
    ExportData Use(1);
    bool result = Use.Action();
    if(result)
        cout << "\n\n\n\n\tExport Data success\n";
    else
        cout << "\n\n\n\n\tExport Data failed\n";
}

void admin(){
    system("cls");
    cout << "\tplease inter which operation you want to choice : \n\n";
    cout << "\t-     1: Add account\n\t-     2: Change account\n\t";
    cout << "-     3: Delete account\n\t-     4: Expot data\n\t-     5: Back\n\t: ";
    int type;   cin >> type;
    system("cls");
    switch (type) {
        case 1:
            add(); Sleep(1000); admin(); break;
        case 2:
            change(); Sleep(1000); admin(); break;
        case 3:
            delete_(); Sleep(1000); admin(); break;
        case 4:
            exportData(); Sleep(1000); admin(); break;
        case 5:
            system("cls"); cout << "\n\n\n\n\tGoodBy......\n";
            Sleep(1000); system("cls"); break;
    }
}

void UI(){
    system("cls");
    string ID, password;
    cout << "\n\n\n\t   please input ID : "; cin >> ID;
    cout << "\n\n\t   please input password : ";
    char ch;
    while((ch = _getch()) != '\r') {
        password += ch;
        putchar('*');
    }
    if(Check(ID, password)) {
        cout << "\n\n\t   Welcome ! " << ID << "\n";
        Sleep(1000); system("cls");
        if(ID == "admin") admin();
    }
    else{
        cout << "\n\n\t   ID or password is wrong !\n";
        Sleep(1000);
        UI();
    }
}

void Init(){
    system("title Identity recording system");
    system("color b0");
    system("mode con cols=60 lines=15");
}

int main() {
    Init();  UI();
    return 0;
}
