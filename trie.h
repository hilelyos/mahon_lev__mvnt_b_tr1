#pragma once
#include <iostream>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;


struct TrieNode
{
    TrieNode* children[ALPHABET_SIZE];
    bool isWordEnd;
};

TrieNode* getNode();//create new node
bool isLastNode(TrieNode* root);//check if node is last
bool insertT(TrieNode* root, string key);//insert word
int delT(TrieNode* root, string key);//delete word
bool searchT(TrieNode* root, string key);//search word
int printAutoSuggestionsT(TrieNode* root, string query, string dadLatter);
int myPrint(TrieNode* root, string str);
void printT(TrieNode* t, int level);//print trie
string pop_front(string key);//pop first letter

class Trie
{
    TrieNode* root;

public:
    Trie() { root = getNode(); }//create new trie
    bool insert(string wrd) { return insertT(root, wrd); }//insert word
    bool delW(string wrd)//delete word
    {
        int index = (int)wrd.front() - (int)'a';
        wrd = pop_front(wrd);
        int sucsses = delT(root->children[index], wrd);

        if (sucsses == 1)//if word deleted
        {
			delete root->children[index];
			root->children[index] = nullptr;
		}

        return sucsses != 0;
    }

    int printAutoSuggestions(string wrd) { return printAutoSuggestionsT(root, wrd, ""); }
    bool search(string key) { return searchT(root, key); }//search word
    void printTrie() { printT(root, 0); }//print trie
};
