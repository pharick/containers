#ifndef FT_CONTAINERS_LIST_ITERATOR_HPP
# define FT_CONTAINERS_LIST_ITERATOR_HPP

# include "../iterator.hpp"
# include "../list.hpp"

namespace ft {

    /**
     * List iterator
     * @tparam T         List elements type
     * @tparam Pointer   Pointer type
     * @tparam Reference Reference type
     */
    template<typename T, typename Pointer, typename Reference>
    class list_iterator {
        friend class list<T>;

        ListNode <T> *_node;

    public:
        typedef T                          value_type;
        typedef ptrdiff_t                  difference_type;
        typedef Pointer                    pointer;
        typedef Reference                  reference;
        typedef bidirectional_iterator_tag iterator_category;

        list_iterator();
        explicit list_iterator(ListNode<T> *node);
        template<typename SPointer, typename SReference>
        list_iterator(const list_iterator<T, SPointer, SReference> &src);

        ~list_iterator();

        template<typename SPointer, typename SReference>
        list_iterator       &operator=(const list_iterator<T, SPointer, SReference> &other);

        ListNode<T>         *baseNode() const;

        reference           operator*() const;
        pointer             operator->() const;

        list_iterator       &operator++();
        const list_iterator operator++(int);

        list_iterator       &operator--();
        const list_iterator operator--(int);
    };

    template<typename T, typename Pointer, typename Reference>
    list_iterator<T, Pointer, Reference>::list_iterator(): _node(NULL) {}

    /**
     * Constructor from node pointer
     * @param node Pointer to node
     */
    template<typename T, typename Pointer, typename Reference>
    list_iterator<T, Pointer, Reference>::list_iterator(ListNode <T> *node): _node(node) {}

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    list_iterator<T, Pointer, Reference>::list_iterator(const list_iterator<T, SPointer, SReference> &src): _node(src.baseNode()) {}

    template<typename T, typename Pointer, typename Reference>
    list_iterator<T, Pointer, Reference>::~list_iterator() {}

    template<typename T, typename Pointer, typename Reference>
    template<typename SPointer, typename SReference>
    list_iterator<T, Pointer, Reference> &list_iterator<T, Pointer, Reference>::operator=(const list_iterator<T, SPointer, SReference> &other) {
        this->_node = other.baseNode();
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    ListNode<T> *list_iterator<T, Pointer, Reference>::baseNode() const {
        return (_node);
    }

    template<typename T, typename Pointer, typename Reference>
    typename list_iterator<T, Pointer, Reference>::reference list_iterator<T, Pointer, Reference>::operator*() const {
        return (*_node->value);
    }

    template<typename T, typename Pointer, typename Reference>
    typename list_iterator<T, Pointer, Reference>::pointer list_iterator<T, Pointer, Reference>::operator->() const {
        return (_node->value);
    }

    template<typename T, typename Pointer, typename Reference>
    list_iterator<T, Pointer, Reference> &list_iterator<T, Pointer, Reference>::operator++() {
        _node = _node->next;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const list_iterator<T, Pointer, Reference> list_iterator<T, Pointer, Reference>::operator++(int) {
        list_iterator<T, Pointer, Reference> it(*this);
        _node = _node->next;
        return (it);
    }

    template<typename T, typename Pointer, typename Reference>
    list_iterator<T, Pointer, Reference> &list_iterator<T, Pointer, Reference>::operator--() {
        _node = _node->prev;
        return (*this);
    }

    template<typename T, typename Pointer, typename Reference>
    const list_iterator<T, Pointer, Reference> list_iterator<T, Pointer, Reference>::operator--(int) {
        list_iterator<T, Pointer, Reference> it(*this);
        _node = _node->prev;
        return (it);
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator==(const list_iterator<T, LPointer, LReference> &lhs, const list_iterator<T, RPointer, RReference> &rhs) {
        return (lhs.baseNode() == rhs.baseNode());
    }

    template<typename T, typename LPointer, typename LReference, typename RPointer, typename RReference>
    bool operator!=(const list_iterator<T, LPointer, LReference> &lhs, const list_iterator<T, RPointer, RReference> &rhs) {
        return (!(lhs == rhs));
    }

}

#endif //FT_CONTAINERS_LIST_ITERATOR_HPP
