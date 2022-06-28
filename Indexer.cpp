#include <bits/stdc++.h>
using namespace std;

// ------------------------------------ Globals ------------------------------------ //
#define MAX_LEN 100
class LinkedList;
class node;
LinkedList *table[100];
vector<string> documents;

// ---------------------------------- Declaration ---------------------------------- //

/**
 * @brief node of an linked list.
 *
 */
class node
{
public:
    string data;
    node *next;
    set<string> docs_name;
    node(string data)
    {
        this->data = data;
        next = NULL;
    }
};

/**
 * @brief Linked list class containing head and tail node .
 *
 */
class LinkedList
{
public:
    node *head;
    node *tail;
    LinkedList()
    {
        head = tail = NULL;
    }

    void iat_head(string data)
    {
        node *n = new node(data);
        head = tail = n;
    }

    void iat_back(string data)
    {
        if (head == NULL)
        {
            iat_head(data);
            return;
        }
        node *n = new node(data);
        node *demo = this->head;
        while (demo->next != NULL)
        {
            demo = demo->next;
        }
        demo->next = n;
    }

    void print()
    {
        node *demo = this->head;
        while (demo != NULL)
        {
            cout << demo->data << "->";

            demo = demo->next;
        }
        cout << "NULL";
        cout << "\n";
    }
};

/**
 * @brief use is used to return multiple values in use search_word(string)
 *
 */
struct use
{
    int flag;
    node *n;
};

// ------------------------------ Method Declarations ------------------------------ //
string string_lower(string);
void add_in_table();
use search_word(string);
void print_table();
void search_engine();
void start();

// --------------------------------- Main Function --------------------------------- //
int main()
{

    for (int i = 0; i < MAX_LEN; i++)
    {
        table[i] = new LinkedList();
    }

    documents.push_back("1.txt");
    documents.push_back("2.txt");
    documents.push_back("3.txt");
    documents.push_back("4.txt");
    documents.push_back("5.txt");
    add_in_table();
    // print_table();

    cout << "\n\n\n\n1. Search a stirng .\n0.Exit..";

    cout << "\n0 -> End the program.\n1 -> Search A Word.\n2-> Print Table Data Structure.";
    int choice = -1;
    cout << "\n\nEnter choice :- ";
    cin >> choice;
    while (choice != 0)
    {
        switch (choice)
        {
        case 1:
        {
            search_engine();
            break;
        }
        case 2:
        {
            cout << "\n";
            print_table();
        }
        default:
            cout << "\nEnter Valid number !!!";
        }

        cout << "\n\nenter your choice :- ";
        cin >> choice;
    }

    return 0;
}

// ------------------------------- Method Definitions ------------------------------ //

/**
 * @brief returns a string in lower format.
 *
 * @param str
 * @return string
 */
string string_lower(string str)
{
    string s = "";
    for (int i = 0; i < str.size(); i++)
    {
        s += tolower(str[i]);
    }
    return s;
}

/**
 * @brief This is the most important function which will add all the data(words) in the table in an structured manner. Colliosion handeling is also done in this code.
 * This part of code acts as an Indexer in the search engine.
 *
 *
 */
void add_in_table()
{

    for (int i = 0; i < documents.size(); i++)
    {
        fstream myFile;
        myFile.open(documents[i], ios::in);

        if (!myFile)
        {
            cout << "\nNo such " << documents[i] << " exists.";
        }
        else
        {
            string ch;
            while (1)
            {
                myFile >> ch;
                use u = search_word(ch);
                int sum = 0;
                for (int i = 0; i < ch.size(); i++)
                {
                    int k = abs(toupper(ch[i]) - 65);
                    sum += k;
                }

                int index = (sum % MAX_LEN);

                if (myFile.eof())
                {
                    break;
                }

                // Collision Handling.
                if (u.flag)
                {
                    u.n->docs_name.insert(documents[i]);
                }
                else
                {
                    LinkedList *L1;
                    L1 = table[index];
                    L1->iat_back(ch);
                    node *temp;
                    temp = L1->head;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->docs_name.insert(documents[i]);
                }
            }
        }
        myFile.close();
    }
}

/**
 * @brief it returns an use type of data containing a flag and node.
 *
 * @param ch
 * @return use
 */
use search_word(string ch)
{

    use u;

    int sum = 0;
    for (int i = 0; i < ch.size(); i++)
    {
        int k = abs(toupper(ch[i]) - 65);
        sum += k;
    }

    int index = (sum % MAX_LEN);
    LinkedList *L;

    L = table[index];
    node *n = L->head;

    while (n != NULL)
    {
        if (string_lower(n->data) == string_lower(ch))
        {
            u.flag = 1;
            u.n = n;
            return u;
        }

        n = n->next;
    }
    u.flag = 0;
    u.n = NULL;
    return u;
}

/**
 * @brief It prints the Hashtable data structure and the data in it's every node.
 *
 */
void print_table()
{
    for (int i = 0; i < MAX_LEN; i++)
    {
        LinkedList *t2;
        t2 = table[i];
        node *p = t2->head;
        cout << "\n"
             << i << " = ";
        while (p != NULL)
        {
            cout << p->data << "( ";
            set<string>::iterator itr;
            for (itr = p->docs_name.begin(); itr != p->docs_name.end(); itr++)
            {
                cout << *itr << " ";
            }
            cout << ")"
                 << "->";
            p = p->next;
        }
        cout << "NULL";
    }
}

/**
 * @brief It is an combined function used to take an string input and peprform the searching operation. This part acgts as a retriever.
 *
 */
void search_engine()
{
    cout << "\nEnter the string you wanna search :- ";
    string str;
    cin >> str;
    use u = search_word(str);
    set<string>::iterator itr;
    if (u.flag)
    {
        for (itr = u.n->docs_name.begin(); itr != u.n->docs_name.end(); itr++)
        {
            cout << *itr << "\n";
        }
    }
    else
    {
        cout << "\n"
             << str << " do not exist in the data base!!!!";
    }
}

/**
 * @brief Just a UI improvement function.
 *
 */
void start()
{
    cout << "\nstarting ...........";
    cout << "\n..\n..\n..\n..\n..\n..\n..\n..\n\n..\n..\n..\n..\n..\n..";
}
