
int isvalid(char name[], char word[])
{
	int length = strlen(name);
	if (name == NULL)
	{
		return -1;
	}
	if (word == NULL)
	{
		return -1;
	}
	for (int loop1 = 0; loop1 < length; loop1++)
	{
		if (name[loop1] >= 'a'&&name[loop1] <= 'z' || name[loop1] >= 'A'&&name[loop1] <= 'Z')
		{
			loop1++;
		}
		else
		{
			return -1;
		}
	}
}

int Authenticateuser(char username[], char password[], char contactsfile[]) {
	FILE *fp;
	char line[100], name[30], pass[30], path[50];
	int i = 0, j = 0;
	fp = fopen("server_resources/credentials.csv", "r");
	while (fgets(line, 100, fp)) {
		i = 0; j = 0;
		while (line[i] != ',') {
			name[i] = line[i];
			i++;
		}
		name[i] = '\0';
		i++;
		while (line[i] != ',') {
			pass[j] = line[i];
			i++; j++;
		}
		pass[j] = '\0';
		if (strcmp(name, username) == 0 && strcmp(pass, password) == 0) {
			i++;
			j = 0;
			while (line[i] != '\0'&&line[i] != '\n') {
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

char* login(char *uname)
{
	char username[100], password[100];
	char *contactsfile = (char *)malloc(100*sizeof(100));
	printf("Enter Username:");
	scanf("%s", &username);
	printf("Enter Password:");
	scanf("%s", &password);
	if (isvalid(username, password) == -1)
	{
		printf("invalid credentials");
	}
	else if (Authenticateuser(username, password, contactsfile))
	{
		printf("You Are Now Logged In");
		strcpy(uname, username);
		contactsfile[strlen(contactsfile) - 1] = '\0';
		return contactsfile;
	}
	else
	{
		printf("Invalid credentials\n");
	}
	//getchar();
	return NULL;
}

int check(char username[]) {
	FILE *fp;
	char line[100], name[30], pass[30], path[50];
	int i = 0, j = 0;
	fp = fopen("server_resources/credentials.csv", "r");
	while (fgets(line, 100, fp)) {
		i = 0; j = 0;
		while (line[i] != ',') {
			name[i] = line[i];
			i++;
		}
		name[i] = '\0';
		i++;
		if (strcmp(name, username) == 0)
		{
			return -1;
		}
	}
	return 0;
}

void signup()
{
	FILE *file;
	FILE *contacts;
	char path[100];
	getcwd(path, 100);
	strcat(path, "\\server_resources");
	file = fopen("server_resources/credentials.csv", "a");
	char name[20], password[20];
	printf("enter the username ");
	scanf("%s", name);
	printf("enter the password ");
	scanf("%s", password);
	if (isvalid(name, password) == -1)
	{
		printf("\nInvalid Credentials");
	}
	else if (check(name) == -1)
	{
		printf("\nUsername already exits");
	}
	else
	{
		fprintf(file, "%s,", name);
		strcat(name, ".csv");
		strcat(path, "\\");
		strcat(path, name);
		contacts = fopen(path, "w");
		fprintf(file, "%s,", password);
		fprintf(file, "%s\n", path);
	}
	fclose(file);
	getchar();
}

void logout(trie *root)
{
	if (root != NULL)
	{
		int i = 0;
		for (i = 0; i < 26; i++) {
			if (root != NULL) {
				logout(root->next[i]);
			}
			free(root);
			root = NULL;
		}
	}
}