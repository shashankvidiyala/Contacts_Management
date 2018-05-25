//db

int counter = 0;
void int_to_str(char* name, int val){
	name[0] = (char)('0' + val);
	name[1] = '.', name[2] = 'c', name[3] = 's', name[4] = 'v', name[5] = 0;
}

void copy_to_dump(FILE *source, FILE *destination){
	char temp[1000];
	while (fgets(temp, 1000, source)){
		fprintf(destination, "%s", temp);
	}
}
struct Query_Result generate_pull_data(char *user_name, int query_id){
	struct Query_Result data;
	data.query_id = query_id;
	if (query_id && (page_array[query_id - 1].state)){
		fgets(data.response, 1000, page_array[query_id - 1].fp);
		if (feof(page_array[query_id - 1].fp))   fclose(page_array[query_id - 1].fp), data.query_id = 0;
		return data;
	}
	char name[10];
	int_to_str(name, counter);
	FILE *temp_file = fopen(name, "w");
	FILE *main_db_file = fopen(user_name, "r");
	if (!main_db_file || !feof(main_db_file)){
		data.query_id = -1;
		return data;
	}
	copy_to_dump(main_db_file, temp_file);
	fclose(temp_file);
	fclose(main_db_file);
	page_array[counter].fp = fopen(name, "r");
	page_array[counter].state = 1;
	query_id = counter + 1;
	counter = (counter + 1) % 10;
	return generate_pull_data(user_name, query_id);
}

int iniatite_db(){
	int i = 0;
	for (i = 0; i<10; i++)
		page_array[i].state = 0;
	return 1;
}