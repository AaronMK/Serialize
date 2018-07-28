#include <Serialize/CodeGen/Node.h>

namespace Serialize::CodeGen
{
	Node* Node::iterator::operator->()
	{
		return (*mIterator).get();
	}

	Node& Node::iterator::operator*()
	{
		return *(*mIterator);
	}

	bool Node::iterator::operator==(const iterator& other) const
	{
		return mIterator == other.mIterator;
	}

	bool Node::iterator::operator!=(const iterator& other) const
	{
		return mIterator != other.mIterator;
	}

	Node::iterator& Node::iterator::operator++()
	{
		++mIterator;
		return *this;
	}

	Node::iterator Node::iterator::operator++(int)
	{
		return iterator(mIterator++);
	}


	Node::iterator& Node::iterator::operator--()
	{
		--mIterator;
		return *this;
	}

	Node::iterator Node::iterator::operator--(int)
	{
		return iterator(mIterator--);
	}


	Node::iterator::iterator(const NodeList::iterator& nlIterator)
		: mIterator(nlIterator)
	{

	}

	std::type_index Node::iterator::typeIndex() const
	{
		return (*mIterator).typeIndex();
	}

	//////////////////////////

	const Node* Node::const_iterator::operator->() const
	{
		return (*mIterator).get();
	}

	const Node& Node::const_iterator::operator*() const
	{
		return *(*mIterator);
	}

	bool Node::const_iterator::operator==(const const_iterator& other) const
	{
		return mIterator == other.mIterator;
	}

	bool Node::const_iterator::operator!=(const const_iterator& other) const
	{
		return mIterator != other.mIterator;
	}

	Node::const_iterator& Node::const_iterator::operator++()
	{
		++mIterator;
		return *this;
	}

	Node::const_iterator Node::const_iterator::operator++(int)
	{
		return const_iterator(mIterator++);
	}


	Node::const_iterator& Node::const_iterator::operator--()
	{
		--mIterator;
		return *this;
	}

	Node::const_iterator Node::const_iterator::operator--(int)
	{
		return const_iterator(mIterator--);
	}


	Node::const_iterator::const_iterator(NodeList::const_iterator& nlIterator)
		: mIterator(nlIterator)
	{
	}

	std::type_index Node::const_iterator::typeIndex() const
	{
		return (*mIterator).typeIndex();
	}

	//////////////////////////


	Node::Node()
		: mParent(nullptr)
	{
	}

	Node::~Node()
	{
	}

	void Node::setParent(Node* parent)
	{
		mParent = parent;
	}

	const Node* Node::parent() const
	{
		return mParent;
	}

	Node* Node::parent()
	{
		return mParent;
	}

	Node::iterator Node::begin()
	{
		return iterator(mChildren.begin());
	}

	Node::const_iterator Node::begin() const
	{
		return const_iterator(mChildren.begin());
	}

	Node::iterator Node::end()
	{
		return iterator(mChildren.end());
	}

	Node::const_iterator Node::end() const
	{
		return const_iterator(mChildren.end());
	}
}