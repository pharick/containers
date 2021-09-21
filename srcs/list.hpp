#ifndef FT_CONTAINERS_LIST_HPP
# define FT_CONTAINERS_LIST_HPP

namespace ft {
    template< typename T, typename Alloc = std::allocator<T> > class list;
    template<typename T> struct ListNode;
}

# include <memory>
# include "type_traits.hpp"
# include "iterators/list_iterator.hpp"

namespace ft {

    template<typename T>
    struct ListNode {
        T        *value;
        ListNode *next;
        ListNode *prev;
    };

    /**
     * Sequence containers that allow constant time insert and erase operations
     * anywhere within the sequence, and iteration in both directions
     * @tparam T     Type of the elements
     * @tparam Alloc Type of the allocator object used to define the storage allocation model
     */
    template< typename T, typename Alloc >
    class list {
    public:
        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef list_iterator<T, T*, T&>                            iterator;
        typedef list_iterator<T, const T*, const T&>                const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t                                              size_type;

    private:
        typedef std::allocator< ListNode<T> > node_allocator_type;

        allocator_type      _alloc;
        node_allocator_type _node_alloc;
        ListNode<T>         *_last;

        ListNode<T>   *_createNode(value_type value);
        ListNode<T>   *_createEndNode();
        void        _clearNode(ListNode<T> *node);
        void        _clear();
        list        *_split();

        static void _insertNodeBefore(ListNode<T> *node, ListNode<T> *newNode);
        static bool _isLess(T a, T b);

    public:
        explicit list(const allocator_type &alloc = allocator_type());
        explicit list(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type());
        template<typename InputIterator>
        list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
             typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL);
        list(const list &x);

        ~list();

        list &operator=(const list &other);

        iterator               begin();
        const_iterator         begin() const;

        iterator               end();
        const_iterator         end() const;

        reverse_iterator       rbegin();
        const_reverse_iterator rbegin() const;

        reverse_iterator       rend();
        const_reverse_iterator rend() const;

        bool                   empty() const;
        size_type              size() const;
        size_type              max_size() const;

        reference              front();
        const_reference        front() const;

        reference              back();
        const_reference        back() const;

        template<typename InputIterator>
        void                   assign(InputIterator first, InputIterator last,
                                      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL);
        void                   assign(size_type n, const value_type &val);

        void                   push_front(const value_type &val);
        void                   pop_front();

        void                   push_back(const value_type &val);
        void                   pop_back();

        iterator               insert(iterator position, const value_type &val);
        void                   insert(iterator position, size_type n, const value_type &val);
        template<typename InputIterator>
        void                   insert(iterator position, InputIterator first, InputIterator last,
                                      typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL);

        iterator               erase(iterator position);
        iterator               erase(iterator first, iterator last);

        void                   swap(list &src);
        void                   resize(size_type n, value_type val = value_type());
        void                   clear();

        void                   splice(iterator position, list &src);
        void                   splice(iterator position, list &src, iterator i);
        void                   splice(iterator position, list &src, iterator first, iterator last);

        void                   remove(const value_type &val);
        template<typename Predicate>
        void                   remove_if(Predicate pred);

        void                   unique();
        template<typename BinaryPredicate>
        void                   unique(BinaryPredicate binary_pred);

        void                   merge(list &src);
        template<typename Compare>
        void                   merge(list &src, Compare comp);

        void                   sort();
        template<typename Compare>
        void                   sort(Compare comp);

        void                   reverse();

        allocator_type         get_allocator() const;
    };

    /**
     * Creates and returns new list node
     * @param value RBTreeNode value
     * @param next  Next node pointer
     * @param prev  Previous node pointer
     * @return      Created node
     */
    template<typename T, typename Alloc>
    ListNode<T> *list<T, Alloc>::_createNode(value_type value) {
        ListNode<T> *node = _node_alloc.allocate(1);
        node->value = _alloc.allocate(1);
        _alloc.construct(node->value, value);
        node->next = NULL;
        node->prev = NULL;
        return (node);
    }

    /**
     * Creates and returns past the end node
     * @return Past-the-end node
     */
    template<typename T, typename Alloc>
    ListNode<T> *list<T, Alloc>::_createEndNode() {
        ListNode<T> *node = _node_alloc.allocate(1);
        node->value = _alloc.allocate(1);
        _alloc.construct(node->value, T());
        node->next = node;
        node->prev = node;
        return (node);
    }

    /**
     * Destroy and deallocate one node
     * @param node
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::_clearNode(ListNode<T> *node) {
        _alloc.destroy(node->value);
        _alloc.deallocate(node->value, 1);
        _node_alloc.destroy(node);
        _node_alloc.deallocate(node, 1);
    }

    /**
     * Clears list content
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::_clear() {
        ListNode<T> *node = _last->next;
        ListNode<T> *next;

        while (node != _last) {
            next = node->next;
            _clearNode(node);
            node = next;
        }

        _last->next = _last;
        _last->prev = _last;
    }

    /**
     * Splits list into two halves
     * @return Second half of the list
     */
    template<typename T, typename Alloc>
    list<T, Alloc> *list<T, Alloc>::_split() {
        iterator fast = begin();
        iterator slow = begin();

        iterator fast_next = fast;
        fast_next++;

        iterator fast_next2 = fast_next;
        fast_next2++;

        while (fast_next != end() && fast_next2 != end()) {
            fast++;
            fast++;

            fast_next = fast;
            fast_next++;

            fast_next2 = fast_next;
            fast_next2++;

            slow++;
        }

        slow++;
        list *second = new list();
        second->splice(second->end(), *this, slow, end());
        return (second);
    }

    /**
     * Inserts new node before given
     * @param node    Given node
     * @param newNode New node
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::_insertNodeBefore(ListNode<T> *node, ListNode<T> *newNode) {
        ListNode<T> *prev = node->prev;

        prev->next = newNode;
        newNode->prev = prev;
        newNode->next = node;
        node->prev = newNode;
    }

    template<typename T, typename Alloc>
    bool list<T, Alloc>::_isLess(T a, T b) {
        return (a < b);
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::list(const allocator_type &alloc): _alloc(alloc) {
        _last = _createEndNode();
    }

    /**
     * Fill constructor
     * @param n     Element count
     * @param val   Fill value
     * @param alloc Allocator
     */
    template<typename T, typename Alloc>
    list<T, Alloc>::list(list::size_type n, const value_type &val, const allocator_type &alloc): _alloc(alloc) {
            _last = _createEndNode();
            insert(end(), n, val);
    }

    /**
     * Range constructor
     * @param first First element in range
     * @param last  Past the end element in range
     * @param alloc Allocator
     */
    template<typename T, typename Alloc>
    template<class InputIterator>
    list<T, Alloc>::list(InputIterator first, InputIterator last, const allocator_type &alloc,
                         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *): _alloc(alloc) {
        _last = _createEndNode();
        insert(end(), first, last);
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::list(const list &x): _alloc(x._alloc) {
        _last = _createEndNode();
        insert(end(), x.begin(), x.end());
    }

    template<typename T, typename Alloc>
    list<T, Alloc>::~list() {
        _clear();
        _alloc.destroy(_last->value);
        _alloc.deallocate(_last->value, 1);
        _node_alloc.destroy(_last);
        _node_alloc.deallocate(_last, 1);
    }

    template<typename T, typename Alloc>
    list<T, Alloc> &list<T, Alloc>::operator=(const list &other) {
        if (this == &other)
            return (*this);

        _clear();
        insert(end(), other.begin(), other.end());

        return (*this);
    }

    /**
     * Return iterator to beginning
     * @return An iterator to the beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::begin() {
        return (iterator(_last->next));
    }

    /**
     * Return const iterator to beginning
     * @return A const iterator to the beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::begin() const {
        return (const_iterator(_last->next));
    }

    /**
     * Return iterator to end
     * @return An iterator to the element past the end of the sequence
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::end() {
        return (iterator(_last));
    }

    /**
     * Return const iterator to end
     * @return A const iterator to the element past the end of the sequence
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_iterator list<T, Alloc>::end() const {
        return (const_iterator(_last));
    }

    /**
     * Return reverse iterator to reverse beginning
     * @return Returns a reverse iterator pointing to the last element in the container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rbegin() {
        return (reverse_iterator(end()));
    }

    /**
     * Return const reverse iterator to reverse beginning
     * @return Returns a const reverse iterator pointing to the last element in the container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rbegin() const {
        return (const_reverse_iterator(end()));
    }

    /**
     * Return reverse iterator to reverse end
     * @return A reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::reverse_iterator list<T, Alloc>::rend() {
        return (reverse_iterator(begin()));
    }

    /**
     * Return const reverse iterator to reverse end
     * @return A const reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reverse_iterator list<T, Alloc>::rend() const {
        return (const_reverse_iterator(begin()));
    }

    /**
     * Test whether container is empty
     * @return true if the container size is 0, false otherwise
     */
    template<typename T, typename Alloc>
    bool list<T, Alloc>::empty() const {
        return (_last->next == _last);
    }

    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::size() const {
        size_t    size = 0;
        ListNode<T> *node = _last->next;

        while (node != _last) {
            size++;
            node = node->next;
        }

        return (size);
    }

    /**
     * Return maximum size
     * @return The maximum number of elements the object can hold as content
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::size_type list<T, Alloc>::max_size() const {
        size_type a = _alloc.max_size();
        size_type b = _node_alloc.max_size();
        return (a < b ? a : b);
    }

    /**
     * Access first element
     * @return A reference to the first element in the list container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::reference list<T, Alloc>::front() {
        return (*_last->next->value);
    }

    /**
     * Access first element
     * @return A const reference to the first element in the list container
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reference list<T, Alloc>::front() const {
        return (*_last->next->value);
    }

    /**
     * Access last element
     * @return A reference to the last element in the list
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::reference list<T, Alloc>::back() {
        return (*_last->prev->value);
    }

    /**
     * Access last element
     * @return A const reference to the last element in the list
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::const_reference list<T, Alloc>::back() const {
        return (*_last->prev->value);
    }

    /**
     * Assign new content to container
     * @param first Input iterator to the initial position in a sequence
     * @param last  Input iterator to the final position in a sequence
     */
    template<typename T, typename Alloc>
    template<typename InputIterator>
    void list<T, Alloc>::assign(InputIterator first, InputIterator last,
                                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type*) {
        _clear();
        insert(end(), first, last);
    }

    /**
     * Assign new content to container
     * @param n   New size for the container
     * @param val Value to fill the container with
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::assign(list::size_type n, const list::value_type &val) {
        _clear();
        insert(end(), n, val);
    }

    /**
     * Insert element at beginning
     * @param val Value to be copied to the inserted element
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::push_front(const value_type &val) {
        insert(begin(), val);
    }

    /**
     * Delete first element
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::pop_front() {
        erase(begin());
    }

    /**
     * Add element at the end
     * @param val Value to be copied to the new element
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::push_back(const value_type &val) {
        insert(end(), val);
    }

    /**
     * Delete last element
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::pop_back() {
        list::iterator it = end();
        it--;
        erase(it);
    }

    /**
     * Inserts new element before the element at the specified position
     * @param position Position in the container where the new element inserted
     * @param val      New element value
     * @return An iterator that points to the newly inserted element
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::insert(list::iterator position, const value_type &val) {
        ListNode<value_type> *newNode = _createNode(val);

        newNode->next = position._node;
        newNode->prev = position._node->prev;

        position._node->prev->next = newNode;
        position._node->prev = newNode;

        return (--position);
    }

    /**
     * Inserts n new elements before the element at the specified position
     * @param position Position in the container where the new elements are inserted
     * @param n        Number of elements to insert
     * @param val      New elements value
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::insert(list::iterator position, list::size_type n, const value_type &val) {
        for (size_type i = 0; i < n; i++) {
            insert(position, val);
        }
    }

    /**
     * Inserts new elements from range before the element at the specified position
     * @param position Position in the container where the new elements are inserted
     * @param first    Begin of the range
     * @param last     Past-the-end of the range
     */
    template<typename T, typename Alloc>
    template<class InputIterator>
    void list<T, Alloc>::insert(list::iterator position, InputIterator first, InputIterator last,
                                typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type *) {
        InputIterator it;
        for (it = first; it != last; it++) {
            insert(position, *it);
        }
    }

    /**
     * Erase elements
     * @param position Iterator pointing to a single element to be removed from the list
     * @return An iterator pointing to the element that followed the last element erased by the function call
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::erase(list::iterator position) {
        list::iterator next_it = position;
        next_it++;

        ListNode<T> *prev = position._node->prev;
        ListNode<T> *next = position._node->next;

        _clearNode(position._node);
        prev->next = next;
        next->prev = prev;

        return (next_it);
    }

    /**
     * Erase elements
     * @param first Iterator specifying first element of the range
     * @param last  Iterator specifying past the end element of the range
     * @return An iterator pointing to the element that followed the last element erased by the function call
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::iterator list<T, Alloc>::erase(list::iterator first, list::iterator last) {
        list::iterator it;
        for (it = first; it != last; it++) {
            erase(it);
        }

        return (last);
    }

    /**
     * Swap content
     * @param src Another list container of the same type as this
     *            whose content is swapped with that of this container
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::swap(list &src) {
        ListNode<T>           *tmp_last = _last;
        allocator_type      tmp_alloc = _alloc;
        node_allocator_type tmp_node_alloc = _node_alloc;

        _last = src._last;
        _alloc = src._alloc;
        _node_alloc = src._node_alloc;

        src._last = tmp_last;
        src._alloc = tmp_alloc;
        src._node_alloc = tmp_node_alloc;
    }

    /**
     * Change size
     * @param n   New container size, expressed in number of elements
     * @param val Object whose content is copied to the added elements
     *            in case that n is greater than the current container size
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::resize(list::size_type n, value_type val) {
        size_type s = size();
        if (n < s) {
            for (size_type i = 0; i < s - n; i++) {
                erase(--end());
            }
        } else if (n > s) {
            insert(end(), n - s, val);
        }
    }

    /**
     * Clear content
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::clear() {
        _clear();
    }

    /**
     * Transfer elements from list to list
     * @param position Position within the container where the elements of x are inserted
     * @param src      A list object of the same type
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::splice(list::iterator position, list &src) {
        splice(position, src, src.begin(), src.end());
    }

    /**
     * Transfer elements from list to list
     * @param position Position within the container where the elements of x are inserted
     * @param src      A list object of the same type
     * @param i        Iterator to an element in src. Only this single element is transferred
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::splice(list::iterator position, list &src, list::iterator i) {
        list::iterator next = i;
        next++;
        splice(position, src, i, next);
    }

    /**
     * Transfer elements from list to list
     * @param position Position within the container where the elements of x are inserted
     * @param src      A list object of the same type
     * @param first    Iterator specifying begin of range of elements in x
     * @param last     Iterator specifying end of range of elements in x
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::splice(list::iterator position, list &src, list::iterator first, list::iterator last) {
        (void)src;
        ListNode<T> *src_prev = first._node->prev;
        ListNode<T> *src_next = last._node;
        ListNode<T> *this_prev = position._node->prev;
        ListNode<T> *this_next = position._node;
        ListNode<T> *first_node = first._node;
        ListNode<T> *last_node = last._node->prev;

        src_prev->next = src_next;
        src_next->prev = src_prev;

        this_prev->next = first_node;
        first_node->prev = this_prev;
        this_next->prev = last_node;
        last_node->next = this_next;
    }

    /**
     * Remove elements with specific value
     * @param val Value of the elements to be removed
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::remove(const value_type &val) {
        for (iterator it = begin(); it != end(); it++) {
            if (*it == val) {
                erase(it);
            }
        }
    }

    /**
     * Remove elements fulfilling condition
     * @param pred Unary predicate that, taking a value of the same type
     *             as those contained in the forward_list object,
     *             returns true for those values to be removed from the container,
     *             and false for those remaining
     */
    template<typename T, typename Alloc>
    template<typename Predicate>
    void list<T, Alloc>::remove_if(Predicate pred) {
        for (iterator it = begin(); it != end(); it++) {
            if (pred(*it)) {
                erase(it);
            }
        }
    }

    /**
     * Removes all but the first element from every consecutive group
     * of equal elements in the container.
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::unique() {
        for (iterator it = ++begin(); it != end(); it++) {
            if (*it == *it._node->prev->value) {
                erase(it);
            }
        }
    }

    /**
     * Removes all but the first element from every consecutive group
     * of equal elements in the container.
     * @param binary_pred Binary predicate that, taking two values of the same type than those contained in the list,
     *                    returns true to remove the element passed as first argument from the container, and false otherwise
     */
    template<typename T, typename Alloc>
    template<typename BinaryPredicate>
    void list<T, Alloc>::unique(BinaryPredicate binary_pred) {
        for (iterator it = ++begin(); it != end(); it++) {
            if (binary_pred(*it, *it._node->prev->value)) {
                erase(it);
            }
        }
    }

    /**
     * Merge sorted lists
     * @param src A list object of the same type
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::merge(list &src) {
        merge(src, list::_isLess);
    }

    /**
     * Merge sorted lists
     * @param src  A list object of the same type
     * @param comp Binary predicate that, taking two values of the same type than those contained in the list,
     *             returns true if the first argument is considered to go before the second
     *             in the strict weak ordering it defines, and false otherwise
     */
    template<typename T, typename Alloc>
    template<typename Compare>
    void list<T, Alloc>::merge(list &src, Compare comp) {
        ListNode<T> *node1 = begin()._node;
        ListNode<T> *node2 = src.begin()._node;
        ListNode<T> *next1;
        ListNode<T> *next2;

        while (node2 != src.end()._node) {
            next1 = node1->next;
            next2 = node2->next;

            if (node1 == end()._node || comp(*node2->value, *node1->value)) {
                list::_insertNodeBefore(node1, node2);
                node2 = next2;
            } else {
                node1 = next1;
            }
        }

        src.end()._node->prev = src.end()._node;
        src.end()._node->next = src.end()._node;
    }

    /**
     * Sort elements in container
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::sort() {
        sort(_isLess);
    }

    /**
     * Sort elements in container
     * @param comp Binary predicate that, taking two values of the same type of those contained in the list,
     *             returns true if the first argument goes before the second argument in the strict weak ordering
     *             it defines, and false otherwise
     */
    template<typename T, typename Alloc>
    template<typename Compare>
    void list<T, Alloc>::sort(Compare comp) {
        if (begin() == end() || ++begin() == end())
            return;

        list *second = _split();

        sort(comp);
        second->sort(comp);

        merge(*second, comp);
        delete second;
    }

    /**
     * Reverse the order of elements
     */
    template<typename T, typename Alloc>
    void list<T, Alloc>::reverse() {
        ListNode<T> *node = begin()._node;
        ListNode<T> *next;
        ListNode<T> *tmp;

        while (node != end()._node) {
            next = node->next;

            tmp = node->next;
            node->next = node->prev;
            node->prev = tmp;

            node = next;
        }

        tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;
    }

    /**
     * Returns a copy of the allocator object associated with the list container
     * @return The allocator
     */
    template<typename T, typename Alloc>
    typename list<T, Alloc>::allocator_type list<T, Alloc>::get_allocator() const {
        return (_alloc);
    }

    template<typename T, typename Alloc>
    bool operator==(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        typename list<T, Alloc>::const_iterator it1 = lhs.begin();
        typename list<T, Alloc>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end() && *it1 == *it2) {
            it1++;
            it2++;
        }

        return (it1 == lhs.end() && it2 == rhs.end());
    }

    template<typename T, typename Alloc>
    bool operator!=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return (!(lhs == rhs));
    }

    template<typename T, typename Alloc>
    bool operator<(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        typename list<T, Alloc>::const_iterator it1 = lhs.begin();
        typename list<T, Alloc>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end() && *it1 == *it2) {
            it1++;
            it2++;
        }

        return ((it1 == lhs.end() && it2 != rhs.end()) ||
                (it1 != lhs.end() && it2 != rhs.end() && *it1 < *it2));
    }

    template<typename T, typename Alloc>
    bool operator<=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return (!(rhs < lhs));
    }

    template<typename T, typename Alloc>
    bool operator>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template<typename T, typename Alloc>
    bool operator>=(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs) {
        return (!(lhs < rhs));
    }

    template<typename T, typename Alloc>
    void swap(list<T, Alloc> &x, list<T, Alloc> &y) {
        x.swap(y);
    }
}

#endif //FT_CONTAINERS_LIST_HPP
