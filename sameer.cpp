#include<iostream>
#include<string.h>
#include<fstream>
#include<string>
using namespace std;


struct trie {
	bool isEndOfWord;
	int *fpValue;
	struct trie *next[26];
}*root=NULL;

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
void insertIntoTrie(char *name, int pos) {

	int i = 0;
	trie *curr = root;
	while(name[i] != '\0'){

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


void print_trie(trie *curr,char *name,int len) {
	FILE *f = fopen("input.txt", "r");

	for (int i = 0; i < 26; i++) {

		if (curr->next[i] != NULL) {
			name[len] = ('a' + i);

			if (curr->next[i]->fpValue != NULL) {
				name[len + 1] = '\0';
				cout << name<<" :";
				fseek(f, *(curr->next[i]->fpValue), 0);
				char buff[50]; fscanf(f, "%[^\n]\n", buff);
				cout << buff << "\n";

			}

			print_trie(curr->next[i],name,len+1);

		}

	}

}


void load(FILE *f) {

	char buff[100];
	while (true) {
		int pos;
		
		pos = ftell(f);
		if (fscanf(f, "%[^\n]\n", buff) == EOF) {
			break;
		}

		char *name = strtok(buff, ",");
		insertIntoTrie(_strlwr(name),pos);
	}

}

int main(void) {
	FILE *f = fopen("input.txt", "r+");
	load(f);

	char name[100];
	int len = 0;

	print_trie(root, &name[0], len);

}