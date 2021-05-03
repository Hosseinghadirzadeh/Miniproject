#include <iostream>

using namespace std;
struct words {
    string word;
    words *next;
    words *syn;
};
words *Head = nullptr;


words *CreateWord(const string &);//A function to create a word
void print();//Print function
void AddWord(words *);// A function for inserting words in the Linked list
int DeleteWord(string);// A function to delete a word from the list
void search(string);// A function to search among words
void DeleteSynonyms();

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
    int n;
    cout << "Enter the number of the synonyms:\n";
    cin >> n;
    node->syn = nullptr;

    words *current2;

    for (int i = 0; i < n; ++i) {
        words *sw = new words;//sw= synonym words
        sw->syn = nullptr;
        cout << "Enter your synonym:\n";
        cin >> sw->word;
        current2 = node->syn;
        if (current2 == nullptr || sw->word < current2->word) {
            sw->next = current2;
            current2 = sw;
        } else {

            while (current2->next != nullptr && current2->next->word < sw->word) {
                current2 = current2->next;
            }
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
                else prev->next = current->next;
                delete current->syn;
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


//    if (current == nullptr)
//        cout << "List is empty";
//    else
    while (current != nullptr) {

        if (current->word == word) {
            cout << "word: " << current->word << endl;
            current2 = current->syn;
            while (current2 != nullptr) {
                cout << current2->word;
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
    words *current2 = current->syn;
    while (current != nullptr) {
        cout << "word: " << current->word << endl;
        cout << "synonyms:\n";
        while (current2 != nullptr) {
            cout << "\t" << current2->word;
            current2 = current2->next;
        }
        current = current->next;
    }

}
void DeleteSynonyms(){







}