#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>


int isValidName(char *name)
{
	int i;
	for (i = 0; i < strlen(name); i++)
	{
		if (!((name[i] > 'a'&&name[i]<'z') || (name[i]>'A' || name[i] < 'Z')))
			return 0;
	}
	return 1;
}

int isValidNumber(char *num)
{
	int i;
	for (i = 0; i < strlen(num); i++)
	{
		if (!((num[i] >= '0'&&num[i]<='9') ||num[i]=='+'))
			return 0;
	}
	return 1;
}

int isValidMail(char *mail)
{
	int i=0;
	while (mail[i] != '@'&&i<strlen(mail))
		i++;
	if (i == strlen(mail) || i == 0)
		return 0;
	int at = i;
	while (mail[i] != '.'&&i<strlen(mail))
		i++;
	if (i == at + 1 || i >= strlen(mail)-1)
		return 0;
	return 1;

}

bool add_contact(trie *root, char *fileName, char *name, char *phno, char *mail)
{
	if (!isValidName(name))
		return 0;
	if (!(isValidNumber(phno)))
		return 0;
	if (!(isValidMail(mail)))
		return 0;
	long int record_pos = search_contact(root, name);
	if (record_pos != -1)
	{
			return 0;
	}
	FILE *fp = fopen(fileName, "r+");
	if (fp == NULL)
		return 0;
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s,%s,%s\n",name,phno,mail);

	fclose(fp);
	return 1;
}
