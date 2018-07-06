#pragma once

namespace Containers
{
	template<typename K, typename I>
	struct Node
	{
		using Key = K;
		using Item = I;

		Key				key;
		Item			item;
		Node			*next;
	};

	template<typename K, typename I>
	class Dictionary
	{
	public:
		using Key = K;
		using Item = I;

		Dictionary();
		Dictionary(const Dictionary<Key, Item> &rhs);
		Dictionary(Dictionary<Key, Item> &&rhs);
		~Dictionary();
		
		void insertFront(Key k, Item i);
		void insertEnd(Key k, Item i);
		void update(Key k, Item i);
		Item* lookup(Key k);
		void remove(Key k);
		void printList();
		void clearList();
		Dictionary<Key, Item>& operator=(const Dictionary<Key, Item> &rhs);
		Dictionary<Key, Item>& operator=(Dictionary<Key, Item> &&rhs);

	private:
		Node<Key, Item>		*head;
		Node<Key, Item>		*tail;

		void printListWorker(Node<Key, Item>* node);
		void clearListWorker(Node<Key, Item>* node);
	};
}