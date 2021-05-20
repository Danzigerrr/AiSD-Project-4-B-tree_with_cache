#include "Btree.h"

char input[MAX_INPUT_LENGTH];


FILE* fptr;


int get_value_from_char(char znak[MAX_INPUT_LENGTH], int poczatek);


int main() {
	fptr = fopen("test1.txt", "r");
	if (fptr == NULL) {
		cout << "ERROR opening file";
		return 0;
	}

	while (fgets(input, MAX_INPUT_LENGTH, fptr) != NULL) {

		int com_index = 0;

		if (get_command(&com_index)) {
			int value = get_value(com_index);
			do_command(com_index, value);
		}
		else
			printf("  Incorrect input\n");

	}
	fclose(fptr);
	return 0;
}

int get_value_from_char(char znak[MAX_INPUT_LENGTH], int poczatek)
{
	int result = 0, i = 0;
	while (znak[poczatek + i] >= 48 && znak[poczatek + i] <= 57)
	{
		result = result * 10 + (znak[poczatek + i] - 48);
		i++;
	}
	return result;
}
bool get_command(int* com_index) {
	char commands[COM_COUNT][COM_LENGTH]{
	"I\n",
	"A\n",
	"?\n" ,
	"P\n" ,
	"LOAD\n" ,
	"SAVE\n",
	"REMOVE\n",
	"/\n",
	"X\n",
	"CACHE\n",

	};
	for (int j = 0; j < COM_COUNT; j++) {
		if (strcmp(input, commands[j]) == 0) {
			*com_index = j;
			return true;
		}
	}
	return false;
}

void do_command(int com_index, int value) {

	switch (com_index) {
	case CONSTRUCT:
		cout << endl;
		order = value;
		tree.constr();
		break;
	case ADD:
		cout << endl;
		tree.insert(value);
		break;
	case SEARCH:
		tree.search(tree.getRoot(), value);
		break;
	case PRINT:
		
		tree.InOrderPrint(tree.getRoot());
		break;
	case LOAD:
		order = value;
		tree.load();
		break;
	case SAVE:
		tree.save();
	case REMOVE:
		tree.remove(value);
		break;
	case IGNORE:
		//cout << endl;
		break;
	case END:
		exit(1);
		break;
	case CACHE:
		tree.cache();
		break;
	}
}


int get_value(int com_index) {
	int result = 0;
	if (com_index == CONSTRUCT || com_index == ADD || com_index == SEARCH || com_index == REMOVE || com_index == LOAD)
		if (fgets(input, MAX_INPUT_LENGTH, fptr) != NULL)
			result = get_value_from_char(input, 0);

	return result;
}


