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

TEST_CASE ("Insert At")
{
    DLinkedList<int> list;
    bool invalidIndexException;
    try
    {
        list.insertAt(-1, 9);
    }
    catch (std::out_of_range& exc)
    {
        invalidIndexException = true;
    }
            CHECK(invalidIndexException);

    invalidIndexException = false;

    try
    {
        list.insertAt(1, 9);
    }
    catch (std::out_of_range& exc)
    {
        invalidIndexException = true;
    }

            CHECK(invalidIndexException);

    list.insertAt(0, 9);
            CHECK(list.get(0) == 9);

    invalidIndexException = false;
    try
    {
        list.insertAt(2, 4);
    }
    catch (std::invalid_argument& exc)
    {
        invalidIndexException = true;
    }

            CHECK(invalidIndexException);


    list.insertAt(0, 8);
            CHECK(list.get(0) == 8);
    list.insertAt(1, 10);
            CHECK(list.get(1) == 10);
    list.insertAt(1, 11);
            CHECK(list.get(1) == 11);
    list.insertAt(4, 20);
            CHECK(list.get(4) == 20);

    int expectedValues[5] = {8, 11, 10, 9, 20};
    int index = 0;

    for (int x : list)
    {
                CHECK(expectedValues[index++] == x);
    }
}

TEST_CASE ("Copy Constructor")
{
    DLinkedList<int> list;
    DLinkedList<int> list2(list);
            CHECK(list2.isEmpty());
    list.insertBack(4);
    list.insertBack(6);
    list.insertBack(1);
    list.insertBack(12);

    DLinkedList<int> list3(list);

    int expectedValues[4] = {4, 6, 1, 12};
    int index = 0;

    for (int x : list3)
    {
                CHECK(x == expectedValues[index++]);
    }
}

TEST_CASE ("Remove Front")
{
    DLinkedList<int> list;
    bool exception = false;

    try
    {
        list.removeFront();
    }
    catch (std::out_of_range& exc)
    {
        exception = true;
    }

            CHECK(exception);

    list.insertBack(3);
            CHECK(list.removeFront() == 3);
            CHECK(list.isEmpty());

    list.insertBack(9);
    list.insertBack(2);
            CHECK(list.removeFront() == 9);
            CHECK(list.removeFront() == 2);

}

TEST_CASE ("Remove Back")
{
    DLinkedList<int> list;
    bool exception = false;

    try
    {
        list.removeBack();
    }
    catch (std::out_of_range& exc)
    {
        exception = true;
    }

            CHECK(exception);

    list.insertBack(3);
            CHECK(list.removeBack() == 3);
            CHECK(list.isEmpty());

    list.insertBack(9);
    list.insertBack(2);
            CHECK(list.removeBack() == 2);
            CHECK(list.removeBack() == 9);

}

TEST_CASE ("Delete At")
{
    DLinkedList<int> list;
    bool exception = false;

    try
    {
        list.deleteAt(0);
    }
    catch (std::out_of_range& exc)
    {
        exception = true;
    }

            CHECK(exception);

    list.insertBack(9);

    exception = false;

    try
    {
        list.deleteAt(1);
    }
    catch (std::invalid_argument& exc)
    {
        exception = true;
    }

            CHECK(exception);

    exception = false;

    try
    {
        list.deleteAt(-1);
    }
    catch (std::invalid_argument& exc)
    {
        exception = true;
    }

            CHECK(exception);

            CHECK(list.deleteAt(0) == 9);
            CHECK(list.isEmpty());

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);

    list.deleteAt(2);
            CHECK(list.front() == 1);
            CHECK(list.back() == 2);

    list.insertBack(3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
    list.deleteAt(1);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
    list.insertAt(1, 2);
    list.deleteAt(0);
            CHECK(list.get(0) == 2);
            CHECK(list.get(1) == 3);

            CHECK(list.deleteAt(1) == 3);
            CHECK(list.deleteAt(0) == 2);
            CHECK(list.isEmpty());
}

TEST_CASE("Swap")
{
    DLinkedList<int> list;

}














