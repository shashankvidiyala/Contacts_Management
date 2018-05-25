#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>


typedef struct trie
{
	struct trie *next[26];
	long int fpValue;
	bool isEndOfWord;
};

int strlength(char *string)
{
	int i = 0;
	while (string[i] != '\0')
		i++;
	return i;
}



int char_to_index(char ch)
{
	if (ch > 91)
		return ch - 97;
	else
		return ch - 65;
}

long int search_contact(trie *root,char *name)
{

	int index = 0;
	int length = strlength(name);
	trie *temp = root;
	for (int iter = 0; iter < length; iter++)
	{
		index = char_to_index(name[iter]);

		if (temp->next[index])
		{
			return 0;
		}

		temp = temp->next[index];
	}

	if (temp->isEndOfWord)
		return temp->fpValue;
	else
	{

	}
		return -1;
}


int isValidName(char *name)
{
	int i;
	for (i = 0; i < strlength(name); i++)
	{
		if (!((name[i] > 'a'&&name[i]<'z') || (name[i]>'A' || name[i] < 'Z')))
			return 0;
	}
	return 1;
}

int isValidNumber(char *num)
{
	int i;
	for (i = 0; i < strlength(num); i++)
	{
		if (!((num[i] >= '0'&&num[i] <= '9') || num[i] == '+'))
			return 0;
	}
	return 1;
}

int isValidMail(char *mail)
{
	int i = 0;
	while (mail[i] != '@'&& mail[i] != '\0')
		i++;
	if (i == strlength(mail) || i == 0)
		return 0;
	int at = i;
	while (mail[i] != '.')
		i++;
	if (i == at + 1 || i >= strlength(mail) - 1)
		return 0;
	return 1;

}

int add_contact(trie *root, char *fileName, char *name, char *phno, char *mail)
{
	if (!isValidName(name))
		return -1;
	if (!(isValidNumber(phno)))
		return -1;
	if (!(isValidMail(mail)))
		return -1;
	/*long int record_pos = search_contact(root, name);*/
	int record_pos = -1;
	if (record_pos != -1)
	{
		return -1;
	}
	FILE *fp = fopen(fileName, "r+");
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s,%s,%s\n", name, phno, mail);

	fclose(fp);
}



void edit(trie * root,char *contact_file,char *name)
{
	FILE *fp;
	char *buffer = (char*)malloc(sizeof(char) * 50);
	char *new_name = (char*)malloc(sizeof(char) * 30);
	char *phoneno = (char*)malloc(sizeof(char) * 11);
	char *email = (char*)malloc(sizeof(char) * 40);


	fp = fopen(contact_file, "r+");
	fseek(fp,5, SEEK_SET);
	printf("%s", fgets(buffer,50,fp));
	buffer[0] = '!';
	fseek(fp, 5, SEEK_SET);
	fprintf(fp, "%s", buffer);	

	printf("Enter new Name:\n");
	gets(new_name);
	printf("Enter new Phone number\n");
	gets(phoneno);
	printf("Enter Email Id\n");
	gets(email);

	fclose(fp);
	add_contact(root,contact_file, new_name, phoneno, email);
	
	
}






int main()
{

	/*printf("%d %d", char_to_index('Z'), char_to_index('z'));*/
	edit(NULL,"xyz.txt","hello");
	system("pause");
	return 0;
}