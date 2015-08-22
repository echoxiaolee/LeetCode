/*
 * ��Ŀ������һ��ȫ�����ַ�����ɵ��ֵ䣬�ַ���ȫ���ɴ�д��ĸ���ɡ�����Ϊÿ���ַ�����д���룬��д��
 *       ��ʽ�Ƕ��� n λ�ַ���������һ�� n λ������д��ĸ�����ֵĶ�Ӧ��ʽ���յ绰���̵ķ�ʽ��
 *         2: A,B,C     5: J,K,L    8: T,U,V
 *         3: D,E,F     6: M,N,O    9: W,X,Y,Z
 *         4: G,H,I     7: P,Q,R,S
 *    ��Ŀ����һ��1--12λ�������ҳ����ֵ��г�����������������������ַ������ֵ����ַ����ĸ���������5000��
 *        
 * ˼·��1.���ݷ��ҳ����п��ܵ��ַ���
 *       2.���ֵ��в��Ҵ��ַ����Ƿ���ڡ����ֵ�洢���ù�ϣ��洢�� 
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)

#define HASHTABLE_LENGTH 5001  //��ϣ����
#define STRING_LENGTH   13     //������󳤶�

//�ַ���
typedef struct
{
	char str[STRING_LENGTH];
	int length;
}HString;

HString string={'\0',0};             //�ݴ���ܵ��ַ���
HString hashTable[HASHTABLE_LENGTH]; //��ϣ��

//hash����,�����ϣ��
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
		//�����ͻ������̽����ɢ��
		if(step>0)
    		step=-step;
		else{
			step=-step;
			step++;
		}
	}
}

//���ļ��ж��ֵ�
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
        if(ch=='\n'){//����һ���ַ���
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

//�ڹ�ϣ���в����Ƿ���ڸ��ַ���,���ڷ���1�������ڷ���0
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
		//�����ͻ������̽����ɢ��
		if(step>0)
    		step=-step;
		else{
			step=-step;
			step++;
		}
	}
	return 0;
}

//�����п��ܵ��ַ���
void getString(char* num)
{
	int i,digit,max;
	if(*num==0){//�ݹ���ڣ��ַ����ѵ�ĩβ
		string.str[string.length]='\0';
        if(search(string.str))//����ַ����������ֵ��У����
			puts(string.str);
		return;
	}

	digit=*num-'0';//ȡ��һλ�ַ���ת������
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
        getString(num+1); //�ݹ�
		string.length--;
	}
}

void main()
{
	char num[STRING_LENGTH];   //������������ֳ�����unsigned long�ķ�Χ���������ַ������洢
	readString();              //���ֵ���ļ��ж����ڴ�
    printf("please inputer an number(1--12λ,������0��1)\n");
    scanf("%s",num);
	getString(num);
}


