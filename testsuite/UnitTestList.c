/*
 * UnitTestList.c
 *
 *      Author: marissa
 */

#include <stdio.h>
#include <stdlib.h>

#include "Object.h"
#include "Node.h"
#include "List.h"

/*
 * macro to mimic the functionality of assert() from <assert.h>. The difference is that this version doesn't exit the program entirely.
 * It will just break out of the current function (or test case in this context).
 */
#define myassert(expr) if(!(expr)){ fprintf(stderr, "\t[assertion failed] %s: %s\n", __PRETTY_FUNCTION__, __STRING(expr)); return 0; }

struct list *testlist;

int testCount = 0;
int passCount = 0;

void printTestInfo(char* testName, char *info)
{
    fprintf(stdout, "%s - %s\n", testName, info);
}

void printTestResult(char* testName, int passed)
{
    if(passed) {
        fprintf(stdout, "%s - %s\n\n", "[PASSED]", testName);
    } else {
        fprintf(stdout, "%s - %s\n\n", "[FAILED]", testName);
    }
}

struct node *createTestNode(int jobid)
{
    struct object * job = createObject(jobid, "cmd args");
    struct node *node = createNode(job);
    return node;
}

///////////////////////////////////////////////////////
//
//No need to do a test for the freeList() function
//
///////////////////////////////////////////////////////


//Test 1
int addAtFrontWithNoNodes()
{
    struct node *node = createTestNode(1);
    addAtFront(testlist, node);
    myassert(testlist->size == 1)
    myassert(testlist->head == node)
    myassert(testlist->tail == node)
    myassert(testlist->head->next == NULL)
    myassert(testlist->head->prev == NULL)
    
    return 1;
}

//Test 2
int addAtFrontWithOneNode()
{
    struct node *startingNode = createTestNode(1);
    struct node *node = createTestNode(1);
    addAtRear(testlist, startingNode);
    addAtFront(testlist, node);
    myassert(testlist->size == 2)
    myassert(testlist->head == node)
    myassert(testlist->tail == startingNode)
    myassert(testlist->head->next == startingNode)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == node)
    
    return 1;

}

//Test 3
int addAtFrontWithTwoNodes(){
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    struct node *node = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    addAtFront(testlist, node);
    myassert(testlist->size == 3)
    myassert(testlist->head == node)
    myassert(testlist->tail == secondNode)
    myassert(testlist->head->next == firstNode)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == firstNode)
    
    return 1;
    
}
//Test 4
int addAtRearWithNoNodes()
{
	//Writing my own test!
	struct node *node = createTestNode(1);

    addAtRear(testlist, node);
    myassert(testlist->size == 1)
    myassert(testlist->head == node)
    myassert(testlist->tail == node)
    myassert(testlist->head->next == NULL)

	
 //	printTestInfo("addAtRearWithNoNodes", "(not implemented)");
    return 1;
}
//Test 5
int addAtRearWithOneNode()
{
    struct node *startingNode = createTestNode(1);
    struct node *node = createTestNode(1);
    addAtFront(testlist, startingNode);
    addAtRear(testlist, node);
    myassert(testlist->size == 2)
    myassert(testlist->head == startingNode)
    myassert(testlist->tail == node)
    myassert(testlist->head->next == node)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == startingNode)
    
    
    return 1;

}

//Test 6
int addAtRearWithTwoNodes(){
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    struct node *node = createTestNode(1);
    
    addAtFront(testlist, firstNode);
    addAtFront(testlist, secondNode);
    addAtRear(testlist, node);
    
    myassert(testlist->size == 3)
    myassert(testlist->head == secondNode)
    myassert(testlist->tail == node)
    myassert(testlist->head->next == firstNode)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == firstNode)
    
    return 1;
    
}

//Test 7
int removeFrontWithOneNode()
{
    struct node *startingNode = createTestNode(1);
    
    addAtFront(testlist, startingNode);
    
    myassert(removeFront(testlist) == startingNode)
    myassert(testlist->size == 0)
    myassert(testlist->head == NULL)
    myassert(testlist->tail == NULL)
    freeNode(startingNode, testlist->freeObject);
    
/*  myassert(testlist->head->next == NULL)        can't call a next on a NULL silly
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == NULL)
*/

    return 1;
    

}

//Test 8
int removeFrontWithTwoNodes()
{
    struct node *secondNode = createTestNode(1);
    struct node *firstNode =  createTestNode(1);
    
    addAtFront(testlist, secondNode);
    addAtFront(testlist, firstNode);
    
    myassert(removeFront(testlist) == firstNode)
    myassert(testlist->size == 1)
    myassert(testlist->head == secondNode)
    myassert(testlist->tail == secondNode)
    myassert(testlist->head->next == NULL)
    myassert(testlist->head->prev == NULL)
    
    freeNode(firstNode, testlist->freeObject);

    return 1;
    

}

//Test 9
int removeRearWithOneNode()
{
    struct node *startingNode = createTestNode(1);
    
    addAtFront(testlist, startingNode);
    
    myassert(removeRear(testlist) == startingNode)
    myassert(testlist->size == 0)
    myassert(testlist->head == NULL)
    myassert(testlist->tail == NULL)
    
    freeNode(startingNode, testlist->freeObject);
    return 1;
    

}

//Test 10
int removeRearWithTwoNodes()
{
    struct node *secondNode = createTestNode(1);
    struct node *firstNode =  createTestNode(1);
    
    addAtFront(testlist, secondNode);
    addAtFront(testlist, firstNode);
    
    myassert(removeRear(testlist) == secondNode)
    myassert(testlist->size == 1)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == firstNode)
    myassert(testlist->head->next == NULL)
    myassert(testlist->head->prev == NULL)

    freeNode(secondNode, testlist->freeObject);
    return 1;
    

}

//Test 11
int removeContainedNodeFromListWithOneNode()
{
    
    struct node *startingNode = createTestNode(1);
    
    addAtFront(testlist, startingNode);
    
    myassert(removeNode(testlist, startingNode) == startingNode)
    myassert(testlist->size == 0)
    myassert(testlist->head == NULL)
    myassert(testlist->tail == NULL)

    freeNode(startingNode, testlist->freeObject);
    return 1;
    
}

//Test 12
int removeContainedFirstNodeFromListWithTwoNodes(){
    
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    
    myassert(removeNode(testlist, firstNode) == firstNode)
    myassert(testlist->size == 1)
    myassert(testlist->head == secondNode)
    myassert(testlist->tail == secondNode)
    myassert(testlist->head->next == NULL)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == NULL)
    
    freeNode(firstNode, testlist->freeObject);
    return 1;
}  

//Test 13
int removeContainedMiddleNodeFromListWithThreeNodes(){
    
    struct node *firstNode = createTestNode(1);
    struct node *middleNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, middleNode);
    addAtRear(testlist, secondNode);
    
    myassert(removeNode(testlist, middleNode) == middleNode)
    myassert(testlist->size == 2)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == secondNode)
    myassert(testlist->head->next == secondNode)
    myassert(testlist->head->prev == NULL)
    myassert(testlist->tail->next == NULL)
    myassert(testlist->tail->prev == firstNode)
    
    freeNode(middleNode, testlist->freeObject);
    return 1;
}

//Test 14
int searchForNodeInEmptyList(){

    struct node *unusedNode = createTestNode(1);
    
    myassert(search(testlist, unusedNode) == NULL)
    myassert(testlist->size == 0)
    myassert(testlist->head == NULL)
    myassert(testlist->tail == NULL)

    freeNode(unusedNode, testlist->freeObject);
    return 1;
    
}

//Test 15
int searchForNodeInSizeOneList(){
    
    struct node *firstNode = createTestNode(1);
    
    addAtFront(testlist, firstNode);
    
    myassert(search(testlist, firstNode) == firstNode)
    myassert(testlist->size == 1)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == firstNode)

    
    return 1;
    
}

//Test 16
int searchForNodeInSizeTwoList(){
    
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    
    myassert(search(testlist, secondNode) == secondNode)
    myassert(testlist->size == 2)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == secondNode)

    
    return 1;
    
}

//Test 17
int searchForNodeInSizeThreeList(){
    
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    struct node *thirdNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    addAtRear(testlist, thirdNode);
    
    myassert(search(testlist, secondNode) == secondNode)
    myassert(testlist->size == 3)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == thirdNode)

    
    return 1;
    
}

//Test 18
int searchForUnusedNodeInThreeList(){

    struct node *unusedNode = createTestNode(1);
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    struct node *thirdNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    addAtRear(testlist, thirdNode);
    
    myassert(search(testlist, unusedNode) == NULL)
    myassert(testlist->size == 3)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == thirdNode)

    freeNode(unusedNode, testlist->freeObject);
    
    return 1;
    
}

//Test 19
int reverseListWithOneNode(){
    
    struct node *firstNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    
    reverseList(testlist);
    
    myassert(testlist->size == 1)
    myassert(testlist->head == firstNode)
    myassert(testlist->tail == firstNode)
    
    
    return 1;
}

//Test 20
int reverseListWithThreeNodes(){
    
    struct node *firstNode = createTestNode(1);
    struct node *secondNode = createTestNode(1);
    struct node *thirdNode = createTestNode(1);
    
    addAtRear(testlist, firstNode);
    addAtRear(testlist, secondNode);
    addAtRear(testlist, thirdNode);
    
    reverseList(testlist);
    
    myassert(testlist->size == 3)
    myassert(testlist->head == thirdNode)
    myassert(testlist->tail == firstNode)
    
    return 1;
}


//Test 21
int nullNodeTest()
{
    struct node *testNode = createTestNode(1);
    addAtRear(testlist, testNode);
    
    addAtFront(testlist, NULL);
    myassert(testlist->size == 1)
    myassert(testlist->head == testNode)
    myassert(testlist->tail == testNode)
   
    addAtRear(testlist, NULL);
    myassert(testlist->size == 1)
    myassert(testlist->head == testNode)
    myassert(testlist->tail == testNode)
   
    myassert(removeNode(testlist, NULL) == NULL)
    myassert(search(testlist, NULL) == NULL)
    
    return 1;
}

void beforeTest(char* testName)
{
    printTestInfo(testName, "Running...");
    testlist = createList(equals, toString, freeObject);
    testCount++;
}
void afterTest(char* testName, int result)
{
    printTestResult(testName, result);
    freeList(testlist);
    passCount += result;
}
/*
 * TODO: Write your test functions here
 */

void runUnitTests()
{
    int result;
    char *testName;
//Test 1
    testName = "addAtFrontWithNoNodes";
    beforeTest(testName);
    result = addAtFrontWithNoNodes();
    afterTest(testName, result);
//Test 2
    testName = "addAtFrontWithOneNode";
    beforeTest(testName);
    result = addAtFrontWithOneNode();
    afterTest(testName, result);
//Test 3
    testName = "addAtFrontWithTwoNodes";
    beforeTest(testName);
    result = addAtFrontWithTwoNodes();
    afterTest(testName, result);
//Test 4
    testName = "addAtRearWithNoNodes";
    beforeTest(testName);
    result = addAtRearWithNoNodes();
    afterTest(testName, result);
//Test 5
    testName = "addAtRearWithOneNode";
    beforeTest(testName);
    result = addAtRearWithOneNode();
    afterTest(testName, result);
//Test 6
    testName = "addAtRearWithTwoNodes";
    beforeTest(testName);
    result = addAtRearWithTwoNodes();
    afterTest(testName, result);
//Test 7
    testName = "removeFrontWithOneNode";
    beforeTest(testName);
    result = removeFrontWithOneNode();
    afterTest(testName, result);
//Test 8
    testName = "removeFrontWithTwoNodes";
    beforeTest(testName);
    result = removeFrontWithTwoNodes();
    afterTest(testName, result);
//Test 9
    testName = "removeRearWithOneNode";
    beforeTest(testName);
    result = removeRearWithOneNode();
    afterTest(testName, result);
//Test 10
    testName = "removeRearWithTwoNodes";
    beforeTest(testName);
    result = removeRearWithTwoNodes();
    afterTest(testName, result);
//Test 11
    testName = "removeContainedNodeFromListWithOneNode";
    beforeTest(testName);
    result = removeContainedNodeFromListWithOneNode();
    afterTest(testName, result);
//Test 12
    testName = "removeContainedFirstNodeFromListWithTwoNodes";
    beforeTest(testName);
    result = removeContainedFirstNodeFromListWithTwoNodes();
    afterTest(testName, result);
//Test 13
    testName = "removeContainedMiddleNodeFromListWithThreeNodes";
    beforeTest(testName);
    result = removeContainedMiddleNodeFromListWithThreeNodes();
    afterTest(testName, result);
//Test 14
    testName = "searchForNodeInEmptyList";
    beforeTest(testName);
    result = searchForNodeInEmptyList();
    afterTest(testName, result);
//Test 15
    testName = "searchForNodeInSizeOneList";
    beforeTest(testName);
    result = searchForNodeInSizeOneList();
    afterTest(testName, result);
//Test 16
    testName = "searchForNodeInSizeTwoList";
    beforeTest(testName);
    result = searchForNodeInSizeTwoList();
    afterTest(testName, result);
//Test 17
    testName = "searchForNodeInSizeThreeList";
    beforeTest(testName);
    result = searchForNodeInSizeThreeList();
    afterTest(testName, result);
//Test 18
    testName = "searchForUnusedNodeInThreeList";
    beforeTest(testName);
    result = searchForUnusedNodeInThreeList();
    afterTest(testName, result);
//Test 19
    testName = "reverseListWithOneNode";
    beforeTest(testName);
    result = reverseListWithOneNode();
    afterTest(testName, result);
//Test 20
    testName = "reverseListWithThreeNodes";
    beforeTest(testName);
    result = reverseListWithThreeNodes();
    afterTest(testName, result);
//Test 21
    testName = "nullNodeTest";
    beforeTest(testName);
    result = nullNodeTest();
    afterTest(testName, result);

    //TODO: Add in your tests here

    fprintf(stdout, "Test Cases: %d\n",  testCount);
    fprintf(stdout, "Passed: %d\n", passCount);
    fprintf(stdout, "Failed: %d\n", testCount - passCount);
}

int main(int argc, char *argv[])
{
    runUnitTests();
    exit(0);
}
