#include "Projekt4v2.h"
char input[MAX_INPUT_LENGTH];
FILE* fptr;

int main() {
	int testNumber = 1;
	char test[] = "test1proba.txt";

	while (testNumber != 2) {

		cout << test << endl;

		fptr = fopen(test, "r");
		if (fptr == NULL) {
			cout << "ERROR opening file";
			return 0;
		}

		while (fgets(input, MAX_INPUT_LENGTH, fptr) != NULL) {

			get_command();

		}
		fclose(fptr);

		testNumber++;
		test[4] = testNumber + '0';
		BTree* N = new BTree;
		tree = *N;
	}
	return 0;
}

void get_command() {
	char commands[COM_COUNT][COM_LENGTH]{
	"I\n",
	"A\n",
	"?\n" ,
	"P\n",
	"L\n",
	"S\n",
	"R\n",
	"#\n",
	"X\n",
	"C\n"
	};
	bool found = false;
	for (int j = 0; j <= COM_COUNT; j++) {
		if (j == COM_COUNT && found == false) {
			cout << "incorret input" << endl;
			break;
		}

		if (strcmp(input, commands[j]) == 0) {
			found = true;
			int value = get_value(j);
			switch (j) {
			case CONSTRUCT:
				tree.construct(value);
				break;
			case ADD:
				tree.add(value);
				break;
			case SEARCH:
				tree.search(value);
				break;
			case PRINT:
				tree.print();
				break;
			case LOAD:
				tree.load(value);
				break;
			case SAVE:
				tree.save();
				break;
			case REMOVE:
				tree.remove(value);
				break;
			case IGNORE:
				cout << "comment" << endl;
				break;
			case END:
				exit(1);
				break;
			case CACHE:
				tree.cache();
				break;

			}

		}
	}
	
}
int get_value(int com_index) {
	int result = 0;
	if (com_index == CONSTRUCT || com_index == ADD || com_index == SEARCH || com_index == LOAD || com_index == REMOVE)
		if (fgets(input, MAX_INPUT_LENGTH, fptr) != NULL)
			result = get_value_from_char(input, 0);

	return result;
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