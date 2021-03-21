#include <cassert>
#include <iostream>

class Allocator {
	char * ptr, * ptr_top;
	size_t allocSize, freeSize;
public:
	Allocator() {
		allocSize = 0;
		freeSize = 0;
		ptr = nullptr;
		ptr_top = nullptr;
	}

	~Allocator() {
		delete[] ptr;
	}

	void makeAllocator(size_t maxSize) {
		if (ptr != nullptr) {
			delete[] ptr;
			ptr = nullptr;
			ptr_top = nullptr;
			allocSize = 0;
			freeSize = 0;
		}
		ptr = new char[maxSize];
		if (ptr != nullptr) {
			allocSize = maxSize;
			freeSize = maxSize;
			ptr_top = ptr;
		}
	}

	char * alloc(size_t size) {
		if (ptr == nullptr || freeSize < size) {
			return nullptr;
		}
		char * new_ptr = ptr_top;
		ptr_top += size;
		freeSize -= size;
		return new_ptr;
	}

	void reset() {
		ptr_top = ptr;
		freeSize = allocSize;
	}
};

int main() {
	Allocator my_alloc;

	char * ptr = my_alloc.alloc(1);
       	assert(ptr == nullptr);

	my_alloc.makeAllocator(100);

	char *ptr1 = my_alloc.alloc(50);
       	char *ptr2 = my_alloc.alloc(30);
       	char *ptr3 = my_alloc.alloc(20);
	char *ptr4 = my_alloc.alloc(1);

	assert( (ptr1 != nullptr) && 
		(ptr2 != nullptr) &&
		(ptr3 != nullptr) &&
		(ptr4 == nullptr) );

	assert( (ptr2 - ptr1 == 50) &&
		(ptr3 - ptr2 == 30) );

	my_alloc.reset();
	assert(ptr == nullptr);

	ptr1 = my_alloc.alloc(70);
        ptr2 = my_alloc.alloc(20);
        ptr3 = my_alloc.alloc(10);
        ptr4 = my_alloc.alloc(10);

	assert( (ptr1 != nullptr) &&
                (ptr2 != nullptr) &&
                (ptr3 != nullptr) &&
                (ptr4 == nullptr) );

        assert( (ptr2 - ptr1 == 70) &&
                (ptr3 - ptr2 == 20) );

	std::cout << "All tests passed" << std::endl;

	return 0;
}
