#define DOCTEST_CONFIG_IMPLEMENT
#define TEST_CASE DOCTEST_TEST_CASE

#include "doctest.h"

#include "DLinkedList.h"

TEST_CASE ("Iterator")
{
    DLinkedList<int> empty;
    DLinkedList<int>::Iterator it1 = empty.begin();
    int count = 0;
    while (it1 != empty.end())
    {
        count++;
    }
            CHECK(count == 0);

    DLinkedList<int> list;
    list.insertFront(4);

    DLinkedList<int>::Iterator it2 = list.begin();
            CHECK(*it2 == 4);

    list.insertFront(1);
    list.insertFront(6);

    int expectedValues[3] = {6, 1, 4};

    int index = 0;
    DLinkedList<int>::Iterator it3 = list.begin();
    while (it3 != list.end())
    {
                CHECK(*it3 == expectedValues[index++]);
        ++it3;
    }

    index = 0;
    for (int x : list)
    {
                CHECK(x == expectedValues[index++]);
    }
}

TEST_CASE ("Insert Front")
{
    DLinkedList<int> list;
    list.insertFront(4);
            CHECK(*(list.begin()) == 4);

    list.insertFront(7);
            CHECK(*(list.begin()) == 7);

    list.insertFront(1);

    int expectedValues[3] = {1, 7, 4};

    int index = 0;

    for (int x : list)
    {
                CHECK(x == expectedValues[index++]);
    }
}

TEST_CASE ("Insert Back")
{
    DLinkedList<int> list;
    list.insertBack(4);
            CHECK(*(list.begin()) == 4);

    list.insertBack(7);
            CHECK(*(list.begin()) == 4);

    list.insertBack(1);

    int expectedValues[3] = {4, 7, 1};

    int index = 0;

    for (int x : list)
    {
                CHECK(x == expectedValues[index++]);
    }
}

TEST_CASE ("Is Empty")
{
    DLinkedList<int> list;
            CHECK(list.isEmpty());
    list.insertFront(3);
            CHECK(!list.isEmpty());
    DLinkedList<int> list2;
    list2.insertBack(4);
            CHECK(!list2.isEmpty());
}

TEST_CASE ("Size")
{
    DLinkedList<int> list;
            CHECK(list.size() == 0);
    list.insertFront(2);
            CHECK(list.size() == 1);
    list.insertBack(4);
            CHECK(list.size() == 2);
    list.insertFront(22);
    list.insertBack(11);
            CHECK(list.size() == 4);
}

TEST_CASE ("Front")
{
    DLinkedList<int> list;
    bool exception = false;
    try
    {
        list.front();
    }
    catch (std::out_of_range& exc)
    {
        exception = true;
    }
            CHECK(exception);
    list.insertFront(3);
            CHECK(list.front() == 3);
    list.insertBack(5);
            CHECK(list.front() == 3);
    list.insertFront(9);
            CHECK(list.front() == 9);
}

TEST_CASE ("Back")
{
    DLinkedList<int> list;
    bool exception = false;
    try
    {
        list.back();
    }
    catch (std::out_of_range& exc)
    {
        exception = true;
    }
            CHECK(exception);
    list.insertBack(3);
            CHECK(list.back() == 3);
    list.insertFront(4);
            CHECK(list.back() == 3);
    list.insertBack(9);
            CHECK(list.back() == 9);
}

TEST_CASE ("Get")
{
    DLinkedList<int> list;
    bool emptyException = false;
    try
    {
        list.get(0);
    }
    catch (std::out_of_range& exc)
    {
        emptyException = true;
    }

            CHECK(emptyException);

    list.insertFront(3);
    bool outOfRangeException = false;
    try
    {
        list.get(-1);
    }
    catch (std::invalid_argument& exc)
    {
        outOfRangeException = true;
    }

            CHECK(outOfRangeException);

    outOfRangeException = false;

    try
    {
        list.get(1);
    }
    catch (std::invalid_argument& exc)
    {
        outOfRangeException = true;
    }

            CHECK(outOfRangeException);

            CHECK(list.get(0) == 3);
    list.insertFront(5);
            CHECK(list.get(0) == 5);
            CHECK(list.get(1) == 3);
    list.insertBack(11);
            CHECK(list.get(2) == 11);
    list.insertBack(22);
            CHECK(list.get(3) == 22);
}

TEST_CASE ("Reverse")
{
    DLinkedList<int> list;
    list.insertBack(3);

    list.reverse();
            CHECK(list.front() == 3);
            CHECK(list.back() == 3);

    list.insertBack(9);
    list.insertBack(14);
    list.insertBack(22);

            CHECK(list.get(1) == 9);
            CHECK(list.get(2) == 14);

    list.reverse();

            CHECK(list.get(0) == 22);
            CHECK(list.get(3) == 3);
            CHECK(list.front() == 22);
            CHECK(list.back() == 3);
            CHECK(list.get(1) == 14);
            CHECK(list.get(2) == 9);
    int expectedValues[4] = {22, 14, 9, 3};
    int index = 0;

    for (int x : list)
    {

                CHECK(x == expectedValues[index++]);
    }
}

TEST_CASE("Copy Constructor")
{
    DLinkedList<int> list;
    list.insertBack(4);
    list.insertBack(6);
    list.insertBack(1);
    list.insertBack(12);

    DLinkedList<int> list2(list);

    int expectedValues[4] = {4, 6, 1, 12};
    int index = 0;

    for(int x : list2)
    {
        CHECK(x == expectedValues[index++]);
    }
}
