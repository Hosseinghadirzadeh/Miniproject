#include <iostream>

using namespace std;
struct words {
    string word;
    words *next;
    words *syn;
};
words *Head = nullptr;

void CreateWord();// A function for inserting words in the Linked list
int DeleteWord(string);// A function to delete a word from the list


int main() {
    while (true){
    int selector;
    cout << "0.EXIT\n";
    cout << "1.ADD word and their synonyms\n";
    cout << "2.Delete a word with it's synonyms\n";
    cin >> selector;
    switch (selector) {
        case 0:
            return 0;
        case 1:
            CreateWord();
            break;
        case 2:
            cout << "Enter the word you want to be deleted:\n";
            string dword;
            cin >> dword;
            DeleteWord(dword);
            break;


             }


    }
    return 0;

}

void CreateWord() {
    words *current;
    int n;
    cout << "Enter the word:\n";
    words *node = new words;
    cin >> node->word;
    node->next = nullptr;
    if (Head == nullptr || node->word < Head->word) {
        node->next = Head;
        Head = node;
    } else {
        current = Head;
        while (current->next != nullptr && current->next->word < node->word) {
            current = current->next;
        }
        if (current->next->word != node->word) {
            node->next = current->next;
            current->next = node;
        }

    }
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
    words *prev = nullptr;
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