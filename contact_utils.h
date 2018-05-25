
//node creation and initialization
trie *createNode() {

	trie *temp = (trie *)malloc(sizeof(trie));
	for (int i = 0; i < 26; i++) {
		temp->next[i] = NULL;
	}
	temp->fpValue = NULL;
	temp->isEndOfWord = false;

	return temp;
}

//inserting into trie
void insertIntoTrie(trie *root, char *name, int pos) {

	int i = 0;
	trie *curr = root;
	while (name[i] != '\0'){

		if (root == NULL) {

			root = createNode();
			curr = root;
		}

		if (curr->next[name[i] - 'a'] == NULL) {

			curr->next[name[i] - 'a'] = createNode();
		}

		curr = curr->next[name[i] - 'a'];
		i++;

	}

	curr->fpValue = (int *)malloc(sizeof(int));
	*(curr->fpValue) = pos;
	curr->isEndOfWord = true;
}


trie * load_the_data(char *filename) {
	if (filename == NULL)
		return NULL;
	FILE *f = fopen(filename, "r+");
	char buff[100];
	trie *root = NULL;
	while (true) {
		int pos;

		pos = ftell(f);
		if (fscanf(f, "%[^\n]\n", buff) == EOF) {
			break;
		}

		char *name = strtok(buff, ",");
		insertIntoTrie(root,_strlwr(name), pos);
	}
	return root;

}


long int search_contact(trie *root, char *name)
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
		return *(temp->fpValue);
	return -1;
}



bool add_contact(trie *root, char *fileName, char *name, char *phno, char *mail)
{
	if (!(isValidName(name) && isValidNumber(phno) && isValidMail(mail)))
		return false;
	long int record_pos = search_contact(root, name);
	if (record_pos != -1)
	{
		return false;
	}
	FILE *fp = fopen(fileName, "r+");
	if (fp == NULL)
		return false;
	fseek(fp, 0, SEEK_END);
	fprintf(fp, "%s,%s,%s\n", name, phno, mail);

	fclose(fp);
	return true;
}



bool edit_contact(trie * root, char *contact_file, char *name)
{
	FILE *fp;
	char *buffer = (char*)malloc(sizeof(char) * 50);
	char *new_name = (char*)malloc(sizeof(char) * 30);
	char *phoneno = (char*)malloc(sizeof(char) * 11);
	char *email = (char*)malloc(sizeof(char) * 40);


	fp = fopen(contact_file, "r+");
	fseek(fp, 5, SEEK_SET);
	printf("%s", fgets(buffer, 50, fp));
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
	if (add_contact(root, contact_file, new_name, phoneno, email))
		return true;
	return false;

}

void add(trie *trie_head, char *contact_file)
{
	char *name, *phonenum, *email;
	name = prompt("Enter the Contact Name:");
	phonenum = prompt("Enter the Contact Phone Number:");
	email = prompt("Enter the Contact Email:");
	if (add_contact(trie_head, contact_file, name, phonenum, email))
		printf("Contact added Successfully");
	else
		printf("Failed to add the contact");
}


void print_contact(char *contact)
{
	int count = 0;
	char **splitted_string = splitString(contact, ",", &count);
	if (count == 3)
	{
		splitted_string[count - 1][strlen(splitted_string[count - 1]) - 1] = '\0';
		printf("\n%-30s %20s %30s", splitted_string[0], splitted_string[1], splitted_string[2]);
	}
	else
	{
		printf("\nUnable to view contact");
	}
}


int view_contact_by_name(trie *trie_head, char *contact_file, char *name)
{

	if (trie_head == NULL || contact_file == NULL || name == NULL)
		return 0;
	//int pointer_position = search_contact(trie_head, name);
	int pointer_position = 0;
	FILE *fptr = fopen(contact_file, "r");
	fseek(fptr, pointer_position, SEEK_SET);
	char contact_details[500];
	fgets(contact_details, 500, fptr);
	print_contact(contact_details);
}

void search(trie *trie_head, char *contact_file)
{
	if (trie_head == NULL || contact_file == NULL )
		return;
	char *name = prompt("Enter the contact name:");
	print_headings();
	view_contact_by_name(trie_head,contact_file, name);
}


void view_all_contacts(trie *trie_node, FILE *fptr)
{
	if (trie_node == NULL || fptr == NULL)
		return;
	for (int iter = 0; iter < 26; iter++)
	{
		if (trie_node->isEndOfWord == true)
		{
			int position = *(trie_node->fpValue);
			fseek(fptr, position, SEEK_SET);
			char contact[500];
			fgets(contact, 500, fptr);
			print_contact(contact);
		}
		for (int iter2 = 0; trie_node->next[iter2] != NULL; iter2++)
		{
			view_all_contacts(trie_node->next[iter2], fptr);
		}
	}
}


void view( trie *trie_head, char *contact_file)
{
	if (trie_head == NULL || contact_file == NULL)
		return;
	FILE *fptr = fopen(contact_file, "r");
	if (fptr != NULL)
		view_all_contacts(trie_head, fptr);
	else
		printf("\nUnable to read the contacts.");
}


bool mark_trie_name_delete(struct trie *trie_head, char *name){
	if (trie_head == NULL)
		return false;
	int level;
	int length = strlen(name);
	int index;
	struct trie *temp = trie_head;
	for (level = 0; level < length; level++){
		char letter = name[level];
		if (letter >= 'A' && letter <= 'Z')
			index = int(name[level]) - int('A');
		else if (letter >= 'a' && letter <= 'z')
			index = index = int(name[level]) - int('a');
		temp = temp->next[index];
	}
	if (temp != 0 && temp->isEndOfWord)
		temp->isEndOfWord = false;
}

bool check_name_validity(char *name){
	if (name == NULL)
		return false;
	for (int i = 0; i < strlen(name); i++)
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')))
			return false;

	return true;
}

bool delete_contact(struct trie *trie_head, char *file_name, char *name){
	FILE *fp = fopen(file_name, "r+");
	if (fp == NULL)
		return -1;
	bool valid = check_name_validity(name);
	if (valid == false)
		return false;
	char ch = '!';
	int file_position = search_contact(trie_head, name);
	if (file_position == -1){
		return -1;
	}
	else{
		fseek(fp, file_position, SEEK_SET);
		fputc(ch, fp);
		bool del = mark_trie_name_delete(trie_head, name);
		if (del == false)
			return false;
	}
}

void delet( trie *trie_head, char *contact_file)
{
	char *name = prompt("Enter the contact name to delete:");
	if (delete_contact(trie_head, contact_file, name))
		printf("\nContact has been deleted succcessfully.");
	else
		printf("\nFailed to delete the contact");
}

void edit( trie *trie_head, char *contact_file)
{
	char *name = prompt("Enter the contact name to edit:");
	if (edit_contact(trie_head, contact_file, name))
		printf("\nChanges applied successfully");
	else
		printf("\nFailed to apply changes.");
}



