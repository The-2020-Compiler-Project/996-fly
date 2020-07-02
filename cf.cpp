#pragma once 
#include "preProcess.h"

static char kt[32][20] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"mian", "while"
};//�ؼ���kt
static char pt[40][5] = {
	"(",")","[","]","{","}","->",".","::","++","--","!","~","-","+","*","&","/","%","<<",
	">>","<","<=",">",">=","^","|","&&","||","?:","=","+=","-=","&="
	"|=",",",";","#",":",":="

};//���pt
static char it[1000][20] = { "" };//��ʶ��it
static char ct[1000] = { "" };//���ַ���ct
static char st[1000][20] = { "" };//�ַ�����st
static char c[1000][20] = { "" };//������c
int num_it = 0;//it��ʶ�������
int num_ct = 0;//���ַ���ct����
int num_st = 0;//�ַ�����st����
int num_c = 0;//������c����

//���ҹؼ���kt
int searchkt(char kt[][20], char s[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(kt[i], s) == 0)
		{
			return i + 1;//���ҳɹ�������syn
		}
		return -1;//����ʧ�ܣ�����-1����Ϊ��ʶ��
	}
}
//����ĳ�ַ����Ƿ���ĳ���г��֣���ά���飩
int searcht(char t[][20], char s[])
{
	for (int i = 0; t[i][0] != '/0'; i++)
	{
		if (strcmp(t[i], s) == 0)
		{
			return i + 1;//���ҳɹ�������syn
		}
		return -1;//����ʧ�ܣ�����ʱ�ñ���û�и��ַ�
	}
}
//�����ַ��Ƿ����ַ���ct�г���
int searchct(char c[],char s)
{
	for (int i = 0; c[i] != '/0'; i++)
	{
		if (c[i]==s)
		{
			return i + 1;//���ҳɹ�������syn
		}
		return -1;//����ʧ�ܣ�����ʱ�ñ���û�и��ַ�
	}
}
//�ж��ǲ�����ĸ
bool isletter(char ch)
{
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//�ж��ǲ�������
bool isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//ȡ�������ַ���ע��
void preresource(char r[], int pProject)
{
	int num_afrer = 0;//after_resource�±�
	char after_resource[10000];//�洢Ԥ������Դ����
	for (int i = 0; i < pProject; i++)
	{
		if (r[i] != '\n' && r[i] != '\r' && r[i] != '\t' && r[i] != '\v')
		{/*��ɨ�赽�����ַ���
		   �ո�\n���س�\r��ˮƽ�Ʊ��\t����ֱ�Ʊ��\v�������*/
			after_resource[num_afrer++] = r[i];
		}
		if (r[i] == '/' && r[i + 1] == '/')
		{//�����ע�Ϳ�ͷ��//��,����ע��
			while (r[i] != '\n')
			{//��Ϊ�վ�һֱ����ɨ��
				i++;
			}
		}
		if (r[i] == '/' && r[i + 1] == '*')
		{//����ע�Ϳ�ͷ��/*........*/��
			i += 2;
			while (r[i] != '*' || r[i + 1] != '/')
			{//û����������ע�ͽ�β��*/����һֱ����ɨ��
				i++;
				if (r[i] == '$')//'$'�ļ�������
				{
					cout << "ע�ʹ���" << endl;
					exit(0);//ע��û��"*/",����
				}
			}
			i += 2;//������*/������+2
		}
	}
	after_resource[num_afrer] = '\0';
	strcpy(r, after_resource);
}
void scanner(int& syn, char resourceproject[], char token[], int& pProject)
{//syn�ڸñ��˳��resourceprojectԴ����pProjectָ��
	FILE* fp1;
	if ((fp1 = fopen("d:\\text_cf1.txt", "at+")) == NULL)
	{
		cout << "can't open this file";
		exit(0);
	}
	int i, count = 0;//count������token[]ָʾ�����Ѽ������ַ�
	char ch='\0';//���ж�
	ch == resourceproject[pProject];
	while (ch == ' ')
	{//���˿ո�,��ֹʶ��ո��ֹͣ
		pProject++;
		ch == resourceproject[pProject];
	}
	for (i = 0; i < 20; i++)
	{//token�ռ�ǰ����
		token[i] = '\n';
	}
	if (isletter(resourceproject[pProject]))
	{//�����ͷΪ��ĸ
		token[count++] = resourceproject[pProject];//��¼
		pProject++;
		while (isletter(resourceproject[pProject]) || isdigit(resourceproject[pProject]))
		{//���������ĸ��������
			token[count++] = resourceproject[pProject];//��¼
			pProject++;
		}
		token[count] == '/0';
		syn = searchkt(kt, token);//�ж��Ƿ�Ϊ�ؼ��֣����򷵻ر���˳��
		if (syn == -1)
		{//���ǹؼ���
			syn = searcht(it, token);//�ж��Ƿ��Ѵ��ڱ�ʶ�����У������򷵻ر���˳�򣬷�֮����it��
			if (syn == -1)
			{
				strcpy(it[num_it++], token);//�����ʶ����
				syn = num_it;
			}
			cout << "<" << "it" << "," << syn << "," << it[syn - 1] << ">" << endl;
			fprintf(fp1, "<it,%d,%s>\n", syn, it[syn - 1]);
		}
		if (syn != -1)
		{//�ǹؼ���
			cout << "<" << "kt" << "," << syn << "," << kt[syn - 1] << ">" << endl;
			fprintf(fp1, "<kt,%d,%s>\n", syn, kt[syn - 1]);
		}
	}
	else if (isdigit(resourceproject[pProject]))
	{//�����ͷΪ����
		while (isdigit(resourceproject[pProject]))
		{
			token[count++] = resourceproject[pProject];
			pProject++;
		}
		token[count] = '/0';
		syn = searcht(c, token);//���ҳ�����
		if (syn == -1)
		{//������c��û�и�����
			strcpy(c[num_c++], token);
			syn = num_c;
		}
		cout << "<" << "c" << "," << syn << "," << c[syn - 1] << ">" << endl;
		fprintf(fp1, "<c,%d,%s>\n", syn, c[syn - 1]);
	}
	else if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' 
			|| ch == '}' ||  ch == '.'|| ch == '!' || ch == '~' || ch == '*' 
			|| ch == '/'|| ch == '%' || ch == '^' || ch == '?' ||ch == ','
			|| ch == '='|| ch == ';' || ch == '#')
	{//�����ͷΪ����������ǽ��
		token[0] = resourceproject[pProject];
		token[1] = '\0';//�γɵ��ַ���
		for (i = 0; i < 46; i++)
		{
			if (strcmp(token, pt[i]) == 0)
			{
				syn = i + 1;//�õ��÷����ڷ��ű�pt�е�˳��
				break;
			}
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '-')
	{// -> , - , -- , -=
		pProject++;
		if (resourceproject[pProject] == '>')
		{
			syn = 7;
		}
		else if (resourceproject[pProject] == '-')
		{
			syn = 11;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 33;
		}
		else
		{
			pProject--;
			syn = 14;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == ':')
	{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == ':')
		{
			syn = 9;
		 }
		else if (resourceproject[pProject] == '=')
		{
			syn = 40;
		}
		else
		{
			pProject--;
			syn = 39;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '+')
	{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '+')
		{
			syn = 10;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 32;
		}
		else
		{
			pProject--;
			syn = 15;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '&')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '&')
		{
			syn = 28;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 34;
		}
		else
		{
			pProject--;
			syn = 17;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
		}
	else if (resourceproject[pProject] == '<')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '<')
		{
			syn = 20;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 23;
		}
		else
		{
			pProject--;
			syn = 22;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '>')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '>')
		{
			syn = 21;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 25;
		}
		else
		{
			pProject--;
			syn = 24;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '|')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '|')
		{
			syn = 29;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 35;
		}
		else
		{
			pProject--;
			syn = 27;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '$')
	{//�Զ���$ ������
		syn = 0;
	}
	else
	{
		cout << "error:���ܱ�ʶ�� " << resourceproject[pProject] << endl;
		exit(0);
	}
	fclose(fp1);
}