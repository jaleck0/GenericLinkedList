#include "unity.h"
#include "linked_list.h"

// I rather dislike keeping line numbers updated, so I made my own
// macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}


// TODO:
//  - Rename and change this test to something usefull
//  - Add more tests
//  - Remove this comment :)
// Should you need a list of all TEST_ASSERT macros: take a look
// at unity.h
void test_AddTailElement(void)
{
    int number = 8;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number);

    int returnNumber = *(int*)LinkedListGetHead(list);

    TEST_ASSERT_EQUAL(returnNumber, number);
    DestroyLinkedList(&list);
}

void test_Add4TailElements(void)
{
    int number0 = 8;
    int number1 = 5;
    int number2 = 2;
    int number3 = 6;

    LinkedList* list = InitialiseLinkedList(sizeof(int));
    
    LinkedListAddTail(list, &number0);
    LinkedListAddTail(list, &number1);
    LinkedListAddTail(list, &number2);
    LinkedListAddTail(list, &number3);

    int returnNumber0 = *(int*)LinkedListGetNext(list);
    int returnNumber1 = *(int*)LinkedListGetNext(list);
    int returnNumber2 = *(int*)LinkedListGetNext(list);
    int returnNumber3 = *(int*)LinkedListGetNext(list);
    int returnNumber4 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    TEST_ASSERT_EQUAL(returnNumber1, number1);
    TEST_ASSERT_EQUAL(returnNumber2, number2);
    TEST_ASSERT_EQUAL(returnNumber3, number3);
    TEST_ASSERT_EQUAL(returnNumber0, returnNumber4);
    DestroyLinkedList(&list);
}

void test_AddFirstElementAtRightIndex(void)
{
    int number0 = 8;

    LinkedList* list = InitialiseLinkedList(sizeof(int));
    
    LinkedListAddAt(list, 0,&number0);

    int returnNumber0 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    DestroyLinkedList(&list);
}

void test_AddFirstElementAtWrongIndex(void)
{
    int number0 = 8;

    LinkedList* list = InitialiseLinkedList(sizeof(int));
    
    LinkedListAddAt(list, 2,&number0);

    int returnNumber0 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    DestroyLinkedList(&list);
}


void test_AddElementsAtEndIndex(void)
{
    int number0 = 2;
    int number1 = 6;


    LinkedList* list = InitialiseLinkedList(sizeof(int));
    
    LinkedListAddAt(list, 0,&number0);
    LinkedListAddAt(list, 1,&number1);

    int returnNumber0 = *(int*)LinkedListGetNext(list);
    int returnNumber1 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    TEST_ASSERT_EQUAL(returnNumber1, number1);
    DestroyLinkedList(&list);
}

void test_GetHeadNoElements(void)
{
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    
    TEST_ASSERT_NULL(LinkedListGetHead(list));
    DestroyLinkedList(&list);
}

void test_GetHeadWithElements(void)
{
    int number0 = 2;
    int number1 = 6;

    LinkedList* list = InitialiseLinkedList(sizeof(int));

    LinkedListAddAt(list, 0,&number0);
    LinkedListAddAt(list, 1,&number1);

    int returnNumber0 = *(int*)LinkedListGetHead(list);
    int returnNumber1 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    TEST_ASSERT_EQUAL(returnNumber1, number1);
    DestroyLinkedList(&list);
}

void test_GetNextOverflow(void)
{
    int number0 = 2;
    int number1 = 6;

    LinkedList* list = InitialiseLinkedList(sizeof(int));

    LinkedListAddAt(list, 0,&number0);
    LinkedListAddAt(list, 1,&number1);

    int returnNumber0 = *(int*)LinkedListGetHead(list);
    int returnNumber1 = *(int*)LinkedListGetNext(list);
    int returnNumber2 = *(int*)LinkedListGetNext(list);

    TEST_ASSERT_EQUAL(returnNumber0, number0);
    TEST_ASSERT_EQUAL(returnNumber1, number1);
    TEST_ASSERT_EQUAL(returnNumber2, number0);
    DestroyLinkedList(&list);
}

void test_RemoveNonExistentTail(void)
{
    LinkedList* list = InitialiseLinkedList(sizeof(int));

    TEST_ASSERT_EQUAL(LinkedListRemoveTail(list), -1);
    DestroyLinkedList(&list);
}

void test_RemoveFirstIndex(void)
{
    int number0 = 9;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number0);
    int returnNumber0 = *(int*)LinkedListGetHead(list);
    TEST_ASSERT_EQUAL(returnNumber0, number0);
    LinkedListRemoveTail(list);
    TEST_ASSERT_NULL(LinkedListGetHead(list));
    DestroyLinkedList(&list);
}

void test_RemoveExistentTail(void)
{
    int number0 = 9;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number0);
    TEST_ASSERT_EQUAL(LinkedListRemoveTail(list), 0);
    TEST_ASSERT_NULL(LinkedListGetHead(list));
    DestroyLinkedList(&list);
}

void test_RemoveAtNonExistent(void)
{
    LinkedList* list = InitialiseLinkedList(sizeof(int));

    TEST_ASSERT_EQUAL(LinkedListRemoveAt(list,0), -1);
    DestroyLinkedList(&list);
}

void test_RemoveAtFirstIndex(void)
{
    int number0 = 9;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number0);
    int returnNumber0 = *(int*)LinkedListGetHead(list);
    TEST_ASSERT_EQUAL(returnNumber0, number0);
    LinkedListRemoveAt(list,0);
    TEST_ASSERT_NULL(LinkedListGetHead(list));
    DestroyLinkedList(&list);
}

void test_RemoveExistentLongTail(void)
{
    int number0 = 9;
    int number1 = 10;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number0);
    LinkedListAddTail(list, &number1);
    TEST_ASSERT_EQUAL(LinkedListRemoveTail(list), 0);
    int retNumber0 = *(int*)LinkedListGetHead(list);
    TEST_ASSERT_EQUAL( retNumber0, number0);
    DestroyLinkedList(&list);
}

void test_RemoveAtExistentIndex(void)
{
    int number0 = 9;
    int number1 = 10;
    LinkedList* list = InitialiseLinkedList(sizeof(int));
    LinkedListAddTail(list, &number0);
    LinkedListAddTail(list, &number1);
    TEST_ASSERT_EQUAL(LinkedListRemoveAt(list,1), 0);
    int retNumber0 = *(int*)LinkedListGetHead(list);
    TEST_ASSERT_EQUAL( retNumber0, number0);
    DestroyLinkedList(&list);
}

void test_RemoveAllValid(void)
{
    int number0 = 9;
    int number1 = 10;
    
    LinkedList* list = InitialiseLinkedList(sizeof(int));

    LinkedListAddTail(list, &number0);
    LinkedListAddTail(list, &number1);

    LinkedListRemoveAll(list);

    TEST_ASSERT_NULL(LinkedListGetHead(list));
    TEST_ASSERT_NULL(LinkedListGetNext(list));
    DestroyLinkedList(&list);
}

void test_RemoveList(void)
{
    LinkedList* list = InitialiseLinkedList(sizeof(int));

    TEST_ASSERT_NULL(LinkedListGetNext(list));
    DestroyLinkedList(&list);
}

void test_InvalidListConstructor(void)
{
    TEST_ASSERT_NULL(InitialiseLinkedList(0));
}

void test_LinkedListLengthWithElements(void)
{
    int number0 = 9;
    int number1 = 10;
    LinkedList* list = InitialiseLinkedList(sizeof(int));

    LinkedListAddTail(list, &number0);
    LinkedListAddTail(list, &number1);

    size_t size = LinkedListGetLength(list);
    size_t trueSize = 2; 
    

    TEST_ASSERT_EQUAL(size, trueSize);
    DestroyLinkedList(&list);
}



int main(/*int argc, char* argv[]*/)
{
    UnityBegin();

    MY_RUN_TEST(test_AddTailElement);
    MY_RUN_TEST(test_Add4TailElements);
    MY_RUN_TEST(test_AddFirstElementAtRightIndex);
    MY_RUN_TEST(test_AddFirstElementAtWrongIndex);
    MY_RUN_TEST(test_AddElementsAtEndIndex);
    MY_RUN_TEST(test_GetHeadNoElements);
    MY_RUN_TEST(test_GetHeadWithElements);
    MY_RUN_TEST(test_GetNextOverflow);
    MY_RUN_TEST(test_RemoveNonExistentTail);
    MY_RUN_TEST(test_RemoveExistentTail);
    MY_RUN_TEST(test_RemoveExistentLongTail);
    MY_RUN_TEST(test_RemoveAllValid);
    MY_RUN_TEST(test_RemoveList);
    MY_RUN_TEST(test_InvalidListConstructor);
    MY_RUN_TEST(test_LinkedListLengthWithElements);
    
    return UnityEnd();
}
