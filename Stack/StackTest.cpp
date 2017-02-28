#include <string>
#include <iostream>
#include "StackLib.h"



const int TEST_SIZE = 101;//!<Auxiliary const for unit test
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Auxiliary macro for unit test
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#define ASSERT_EQ(expression1,expression2)\
	if((expression1)!=(expression2)) throw ver_error;\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test pushing of elements
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#define TEST_PUSH()\
    try{\
		Stack* st=new Stack;\
		for (int i = 0; i < TEST_SIZE; i++){\
			st->push(i);\
		    ASSERT_EQ(st->size(), i+1);\
										}\
		std::cout << "Test push passed\n";\
		delete(st);\
	}\
	catch (int numberoferror){\
		std::cout << "Test push failed\n";\
	}\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test remove from empty stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_POP_FROM_EMPTY()\
	try{\
		Stack* st=new Stack;\
        st->pop();\
		delete(st);\
    }\
    catch (int numberoferror){\
	    if (numberoferror == empty_stack)std::cout << "Test pop from empty passed\n"; \
	    else std::cout << "Test pop from empty failed\n";\
    }\
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test remove all elements and cheking return elements 
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_POP_NORMAL()\
	try{\
		Stack* st = new Stack; \
        for (int i = 0; i < TEST_SIZE; i++)\
	    st->push(i);\
        for (int i = TEST_SIZE-1; i >= 0; i--){\
	        ASSERT_EQ(st->pop(),i)\
				}\
		std::cout << "Test pop normal passed\n"; \
		delete(st);\
	}\
	catch(int numberoferror){\
		std::cout << "Test pop normal failed\n"; \
    }\
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test cheking top element of empty stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_TOP_FROM_EMPTY()\
    try{\
		Stack* st = new Stack; \
	    st->top();\
		delete(st);\
    }\
    catch (int numberoferror){\
	    if (numberoferror == empty_stack)std::cout << "Test top from empty passed\n"; \
     	else std::cout << "Test top from empty failed\n"; \
	}\
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test cheking top elements of stack 
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_TOP_NORMAL()\
	try{\
		Stack* st=new Stack;\
		for (int i = 0; i < TEST_SIZE; i++){\
			st->push(i);\
			ASSERT_EQ(i, st->top());\
								}\
		std::cout << "Test top normal passed\n"; \
		delete(st);\
	}\
	catch (int numberoferror){\
		std::cout << "Test top normal failed\n"; \
	}\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test operator of equation
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_EQUATING()\
	try{\
		Stack* st=new Stack,* truecopy=new Stack; \
		for(int i = 0; i < TEST_SIZE; i++)\
			st->push(i);\
		*truecopy = *st;\
		st->pop();\
		ASSERT_EQ(TEST_SIZE-2, st->top());\
		ASSERT_EQ(TEST_SIZE-1, truecopy->top());\
		std::cout << "Test operator equating passed\n"; \
		delete(st);\
		delete(truecopy);\
    }\
    catch (int numberoferror){\
		std::cout << "Test operator equating failed\n"; \
    }\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Macro to test opening dump.txt
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST_DUMP()\
	try{\
		Stack* st = new Stack;\
		for (int i=0; i < TEST_SIZE; i++)\
			st->push(i);\
			st->dump();\
			std::cout << "Test dump passed\n"; \
		delete(st);\
    }\
	catch (int numberoferror){\
		std::cout << "Test dump failed\n"; \
	}\
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Main macro to call other tests
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
#define TEST(method)\
	if(method=="push")\
	    TEST_PUSH()\
	if(method=="pop"){\
	    TEST_POP_FROM_EMPTY()\
		TEST_POP_NORMAL()\
		}\
	if(method=="top"){\
		TEST_TOP_FROM_EMPTY()\
		TEST_TOP_NORMAL()\
		}\
	if(method=="equating")\
		TEST_EQUATING()\
    if(method=="dump")\
		TEST_DUMP()\

int main(){
	TEST("push");
	TEST("pop");
	TEST("top");
	TEST("equating");
	TEST("dump");
	getchar();
}



