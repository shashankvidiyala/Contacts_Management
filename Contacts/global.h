
struct trie {
	bool isEndOfWord;
	int *fpValue;
	struct trie *next[26];
};


struct Query_Result{
	char response[1000];
	int query_id;
};
struct page_data{
	FILE *fp;
	int state;
};
struct page_data page_array[10];