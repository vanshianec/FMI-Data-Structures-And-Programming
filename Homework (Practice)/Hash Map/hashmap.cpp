#ifndef _HASHMAP_CPP
#define _HASHMAP_CPP

#include "hashmap.h"
#include <cassert>

template<class K, class V>
HashMap<K, V>::HashMap(int _size, int (*_hash)(K)) : size(_size), hash(_hash)
{
    table = new Entry *[size];
    for (int i = 0; i < size; i++)
    {
        table[i] = nullptr;
    }
}

template<class K, class V>
V& HashMap<K, V>::operator[](const K& key)
{
    int index = hash(key);
    Entry *entry = find(index, key);

    if (entry != nullptr)
    {
        return entry->value;
    }

    table[index] = new Entry{key, V(), table[index]};
    return table[index]->value;
}

template<class K, class V>
V HashMap<K, V>::operator[](const K& key) const
{
    int index = hash(key);
    Entry *entry = find(index, key);

    assert(entry != nullptr);

    return entry->value;
}

template<class K, class V>
bool HashMap<K, V>::containsKey(const K& key) const
{
    int index = hash(key);
    Entry *entry = find(index, key);
    return entry != nullptr;
}

template<class K, class V>
typename HashMap<K, V>::Entry *HashMap<K, V>::find(int index, const K& key) const
{
    Entry *current = table[index];
    while (current != nullptr && current->key != key)
    {
        current = current->next;
    }

    return current;
}

template<class K, class V>
HashMap<K, V>::Iterator::Iterator(HashMap::Entry **_table, int _size) : table(_table), size(_size)
{
    currentEntry = nullptr;

    if (table == nullptr)
    {
        return;
    }

    int row = 0;
    while (row < size && table[row] == nullptr)
    {
        row++;
    }

    if (row == size)
    {
        return;
    }

    currentRow = row;
    currentEntry = table[currentRow];
}

template<class K, class V>
K HashMap<K, V>::Iterator::operator*() const
{
    assert(currentEntry != nullptr);
    return currentEntry->key;
}

template<class K, class V>
bool HashMap<K, V>::Iterator::operator!=(const HashMap::Iterator& other) const
{
    return currentEntry != other.currentEntry;
}

template<class K, class V>
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
    assert(currentEntry != nullptr);

    currentEntry = currentEntry->next;
    if (currentEntry == nullptr)
    {
        currentRow++;
        while (currentRow < size && table[currentRow] == nullptr)
        {
            currentRow++;
        }

        if (currentRow != size)
        {
            currentEntry = table[currentRow];
        }
    }

    return *this;
}

template<class K, class V>
typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
    return HashMap::Iterator(table, size);
}

template<class K, class V>
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
    return HashMap::Iterator(nullptr, 0);
}

#endif

