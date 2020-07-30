/*	Data Structures and Algorithms
 *	27-05-19
 * 	Assignment 2:
 * 	Ideas Bank
 *
 * 	IdeasBank.h
 *
 * 	Adds ideas to an AVL tree, performs actions on ideas in the AVL tree
 * 	and functions for obtaining data to show to the user
 *
 */
struct Index {
	string key;
	vector<int> idList;

public:
	Index() {

	}

	Index(string k, vector<int> &i) :
			key(k), idList(i) {
	}
};

// Global function to print indicies inside of AVL tree
void printIndicies(Index data) {
	if (data.key != " ") {
		cout << "KEY: " << data.key;
		cout << "\nRelated Ideas: ";
		for (int id : data.idList)
			cout << id << setw(3);
		cout << endl;
	}
	cout << endl;
}

class IdeasBank: public Idea {
private:
	int idea_id;
	string id_string;
	string idea_proposer;
	string idea_content;
	string idea_keywords;
	map<int, Idea> ideaHash;
	vector<string> indexedWords;
	AvlTree<Index, string> indexTree;
public:
	/* ========== MAP FUNCTIONS ========== */

	// Stores an idea to the map
	void addToMap(int, Idea);

	// Clears the map of all data
	void deleteMap();

	// Prints the map
	void printMap();

	/* ========== FUNCTIONS TO FIND RELATED IDEAS/KEYS ========== */

	// Returns related keywords
	void relatedWord(string);

	// Related ideas of ideas.
	void relatedIdeas(int);

	// Function to store related ideas to current iterator position idea
	vector<int> getRelatedIdeas(map<int, Idea>::iterator);

	// Searches for related ideas from indexing tree
	void relatedIdeasFromTree(string);

	/* ========== INDEXING FUNCTIONS ========== */

	// Calls indexWord for keywords, then again for contents
	void indexFile();

	// Function to index passed word
	void indexWord(string k);

	// Prints word indicies
	void traverseIndicies();

	/* ========== FUNCTIONS TO RECEIVE/MODIFY IDEAS ========== */

	// Receives idea from user
	void ideasFromKeyboard();

	// Receives idea from text document
	void ideasFromDoc(string);

	// Deletes an idea in map
	void deleteIdea(int);
};

/* ========== MAP FUNCTIONS ========== */

void IdeasBank::deleteMap() {
	ideaHash.clear();
}

void IdeasBank::addToMap(int id, Idea idea) {
	ideaHash.insert(pair<int, Idea>(id, idea));
}

void IdeasBank::printMap() {
	if (ideaHash.empty()) {
		cout << "Map is empty.\n";
		return;
	}

	// Iteratre through the map, print all contents of map
	map<int, Idea>::iterator itr = ideaHash.begin();
	for (itr = ideaHash.begin(); itr != ideaHash.end(); ++itr) {
		cout << "\nIdea " << itr->second.getId() << endl;
		cout << "Proposer: " << setw(3) << itr->second.getProposer() << endl;
		cout << "Keywords: " << setw(3);
		itr->second.printKeywords();
		cout << "\nContent:  " << setw(3) << itr->second.getContent() << endl;
		cout << "Related ideas: ";
		// Call function to find ideas related to itr position
		for (int i : getRelatedIdeas(itr))
			cout << i << setw(3);
		cout << endl << endl;
	}
}
/* ========== END MAP FUNCTIONS ========== */

/* ========== FUNCTIONS TO FIND RELATED IDEAS/KEYS ========== */

void IdeasBank::relatedWord(string word) {
	cout << "Search outcome from Ideasbank.\n\n";
	cout << "Related ideas: \n";

	// Using the Idea class function checkWord() to check passed word in all keywords and content
	map<int, Idea>::iterator itr = ideaHash.begin();
	for (itr = ideaHash.begin(); itr != ideaHash.end(); ++itr) {
		if (itr->second.checkWord(word)) {
			cout << "Idea " << itr->second.getId() << "\nProposer: "
					<< itr->second.getProposer() << "\nKeywords: ";
			itr->second.printKeywords();
			cout << "\nContent: " << itr->second.getContent() << "\n\n";
		}
	}
}

void IdeasBank::relatedIdeas(int id) {
	// Iterate through the map to find related ideas
	map<int, Idea>::iterator itr;
	for (itr = ideaHash.begin(); itr != ideaHash.end(); ++itr) {
		if (id == itr->second.getId())
			for (int i : getRelatedIdeas(itr))
				if (i != id)
					cout << i << setw(3);
	}
	cout << endl;
}

vector<int> IdeasBank::getRelatedIdeas(map<int, Idea>::iterator itr) {
	Index index;
	vector<int> relatedIdeas_vec;
	for (string keyword : itr->second.getKeywords())
		if (indexTree.AVL_Retrieve(keyword, index)) {
			for (int i : index.idList) {
				bool found = false;
				for (unsigned int j = 0; j < relatedIdeas_vec.size(); j++) {
					if (i == relatedIdeas_vec[j]) {
						found = true;
						break;
					}
				}
				if (!found)
					relatedIdeas_vec.push_back(i);
			}
		}
	sort(relatedIdeas_vec.begin(), relatedIdeas_vec.end());
	return relatedIdeas_vec;
}

void IdeasBank::relatedIdeasFromTree(string k) {
	Index index;
	map<int, Idea>::iterator itr;
// If the passed word is inside the tree already, print the associated IDs
	if (indexTree.AVL_Retrieve(k, index)) {
		for (int i : index.idList) {
			itr = ideaHash.find(i);
			cout << "\nIdea " << itr->second.getId() << endl;
			cout << "Proposer: " << setw(3) << itr->second.getProposer()
					<< endl;
			cout << "Keywords: " << setw(3);
			itr->second.printKeywords();
			cout << "\nContent:  " << setw(3) << itr->second.getContent()
					<< endl;
			cout << endl;
		}
	}
}

/* ========== END FUNCTIONS TO FIND RELATED IDEAS/KEYS ========== */

/* ========== INDEXING FUNCTIONS ========== */

void IdeasBank::indexFile() {
	map<int, Idea>::iterator itr;
	for (itr = ideaHash.begin(); itr != ideaHash.end(); ++itr) {
		//Indexing keywords
		for (string keyword : itr->second.getKeywords()) {
			indexWord(keyword);
		}

		// Indexing contents
		stringstream ss(itr->second.getContent());
		for (string s; ss; ss >> s) {
			indexWord(s);
		}
	}
}

void IdeasBank::indexWord(string k) {
// Ignores empty characters (new lines)
	if (k.empty())
		return;
// Also removes all unwanted characters in the string.
	char chars[] = "().,!?";
	for (char c : chars)
		k.erase(remove(k.begin(), k.end(), c), k.end());

	map<int, Idea>::iterator itr;
	vector<int> indexedId;
	for (itr = ideaHash.begin(); itr != ideaHash.end(); ++itr) {
		// If the keyword is in this current idea
		if (itr->second.checkWord(k))
			// Save the idea in a vector
			indexedId.push_back(itr->second.getId());
	}

	Index index = Index(k, indexedId);
// If that keyword is not already stored in the tree, store it
	if (!indexTree.AVL_Retrieve(k, index)) {
		indexTree.AVL_Insert(index);
	}
}
void IdeasBank::traverseIndicies() {
	indexTree.AVL_Traverse(&printIndicies);
}

/* ========== END INDEXING FUNCTIONS ========== */

/* ========== FUNCTIONS TO RECEIVE/MODIFY IDEAS ========== */

void IdeasBank::deleteIdea(int i) {
// Removing idea from the indexing list
	auto search = ideaHash.find(i);
	vector < string > key = search->second.getKeywords();
	stringstream content(search->second.getContent());
	for (string k : key)
		indexTree.AVL_Delete(k);
	for (string c; content; content >> c)
		indexTree.AVL_Delete(c);

// Removing idea from map
	ideaHash.erase(i);
	cout << "Idea " << i << " deleted\n";
}

void IdeasBank::ideasFromDoc(string filename) {
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "Could not find file.\n";
		return;
	}
	Idea idea;
	while (!infile.eof()) {
		getline(infile, id_string, '#');
		getline(infile, idea_proposer, '#');
		getline(infile, idea_keywords, '#');
		getline(infile, idea_content, '#');
		stringstream id(id_string);
		id >> idea_id;
		stringstream ss(idea_keywords);
		vector < string > idea_keywords_vec;
		do {
			string word;
			getline(ss, word, ' ');
			idea_keywords_vec.push_back(word);
			word = "";
		} while (ss);

		Idea newIdea = Idea(idea_id, idea_proposer, idea_keywords_vec,
				idea_content);

		addToMap(idea_id, newIdea);
	}
	cout << "Ideas imported.\n";
}

void IdeasBank::ideasFromKeyboard() {
	string p, c, k;
	vector < string > k1;

	cout << "Enter proposer: ";
	getline(cin, p);
	cin.ignore();

	cout << "Enter content: ";
	getline(cin, c);
	cin.ignore();

	cout << "Enter keywords to do with content: ";
	getline(cin, k);
	cin.ignore();
	cout << endl;

	stringstream ss(k);
	do {
		string word;
		getline(ss, word, ' ');
		k1.push_back(word);
		word = "";
	} while (ss);

	int ideaCount = ideaHash.size();
	Idea newIdea = Idea(ideaCount + 1, p, k1, c);
	addToMap(ideaCount + 1, newIdea);

	cout << endl;
}

/* ========== END FUNCTIONS TO RECEIVE/MODIFY IDEAS ========== */
