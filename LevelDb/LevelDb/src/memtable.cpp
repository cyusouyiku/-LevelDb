//
//  memtable.cpp
//  LevelDb
//
//  Created by 张宗煜 on 2025/7/13.
//

#include <iostream>
#include <string>
#include <vector>
#include "memtable.hpp"
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

void SkipList::put(const string& key, const string& value) {
    Node* x = head;
    vector<Node*> update(maxLevel, nullptr);
    for (int i = currentLevel-1; i>=0; i--){
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x && x->key == key){
        x->value = value;
        x->deleted = false;
    } else {
        int lvl = randomLevel();
        for (int i = currentLevel; i < lvl; i++) {
            update[i] = head;
        }
        if (lvl > currentLevel) {
            currentLevel = lvl;
        }
        Node* newNode = new Node(lvl, key, value, false);
        for (int i = 0; i < lvl; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        currentSize++;
    }
}

bool SkipList::remove(const string& key){
    Node* x = head;
    vector<Node*> update(maxLevel, nullptr);
    for (int i = currentLevel-1; i>=0; i--){
        while (x->forward[i] && x->forward[i]->key < key) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
    if (x && x->key == key && !x->deleted){
        x->value = "";
        x->deleted = true;
        currentSize--;
        return true;
    }
    return false;
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

void SkipList::clear(){
    Node* x = head->forward[0];
    while (x) {
        Node* next = x->forward[0];
        delete x;
        x = next;
    }
    for (int i = 0; i < maxLevel; i++) {
        head->forward[i] = nullptr;
    }
    currentLevel = 1;
    currentSize = 0;
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
