/*
 * 题目：给定一个全部由字符串组成的字典，字符串全部由大写字母构成。其中为每个字符串编写密码，编写的
 *       方式是对于 n 位字符串，给定一个 n 位数，大写字母与数字的对应方式按照电话键盘的方式：
 *         2: A,B,C     5: J,K,L    8: T,U,V
 *         3: D,E,F     6: M,N,O    9: W,X,Y,Z
 *         4: G,H,I     7: P,Q,R,S
 *    题目给出一个1--12位的数，找出在字典中出现且密码是这个数的所有字符串。字典中字符串的个数不超过5000。
 *        
 * 思路：1.回溯法找出所有可能的字符串
 *       2.在字典中查找此字符串是否存在。（字典存储采用哈希表存储） 
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

#define HASHTABLE_LENGTH 5001  //哈希表长度
#define STRING_LENGTH   13     //单词最大长度

//字符串
typedef struct
{
	char str[STRING_LENGTH];
	int length;
}HString;

HString string={'\0',0};             //暂存可能的字符串
HString hashTable[HASHTABLE_LENGTH]; //哈希表

//hash函数,构造哈希表
void createHashTable(char *str)
{
	int i,key,step=1;
	i=key=0;
	while(str[i]){
		key+=str[i++]-'A';
	}
	key%=HASHTABLE_LENGTH;
	while(1){
		if(hashTable[key].length==0){
			hashTable[key].length=strlen(str);
			strcpy(hashTable[key].str,str);
			break;
		}
		key=(key+step+HASHTABLE_LENGTH)%HASHTABLE_LENGTH;
		//处理冲突，线性探测再散列
		if(step>0)
    		step=-step;
		else{
			step=-step;
			step++;
		}
	}
}

//从文件中读字典
void readString()
{
	int i;
	char str[STRING_LENGTH];
	char ch;
	FILE *fp;
    if((fp=fopen("document/dictionary.txt","r"))==NULL){   
       printf("can not open file!\n");   
       exit(0);   
    }  
	
    i=0;
    while((ch=getc(fp))!=EOF){   
        if(ch=='\n'){//读完一个字符串
			str[i]='\0';
            createHashTable(str);
			i=0;
			continue;
		}
		str[i++]=ch;
	}

    if(fclose(fp)){   
        printf("can not close file!\n");   
        exit(0);   
    }   
}

//在哈希表中查找是否存在该字符串,存在返回1，不存在返回0
int search(char *str)
{
	int i,key,step=1;
	i=key=0;
	while(str[i]){
		key+=str[i++]-'A';
	}
	key%=HASHTABLE_LENGTH;
	while(1){
		if(hashTable[key].length==0)
			return 0;
		if(strcmp(hashTable[key].str,str)==0){
			return 1;
		}
		key=(key+step+HASHTABLE_LENGTH)%HASHTABLE_LENGTH;
		//处理冲突，线性探测再散列
		if(step>0)
    		step=-step;
		else{
			step=-step;
			step++;
		}
	}
	return 0;
}

//求所有可能的字符串
void getString(char* num)
{
	int i,digit,max;
	if(*num==0){//递归出口，字符串已到末尾
		string.str[string.length]='\0';
        if(search(string.str))//这个字符串存在于字典中，输出
			puts(string.str);
		return;
	}

	digit=*num-'0';//取第一位字符，转成数字
	if(digit>=2&&digit<=6){
		i=(digit-2)*3+'A';
		max=(digit-2)*3+'A'+3;
	}
	else if(digit==7){
		i='P';
		max='P'+4;
	}
	else if(digit==8){
		i='T';
		max='T'+3;
	}
	else if(digit==9){
		i='W';
		max='W'+4;
	}

	for(i;i<max;i++){
		string.str[string.length++]=i;
        getString(num+1); //递归
		string.length--;
	}
}

void main()
{
	char num[STRING_LENGTH];   //由于输入的数字超出了unsigned long的范围，所以用字符串来存储
	readString();              //把字典从文件中读入内存
    printf("please inputer an number(1--12位,不能有0或1)\n");
    scanf("%s",num);
	getString(num);
}


