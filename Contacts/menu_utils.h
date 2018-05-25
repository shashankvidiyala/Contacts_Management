void show_authentication_menu();
char *user_name = (char*)malloc(sizeof(char) * 40);
void show_main_menu(trie *trie_head, char *contact_file)
{
	clear_screen();
	trie_head = load_the_data(contact_file);
	printf("--Main Menu--");
	printf("\n1.Add Contact");
	printf("\n2.Search a contact");
	printf("\n3.View Contacts");
	printf("\n4.Delete Contact");
	printf("\n5.Edit Contact");
	printf("\n6.Logout");
	printf("\n7.Push");
	printf("\n8.Exit");
	char *ch;
	ch = prompt("Enter your choice:");
	switch (*ch)
	{
	case '1':
		clear_screen();
		add(trie_head, contact_file);
		break;
	case '2':
		clear_screen();
		search(trie_head, contact_file);
		break;
	case '3':
		clear_screen();
		print_headings();
		view(trie_head, contact_file);
		break;
	case '4':
		clear_screen();
		delet(trie_head, contact_file);
		break;
	case '5':
		clear_screen();
		edit(trie_head, contact_file);
		break;
	case '6':
		clear_screen();
		logout(trie_head);
		show_authentication_menu();
		break;
	case '7':
		push(user_name);
		break;
	case '8':
		exit(0);
		break;
	}
	press_any_key();
	show_main_menu(trie_head, contact_file);
}

void show_authentication_menu()
{
	clear_screen();
	trie *trie_head;
	char *contact_file;
	printf("--Authentication Menu--");
	printf("\n1.Login");
	printf("\n2.Signup");
	printf("\n3.Exit");
	char *ch = prompt("Enter your choice:");
	switch (*ch)
	{
	case '1':
		clear_screen();
		contact_file = login(user_name);
		if (contact_file == NULL)
			break;
		pull(contact_file);
		strcpy(contact_file, "localdb.csv");
		trie_head = load_the_data(contact_file);
		if (contact_file != NULL){
			show_main_menu(trie_head, contact_file);
			return;
		}
		break;
	case '2':
		signup();
		break;
	case '3':
		exit(0);
		break;
	}
	printf("\nPress any key to return to Authentication Menu.");
	_getch();
	show_authentication_menu();
}
