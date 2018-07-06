#include <iostream>
#include <string>
#include "Dictionary.h"

int main()
{
	// declaring a dictionary object with string key and item
	Containers::Dictionary<std::string, std::string> 
		dict = Containers::Dictionary<std::string, std::string>();

	// Case 1: Insert to the end
	dict.insertEnd("3", "Three");
	dict.insertEnd("9", "Nine");
	dict.insertEnd("8", "Eight");
	std::cout << "Case 1: ";
	dict.printList();

	// Case 2: Insert to the front
	dict.insertFront("2", "Two");
	dict.insertFront("1", "One");
	std::cout << "Case 2: ";
	dict.printList();

	// Case 3: Remove at head
	dict.remove("1");
	std::cout << "Case 3: ";
	dict.printList();

	// Case 4: Remove at middle
	dict.remove("3");
	std::cout << "Case 4: ";
	dict.printList();

	// Case 5: Remove at tail 
	dict.remove("9");
	std::cout << "Case 5: ";
	dict.printList();

	// Remove non existent key
	// dict.remove("1337"); // <-- problematic line

	// Case 6: Printing pointer returned from lookup
	auto item = dict.lookup("2");
	std::cout << "Case 6: " << *item << std::endl; 

	auto item2 = dict.lookup("null");
	if (!item2) 
		std::cout << "Case 6: Looking up invalid key will return null pointer" << std::endl;

	// Case 7: Inserting existing key will update the item
	dict.insertEnd("9", "Item of '9' has been changed");
	std::cout << "Case 7: ";
	dict.printList();

	// Case 8: Copy constructor
	Containers::Dictionary<std::string, std::string> 
		dict2 = Containers::Dictionary<std::string, std::string>(dict);
	
	// Clear items in dict to show dict2 is a deep copy of dict
	dict.clearList();
	std::cout << "Case 8: Dict 1 --- ";
	dict.printList();
	std::cout << std::endl;
	
	std::cout << "Case 8: Dict 2 --- ";
	dict2.printList();

	// Case 9: Copy operator
	Containers::Dictionary<std::string, std::string> dict3;
	dict3 = dict2;
	std::cout << "Case 9: Dict 2 --- ";
	dict2.printList();
	std::cout << "Case 9: Dict 3 --- ";
	dict3.printList();

	/*dict2.remove("0");
	dict3.remove("1");*/ // <-- remove not existing key will crash

	// To prove operator= is working, dict3 is a deep copy of dict2 
	dict3.remove("2");
	std::cout << "Case 9: Current Dict 2 --- ";
	dict2.printList();
	std::cout << "Case 9: Current Dict 3 --- ";
	dict3.printList();

	// Case 10: Parametrically polymorphic template parameters
	// List of explicit instantiations supported in ExpInstDict.cpp
	Containers::Dictionary<int, std::string> intStrDict = Containers::Dictionary<int, std::string>();
	intStrDict.insertFront(2, "Two");
	intStrDict.insertFront(1, "One");
	intStrDict.insertEnd(3, "Three");
	std::cout << "Case 10: ";
	intStrDict.printList();

	system("pause");
	return 0;
}