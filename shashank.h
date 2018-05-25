#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
struct MyStruct
{
	char Name[40], phonenumber[15], email[40];
};



char * tostr(MyStruct i){
	char *s = (char*)malloc(sizeof(char) * 256);
	sprintf(s, "%s,%s,%s", i.Name, i.phonenumber, i.email);
	return s;
}
int ctokenize(char *ip,char** S){
	int l = 0;
	char *token;
	token = strtok(ip, ",");
	while (token != NULL)
	{
		strcpy(S[l++], token);
		token = strtok(NULL, ",");
	}
	return l;

}
long long searchcontact(char *name,char *filename){
	char**  res;
	res = (char **)malloc(sizeof(char*) * 10);
	for (int i = 0; i < 10; i++)
		res[i] = (char*)malloc(sizeof(char) * 30);
	char buf[256];
	int l =0 ;
	long long pos;
	FILE *fp = fopen(filename, "r");
	pos = ftell(fp);
	fgets(buf, 256, fp);
	while (buf!=NULL)
	{
		l = ctokenize(buf, res);
		if (l < 3){
			fclose(fp);
			return -1;
		}
		else{
			if (strcmp(res[0], name) == 0){
				fclose(fp);
				return pos;
			}
		}
		pos = ftell(fp);
		fgets(buf, 256, fp);

	}
	fclose(fp);
	return -1;
	

}
char* getfilename(char *username){
	FILE *fp = fopen("metadata.csv","r");
	if (fp == NULL){
		printf("Meta Data Not found\n");
		return NULL;
	}
	char buf[256];
	char**  res;
	res = (char **)malloc(sizeof(char*) * 10);
	for (int i = 0; i < 10; i++)
		res[i] = (char*)malloc(sizeof(char) * 30);
	fgets(buf, 256, fp);
	while (buf != NULL){

		int len = ctokenize(buf,res);
		if (len < 3){
			fclose(fp);
			return NULL;
		}
		else
		{
			if (strcmp(username, res[0]) == 0){
				fclose(fp);
				return res[2];
			}
		}
	}
	fclose(fp);
	return NULL;
}



void addcontact(char* filename,MyStruct i){
	FILE *fp = fopen(filename, "a");
	if (fp == NULL){
		printf("File Name not found\n");
	}

	fprintf(fp,"%s\n", tostr(i));
	fclose(fp);

}
void updatecontact(char  *f, MyStruct i,long long pos){
	FILE *fp = fopen(f, "r+");
	if (fp == NULL){
		printf("File Not Found\n");
	}
	fseek(fp, pos,SEEK_SET);
	fprintf(fp, "%s\n", tostr(i));
	fclose(fp);
}


void addorupdate(char *f,MyStruct i){
	long long pos;
	pos = searchcontact(i.Name, f);
	if (pos == -1){
		addcontact(f, i);
	}
	else if(i.Name[0]!='!'){
		updatecontact(f, i, pos);
	}
	else{
		
	}
}

void pushtodb(char *username,MyStruct names[],int len){
	char  *f = getfilename(username);
	if (f == NULL){
		printf("User Name not found\n");
	}
	for(int  i=0;i<len;i++){
		addorupdate(f, names[i]);
	}
	return;

}