#include <malloc.h>
#include <fstream>

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! @file Stack.h
//! Implements a stack class
//!
//! @author cvbnnthc1, 2017
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!@brief Magic numbers for debugging and testing
const int empty_stack = 0xE5;//!<Exception index of action with empty stack
const int memory_error = 0x111E;//!<Exception index of problem with memory allocation
const int file_error = 0xFE;//!<Exception index of problem with opening file
const int ver_error = 0x17E;//!<Exception index ofverification error
const size_t POISON_INT = 0xDEADBEEF;//!< Special consant to mark removing of Stack
typedef float value_type;//!< Element type

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Macro to test object integrity
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

#define ASSERT_OK() \
    if (!ok()) \
	    { \
        dump(); \
        throw ver_error;\
    }\

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Stack class
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

class Stack{
public:
	static const size_t size_step = 5;//!< Portion of allocated memory
	bool empty();
	size_t size();
	void push(value_type new_item);
	value_type pop();
	value_type top();
	void dump();
	bool ok();
	size_t capacity();
	Stack();
	Stack(const Stack &object);
	Stack & operator=(const Stack & object){
		if (this != &object){
			data_ = (value_type*)realloc(data_, 0);
			data_ = (value_type*)realloc(data_, object.capacity_*sizeof(value_type));
			if (!data_) throw memory_error;
			size_ = object.size_;
			capacity_ = object.capacity_;
			for (size_t i = 0; i < size_; i++)
				data_[i] = object.data_[i];
		}
		return *this;
	}
	
	~Stack();
private:
	value_type* data_;//!< Container of stack elements
	size_t size_;//!< Current size of Stack
	size_t capacity_;//!< Current capacity of stack 
};

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Constructor
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

Stack::Stack(){
	size_ = 0;
	capacity_= size_step;
	data_ = (value_type*)realloc(data_, size_step * sizeof(value_type));
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Check emptiness of stack
//!@param none
//!@return statement of stack
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

bool Stack::empty(){
	ASSERT_OK();
	return !size_;
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Size of stack
//!@param none
//!@return size
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

size_t Stack::size(){
	ASSERT_OK();
	return size_;
}

size_t Stack::capacity(){
	ASSERT_OK();
	return capacity_;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Pushes a value to the stack
//!@param new_item is an element to be pushed
//!@return none
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

void Stack::push(value_type new_item){
	ASSERT_OK();
	if (size_ >= capacity_){
		capacity_ = capacity_ + size_step;
		data_ = (value_type*)realloc(data_, capacity_ * sizeof(value_type));
		if (!data_) throw memory_error;
	}
	data_[size_++] = new_item;
	ASSERT_OK();
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Auxiliary verifier, checking statement of stack
//!@param none
//!@return none
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

bool Stack::ok(){
	return size_ <= capacity_ && capacity_ &&  capacity_%size_step==0;//!<Checking right values of fields
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Delete top element and return its value
//!@param none
//!@return deleted element
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

value_type Stack::pop(){
	ASSERT_OK();
	value_type result;
	if (!size_) throw empty_stack;
	result = data_[--size_];
	data_[size_] = POISON_INT;
	if (size_ <= capacity_ - size_step && size_>0 ){
		capacity_ = capacity_ - size_step;
		data_ = (value_type*)realloc(data_, capacity_ * sizeof(value_type));
	}
	ASSERT_OK();
	return result;
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Output stack to dump.txt
//!@param none
//!@return none
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

void Stack::dump(){
	std::ofstream dumpfile("Dump.txt", std::ios_base::app);
	if (!dumpfile.is_open()) throw file_error;
	dumpfile << "class Stack\n";
	if (size_ == POISON_INT && capacity_ == POISON_INT){
		dumpfile << "Size POISON_INT capacity_ POISON_INT\n";
	}
	else {
		if (ok()) dumpfile << "[ok]\n";
		else dumpfile << "ERROR\n";
		dumpfile << "Size " << size_ << " capacity_ " << capacity_ << "\n";
		dumpfile << "data_[" << size_ << "]\n{\n";
		for (size_t i = 0; i < capacity_; i++){
			dumpfile << "  ";
			if (i < size_) dumpfile << "* ";
			dumpfile << "a[" << i << "] = ";
			if (data_[i] == POISON_INT) dumpfile << "POISON_INT\n";
			else dumpfile << data_[i] << "\n";
		}
		dumpfile << "}";
	}
	dumpfile << "\n\n\n";
	dumpfile.close();
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//Top element in stack
//!@param none
//!@return top element
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
value_type Stack::top(){
	ASSERT_OK();
	if (!size_) throw empty_stack;
	return data_[size_ - 1];
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//!Destructor
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

Stack::~Stack(){
	capacity_ = POISON_INT;
	size_ = POISON_INT;
	data_ = (value_type*)realloc(data_, 0);
}

//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
//! Copy constructor
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐

Stack::Stack(const Stack &object){
	data_ = (value_type*)realloc(data_, object.capacity_*sizeof(value_type));
	size_ = object.size_;
	capacity_ = object.capacity_;
	for (size_t i = 0; i < size_; i++)
		data_[i] = object.data_[i];
}
//‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
