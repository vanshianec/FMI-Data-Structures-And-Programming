#ifndef _HASHMAP_H
#define _HASHMAP_H

template<class K, class V>
class HashMap
{

public:
    HashMap(int size, int (*hash)(K key));

    V operator[](const K& key) const;
    V& operator[](const K& key);
    bool containsKey(const K& key) const;

private:
    struct Entry
    {
        K key;
        V value;
        Entry *next;
    };

    Entry **table;
    int (*hash)(K key);
    int size;

    Entry *find(int index, const K& key) const;

public:
    class Iterator
    {
    public:
        Iterator(Entry**, int);
        K operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator&) const;

    private:
        int currentRow;
        Entry* currentEntry;
        Entry **table;
        int size;
    };

    Iterator begin();
    Iterator end();

};

#include "hashmap.cpp"

#endif
