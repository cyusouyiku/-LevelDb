//
//  immutable_memtable.cpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/14.
//

#include <iostream>
#include <string>
#include <vector>
#include "immutable_memtable.hpp"
using namespace std;

SkipList::Node::Node(int level, const string& k, const string& v, bool del)
    : key(k), value(v), forward(level, nullptr), deleted(del) {}

SkipList::SkipList(int maxL, float prob, size_t maxS)
    : maxLevel(maxL), probability(prob), maxSize(maxS),
      currentLevel(1), currentSize(0)
{
    head = new Node(maxLevel, "", "", false);
}

SkipList::~SkipList() {
    clear();
    delete head;
}

int SkipList::randomLevel() {
    int lvl = 1;
    while (((float)rand() / RAND_MAX) < probability && lvl < maxLevel) {
        lvl++;
    }
    return lvl;
}

bool SkipList::contains(const string& key){
    Node* x = head;
    for (int i = currentLevel - 1; i >= 0; i--){
        while (x->forward[i] && x->forward[i]->key < key){
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return x && x->key == key && !x->deleted;
}

bool SkipList::get(const string& key, string& value){
    Node* x = head;
    for (int i = currentLevel -1; i>=0 ; i--){
        while (x->forward[i] && x->forward[i]->key < key){
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x && x->key == key && !x->deleted){
        value = x->value;
        return true;
    }
    return false;
}

void SkipList::print(){
    Node* x = head->forward[0];
    while (x) {
        if (!x->deleted) {
            cout << x->key << ": " << x->value << endl;
        }
        x = x->forward[0];
    }
}

size_t SkipList::size(){
    return currentSize;
}

bool SkipList::isFull(){
    return currentSize >= maxSize;
}


