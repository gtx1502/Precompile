#include <stdio.h>
#include <iostream>  
#include <fstream>
#include <sstream>
#include <string> 
#include <string.h>
#include <stdlib.h>

using namespace std;

#define inString "#include"
#define defString "#define"
#define unString "#undef"
#define ifdefString "#ifdef"
#define ifndefString "#ifndef"
#define ifString "#if"
#define elifString "#elif"
#define elseString "#else"
#define endString "#endif"

string define_array[99];
string define_array1[99];
string value_array[99];
char parameter_array[99];	//part3 x
int count=0;	//define数组长度（有值）
int count1=0;	//define数组长度（无值）
int ifMark=0;	//是否在if类关键字作用范围
int isTrue=0;	//if类关键字后面内容是否为真
int notReplace=0;
int main()
{
	char* get_str(const char *str,string buf);
	string str_replace(int i,char a);
	int compare(char ch[257],string symbol);
	ifstream in;
	ofstream out;
	string buf;	//读入字符串
	string bufArray[99999];//暂时存储字符串数组
	int num=0;
	string out_buf;//输出字符串

	/*打开读入文件*/
	in.open("test.cpp");
	//in.open("test_2.cpp");
	if(!in){  
		cout<<"error"<<buf<<endl;
		return 1;
	}

	/*打开输出文件*/
	out.open("result.cpp");
	//out.open("result_2.cpp");

	/*处理#include*/
	while(getline(in,buf)){
		char *inChar = get_str(inString,buf);
		if(inChar!=NULL){
			inChar=inChar+9;
			if(*inChar=='"'){
				string s(inChar);
				int np=s.find_last_of('"');
				string str1=s.substr(1,np-1);
				const char *c1=str1.c_str();
				ifstream h_in;
				h_in.open(c1);
				if(!h_in){ //该文件打开失败 
					cout<<"error"<<endl;
				}
				string buf1;
				while(getline(h_in,buf1)){
					bufArray[num]=buf1;
					num++;
				}
				continue;
			}
			else{
				bufArray[num]=buf;
				num++;
			}
		}
		else{
			bufArray[num]=buf;
			num++;
		}
	}

	/*#include后*/

	for(int j=0;j<num;j++){
		char *ifdef_char=get_str(ifdefString,bufArray[j]);
		char *ifndef_char=get_str(ifndefString,bufArray[j]);
		char *if_char=get_str(ifString,bufArray[j]);
		char *elif_char=get_str(elifString,bufArray[j]);
		char *else_char=get_str(elseString,bufArray[j]);
		char *end_char=get_str(endString,bufArray[j]);
		char *def_char=get_str(defString,bufArray[j]);
		char *undef_char=get_str(unString,bufArray[j]);

		/*处理#endif*/
		if(end_char!=NULL){
			ifMark=0;
			isTrue=0;
			continue;	//跳过#endif行
		}

		/*处理#ifdef*/
		if(ifdef_char!=NULL){
			ifMark=1;
			ifdef_char+=7;
			string s1(ifdef_char);
			for(int i=0;i<count;i++){
				if(s1==define_array[i]){
					isTrue=1;
				}
			}
			for(int i=0;i<count1;i++){
				if(s1==define_array1[i]){
					isTrue=1;
				}
			}
			continue;//跳过#ifdef行
		}

		/*处理#ifndef*/
		if(ifndef_char!=NULL){
			ifMark=1;
			isTrue=1;
			ifndef_char+=8;
			string s1(ifndef_char);
			for(int i=0;i<count;i++){
				if(s1==define_array[i]){
					isTrue=0;
				}
			}
			for(int i=0;i<count1;i++){
				if(s1==define_array1[i]){
					isTrue=0;
				}
			}
			continue;//跳过#ifndef行
		}
		stringstream ss_stream;
		char bField[4][257];
		memset(bField,0,sizeof(bField));
		ss_stream<<bufArray[j];
		ss_stream.getline(bField[0],99,' ');
		ss_stream.getline(bField[1],99,' ');
		ss_stream.getline(bField[2],99,' ');
		ss_stream.getline(bField[3],99,' ');
		
		/*处理#if 处理#elif 处理#else*/
		if(if_char!=NULL||elif_char!=NULL||else_char!=NULL){
			notReplace=1;
			ifMark=1;
			int comp;
			if(bField[2][0]==0){	//不存在与或运算
				comp=compare(bField[1],">=");
				if(comp==1){
					isTrue=1;
					continue;
				}
				else if(comp==0){
					isTrue=0;
					continue;
				}
				comp=compare(bField[1],"<=");
				if(comp==1){
					isTrue=1;
					continue;
				}
				else if(comp==0){
					isTrue=0;
					continue;
				}
				comp=compare(bField[1],"==");
				if(comp==1){
					isTrue=1;
					continue;
				}
				else if(comp==0){
					isTrue=0;
					continue;
				}
				comp=compare(bField[1],">");
				if(comp==1){
					isTrue=1;
					continue;
				}
				else if(comp==0){
					isTrue=0;
					continue;
				}
				comp=compare(bField[1],"<");
				if(comp==1){
					isTrue=1;
					continue;
				}
				else if(comp==0){
					isTrue=0;
					continue;
				}
			}

			if(bField[2][0]=='&'&&bField[2][1]=='&'){
				int isTrue1;
				int isTrue2;
				comp=compare(bField[1],">=");
				if(comp==1)
					isTrue1=1;
				else if(comp==0)
					isTrue1=0;
				comp=compare(bField[1],"<=");
				if(comp==1)
					isTrue1=1;
				else if(comp==0)
					isTrue1=0;
				comp=compare(bField[1],"==");
				if(comp==1)
					isTrue1=1;
				else if(comp==0)
					isTrue1=0;
				comp=compare(bField[1],">");
				if(comp==1)
					isTrue1=1;
				else if(comp==0)
					isTrue1=0;
				comp=compare(bField[1],"<");
				if(comp==1)
					isTrue1=1;
				else if(comp==0)
					isTrue1=0;
				comp=compare(bField[3],">=");
				if(comp==1)
					isTrue2=1;
				else if(comp==0)
					isTrue2=0;
				comp=compare(bField[3],"<=");
				if(comp==1)
					isTrue2=1;
				else if(comp==0)
					isTrue2=0;
				comp=compare(bField[3],"==");
				if(comp==1)
					isTrue2=1;
				else if(comp==0)
					isTrue2=0;
				comp=compare(bField[3],">");
				if(comp==1)
					isTrue2=1;
				else if(comp==0)
					isTrue2=0;
				comp=compare(bField[3],"<");
				if(comp==1)
					isTrue2=1;
				else if(comp==0)
					isTrue2=0;
				if(isTrue1==1&&isTrue2==1){
					isTrue=1;
					continue;
				}
				else{
					isTrue=0;
					continue;
				}
			}
		}
		ss_stream.clear();

		if(ifMark==1&&isTrue==0){	//跳过该行
			continue;
		}

		/*替换define内容*/
		if(def_char==NULL&&undef_char==NULL){
			for(int i=0;i<count;i++){
				char* c; 
				const int len = define_array[i].length(); 
				c = new char[len+1]; 
				strcpy(c,define_array[i].c_str());
				char *replace=get_str(c,bufArray[j]);
				string::size_type position;
				position=bufArray[j].find(define_array[i]);
				if(position != bufArray[j].npos){
					if(notReplace==1){}
					else{
						//part3
						if(parameter_array[i]!=0){
							string::size_type position1,position2;
							position1=bufArray[j].find("(");
							string str=str_replace(i,bufArray[j][position1+1]);
							bufArray[j]=bufArray[j].replace(position,define_array[i].length()+3,str);
							for(int k=0;k<count;k++){
								position2=bufArray[j].find(define_array[k]);
								if(position2!=bufArray[j].npos){
									int position3=bufArray[j].find_last_of("(");
									string str1=str_replace(k,bufArray[j][position3+1]);
									cout<<str1<<endl;
									bufArray[j]=bufArray[j].replace(position2,define_array[k].length()+3,str1);
								}
							}
							cout<<bufArray[j]<<endl;
						}
						//part2
						else
							bufArray[j]=bufArray[j].replace(position,len,value_array[i]);
					}
				}
			}
			if(bufArray[j].length()!=0)
				out_buf=out_buf+bufArray[j]+"\n";
		}

		/*处理#define*/
		if(def_char!=NULL){
			def_char+=8;
			string s1(def_char);
			string::size_type position;
			int np=s1.find_last_of(' ');
			if(np>=0){
				string str1=s1.substr(0,np);
				position=str1.find("(");
				//part2 有值
				if(position==s1.npos){
					def_char+=(np+1);
					string s2(def_char);
					define_array[count]=str1;
					value_array[count]=s2;
					count++;
				}
				//part3
				else{
					int np=s1.find_last_of(' ');
					if(np>=0){
						string str1=s1.substr(0,np);
						def_char+=(np+1);
						int np=str1.find_first_of('(');
						string s2(def_char);
						define_array[count]=str1.substr(0,np);
						value_array[count]=s2;
						parameter_array[count]=s1[position+1];
						count++;
					}
				}
			}
			//part2 无值
			else{
				string s(def_char);
				define_array1[count1]=s;
				count1++;
			}			
		}
		
		/*处理#undef*/
		if(undef_char!=NULL){	
			undef_char+=7;
			string s1(undef_char);
			for(int i=0;i<count;i++){
				if(s1==define_array[i]){
					if(i==count-1){
						define_array[i]="";
						value_array[i]="";
					}
					else{
						define_array[i]=define_array[count-1];
						value_array[i]=value_array[count-1];
						define_array[count-1]="";
						value_array[count-1]="";
					}
					continue;
				}
			}
			for(int i=0;i<count1;i++){
				if(s1==define_array1[i]){
					if(i==count1-1)
						define_array1[i]="";
					else{
						define_array1[i]=define_array1[count1-1];
						define_array1[count1-1]="";
					}
					continue;
				}
			}
		}
		
	}
	out<<out_buf<<endl;
	return 0;
}

/*
*参数：字符串和比较符
*
*返回值：
*比较符不存在：-1
*比较结果为真：1
*比较结果为假：0
*
*/
int compare(char ch[257],string symbol){
	string::size_type position;
	string temp(ch);
	position=temp.find(symbol);
	string temp1="";
	string temp2="";
	int left;
	int right;
	if(position != temp.npos){
		for(int i=0;i<position;i++)
			temp1+=ch[i];
		if(symbol==">="||symbol=="<="||symbol=="=="){
			for(int i=position+2;ch[i]!=0;i++)
				temp2+=ch[i];
		}
		else{
			for(int i=position+1;ch[i]!=0;i++)
				temp2+=ch[i];
		}
		for(int i=0;i<count;i++){
			if(temp1==define_array[i]){
				left=atoi(value_array[i].c_str());
			}
		}
		right=atoi(temp2.c_str());
		if(symbol==">="){
			if(left>=right)
				return 1;
			else
				return 0;
		}
		else if(symbol=="<="){
			if(left<=right)
				return 1;
			else
				return 0;
		}
		else if(symbol=="=="){
			if(left==right)
				return 1;
			else
				return 0;
		}
		else if(symbol==">"){
			if(left>right)
				return 1;
			else
				return 0;
		}
		else if(symbol=="<"){
			if(left<right)
				return 1;
			else
				return 0;
		}
	}
	return -1;	//不存在该符号
}

/*
*i:数组下标 a：test_2中的a
*返回：一次替换后的字符串
*/
string str_replace(int i,char a){
	string::size_type position,position1;
	position=value_array[i].find(parameter_array[i]);
	string str=value_array[i];
	str[position]=a;
	string substr=str.substr(position+1);
	int j=0;
	do{
		j++;
		position1=substr.find(parameter_array[i]);
		if(position1==substr.npos)
			break;
		substr=substr.substr(position1+1,substr.length()-position1-1);
		str[position+position1+j]=a;
	}
	while(position1!=substr.npos);
	return str;
}
/*
*判断是否有某个关键字
*/
char* get_str(const char *str,string buf){		
	const char *includeStr=str;
	const char *bufArray = buf.c_str();
	char *bufArray1=new char[strlen(bufArray)+1];
	strcpy(bufArray1, bufArray);
	char *c = strstr(bufArray1,includeStr);
	return c;
}
