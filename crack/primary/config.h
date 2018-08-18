#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct Config{
private:
    string Cmd;//解压命令，根据文件类型不同，zip和7z用7z，rar用rar
    string targetFile;//绝对路径
    int minLength;
    int maxLength;
    char charSet[256];//大小写字母-c 数字-n 空格 所有字符 -a
    int charSetSize;
    int pcount;//计数，已尝试多少密码
public:
    Config(int argc, char *argv[]);//默认构造函数
    void setcharset(string cscmd);//设置字符集范围
    void setCmd(string exten);//设置解压命令及参数
    string getexten(string filename);//获取文件扩展名
    void start();
    void loop(string password, int current, int target);
    bool trypw(string targetFile, string password, string unrarFile);
    void print_parm();//打印所有参数
}Config;

#endif // CONFIG_H_INCLUDED
