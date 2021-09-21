#ifndef FT_CONTAINERS_RB_TREE_HPP
# define FT_CONTAINERS_RB_TREE_HPP

namespace ft {
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc> class RBTree;
    template<typename T> struct RBTreeNode;
}

# include <memory>
# include <iostream>
# include "algorithm.hpp"
# include "iterators/rb_tree_iterator.hpp"
# include "utility.hpp"
# include "functional.hpp"

namespace ft {

    /**
     * Red-black tree node
     * @tparam T Type of the element
     */
    template<typename T>
    struct RBTreeNode {
        T          *value;
        RBTreeNode *left;
        RBTreeNode *right;
        RBTreeNode *parent;
        bool       color;

        RBTreeNode(T *value);
    };

    template<typename T>
    RBTreeNode<T>::RBTreeNode(T *value): value(value), left(NULL), right(NULL), parent(NULL), color(true) {}

    /**
     * Red-black tree container
     * @tparam T         Type of the elements
     * @tparam Compare   A binary predicate that takes two element keys as arguments and returns a bool
     * @tparam Alloc     Type of the allocator object used to define the storage allocation model
     * @tparam NodeAlloc Type of the allocator object used to define the storage allocation model for nodes
     */
    template< typename T, typename Compare = ft::less<T>, typename Alloc = std::allocator<T>, typename NodeAlloc = std::allocator< RBTreeNode<T> > >
    class RBTree {
    public:
        typedef T                                       value_type;
        typedef Alloc                                   allocator_type;
        typedef NodeAlloc                               node_allocator_type;
        typedef Compare                                 value_compare;
        typedef rb_tree_iterator<T, T*, T&>             iterator;
        typedef rb_tree_iterator<T, const T*, const T&> const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        typedef ptrdiff_t                               difference_type;
        typedef size_t                                  size_type;

    private:
        allocator_type         _alloc;
        node_allocator_type    _node_alloc;
        value_compare          _comp;
        RBTreeNode<value_type> *_root;
        RBTreeNode<value_type> *_end;
        size_type              _size;

        RBTreeNode<value_type>              *_find_leftmost_node(RBTreeNode<value_type> *node) const;
        RBTreeNode<value_type>              *_find_rightmost_node(RBTreeNode<value_type> *node) const;
        RBTreeNode<value_type>              *_create_node(const value_type &val);
        void                                _clear_node(RBTreeNode<value_type> *node);
        pair<RBTreeNode<value_type>*, bool> _bst_insert(RBTreeNode<value_type> *node);
        RBTreeNode<value_type>              *_bst_erase(RBTreeNode<value_type> *node);
        void                                _bst_clear(RBTreeNode<value_type> *node);
        RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *
        _bst_clone(RBTreeNode <value_type> *node, RBTreeNode <value_type> *parent);
        RBTreeNode<value_type>              *_bst_find(const value_type &val, RBTreeNode<value_type> *node) const;
        RBTreeNode<value_type>              *_bst_lower_bound(const value_type &val, RBTreeNode<value_type> *node) const;
        RBTreeNode<value_type>              *_bst_upper_bound(const value_type &val, RBTreeNode<value_type> *node) const;
        void                                _rotateLeft(RBTreeNode<value_type> *node);
        void                                _rotateRight(RBTreeNode<value_type> *node);
        void                                _balance(RBTreeNode<value_type> *node);
        void                                _print(RBTreeNode<value_type> *root, int space) const;

    public:
        RBTree(const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type(), const node_allocator_type &node_alloc = node_allocator_type());
        RBTree(const RBTree &src);

        ~RBTree();

        RBTree                               &operator=(const RBTree &other);

        iterator                             begin();
        const_iterator                       begin() const;

        iterator                             end();
        const_iterator                       end() const;

        reverse_iterator                     rbegin();
        const_reverse_iterator               rbegin() const;

        reverse_iterator                     rend();
        const_reverse_iterator               rend() const;

        bool                                 empty() const;
        size_type                            size() const;
        size_type                            max_size() const;

        pair<iterator, bool>                 insert(const value_type &value);
        iterator                             insert(iterator position, const value_type &val);
        template<typename InputIterator>
        void                                 insert(InputIterator first, InputIterator last,
                                                    typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);

        void                                 erase(iterator position);
        size_type                            erase(const value_type &val);
        void                                 erase(iterator first, iterator last);

        void                                 swap(RBTree &x);
        void                                 clear();

        value_compare                        value_comp() const;

        iterator                             find(const value_type &val);
        const_iterator                       find(const value_type &val) const;

        size_type                            count(const value_type &val) const;

        iterator                             lower_bound(const value_type &val);
        const_iterator                       lower_bound(const value_type &val) const;

        iterator                             upper_bound(const value_type &val);
        const_iterator                       upper_bound(const value_type &val) const;

        pair<iterator, iterator>             equal_range(const value_type &val);
        pair<const_iterator, const_iterator> equal_range(const value_type &val) const;

        allocator_type                       get_allocator() const;

        void                                 print() const;
    };

    /**
     * Find leftmost child of given node
     * @param node Root node
     * @return Leftmost child
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *RBTree<T, Compare, Alloc, NodeAlloc>::_find_leftmost_node(RBTreeNode<value_type> *node) const {
        while (node && node->left)
            node = node->left;
        return (node);
    }

    /**
     * Find rightmost child of given node
     * @param node Root node
     * @return Rightmost child
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *RBTree<T, Compare, Alloc, NodeAlloc>::_find_rightmost_node(RBTreeNode<value_type> *node) const {
        while (node && node->right)
            node = node->right;
        return (node);
    }

    /**
     * Creates new node
     * @param val Value of new node
     * @return New node
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *RBTree<T, Compare, Alloc, NodeAlloc>::_create_node(const value_type &val) {
        value_type *p = _alloc.allocate(1);
        _alloc.construct(p, val);

        RBTreeNode<value_type> *node = _node_alloc.allocate(1);
        _node_alloc.construct(node, RBTreeNode<value_type>(p));

        return (node);
    }

    /**
     * Destroy and deallocate one node
     * @param node
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_clear_node(RBTreeNode<value_type> *node) {
        if (node->value) {
            _alloc.destroy(node->value);
            _alloc.deallocate(node->value, 1);
        }
        _node_alloc.destroy(node);
        _node_alloc.deallocate(node, 1);
    }

    /**
     * Inserts new node to binary search tree
     * @param node
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    pair<RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type>*, bool> RBTree<T, Compare, Alloc, NodeAlloc>::_bst_insert(RBTreeNode<value_type> *node) {
        if (!_root) {
            _root = node;
            return (ft::make_pair(node, true));
        }

        RBTreeNode<T> *x = _root;
        RBTreeNode<T> *y = NULL;

        while (x) {
            y = x;

            if (_comp(*x->value, *node->value))
                x = y->right;
            else if (_comp(*node->value, *x->value))
                x = y->left;
            else
                return (ft::make_pair(x, false));
        }

        node->parent = y;

        if (_comp(*y->value, *node->value))
            y->right = node;
        else
            y->left = node;

        return (ft::make_pair(node, true));
    }

    /**
     * Remove one node from binary search tree
     * @param node
     * @return Node to perform balance function
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *RBTree<T, Compare, Alloc, NodeAlloc>::_bst_erase(RBTreeNode<value_type> *node) {
        if (!node)
            return (NULL);

        RBTreeNode<value_type> *parent = node->parent;

        if (!node->left && !node->right) {
            if (parent == _end) {
                _root = NULL;
            } else if (parent->left == node) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }

            _clear_node(node);
            return (parent);
        }

        if (!node->right) {
            RBTreeNode<value_type> *left = node->left;

            if (node->parent == _end) {
                _root = left;
                left->parent = NULL;
            } else if (node->parent->left == node) {
                node->parent->left = left;
                left->parent = node->parent;
            } else {
                node->parent->right = left;
                left->parent = node->parent;
            }

            _clear_node(node);
            return (left);
        }

        if (!node->left) {
            RBTreeNode<value_type> *right = node->right;

            if (node->parent == _end) {
                _root = right;
                right->parent = NULL;
            } else if (node->parent->left == node) {
                node->parent->left = right;
                right->parent = node->parent;
            } else {
                node->parent->right = right;
                right->parent = node->parent;
            }

            _clear_node(node);
            return (right);
        }

        RBTreeNode<value_type> *prev = _find_rightmost_node(node->left);

        _alloc.destroy(node->value);
        _alloc.construct(node->value, *prev->value);

        return (_bst_erase(prev));
    }

    /**
     * Clear binary search tree
     * @param node Root
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_bst_clear(RBTreeNode<value_type> *node) {
        if (!node)
            return;
        _bst_clear(node->left);
        _bst_clear(node->right);
        _clear_node(node);
    }

    /**
     * Clone binary tree
     * @param node   Root of old tree
     * @param parent Pointer to the parent
     * @return Root of new tree
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *RBTree<T, Compare, Alloc, NodeAlloc>::_bst_clone(RBTreeNode <value_type> *node, RBTreeNode <value_type> *parent) {
        if (!node)
            return (NULL);

        RBTreeNode<value_type> *new_node = _create_node(*node->value);
        new_node->parent = parent;
        new_node->color = node->color;

        new_node->left = _bst_clone(node->left, new_node);
        new_node->right = _bst_clone(node->right, new_node);

        return (new_node);
    }

    /**
     * Find node in binary search tree
     * @param val  Value to be searched for
     * @param node Root
     * @return A pointer to the node, if a node with specified value is found, pointer to end otherwise
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *
    RBTree<T, Compare, Alloc, NodeAlloc>::_bst_find(const value_type &val, RBTreeNode<value_type> *node) const {
        if (!node)
            return (_end);
        if (_comp(*node->value, val))
            return (_bst_find(val, node->right));
        else if (_comp(val, *node->value))
            return (_bst_find(val, node->left));
        else
            return (node);
    }

    /**
     * Return pointer to lower bound node
     * @param val  Value to search for
     * @param node Root
     * @return
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *
    RBTree<T, Compare, Alloc, NodeAlloc>::_bst_lower_bound(const value_type &val, RBTreeNode<value_type> *node) const {
        if (!node)
            return (_end);
        if (_comp(*node->value, val))
            return (_bst_lower_bound(val, node->right));
        else {
            RBTreeNode<value_type> *left = _bst_lower_bound(val, node->left);
            return (left != _end ? left : node);
        }
    }

    /**
     * Return pointer to upper bound node
     * @param val  Value to search for
     * @param node Root
     * @return
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTreeNode<typename RBTree<T, Compare, Alloc, NodeAlloc>::value_type> *
    RBTree<T, Compare, Alloc, NodeAlloc>::_bst_upper_bound(const value_type &val, RBTreeNode<value_type> *node) const {
        if (!node)
            return (_end);
        if (!_comp(val, *node->value))
            return (_bst_upper_bound(val, node->right));
        else {
            RBTreeNode<value_type> *left = _bst_upper_bound(val, node->left);
            return (left != _end ? left : node);
        }
    }

    /**
     * Rotate subtree left
     * @param node Root
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_rotateLeft(RBTreeNode<value_type> *node) {
        RBTreeNode<value_type> *right = node->right;
        node->right = right->left;

        if (node->right)
            node->right->parent = node;

        right->parent = node->parent;

        if (!node->parent)
            _root = right;
        else if (node == node->parent->left)
            node->parent->left = right;
        else
            node->parent->right = right;

        right->left = node;
        node->parent = right;
    }

    /**
     * Rotate subtree right
     * @param node Root
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_rotateRight(RBTreeNode<value_type> *node) {
        RBTreeNode<value_type> *left = node->left;
        node->left = left->right;

        if (node->left)
            node->left->parent = node;

        left->parent = node->parent;

        if (!node->parent)
            _root = left;
        else if (node == node->parent->left)
            node->parent->left = left;
        else
            node->parent->right = left;

        left->right = node;
        node->parent = left;
    }

    /**
     * Balance red-black tree
     * @param node
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_balance(RBTreeNode<value_type> *node) {
        RBTreeNode<value_type> *parent;
        RBTreeNode<value_type> *grandparent;
        RBTreeNode<value_type> *uncle;

        while (node != _root && node->color && node->parent->color) {
            parent = node->parent;
            grandparent = node->parent->parent;

            if (parent == grandparent->left) {
                uncle = grandparent->right;

                if (uncle && uncle->color) {
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        _rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    _rotateRight(grandparent);
                    ft::swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                uncle = grandparent->left;

                if (uncle && uncle->color) {
                    grandparent->color = true;
                    parent->color = false;
                    uncle->color = false;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        _rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    _rotateLeft(grandparent);
                    ft::swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        _root->color = false;
    }

    /**
     * Default constructor
     * @param comp       Binary predicate that, taking two element keys as argument, returns true if the first argument
     *                   goes before the second argument in the strict weak ordering it defines, and false otherwise
     * @param alloc      Allocator object
     * @param node_alloc Allocator object for nodes
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTree<T, Compare, Alloc, NodeAlloc>::RBTree(const value_compare &comp, const allocator_type &alloc, const node_allocator_type &node_alloc):
    _alloc(alloc), _node_alloc(node_alloc), _comp(comp), _root(NULL), _size(0) {
        _end = _node_alloc.allocate(1);
        _node_alloc.construct(_end, RBTreeNode<value_type>(NULL));
    }

    /**
     * Copy constructor
     * @param src Another RBTree object of the same type
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTree<T, Compare, Alloc, NodeAlloc>::RBTree(const RBTree &src):
    _alloc(src._alloc), _node_alloc(src._node_alloc), _comp(src._comp), _root(NULL), _size(src._size) {
        _root = _bst_clone(src._root, NULL);
        _end = _node_alloc.allocate(1);
        _node_alloc.construct(_end, RBTreeNode<value_type>(NULL));
        if (_root) {
            _root->parent = _end;
            _end->left = _root;
        }
    }

    /**
     * Destructor
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTree<T, Compare, Alloc, NodeAlloc>::~RBTree() {
        clear();
        _clear_node(_end);
    }

    /**
     * Copy container content
     * @param other A map object of the same type
     * @return *this
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    RBTree<T, Compare, Alloc, NodeAlloc> &RBTree<T, Compare, Alloc, NodeAlloc>::operator=(const RBTree &other) {
        if (this == &other)
            return (*this);

        clear();

        _alloc = other._alloc;
        _node_alloc = other._node_alloc;
        _comp = other._comp;
        _root = _bst_clone(other._root, NULL);
        _size = other._size;

        return (*this);
    }

    /**
     * Return iterator to beginning
     * @return An iterator to the first element in the container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator RBTree<T, Compare, Alloc, NodeAlloc>::begin() {
        RBTreeNode<T> *node = _root;

        if (!node)
            return (end());

        return (iterator(_find_leftmost_node(node)));
    }

    /**
     * Return const iterator to beginning
     * @return A const iterator to the first element in the container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator RBTree<T, Compare, Alloc, NodeAlloc>::begin() const {
        RBTreeNode<T> *node = _root;

        if (!node)
            return (end());

        return (const_iterator(_find_leftmost_node(node)));
    }

    /**
     * Return iterator to end
     * @return An iterator to the past-the-end element in the container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator RBTree<T, Compare, Alloc, NodeAlloc>::end() {
        return (iterator(_end));
    }

    /**
     * Return const iterator to end
     * @return A const iterator to the past-the-end element in the container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator RBTree<T, Compare, Alloc, NodeAlloc>::end() const {
        return (const_iterator(_end));
    }

    /**
     * Return reverse iterator to reverse beginning
     * @return A reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::reverse_iterator RBTree<T, Compare, Alloc, NodeAlloc>::rbegin() {
        return (reverse_iterator(end()));
    }

    /**
     * Return const reverse iterator to reverse beginning
     * @return A const reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_reverse_iterator RBTree<T, Compare, Alloc, NodeAlloc>::rbegin() const {
        return (const_reverse_iterator(end()));
    }

    /**
     * Return reverse iterator to reverse end
     * @return A reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::reverse_iterator RBTree<T, Compare, Alloc, NodeAlloc>::rend() {
        return (reverse_iterator(begin()));
    }

    /**
     * Return const reverse iterator to reverse end
     * @return A const reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_reverse_iterator RBTree<T, Compare, Alloc, NodeAlloc>::rend() const {
        return (const_reverse_iterator(begin()));
    }

    /**
     * Test whether container is empty
     * @return true if the container size is 0, false otherwise
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    bool RBTree<T, Compare, Alloc, NodeAlloc>::empty() const {
        return (!_root);
    }

    /**
     * Return container size
     * @return The number of elements in the container
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::size_type RBTree<T, Compare, Alloc, NodeAlloc>::size() const {
        return (_size);
    }

    /**
     * Return maximum size
     * @return The maximum number of elements a map container can hold as content
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::size_type RBTree<T, Compare, Alloc, NodeAlloc>::max_size() const {
        size_type a = _alloc.max_size();
        size_type b = _node_alloc.max_size();
        return (a < b ? a : b);
    }

    /**
     * Insert element
     * @param val Value to be copied to the inserted element
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    pair<typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator, bool> RBTree<T, Compare, Alloc, NodeAlloc>::insert(const value_type &val) {
        RBTreeNode<value_type> *node = _create_node(val);

        if (_root)
            _root->parent = NULL;

        ft::pair<RBTreeNode<value_type>*, bool> res = _bst_insert(node);

        if (!res.second) {
            _clear_node(node);
            _root->parent = _end;
            _end->left = _root;
            return (ft::make_pair(iterator(res.first), false));
        }

        _balance(node);

        _root->parent = _end;
        _end->left = _root;
        _size++;

        return (ft::make_pair(iterator(res.first), true));
    }

    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::RBTree::iterator RBTree<T, Compare, Alloc, NodeAlloc>::insert(RBTree::iterator position, const value_type &val) {
        (void)position;
        return (insert(val).first);
    }

    /**
     * Insert elements
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    template<typename InputIterator>
    void RBTree<T, Compare, Alloc, NodeAlloc>::insert(InputIterator first, InputIterator last,
                                                      typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*) {
        while (first != last) {
            insert(*first);
            first++;
        }
    }

    /**
     * Erase element
     * @param position Iterator pointing to a single element to be removed from the tree
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::erase(RBTree::iterator position) {
        RBTreeNode<value_type> *parent = _bst_erase(position.baseNode());
        if (parent != _end)
            _balance(parent);
        if (_size == 1) {
            _root = NULL;
        } else{
            _root->parent = _end;
            _end->left = _root;
        }
        _size--;
    }

    /**
     * Erase element
     * @param val Value of the element to be removed from the tree
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::size_type RBTree<T, Compare, Alloc, NodeAlloc>::erase(const value_type &val) {
        iterator it = find(val);
        if (it == end())
            return (0);

        erase(it);
        return (1);
    }

    /**
     * Erase elements
     * @param first Iterator to the initial position in a range
     * @param last  Iterator to the final position in a range
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::erase(RBTree::iterator first, RBTree::iterator last) {
        iterator next;
        while (first != last) {
            next = first;
            next++;
            erase(first);
            first = next;
        }
    }

    /**
     * Swap content
     * @param x Another RBTree container of the same type as this
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::swap(RBTree &x) {
        allocator_type         _alloc_tmp = this->_alloc;
        node_allocator_type    _node_alloc_tmp = this->_node_alloc;
        value_compare          _comp_tmp = this->_comp;
        RBTreeNode<value_type> *_root_tmp = this->_root;
        RBTreeNode<value_type> *_end_tmp = this->_end;
        size_type              _size_tmp = this->_size;

        this->_alloc = x._alloc;
        this->_node_alloc = x._node_alloc;
        this->_comp = x._comp;
        this->_root = x._root;
        this->_end = x._end;
        this->_size = x._size;

        x._alloc = _alloc_tmp;
        x._node_alloc = _node_alloc_tmp;
        x._comp = _comp_tmp;
        x._root = _root_tmp;
        x._end = _end_tmp;
        x._size = _size_tmp;
    }

    /**
     * Clear content
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::clear() {
        _bst_clear(_root);
        _root = NULL;
        _size = 0;
    }

    /**
     * Return value comparison object
     * @return The comparison object for element values
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::value_compare RBTree<T, Compare, Alloc, NodeAlloc>::value_comp() const {
        return (_comp);
    }

    /**
     * Get iterator to element
     * @param val Value to be searched for
     * @return An iterator to the element, if an element with specified key is found, or RBTree::end otherwise
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator RBTree<T, Compare, Alloc, NodeAlloc>::find(const value_type &val) {
        return (iterator(_bst_find(val, _root)));
    }

    /**
     * Get const iterator to element
     * @param val Value to be searched for
     * @return A const iterator to the element, if an element with specified key is found, or RBTree::end otherwise
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator RBTree<T, Compare, Alloc, NodeAlloc>::find(const value_type &val) const {
        return (const_iterator(_bst_find(val, _root)));
    }

    /**
     * Count elements with a specific value
     * @param val Value to search for
     * @return 1 if the container contains an element whose value is equivalent to val, or zero otherwise
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::size_type RBTree<T, Compare, Alloc, NodeAlloc>::count(const value_type &val) const {
        iterator it = find(val);
        return (it == end() ? 0 : 1);
    }

    /**
     * Return iterator to lower bound
     * @param val Value to search for
     * @return An iterator to the the first element in the container whose value is not considered to go before val,
     *         or RBTree::end if all values are considered to go before val
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator RBTree<T, Compare, Alloc, NodeAlloc>::lower_bound(const value_type &val) {
        return (iterator(_bst_lower_bound(val, _root)));
    }

    /**
     * Return const iterator to lower bound
     * @param val Value to search for
     * @return A const iterator to the the first element in the container whose value is not considered to go before val,
     *         or RBTree::end if all values are considered to go before val
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator RBTree<T, Compare, Alloc, NodeAlloc>::lower_bound(const value_type &val) const {
        return (const_iterator(_bst_lower_bound(val, _root)));
    }

    /**
     * Return iterator to upper bound
     * @param val Value to search for
     * @return An iterator to the the first element in the container whose value is considered to go after val,
     *         or RBTree::end if no values are considered to go after val
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator RBTree<T, Compare, Alloc, NodeAlloc>::upper_bound(const value_type &val) {
        return (iterator(_bst_upper_bound(val, _root)));
    }

    /**
     * Return const iterator to upper bound
     * @param val Value to search for
     * @return A const iterator to the the first element in the container whose value is considered to go after val,
     *         or RBTree::end if no values are considered to go after val
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator RBTree<T, Compare, Alloc, NodeAlloc>::upper_bound(const value_type &val) const {
        return (const_iterator(_bst_upper_bound(val, _root)));
    }

    /**
     * Get range of equal elements
     * @param val Value to search for
     * @return pair, whose member pair::first is the lower bound of the range, and pair::second is the upper bound
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    pair<typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator, typename RBTree<T, Compare, Alloc, NodeAlloc>::iterator>
    RBTree<T, Compare, Alloc, NodeAlloc>::equal_range(const value_type &val) {
        return (ft::make_pair(lower_bound(val), upper_bound(val)));
    }

    /**
     * Get const range of equal elements
     * @param val Value to search for
     * @return pair, whose member pair::first is the lower bound of the range, and pair::second is the upper bound
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    pair<typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator, typename RBTree<T, Compare, Alloc, NodeAlloc>::const_iterator>
    RBTree<T, Compare, Alloc, NodeAlloc>::equal_range(const value_type &val) const {
        return (ft::make_pair(lower_bound(val), upper_bound(val)));
    }

    /**
     * Get allocator
     * @return The allocator
     */
    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    typename RBTree<T, Compare, Alloc, NodeAlloc>::allocator_type RBTree<T, Compare, Alloc, NodeAlloc>::get_allocator() const {
        return (_alloc);
    }

    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::_print(RBTreeNode<value_type> *root, int space) const {
        if (!root)
            return;

        space += 10;

        _print(root->right, space);

        for (int i = 10; i < space; i++)
            std::cout << " ";
        std::cout << *root->value << "(" << (root->color ? "R" : "B") << ")" << std::endl;

        _print(root->left, space);
    }

    template<typename T, typename Compare, typename Alloc, typename NodeAlloc>
    void RBTree<T, Compare, Alloc, NodeAlloc>::print() const {
        std::cout << "---------------" << std::endl;
        _print(_root, 0);
        std::cout << "---------------" << std::endl;
    }

}

#endif //FT_CONTAINERS_RB_TREE_HPP
