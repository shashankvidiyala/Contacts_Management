void clear_screen()
{
	system("cls");
}

void press_any_key()
{
	printf("\nPress any key to return to main menu.");
	getch();
}

char *prompt(char *message)
{
	fflush(stdin);
	printf("\n%s", message);
	char *input = (char *)malloc(sizeof(char) * 50);
	gets(input);
	return input;
}


void print_headings()
{
	printf("\n%-30s %20s %30s", "Contact Name", "Phone Number","Email Id\n");
}