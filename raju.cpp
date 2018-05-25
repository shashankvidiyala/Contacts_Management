#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct trie{
	int position;
	bool isEndOfWord;
	struct trie* next[26];
};

int Authenticateuser(char username[], char password[],char contactsfile[]){
	FILE *fp;
	char line[100],name[30],pass[30],path[50];
	int i = 0, j = 0;
	fp = fopen("accounts.txt", "r");
	while (fgets(line, 100, fp)){
		i = 0; j = 0;
		while (line[i] != ','){
			name[i] = line[i];
			i++;
		}
		name[i] = '\0';
		i++;
		while (line[i] != ','){
			pass[j] = line[i];
			i++; j++;
		}
		pass[j] = '\0';
		if (strcmp(name, username) == 0 && strcmp(pass, password) == 0){
			i++;
			j = 0;
			while (line[i] != '\0'){
				contactsfile[j] = line[i];
				i++; j++;
			}
			contactsfile[j] = '\0';
			fclose(fp);
			return 1;
		}
	}
	return 0;
}
char* Login(){
	char username[100],password[100],contactsfile[100];
	while (1){
		printf("Enter Username:");
		gets(username);
		printf("Enter Password:");
		gets(password);
		if (Authenticateuser(username, password,contactsfile)){
			printf("You are now logged in\n");
			return contactsfile;
		}
		printf("Invalid credentials\n");
	}
	
}
void Signup(){
	FILE *file;
	FILE *contacts;
	char path[100] = "C:\\PythonCourse\\MRND Summer\\Summerpro1\\Summerpro1\\";
	file = fopen("accounts.txt", "a");
	char name[20], password[20];
	printf("Enter your Name : ");
	scanf("%s", name);
	printf("Enter Password : ");
	scanf("%s", password);
	fprintf(file, "%s,", name);
	strcat(name, ".txt");
	contacts = fopen(name, "w");
	strcat(path, name);
	fprintf(file, "%s,", password);
	fprintf(file, "%s\n", path);
	fclose(file);
	fclose(contacts);
}

void logout(struct trie *root)
{
	int i = 0;
	for (i = 0; i < 26; i++)
	{
		if (root->next[i] != NULL)
		{
			logout(root->next[i]);
		}
		free(root);
	}
}

int main(){
	int op=0;
	char *contactsfile,path[200];
	
	while (1){
		printf("Choose an Option\n1.Login\n2.Signup\nEnter any option and press enter :");
		scanf("%d", &op);
		fflush(stdin);
		if (op == 1){
			contactsfile = Login();
			printf("%s", contactsfile);
			break;
		}
		else if (op == 2){
			Signup();
			break;
		}
		printf("Its an Invalid Option\n");
	}
	return 0;
}