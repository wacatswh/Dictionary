#include <iostream>
#include "Dictionary.h"

template <typename Key, typename Item>
Containers::Dictionary<Key, Item>::Dictionary()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<typename Key, typename Item>
Containers::Dictionary<Key, Item>::Dictionary
(	const Dictionary<Key, Item>	&rhs	)
{
	if (!rhs.head)
		return;

	Node<Key, Item> *temp = rhs.head;

	while (temp)
	{
		insertEnd(temp->key, temp->item);
		temp = temp->next;
	}
}

template<typename Key, typename Item>
Containers::Dictionary<Key, Item>::Dictionary
(	Dictionary	&&rhs	)
{
	if (!rhs.head)
		return;

	Node<Key, Item> *right = rhs.head;
	Node<Key, Item> *left = head;

	left->key = right->key;
	left->item = right->item;

	right = right->next;

	while (right)
	{
		// if there is still a next node with value
		if (left->next != nullptr)
		{
			left = left->next;
			left->key = right->key;
			left->item = right->item;
			right = right->next;
		}

		// if there are no more value in next node of left
		else
		{
			insertEnd(right->key, right->item);
			right = right->next;
		}
	}

	rhs.clearList();
}

template<typename Key, typename Item>
Containers::Dictionary<Key, Item>::~Dictionary()
{
	clearList();
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::insertFront
(	Key		k, 
	Item	i	)
{
	Item *itemExist = lookup(k);

	// Key already exist
	if (itemExist) update(k, i);

	// Key not exist
	else if (!itemExist)
	{
		Node<Key, Item> *temp = new Node<Key, Item>;
		temp->key = k;
		temp->item = i;
		temp->next = nullptr;

		// Dictionary is empty
		if (!head)
		{
			head = temp;
			tail = temp;
			temp = nullptr;
		}

		// Dictionary is not empty
		else
		{
			temp->next = head;
			head = temp;
		}
	}
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::insertEnd
(	Key		k, 
	Item	i	)
{
	Item *itemExist = lookup(k);
	
	// Key already exist
	if (itemExist) update(k, i);

	// Key not exist
	else if (!itemExist)
	{
		Node<Key, Item> *temp = new Node<Key, Item>;
		temp->key = k;
		temp->item = i;
		temp->next = nullptr;

		// Dictionary is empty
		if (!head)
		{
			head = temp;
			tail = temp;
			temp = nullptr;
		}

		// Dictionary is not empty
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::update
(	Key		k, 
	Item	i	)
{
	Node<Key, Item> *traverse = head;

	while (traverse)
	{
		if (traverse->key == k)
		{
			traverse->item = i;
			break;
		}

		else
			traverse = traverse->next;
	}
}

template<typename Key, typename Item>
typename Containers::Dictionary<Key, Item>::Item* Containers::Dictionary<Key, Item>::lookup
(	Key		k	)
{
	Node<Key, Item> *temp;
	temp = head;

	while (temp)
	{
		if (temp->key == k)
			return &(temp->item);

		else
			temp = temp->next;
	}

	return nullptr;
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::remove
(	Key k	)
{
	Node<Key, Item> *current;
	Node<Key, Item> *prev;
	current = head;
	prev = nullptr;

	// move prev and current to target
	while (current != nullptr && current->key != k)
	//          
	{
		prev = current;
		current = current->next;
	}

	// delete at head
	if (current->key == head->key)
	{
		head = head->next;
		delete current;
	}

	// delete at tail
	else if (current->key == tail->key)
	{
		tail = prev;
		tail->next = nullptr;
		delete current;
	}

	// delete at middle
	else
	{
		prev->next = current->next;
		delete current;
	}
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::printList()
{
	if (!head)
		return;
	else
		printListWorker(head);
	std::cout << "\n";
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::printListWorker
(	Node<Key, Item>	*node	)
{
	if (node)
	{
		std::cout << node->item << "->";
		printListWorker(node->next);
	}
}

template<typename Key, typename Item>
Containers::Dictionary<Key, Item>& Containers::Dictionary<Key, Item>::operator=
(	const Dictionary<Key, Item>	&rhs	)
{
	if (!rhs.head)
		return *this;

	clearList();
	
	Node<Key, Item> *temp = rhs.head;

	while (temp)
	{
		insertEnd(temp->key, temp->item);
		temp = temp->next;
	}

	return *this;
}

template<typename Key, typename Item>
Containers::Dictionary<Key, Item>& Containers::Dictionary<Key, Item>::operator=
(	Dictionary<Key, Item>	&&rhs	)
{
	if (!rhs.head)
		return *this;

	Node<Key, Item> *right = rhs.head;
	Node<Key, Item> *left = head;

	left->key = right->key;
	left->item = right->item;

	right = right->next;

	while (right)
	{
		// if there is still a next node with value
		if (left->next != nullptr)
		{
			left = left->next;
			left->key = right->key;
			left->item = right->item;
			right = right->next;
		}

		// if there are no more value in next node of left
		else
		{
			insertEnd(right->key, right->item);
			right = right->next;
		}
	}

	rhs.clearList();

	return *this;
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::clearList()
{
	clearListWorker(head);
	head = nullptr;
	tail = nullptr;
}

template<typename Key, typename Item>
void Containers::Dictionary<Key, Item>::clearListWorker
(	Node<Key, Item> *node	)
{
	if (node)
	{
		Node<Key, Item> *next = node->next;
		delete node;
		node = next;
		clearListWorker(node);
	}
}