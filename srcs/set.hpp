#ifndef FT_CONTAINERS_SET_HPP
# define FT_CONTAINERS_SET_HPP

# include <memory>
# include "rb_tree.hpp"
# include "iterator.hpp"

namespace ft {

    /**
     * Set container
     * @tparam T       Type of the elements
     * @tparam Compare A binary predicate that takes two arguments of the same type as the elements and returns a bool
     * @tparam Alloc   Type of the allocator object used to define the storage allocation model
     */
    template< typename T, typename Compare = less<T>, typename Alloc = std::allocator<T> >
    class set {
    public:
        typedef T                                                   key_type;
        typedef T                                                   value_type;
        typedef Compare                                             key_compare;
        typedef Compare                                             value_compare;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef typename RBTree<T>::iterator                        iterator;
        typedef typename RBTree<T>::const_iterator                  const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t                                              size_type;

    private:
        RBTree<value_type, value_compare, allocator_type> _tree;

    public:
        explicit set(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
        template<typename InputIterator>
        set(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);
        set(const set &src);

        ~set();

        set                      &operator=(const set &other);

        iterator                 begin();
        const_iterator           begin() const;

        iterator                 end();
        const_iterator           end() const;

        reverse_iterator         rbegin();
        const_reverse_iterator   rbegin() const;

        reverse_iterator         rend();
        const_reverse_iterator   rend() const;

        bool                     empty() const;
        size_type                size() const;
        size_type                max_size() const;

        pair<iterator, bool>     insert(const value_type &val);
        iterator                 insert(iterator position, const value_type &val);
        template<typename InputIterator>
        void                     insert(InputIterator first, InputIterator last,
                                        typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);

        void                     erase(iterator position);
        size_type                erase(const value_type &val);
        void                     erase(iterator first, iterator last);

        void                     swap(set &x);
        void                     clear();

        key_compare              key_comp() const;
        value_compare            value_comp() const;

        iterator                 find(const value_type &val) const;
        size_type                count(const value_type &val) const;

        iterator                 lower_bound(const value_type &val) const;
        iterator                 upper_bound(const value_type &val) const;
        pair<iterator, iterator> equal_range(const value_type &val) const;

        allocator_type           get_allocator() const;
    };

    /**
     * Empty container constructor (default constructor)
     * @param comp  Binary predicate that, taking two values of the same type of those contained in the set,
     *              returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise
     * @param alloc Allocator object
     */
    template<typename T, typename Compare, typename Alloc>
    set<T, Compare, Alloc>::set(const key_compare &comp, const allocator_type &alloc):
    _tree(RBTree<value_type, value_compare, allocator_type>(comp, alloc)) {}

    /**
     * Range constructor
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     * @param comp  Binary predicate that, taking two values of the same type of those contained in the set,
     *              returns true if the first argument goes before the second argument in the strict weak ordering it defines, and false otherwise
     * @param alloc Allocator object
     */
    template<typename T, typename Compare, typename Alloc>
    template<typename InputIterator>
    set<T, Compare, Alloc>::set(InputIterator first, InputIterator last,
                                const key_compare &comp, const allocator_type &alloc,
                                typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*):
                                _tree(RBTree<value_type, value_compare, allocator_type>(comp, alloc)) {
        _tree.insert(first, last);
    }

    /**
     * Copy constructor
     * @param src Another set object of the same type
     */
    template<typename T, typename Compare, typename Alloc>
    set<T, Compare, Alloc>::set(const set &src): _tree(src._tree) {}

    /**
     * Destructor
     */
    template<typename T, typename Compare, typename Alloc>
    set<T, Compare, Alloc>::~set() {}

    /**
     * Copy container content
     */
    template<typename T, typename Compare, typename Alloc>
    set<T, Compare, Alloc> &set<T, Compare, Alloc>::operator=(const set &other) {
        if (this == &other)
            return (*this);
        _tree = other._tree;
        return (*this);
    }

    /**
     * Return iterator to beginning
     * @return An iterator to the first element in the container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::begin() {
        return (_tree.begin());
    }

    /**
     * Return const iterator to beginning
     * @return A const iterator to the first element in the container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::const_iterator set<T, Compare, Alloc>::begin() const {
        return (_tree.begin());
    }

    /**
     * Return iterator to end
     * @return An iterator to the past-the-end element in the container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::end() {
        return (_tree.end());
    }

    /**
     * Return const iterator to end
     * @return A const iterator to the past-the-end element in the container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::const_iterator set<T, Compare, Alloc>::end() const {
        return (_tree.end());
    }

    /**
     * Return reverse iterator to reverse beginning
     * @return A reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::reverse_iterator set<T, Compare, Alloc>::rbegin() {
        return (_tree.rbegin());
    }

    /**
     * Return const reverse iterator to reverse beginning
     * @return A const reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::const_reverse_iterator set<T, Compare, Alloc>::rbegin() const {
        return (_tree.rbegin());
    }

    /**
     * Return reverse iterator to reverse end
     * @return A reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::reverse_iterator set<T, Compare, Alloc>::rend() {
        return (_tree.rend());
    }

    /**
     * Return const reverse iterator to reverse end
     * @return A const reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::const_reverse_iterator set<T, Compare, Alloc>::rend() const {
        return (_tree.rend());
    }

    /**
     * Test whether container is empty
     * @return true if the container size is 0, false otherwise
     */
    template<typename T, typename Compare, typename Alloc>
    bool set<T, Compare, Alloc>::empty() const {
        return (_tree.empty());
    }

    /**
     * Return container size
     * @return The number of elements in the container
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::size_type set<T, Compare, Alloc>::size() const {
        return (_tree.size());
    }

    /**
     * Return maximum size
     * @return The maximum number of elements a set container can hold as content
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::size_type set<T, Compare, Alloc>::max_size() const {
        return (_tree.max_size());
    }

    /**
     * Insert elements
     * @param val Value to be copied to the inserted element
     * @return A pair, with its member pair::first set to an iterator pointing to either the newly inserted element or
     *         to the element with an equivalent value in the set. The pair::second element in the pair is set to true
     *         if a new element was inserted or false if an equivalent key already existed
     */
    template<typename T, typename Compare, typename Alloc>
    pair<typename set<T, Compare, Alloc>::iterator, bool> set<T, Compare, Alloc>::insert(const value_type &val) {
        return (_tree.insert(val));
    }

    /**
     * Insert elements
     * @param position Hint for the position where the element can be inserted
     * @param val      Value to be copied to the inserted element
     * @return Iterator pointing to either the newly inserted element or to the element that already had an equivalent value in the set
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::insert(set::iterator position, const value_type &val) {
        return (_tree.insert(position, val));
    }

    /**
     * Insert elements
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     */
    template<typename T, typename Compare, typename Alloc>
    template<typename InputIterator>
    void set<T, Compare, Alloc>::insert(InputIterator first, InputIterator last,
                                        typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*) {
        _tree.insert(first, last);
    }

    /**
     * Erase elements
     * @param position Iterator pointing to a single element to be removed from the set
     */
    template<typename T, typename Compare, typename Alloc>
    void set<T, Compare, Alloc>::erase(iterator position) {
        _tree.erase(position);
    }

    /**
     * Erase elements
     * @param val Value of the element to be removed from the set
     * @return Number of elements erased
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::size_type set<T, Compare, Alloc>::erase(const value_type &val) {
        return (_tree.erase(val));
    }

    /**
     * Erase elements
     * @param first Iterator to the initial position in a range
     * @param last  Iterator to the final position in a range
     */
    template<typename T, typename Compare, typename Alloc>
    void set<T, Compare, Alloc>::erase(set::iterator first, set::iterator last) {
        _tree.erase(first, last);
    }

    /**
    * Swap content
    * @param x Another set container of the same type as this
    */
    template<typename T, typename Compare, typename Alloc>
    void set<T, Compare, Alloc>::swap(set &x) {
        _tree.swap(x._tree);
    }

    /**
    * Clear content
    */
    template<typename T, typename Compare, typename Alloc>
    void set<T, Compare, Alloc>::clear() {
        _tree.clear();
    }

    /**
     * Return key comparison object
     * @return The comparison object
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::key_compare set<T, Compare, Alloc>::key_comp() const {
        return (_tree.value_comp());
    }

    /**
     * Return value comparison object
     * @return The comparison object for element values
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::value_compare set<T, Compare, Alloc>::value_comp() const {
        return (_tree.value_comp());
    }

    /**
     * Get iterator to element
     * @param val Value to be searched for
     * @return An iterator to the element, if an element with specified value is found, or set::end otherwise
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::find(const value_type &val) const {
        return (_tree.find(val));
    }

    /**
    * Count elements with a specific value
    * @param val Value to search for
    * @return 1 if the container contains an element whose value is equivalent to val, or zero otherwise
    */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::size_type set<T, Compare, Alloc>::count(const value_type &val) const {
        return (_tree.count(val));
    }

    /**
     * Return iterator to lower bound
     * @param val Value to compare
     * @return An iterator to the the first element in the container which is not considered to go before val,
     *         or set::end if all elements are considered to go before val
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::lower_bound(const value_type &val) const {
        return (_tree.lower_bound(val));
    }

    /**
     * Return iterator to upper bound
     * @param val Value to compare
     * @return An iterator to the the first element in the container which is considered to go after val,
     *         or set::end if no elements are considered to go after val
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::iterator set<T, Compare, Alloc>::upper_bound(const value_type &val) const {
        return (_tree.lower_bound(val));
    }

    /**
     * Get range of equal elements
     * @param val Value to search for
     * @return pair, whose member pair::first is the lower bound of the range (the same as lower_bound),
     *         and pair::second is the upper bound (the same as upper_bound)
     */
    template<typename T, typename Compare, typename Alloc>
    pair <typename set<T, Compare, Alloc>::iterator, typename set<T, Compare, Alloc>::iterator>
    set<T, Compare, Alloc>::equal_range(const value_type &val) const {
        return (_tree.equal_range(val));
    }

    /**
     * Get allocator
     * @return The allocator
     */
    template<typename T, typename Compare, typename Alloc>
    typename set<T, Compare, Alloc>::allocator_type set<T, Compare, Alloc>::get_allocator() const {
        return (_tree.get_allocator());
    }


}

#endif //FT_CONTAINERS_SET_HPP
