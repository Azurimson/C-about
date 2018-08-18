#include "config.h"
using namespace std;

void Config::setcharset(string cscmd)//设置字符集，根据参数直接从文件读取
{
    ifstream sin("charset");
    if(!sin.is_open()) {
        cout << "字符配置文件加载失败" << endl;
        system("pause");
        exit(-1);
    }
    int flag = 0;
    while(!sin.eof()){
        char cbuf[256];
        sin.getline(cbuf,255);
        string sbuf = cbuf;
        if(sbuf == cscmd)
        {
            flag = 1;
            sin.getline(this->charSet, 255);
            sbuf = this->charSet;
            this->charSetSize = sbuf.length();
        }
    }
    sin.close();
    if(flag == 0) {
        cout << "字符配置文件内容有误:" << endl;
        system("pause");
        exit(-1);
    }
}

string Config::getexten(string filename)//获取文件扩展名
{
    return filename.substr(filename.find_last_of('.') + 1);
}

void Config::setCmd(string exten)
{
    if(exten == "rar"){
        this->Cmd = "rar e -p";
    }
    else if (exten == "zip" || exten == "7z") {
        this->Cmd = "7z e -p";
    } else {
        cout << "不支持该种压缩类型" << endl;
        system("pause");
        exit(-1);
    }
}

Config::Config(int argc, char *argv[])//获取参数
{
    this->pcount = 0;
    if(argc == 5) {
        this->targetFile = argv[1];
        string exten = getexten(this->targetFile);
        setCmd(exten);
        this->minLength = atoi(argv[2]);
        this->maxLength = atoi(argv[3]);
        setcharset(argv[4]);
    }else if(argc == 2) {
        ifstream fin(argv[1]);
        if(!fin.is_open()) {
            cout << "配置文件加载失败" << endl;
            system("pause");
            exit(-1);
        }
        while(!fin.eof()){
            char cbuf[256];
            fin.getline(cbuf,255);
            string sbuf = cbuf;
            if(sbuf=="[Target]")
            {
                fin.getline(cbuf,255);
                this->targetFile = cbuf;
                string exten = getexten(this->targetFile);
                setCmd(exten);
            }
            else if(sbuf=="[min_length]")
            {
                fin.getline(cbuf,255);
                this->minLength = atoi(cbuf);
            }
            else if(sbuf=="[max_length]")
            {
                fin.getline(cbuf,255);
                this->maxLength = atoi(cbuf);
            }
            else if(sbuf=="[Charset]")
            {
                fin.getline(cbuf,255);
                setcharset(cbuf);
            }
            else{
                cout << "配置文件内容有误:" << endl;
                cout << sbuf << endl;
                system("pause");
                exit(-1);
            }
        }
        fin.close();
    }else {
        cout << "命令行参数错误" << endl;
        system("pause");
        exit(-1);
    }
}

//测试密码
bool Config::trypw(string targetFile,string password,string unrarFile){
    string cmd = this->Cmd + password + " " + targetFile + " >log";
    int f = system(cmd.c_str());
//    ofstream of("info", ios::app);//打印每次命令的返回值
//    of << f << endl;
//    of.close();
    if(f == 0)
        return true;
    return false;
}

//递归尝试密码
void Config::loop(string password,int current,int target) {
    if(current == target){
        system("cls");
//        ofstream op("password", ios::app);//打印尝试的每一个密码
//        op << password << endl;
//        op.close();
        this->pcount ++;
        cout << "当前尝试长度: " << target << endl;
        cout << "已尝试密码: " << this->pcount << "个" << endl;
        cout << "当前尝试密码: " << password << endl << endl;
        cout << "---------------------" << endl << endl;
        this->pcount ++;
        if(trypw(this->targetFile, password, this->Cmd)){
            cout << "破解成功:" << password << endl;
            system("pause");
            exit(0);
        }
        return;
    }
    for(int i = 0; i < this->charSetSize; i++){
        string newPassword = password + this->charSet[i];
        loop(newPassword, current+1, target); //当前密码长度+1
    }
}

void Config::start()
{
    system("cls");
    cout << "开始破解.." << endl;
    string password = "";
    for(int i = this->minLength; i <= this->maxLength; i++){
        loop(password, 0, i);
    }
}

void Config::print_parm()
{
    ofstream of("info");
    of << this->Cmd << endl;
    of << this->targetFile << endl;
    of << this->minLength << endl;
    of << this->maxLength << endl;
    of << this->charSet << endl;
    of << this->charSetSize << endl;
    of.close();
}
