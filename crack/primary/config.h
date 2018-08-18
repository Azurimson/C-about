#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct Config{
private:
    string Cmd;//��ѹ��������ļ����Ͳ�ͬ��zip��7z��7z��rar��rar
    string targetFile;//����·��
    int minLength;
    int maxLength;
    char charSet[256];//��Сд��ĸ-c ����-n �ո� �����ַ� -a
    int charSetSize;
    int pcount;//�������ѳ��Զ�������
public:
    Config(int argc, char *argv[]);//Ĭ�Ϲ��캯��
    void setcharset(string cscmd);//�����ַ�����Χ
    void setCmd(string exten);//���ý�ѹ�������
    string getexten(string filename);//��ȡ�ļ���չ��
    void start();
    void loop(string password, int current, int target);
    bool trypw(string targetFile, string password, string unrarFile);
    void print_parm();//��ӡ���в���
}Config;

#endif // CONFIG_H_INCLUDED
