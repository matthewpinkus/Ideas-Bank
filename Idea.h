/*	Data Structures and Algorithms
 *	27-05-19
 * 	Assignment 2:
 * 	Ideas Bank
 *
 * 	Idea.h
 *
 * 	Ideas for IdeasBank.h are stored in the class Idea
 *
 */

class Idea {
private:
	int id;
	string proposer;
	string content;
	string keywords;
	vector<int> relatedIds_vec;
	vector<string> keywords_vec;
public:
	Idea() {

	}

	// Constructor to create ideas when passed in values that are contained in an Idea object
	Idea(int v, string p, vector<string> &k1, string c) :
			id(v), proposer(p), content(c), keywords_vec(k1) {
	}

/* ========== SETTING AND GETTING FUNCTIONS FOR CLASS VARIABLES ========== */
	void setId(int v) {
		id = v;
	}

	int getId() {
		return id;
	}

	void setProposer(string s) {
		proposer = s;
	}

	string getProposer() {
		return proposer;
	}

	void setContent(string s) {
		content = s;
	}

	string getContent() {
		return content;
	}

	vector<string> getKeywords() {
		return keywords_vec;
	}

	void setIdeasVec(vector<int>& i)   {
		relatedIds_vec = i;
	}

	vector<int> getIdeasVec() {
		return relatedIds_vec;
	}

/* ========== PRINTING FUNCTIONS FOR CLASS VARIABLES ========== */

	void printId() {
		cout << id << endl;
	}
	void printProposer() {
		cout << proposer << endl;
	}

	void printContent() {
		cout << content << endl;
	}

	void printKeywords() {
		for (unsigned int i = 0; i < keywords_vec.size(); i++) {
			if (i == keywords_vec.size() - 2)
				cout << keywords_vec[i];
			else
				cout << keywords_vec[i] << ", ";
		}
	}

/* ========== FUNCTIONS TO CHECK VARIABLES ========== */

	// Checks if data passed is in keywords, return true if found
	bool checkKeywords(string s);

	// Checks if data passed is in content, return true if found
	bool checkContent(string s);

	// Checks if a word is in keyword or content.
	bool checkWord(string s);
};


bool Idea::checkKeywords(string s) {
	for (unsigned int i = 0; i < keywords_vec.size(); i++) {
		if (s == keywords_vec[i])
			return true;
	}
	return false;
}

bool Idea::checkContent(string s) {
	size_t found;
	found = content.find(s);
	if (found != string::npos)
		return true;
	else
		return false;
}

bool Idea::checkWord(string s) {
	if (checkKeywords(s) || checkContent(s))
		return true;
	return false;

}

