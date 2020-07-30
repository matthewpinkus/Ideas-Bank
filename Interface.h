/*	Data Structures and Algorithms
 *	27-05-19
 * 	Assignment 2:
 * 	Ideas Bank
 *
 * 	Interface.h
 *
 *  User interface to select options from a menu to perform
 *  actions in IdeasBank.h
 *
 */

class Interface {
public:
	void start();
};

void Interface::start() {
	IdeasBank ib;
	Idea idea;
	string filename, word;
	AvlTree < Index, string > tree;
	int ans, id, num;
	srand (time(NULL));

cout	<< "Menu: \n";
	do {
		cout << "1. Import ideas from a file \n";
		cout << "2. Print the ideas bank \n";
		cout << "3. Print word indicies \n";
		cout << "4. Search for related ideas from ideas bank\n";
		cout << "5. Search for related ideas from indexing tree\n";
		cout << "6. Related ideas of an idea\n";
		cout << "7. Delete an idea\n";
		cout << "8. Import ideas from keyboard\n";
		cout << "9. Quit\n";
		cin >> ans;

		switch (ans) {
		case 1:
			cout << "\nPlease input the file name, including it's full path...";
			cin >> filename;
			ib.ideasFromDoc(filename);
			ib.indexFile();
			break;

		case 2:
			ib.printMap();
			break;

		case 3:
			ib.traverseIndicies();
			break;

		case 4:
			cout << "Please input a word...\n";
			cin >> word;
			ib.relatedWord(word);
			break;

		case 5:
			cout << "Please input a word...\n";
			cin >> word;
			ib.relatedIdeasFromTree(word);
			break;

		case 6:
			cout
					<< "\nPlease input the id of the idea you want to find ideas it relates to...";
			cin >> id;
			ib.relatedIdeas(id);
			break;

		case 7:
			cout << "\nEnter the id of the idea you want to delete...";
			cin >> num;
			ib.deleteIdea(num);
			break;

		case 8:
			ib.ideasFromKeyboard();
			break;
		}
		cout << endl;
	} while (ans != 9);
	cout << "Program finished";
}

