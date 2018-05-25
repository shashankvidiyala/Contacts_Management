
#pragma once
struct MyStruct
{
	char Name[40], phonenumber[15], email[40];
};



char * tostr(MyStruct i){
	char *s = (char*)malloc(sizeof(char) * 256);
	sprintf(s, "%s,%s,%s", i.Name, i.phonenumber, i.email);
	return s;
}
int ctokenize(char *ip, char** S){
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
long long searchcontact(char *name, char *filename){
	char**  res;
	res = (char **)malloc(sizeof(char*) * 10);
	for (int i = 0; i < 10; i++)
		res[i] = (char*)malloc(sizeof(char) * 30);
	char buf[256];
	int l = 0;
	long long pos;
	FILE *fp = fopen(filename, "r");
	pos = ftell(fp);
	fgets(buf, 256, fp);
	while (buf != NULL)
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
	FILE *fp = fopen("server_resources/credentials.csv", "r");
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

		int len = ctokenize(buf, res);
		if (len < 3){
			fclose(fp);
			return NULL;
		}
		else
		{
			if (strcmp(username, res[0]) == 0){
				fclose(fp);
				res[2][strlen(res[2]) - 1] = '\0';
				return res[2];
			}
		}
		fgets(buf, 256, fp);
	}
	fclose(fp);
	return NULL;
}



void addcontact(char* filename, MyStruct i){
	FILE *fp = fopen(filename, "a");
	if (fp == NULL){
		printf("File Name not found\n");
		return;
	}

	fprintf(fp, "%s\n", tostr(i));
	fclose(fp);

}
void updatecontact(char  *f, MyStruct i, long long pos){
	FILE *fp = fopen(f, "r+");
	if (fp == NULL){
		printf("File Not Found\n");
		return;
	}
	fseek(fp, pos, SEEK_SET);
	fprintf(fp, "%s\n", tostr(i));
	fclose(fp);
}
void deletecontact(char *uname, MyStruct i){
	char *str = getfilename(uname);
	if (str == NULL){
		printf("File not found\n");
		return;
	}
	long long pos = searchcontact(i.Name, str);
	if (pos == -1){
		printf("Contact not found\n");
		return;
	}
	else{
		FILE *fp = fopen(str,"r+");
		fseek(fp, pos, SEEK_SET);
		putc('!', fp);
		fclose(fp);
		return;
	}
}

void addorupdate(char *f, MyStruct i){
	long long pos;
	pos = searchcontact(i.Name, f);
	if (pos == -1){
		addcontact(f, i);
	}
	else if (i.Name[0] != '!'){
		updatecontact(f, i, pos);
	}
	else{
		deletecontact(f, i);
	}
}

void pushtodb(char *username, MyStruct names[], int len){
	char  *f = getfilename(username);
	if (f == NULL){
		printf("User Name not found\n");
		return;
	}
	for (int i = 0; i<len; i++){
		addorupdate(f, names[i]);
	}
	return;

}
//server
int k = iniatite_db();

struct Query_Result pull_user_data(char *username, int query_id = 0){
	struct Query_Result db_response = generate_pull_data(username, query_id);
	return db_response;
}


struct Query_Result send_request(char *PATH, char *data_record, char *user_name, int query_id){
	if (!strcmp(PATH, "pull/users_data/")){
		return pull_user_data(user_name, query_id);
	}
}

void pull(char *db_path){
	if (db_path != NULL)
	{
		FILE *local_db = fopen("localdb.csv", "w");
		struct Query_Result result;
		result.query_id = 0;
		do{
			result = send_request("pull/users_data/", NULL, db_path, result.query_id);
			if (result.query_id >= 0)
				fprintf(local_db, "%s", result.response);
		} while (result.query_id > 0);
		fclose(local_db);
	}
}


