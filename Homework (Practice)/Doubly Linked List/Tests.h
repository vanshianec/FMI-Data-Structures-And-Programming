#define DOCTEST_CONFIG_IMPLEMENT
#define TEST_CASE DOCTEST_TEST_CASE
#include "doctest.h"

#include "DLinkedList.h"

TEST_CASE("Constructor")
{
    DLinkedList<int> l1;
    CHECK(l1.isEmpty() == true);
}

TEST_CASE("Copy Constructor")
{
    DLinkedList<int> l1;
    DLinkedList<int> l2(l1);
    CHECK(l1.isEmpty() == true);
    CHECK(l2.isEmpty() == true);

    l1.insertEnd(3);
    l1.insertEnd(5);
    l1.insertEnd(1);

    DLinkedList<int> l3(l1);

   //TODO ADD MORE CASES
}
