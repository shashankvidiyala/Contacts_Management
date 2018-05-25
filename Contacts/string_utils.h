char **splitString(char *input, const char *delimter, int *count)
{
	char **words = (char **)malloc(sizeof(char *) * 20);
	for (int i = 0; i < 20; i++)
		words[i] = (char *)malloc(sizeof(char) * 20);
	char *token = strtok(input, delimter);
	int i = 0;
	while (token != NULL)
	{
		sprintf(words[i++], "%s", token);
		token = strtok(NULL, delimter);
	}
	*count = i;
	return words;
}


int isValidName(char *name)
{
	int i;
	if (strlen(name) == 0)
		return 0;
	for (i = 0; i < strlen(name); i++)
	{
		if (!((name[i] >= 'a'&&name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')))
			return 0;
	}
	return 1;
}

int isValidNumber(char *num)
{
	int i;
	for (i = 0; i < strlen(num); i++)
	{
		if (!((num[i] >= '0'&&num[i] <= '9') || num[i] == '+'))
			return 0;
	}
	return 1;
}

int isValidMail(char *mail)
{
	int i = 0;
	while (mail[i] != '@'&&i<strlen(mail))
		i++;
	if (i == strlen(mail) || i == 0)
		return 0;
	int at = i;
	while (mail[i] != '.'&&i<strlen(mail))
		i++;
	if (i == at + 1 || i >= strlen(mail) - 1)
		return 0;
	return 1;

}

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

