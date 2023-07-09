#include "trie.h"

int CHAR_TO_INDEX(char c) { return ((int)c - (int)'a'); }


TrieNode* getNode()
{
    TrieNode* node = new TrieNode;
    node->isWordEnd = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = nullptr;
    }
    return node;
}

bool isLastNode(TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] == nullptr)
        {
            return 1;
        }
    }
    return 0;
}

bool insertT(TrieNode* root, string key)
{//input: TrieNode*, string; output: bool
    if (key.empty())
    {
        root->isWordEnd = 1;
        return 1;
    }

    if (root->children[CHAR_TO_INDEX(key.front())] == nullptr)
        root->children[CHAR_TO_INDEX(key.front())] = getNode();

    root = root->children[CHAR_TO_INDEX(key.front())];
    key = pop_front(key);

    return insertT(root, key);
}

int delT(TrieNode* root, string key)
{//input: TrieNode*, string; output: int
    if (root == nullptr || !searchT(root, key))//if the tree is empty or the value does not exist in the tree
        return 0;

    if (key.empty())//if the key is empty
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)//Goes over all the sons of the tree
            if (root->children[i] != nullptr)//If the son exists and he is also not the son we are trying to delete
            {
                root->isWordEnd = 0;
                return -1;
            }

        return 1;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)//For every son in the tree
    {
        if (root->isWordEnd || (root->children[i] != nullptr && i != CHAR_TO_INDEX(key.front())))//If it ends with a word or it is not empty and it is not the delete son either
        {
            if (delT(root->children[CHAR_TO_INDEX(key.front())], pop_front(key)) == 1)//If the value returned from deleting the child we want to delete is 1
            {
                delete root->children[CHAR_TO_INDEX(key.front())];
                root->children[CHAR_TO_INDEX(key.front())] = nullptr;
            }

            return -1;
        }
    }
    int result = delT(root->children[CHAR_TO_INDEX(key.front())], pop_front(key));

    if (result == 1)//If the value returned from delete is 1
    {
        delete root->children[CHAR_TO_INDEX(key.front())];
        root->children[CHAR_TO_INDEX(key.front())] = nullptr;
    }

    return result;
}

bool searchT(TrieNode* root, string key)
{//input: TrieNode*, string; output: bool
    TrieNode* curr = root;
    for (int i = 0; i < key.length(); i++)//Goes through all the members in key
    {
        int index = CHAR_TO_INDEX(key[i]);
        if (curr->children[index] == nullptr)//If the next member in the tree is empty
        {
            return false;
        }
        curr = curr->children[index];
    }
    return (curr != nullptr && curr->isWordEnd);
}

int printAutoSuggestionsT(TrieNode* root, string query, string dadLatter = "")//the function prints all the words that start with the query
{//input: TrieNode*, string, string; output: int
    int numOfWords = 0;
    TrieNode* curr = root;
    for (int i = 0; i < query.length(); i++)//for each letter in the query
    {
        dadLatter += query[i];
        int index = CHAR_TO_INDEX(query[i]);
        if (curr->children[index] == nullptr)//if the letter is not in the trie
            return 0;

        curr = curr->children[index];
    }

    cout << dadLatter;
    return myPrint(curr, dadLatter);//print all the words that start with the query in the children of the last letter in the query
}

int myPrint(TrieNode* root, string str)//the function 
{//input: TrieNode*, string; output: int
    static bool firstRun = 1;
    bool flagOfFirstRun = firstRun;
    firstRun = 0;

    int numOfWords = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i] != nullptr)
        {
            if (numOfWords)
                cout << str;
            cout << char(i + 'a');
            myPrint(root->children[i], str+char(i+'a'));

            if (flagOfFirstRun)
                cout << endl;
            
            numOfWords++;
        }
    }
    if (flagOfFirstRun)
        firstRun = 1;
    return numOfWords;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void printT(TrieNode* t, int level)
{//input: TrieNode*, int; output: void
    if (t != nullptr)//if the node is not empty
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)//for each letter in the alphabet
        {
            if (t->children[i] != nullptr)//if the node has a child in the current letter
            {
                for (int i = 0; i < level; i++)//print spaces according to the level
                    cout << "   ";
                char ch = 'a' + i;
                cout << ch << ":" << endl;
                printT(t->children[i], level + 1);//print the child
            }
        }
    }
}

string pop_front(string key)//remove the first letter from the string
{//input: string; output: string
    if (key.size() < 2)//if the string is empty or has only one letter
    {
        string output;
        return output;
    }
    return key.substr(1);
}
