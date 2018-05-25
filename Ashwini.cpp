#include<stdio.h>
#include<string.h>

struct trie {
	struct trie *next[26];
	long int fpvalue;
	bool isEndOfWord;
};

bool mark_trie_name_delete(struct trie *trie_head, char *name){
	if (trie_head == NULL)
		return false;
	int level;
	int length = strlen(name);
	int index;
	struct trie *temp=trie_head;
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

bool delete_contact(struct trie *trie_head,char *file_name,char *name){
	FILE *fp = fopen(file_name, "r+");
	if (fp == NULL)
		return -1;
	bool valid = check_name_validity(name);
	if (valid == false)
		return false;
	char ch='!';
	int file_position = search_contact(name);
	if (file_position == -1){
		return -1;
	}
	else{
		fseek(fp, file_position, SEEK_SET);
		fputc(ch, fp);
		bool del=mark_trie_name_delete(trie_head, name);
		if (del == false)
			return false;
	}
}