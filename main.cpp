#include <iostream>
#include<fstream>

using namespace std;
struct words {
    string word;
    words *next;
    words *syn;
};


void DeleteAllSyn(words *&,
                  words *syn);               //A function to delete all synonyms of the word which is used in DeleteWord function
words *CreateWord(const string &);                  //A function to create a word
void print(words *&);                               //Print function
void AddWord(words *&, words *);                   // A function for inserting words in the Linked list
int DeleteWord(words *&, string);                 // A function to delete a word from the list
void search(words *&, string);                   // A function to search among words
void DeleteSynonyms(words *&);                  // A function to delete single synonyms by searching it
words *systematicSearch(words *&, string word);// This function is not accessible by user and it's systematic
void Edit(words *&);                          //THIS function edits the words
void save(words *&, ofstream &);             // A function to Save the dictionary on file
void ReadFromFile(words *&);                // Read file and make a link list
void AddSynonyms(words *&, string, words *); //add synonyms

int main() {
    words *Head = nullptr;
    int n;
    string syn;
    ofstream Dic_file("dictionaryList.txt");
    bool flag = true;
    string word;
    while (flag) {
        int selector;
        cout << "0.EXIT\n";
        cout << "1.ADD word and their synonyms\n";
        cout << "2.Delete a word with it's synonyms\n";
        cout << "3.Search for word and their synonyms\n";
        cout << "4.Print the dictionary\n";
        cout << "5.Delete Synonym\n";
        cout << "6.Edit Word\n";
        cout << "7.Save the dictionary on file\n";
        cout << "8.Read Dictionary from Existing File\n";
        cin >> selector;
        switch (selector) {
            case 0: {
                string YN;
                cout << "Do you want to save the Dictionary?(Y/N)\n";
                cin >> YN;
                if (YN == "Y") {
                    save(Head, Dic_file);
                    flag = false;
                } else
                    flag = false;
                break;
            }
            case 1: {
                cout << "Enter the word: \n";
                cin >> word;
                AddWord(Head, CreateWord(word));
                //Add synonyms
                cout << "Enter the number of the synonyms:\n";
                cin >> n;

                for (int i = 0; i < n; ++i) {
                    cout << "Enter the synonyms:\n";
                    cin >> syn;
                    AddSynonyms(Head, word, CreateWord(syn));
                }

                break;
            }
            case 2: {
                cout << "Enter the word you want to be deleted:\n";
                string dword;
                cin >> dword;
                DeleteWord(Head, dword);
                break;
            }
            case 3: {
                cout << "Enter the word you want to find: \n";
                string fword;
                cin >> fword;
                search(Head, fword);
                break;
            }
            case 4:
                print(Head);
                break;
            case 5:
                DeleteSynonyms(Head);
                break;
            case 6:
                Edit(Head);
                break;
            case 7:
                save(Head, Dic_file);
                break;
            case 8: {
                ReadFromFile(Head);
                break;
            }

        }


    }
    return 0;

}

void AddWord(words *&Head, words *node) {
    words *current;

    if (Head == nullptr || node->word < Head->word) {
        node->next = Head;
        Head = node;
    } else {
        current = Head;
        while (current->next != nullptr && current->next->word <= node->word) {
            current = current->next;
        }
        if (current->word != node->word) {
            node->next = current->next;
            current->next = node;
        }

    }


}

int DeleteWord(words *&Head, string word) {
    words *current;
    words *prev;
    current = Head;
    if (current == nullptr)
        cout << "List is empty";
    else {
        while (current != nullptr) {
            prev = current;
            if (current->word == word) {
                if (current == Head && current->next == nullptr)
                    Head = nullptr;
                else if (current == Head)
                    Head = Head->next;
                else if (current->next == nullptr)
                    prev->next = nullptr;
                else
                    prev->next = current->next;
                DeleteAllSyn(Head, current->syn);
                delete current;
                return 1;
            }

            current = current->next;
        }

    }

    return 0;
}

void search(words *&Head, string word) {
    words *current;
    words *current2;
    current = Head;


    if (current == nullptr)
        cout << "List is empty";
    else
        while (current != nullptr) {

            if (current->word == word) {
                cout << "\t word: " << current->word << endl;
                current2 = current->syn;
                while (current2 != nullptr) {
                    cout << "\t\t Synonyms: " << current2->word << "\n";
                    current2 = current2->next;
                }
            }
            current = current->next;


        }

}

words *CreateWord(const string &word) {//just creat node and get words for it
    words *node = new words{word, nullptr, nullptr};

    return node;

}

void print(words *&Head) {
    words *current = Head;

    while (current != nullptr) {
        words *current2 = current->syn;
        cout << "\t word: " << current->word << endl;
        cout << "\tsynonyms:\n";
        while (current2 != nullptr) {
            cout << "\t\t " << current2->word << endl;
            current2 = current2->next;
        }
        current = current->next;
    }

}

void DeleteSynonyms(words *&Head) {
    string word, syn;
    words *prev;
    cout << "Enter the word: \n";
    cin >> word;
    words *node = systematicSearch(Head, word);
    cout << "Enter the synonyms of the word: \n";
    cin >> syn;
    words **head = &node->syn;
    words *current = *head;

    while (current) {

        if (current->word == syn) {
            if (current == *head && current->next == nullptr)
                current = nullptr;
            else if (current == *head)
                *head = (*head)->next;
            else if (current->next == nullptr)
                prev->next = nullptr;
            else
                prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }

}

void DeleteAllSyn(words *&Head, words *syn) {
    words *temp;
    while (syn) {
        temp = syn;
        syn = syn->next;
        delete temp;
    }


}

words *systematicSearch(words *&Head, string word) {
    words *current = Head;// search through nodes to find our words(the program use this function the user can't)

    while (current) {
        if (current->word == word)
            return current;
        current = current->next;
    }
    return nullptr;

}

void Edit(words *&Head) {
    string word, newWord;
    cout << "Enter the word you want to be edited:\n";
    cin >> word;
    words *node = systematicSearch(Head, word);
    cout << "========Enter the new word========\n";
    cin >> newWord;
    node->word = newWord;

}

void save(words *&Head, ofstream &file) {
    words *current = Head;
    while (current != nullptr) {
        words *current2 = current->syn;
        file << current->word << "  ";// split words and their synonyms
        while (current2 != nullptr) {
            file << current2->word << "  ";//split synonyms
            current2 = current2->next;
        }
        file << endl;
        current = current->next;
    }

}

void ReadFromFile(words *&Head) {
    string file_address;
    cout << "Enter of your file address(name.txt)\n";
    cin >> file_address;
    ifstream Rfile(file_address);
    string fword;
    int counter = 0;//count the number of spaces

    string mainWord;
    while (getline(Rfile, fword)) {
        string word = "";
        for (char x : fword)
        { if (x == ' ') {//InputFile.txt
                if (counter == 0) {
                    mainWord = word;
                    AddWord(Head, CreateWord(word));
                } else {
                    AddSynonyms(Head, mainWord, CreateWord(word));
                }
                word = "";
                counter++;
            } else {
                word += x;
            }}
        AddSynonyms(Head, mainWord, CreateWord(word));
        counter = 0;
    }

}

void AddSynonyms(words *&Head, string word, words *node) {

    words *current = Head, *current2;
    while (current->word != word) {
        current = current->next;
    }

    if (current->syn == nullptr || node->word < current->syn->word) {
        node->next = current->syn;
        current->syn = node;
    } else {
        current2 = current->syn;
        while (current2->next != nullptr && current2->next->word <= node->word)
            current2 = current2->next;
        node->next = current2->next;
        current2->next = node;

    }


}
