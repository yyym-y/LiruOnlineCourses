# C++砺儒云登录系统

**写在前面**

这次大作业的最大感受......我设计类的能力好差:cry: ....C++图形化好难搞......

其实严格意义上这次大作业在设计上有点失败，一开始想做一个功能非常齐全的系统，并且与前端稍微结合一下

结果发现好像不太行，等功能实现完了以后才发现设计有问题，为了更加易读还得重新再来一遍.....

还有一些没有实现的功能（BUG），也觉得有点可惜...

> * 登录页面的密码输入无法删除（由具体的实现方法导致）
> * 没有加入错误输入判断（随便乱输会直接退出）
> * 加密的密钥竟明文保存在代码中...信息文件也没能实现隐藏
> * 登录失败次数过多没有加上验证码功能

无所谓，那么现在就进行大作业的汇报吧...



## 实机演示画面

**首页：**

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517200155703.png" alt="image-20230517200155703" style="zoom:80%;" />

**登录情况：**

> * 登录成功
>   * 如果是以管理员( `admin` ) 身份登录的话，将会进入管理员功能界面
>   * 其他成员直接退出程序 （个人认为其他成员的功能不属于本系统范畴内）
> * 登录失败
>   * 返回主页面，让用户再次输入账号密码

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517200404351.png" alt="image-20230517200404351" style="zoom:80%;" />           	<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/erer.png" alt="image-20230517200442688" style="zoom:80%;" />



**管理员权限**

* 增加用户
* 修改用户信息
* 删除用户
* 导出用户信息

> **管理员功能页面：**
>
> 管理员通过输入数字选择相应的功能

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/Snipaste_2023-05-17_19-45-21.png" alt="Snipaste_2023-05-17_19-45-21" style="zoom:80%;" />

> **增加用户**
>
> 管理员只需要填写相应的信息即可创建

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/Snipaste_2023-05-17_19-47-55.png" alt="Snipaste_2023-05-17_19-47-55" style="zoom:80%;" />

> **修改用户信息**
>
> 管理员输入ID以及要修改的部分和内容即可，ID不存在会进行提示

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517201938909.png" alt="image-20230517201938909" style="zoom:80%;" />                    <img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/ghgh.png" alt="image-20230517202012479" style="zoom:80%;" />

> **删除用户**
>
> 管理员输入ID即可删除用户，ID不存在会进行提示

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517202148490.png" alt="image-20230517202148490" style="zoom:80%;" />                    <img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517202123045.png" alt="image-20230517202123045" style="zoom:80%;" />

> **导出数据**
>
> 一键导出，无需多虑

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517202946626.png" alt="image-20230517202946626" style="zoom:80%;" />            <img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517202716081.png" alt="image-20230517202716081" style="zoom:80%;" />

> **退出**
>
> 不做展示



## 代码讲解及思想表述

### 类图+设计初衷

<img src="https://gitee.com/qq3109778990/remem_pic/raw/master/img/image-20230517204831172.png" alt="image-20230517204831172" style="zoom:80%;" />



总体涉及知识点：

> 文件操作 + `window.h`的应用 + 匿名函数 + 字符串操作(哈希 + 密钥) + 类的继承 + map应用 + vector应用 + 基础算法 + 函数的重构



> * **GetPath类**
>
> > 设计之初主要是希望快速的获得账号保存信息的文件所在位置，是所有操作的基础
> >
> > 本意功能想直接实现在类内部，因为其他类由类似需求，所以部分封装为外置函数
> >
> > **涉及知识点** ： 文件操作 + `window.h`的应用

```c++
class GetPath{
protected:
    string PATH;
public:
    GetPath(){queryPath();};
    void queryPath();
};
```



> * **EditContent类**
>
> > 继承至 `GetPath`类，设计是为了将所有对于登录信息的操作封装在一起（避免代码中出现多次读取的情况）
> >
> > 单个人感觉写的比较乱，也许分开会更好，但不知道还有什么更加优雅的写法
> >
> > **涉及知识点** ： 匿名函数 + 字符串操作 + 类的继承 + 文件操作 + vector应用 + 基础算法

```c++
class EditContent : public GetPath{
protected:
    int type;
    vector<string> info;
public:
    EditContent(int type_, vector<string> info_) : GetPath(), type(type_), info(info_){};
    EditContent(){};
    bool Action();
};
```



> * **Creat类 / Change类 / Delete类 / ExportData类**
>
> > 这些类都是为了实现管理员权限的功能所设计的，为了能够可以得到信息后创建相应的类实现
> >
> > 但感觉实际上可以直接封装成函数而不是类，但个人觉得封装成类会不会更加清晰？
> >
> > **涉及知识点** ： 类的继承 + 函数的重构 + 文件操作

```c++
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
```



### 重要函数介绍

**passwordEncryption函数**

> 本函数采用与 `BKDRHash函数` 相同的思想，在算法竞赛领域被称为进制哈希，个人认为唯一的缺点是哈希值不能解码为密码
>
> 但如果是密码，加密后无法复原反而更能保证安全，至于需要复原的账号信息，则采用其他手段
>
> 本次哈希所采用的密钥为 **s = 131** 
>
> 根据 $hash = (\sum\limits_n a[n]s^n) \bmod 2^{31}$ , 且本系统的输入的 $ASCII < 127$ 情况下，提高了散列密度 ，散列质量和散列密度更佳
>
> 摒弃了取模操作，采用了 `unsigned long long int` 的自动改变，更加方便也具有更大的空间

```c++
// password encryption
string passwordEncryption(string password){
    unsigned long long Out = 0, key = 131, Mul = 1;
    for(int temp = 0 ; temp < password.size() ; temp++, Mul *= key)
        Out += password[temp] * Mul;
    string FIN = to_string(Out);
    return  FIN;
}
```



**accountEncryption函数**

> 采用了键值对的方式将密钥保存在代码中（具有安全的风险）， 分成了三个部分范围分别使用不同的密钥进行加密
>
> 为了迁就解密算法，所以只做了大小写字母以及数字的键值对应，如果未来进行该进会增加
>
> 对于三个 `key` 的选择，避开了常用字母，也许会有效果？

```c++
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
```



**accountDecode函数**

> 通过匿名函数寻找密钥中的位置，同时通过范围确定类型，同时进行解密

```c++
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
```



## 代码汇总展示

### main.cpp

```c++
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
    cout << "\t-     1: Add account\n\t-     2: Change account\n\t-";
    cout << "3: Delete account\n\t-     4: Expot data\n\t-     5: Back\n\t: ";
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
```



### CLASS.h

```cpp
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
```



### CLASS.cpp

```cpp
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
        //cout <<put <<"---\n";
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
```

