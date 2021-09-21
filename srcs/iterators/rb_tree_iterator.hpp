#ifndef FT_CONTAINERS_RB_TREE_ITERATOR_HPP
# define FT_CONTAINERS_RB_TREE_ITERATOR_HPP

# include "iterator.hpp"
# include "../rb_tree.hpp"

namespace ft {

    /**
     * Red-black tree iterator
     * @tparam T         Tree elements type
     * @tparam Pointer   Pointer type
     * @tparam Reference Reference type
     */
    template<typename T, typename Pointer, typename Reference>
    class rb_tree_iterator {
        RBTreeNode<T> *_node;

    public:
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef Pointer                    pointer;
        typedef Reference                  reference;
        typedef bidirectional_iterator_tag iterator_category;

        rb_tree_iterator();
        explicit rb_tree_iterator(RBTreeNode<T> *node);
        template<typename SPointer, typename SReference>
        rb_tree_iterator(const rb_tree_iterator<T, SPointer, SReference> &src);

        ~rb_tree_iterator();

        template<typename SPointer, typename SReference>
        rb_tree_iterator       &operator=(const rb_tree_iterator<T, SPointer, SReference> &other);

        RBTreeNode<T>          *baseNode() const;

        reference              operator*() const;
        pointer                operator->() const;

        rb_tree_iterator       &operator++();
        const rb_tree_iterator operator++(int);

        rb_tree_iterator       &operator--();
        const rb_tree_iterator operator--(int);
    };

    template<typename T, typename Pointer, typename Reference>
    rb_tree_iterator<T, Pointer, Reference>::rb_tree_iterator(): _node(NULL) {}

    /**
     * Constructor from node pointer
     * @param node Pointer to node
     */
    template<typename T, typename Pointer, typename Reference>
    rb_tree_iterator<T, Pointer, Reference>::rb_tree_iterator(RBTreeNode<T> *node): _node(node) {}

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    rb_tree_iterator<T, Pointer, Reference>::rb_tree_iterator(const rb_tree_iterator<T, SPointer, SReference> &src): _node(src.baseNode()) {}

    template<typename T, typename Pointer, typename Reference>
    rb_tree_iterator<T, Pointer, Reference>::~rb_tree_iterator() {}

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    rb_tree_iterator<T, Pointer, Reference> &
    rb_tree_iterator<T, Pointer, Reference>::operator=(const rb_tree_iterator<T, SPointer, SReference> &other) {
        _node = other.baseNode();
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    RBTreeNode <T> *rb_tree_iterator<T, Pointer, Reference>::baseNode() const {
        return (_node);
    }

    template<typename T, typename Pointer, typename Reference>
    typename rb_tree_iterator<T, Pointer, Reference>::reference rb_tree_iterator<T, Pointer, Reference>::operator*() const {
        return (*_node->value);
    }

    template<typename T, typename Pointer, typename Reference>
    typename rb_tree_iterator<T, Pointer, Reference>::pointer rb_tree_iterator<T, Pointer, Reference>::operator->() const {
        return (_node->value);
    }

    template<typename T, typename Pointer, typename Reference>
    rb_tree_iterator<T, Pointer, Reference> &rb_tree_iterator<T, Pointer, Reference>::operator++() {
        RBTreeNode<T> *p;

        if (_node->right) {
            _node = _node->right;
            while (_node->left)
                _node = _node->left;
        } else {
            p = _node->parent;
            while (p && _node == p->right) {
                _node = p;
                p = p->parent;
            }
            _node = _node->parent;
        }

        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const rb_tree_iterator<T, Pointer, Reference> rb_tree_iterator<T, Pointer, Reference>::operator++(int) {
        rb_tree_iterator it(*this);
        ++(*this);
        return (it);
    }

    template<typename T, typename Pointer, typename Reference>
    rb_tree_iterator<T, Pointer, Reference> &rb_tree_iterator<T, Pointer, Reference>::operator--() {
        RBTreeNode<T> *p;

        if (_node->left) {
            _node = _node->left;
            while (_node->right)
                _node = _node->right;
        } else {
            p = _node->parent;
            while (p && _node == p->left) {
                _node = p;
                p = p->parent;
            }
            _node = _node->parent;
        }

        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const rb_tree_iterator<T, Pointer, Reference> rb_tree_iterator<T, Pointer, Reference>::operator--(int) {
        rb_tree_iterator it(*this);
        --(*this);
        return (it);
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator==(const rb_tree_iterator<T, LPointer, LReference> &lhs, const rb_tree_iterator<T, RPointer, RReference> &rhs) {
        return (lhs.baseNode() == rhs.baseNode());
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator!=(const rb_tree_iterator<T, LPointer, LReference> &lhs, const rb_tree_iterator<T, RPointer, RReference> &rhs) {
        return (!(lhs == rhs));
    }

}

#endif //FT_CONTAINERS_RB_TREE_ITERATOR_HPP
