#include <iostream>

using namespace std;
struct words {
    string word;
    words *next;
    words *syn;
};
words *Head = nullptr;

void DeleteAllSyn(words *syn);//A function to delete all synonyms of the word which is used in DeleteWord function
words *CreateWord(const string &);//A function to create a word
void print();//Print function
void AddWord(words *);// A function for inserting words in the Linked list
int DeleteWord(string);// A function to delete a word from the list
void search(string);// A function to search among words
void DeleteSynonyms();// A function to delete single synonyms by searching it
words *systematicSearch(string word);// This function is not accessible by user and it's systematic
void Edit();

int main() {
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
        cin >> selector;
        switch (selector) {
            case 0:
                flag = false;
                break;
            case 1: {
                cout << "Enter the word: \n";
                cin >> word;
                AddWord(CreateWord(word));

                break;
            }
            case 2: {
                cout << "Enter the word you want to be deleted:\n";
                string dword;
                cin >> dword;
                DeleteWord(dword);
                break;
            }
            case 3: {
                cout << "Enter the word you want to find: \n";
                string fword;
                cin >> fword;
                search(fword);
                break;
            }
            case 4:
                print();
                break;
            case 5:
                DeleteSynonyms();
                break;
            case 6:Edit();
                break;


        }


    }
    return 0;

}

void AddWord(words *node) {
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
    //Add synonyms
    int n;
    cout << "Enter the number of the synonyms:\n";
    cin >> n;
    words *current2;

    for (int i = 0; i < n; ++i) {
        words *sw = new words;
        cout << "Enter your synonym:\n";
        cin >> sw->word;
        if (node->syn == nullptr || sw->word < node->syn->word) {
            sw->next = node->syn;
            node->syn = sw;
        } else {
            current2 = node->syn;
            while (current2->next != nullptr && current2->next->word <= sw->word)
                current2 = current2->next;
            sw->next = current2->next;
            current2->next = sw;

        }
    }


}

int DeleteWord(string word) {
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
                DeleteAllSyn(current->syn);
                delete current;
                return 1;
            }

            current = current->next;
        }

    }

    return 0;
}

void search(string word) {
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

words *CreateWord(const string &word) {
    words *node = new words{word, nullptr, nullptr};

    return node;

}

void print() {
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

void DeleteSynonyms() {
    string word, syn;
    words *prev;
    cout << "Enter the word: \n";
    cin >> word;
    words *node = systematicSearch(word);
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

void DeleteAllSyn(words *syn) {
    words *temp;
    while (syn) {
        temp = syn;
        syn = syn->next;
        delete temp;
    }


}

words *systematicSearch(string word) {
    words *current = Head;

    while (current) {
        if (current->word == word)
            return current;
        current = current->next;
    }
    return nullptr;

}
void Edit(){
    string word,newWord;
    cout<<"Enter the word you want to be edited:\n";
    cin>>word;
    words* node=systematicSearch(word);
    cout<<"========Enter the new word========\n";
    cin>>newWord;
    node->word=newWord;

}