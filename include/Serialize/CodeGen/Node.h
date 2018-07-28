#ifndef _SERIALIZE_CODE_GEN_NODE_H_
#define _SERIALIZE_CODE_GEN_NODE_H_

#include "../Config.h"

#include <StdExt/InPlace.h>

#include <list>
#include <memory>

namespace Serialize::CodeGen
{
	class Node;

	using NodeContainer = StdExt::InPlace<Node, 192>;
	using NodeList = std::list<NodeContainer>;

	/**
	 * @brief
	 *  The base class of all nodes in a document.  Its base functionality keeps, provides access,
	 *  and has ownership of child nodes.
	 */
	class SERIALIZE_EXPORT Node
	{
	public:

		/**
		 * @brief
		 *  A bi-directional iterator for accessing child nodes.
		 */
		class iterator
		{
			friend class Node;
		public:
			iterator() = default;

			Node* operator->();
			Node& operator*();

			bool operator==(const iterator& other) const;
			bool operator!=(const iterator& other) const;

			iterator& operator++();
			iterator operator++(int);

			iterator& operator--();
			iterator operator--(int);

			/**
			 * @brief
			 *  Returns the type index of the referenced node.
			 */
			std::type_index typeIndex() const;
			
			/**
			 * @brief
			 *  Casts the contained node to a node sub-type.
			 */
			template<typename node_t>
			node_t* cast()
			{
				static_assert(std::is_base_of_v<Node, node_t>);
				return (*mIterator).cast<node_t>();
			}

		private:
			iterator(const NodeList::iterator& nlIterator);

			NodeList::iterator mIterator;
		};

		/**
		 * @brief
		 *  A bi-directional const_iterator for accessing child nodes.
		 */
		class const_iterator
		{
			friend class Node;
		public:
			const_iterator() = default;

			const Node* operator->() const;
			const Node& operator*() const;

			bool operator==(const const_iterator& other) const;
			bool operator!=(const const_iterator& other) const;

			const_iterator& operator++();
			const_iterator operator++(int);

			const_iterator& operator--();
			const_iterator operator--(int);

			/**
			 * @brief
			 *  Returns the type index of the referenced node.
			 */
			std::type_index typeIndex() const;

			/**
			 * @brief
			 *  Casts the contained node to a node sub-type.
			 */
			template<typename node_t>
			const node_t* cast() const
			{
				static_assert(std::is_base_of_v<Node, node_t>);
				return (*mIterator).cast<node_t>();
			}

		private:
			const_iterator(NodeList::const_iterator& nlIterator);

			mutable NodeList::const_iterator mIterator;
		};

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		Node(Node&&) = default;
		Node& operator=(Node&&) = default;

		const Node* parent() const;
		Node* parent();

		/**
		 * @brief
		 *  Returns an iterator to the beginning of the child list.
		 */
		iterator begin();

		/**
		 * @brief
		 *  Returns a const_iterator to the beginning of the child list.
		 */
		const_iterator begin() const;

		/**
		 * @brief
		 *  Returns an iterator to the end of the child list.
		 */
		iterator end();

		/**
		 * @brief
		 *  Returns a const_iterator to the end of the child list.
		 */
		const_iterator end() const;

		/**
		 * @brief
		 *  Internally allocates and creates a node of the requested type and adds it to the end of the
		 *  list of children.
		 */
		template<typename node_t, typename... args_t>
		node_t* addChildNode(args_t&& ...arguments)
		{
			static_assert(std::is_base_of_v<Node, node_t>);

			NodeContainer Container = NodeContainer::make<node_t>(arguments...);

			mChildren.push_back(std::move(Container));
			
			node_t* ret = mChildren.back().cast<node_t>();

			return ret;
		}

	protected:
		Node();
		virtual ~Node();

		/**
		 * @brief
		 *  This function is called internally to set the parent node of this node.  It can be overridden
		 *  to handle the event.  An InvalidParent exception should be thrown if the parent is
		 *  unacceptable.  The base function should be called at the end of any overrides.
		 */
		virtual void setParent(Node* parent);

	private:
		NodeList mChildren;
		Node* mParent;
	};
}

#endif // !_SERIALIZE_CODE_GEN_NODE_H_