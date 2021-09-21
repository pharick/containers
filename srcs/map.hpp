#ifndef FT_CONTAINERS_MAP_HPP
# define FT_CONTAINERS_MAP_HPP

# include <memory>
# include "utility.hpp"
# include "functional.hpp"
# include "rb_tree.hpp"
# include "iterator.hpp"

namespace ft {

    /**
     * Associative container that store elements formed by a combination of a key value and a mapped value, following a specific order
     * @tparam Key     Type of the keys
     * @tparam T       Type of the mapped value
     * @tparam Compare A binary predicate that takes two element keys as arguments and returns a bool
     * @tparam Alloc   Type of the allocator object used to define the storage allocation model
     */
    template< typename Key, typename T, typename Compare = less<Key>, typename Alloc = std::allocator< pair<const Key, T> > >
    class map {
    public:
        typedef Key                                                                                key_type;
        typedef T                                                                                  mapped_type;
        typedef pair<const key_type, mapped_type>                                                  value_type;
        typedef Compare                                                                            key_compare;
        typedef Alloc                                                                              allocator_type;
        typedef typename allocator_type::reference                                                 reference;
        typedef typename allocator_type::const_reference                                           const_reference;
        typedef typename allocator_type::pointer                                                   pointer;
        typedef typename allocator_type::const_pointer                                             const_pointer;

    private:
        /**
         * Value comparison object
         */
        class value_compare {
            friend class map;

        protected:
            key_compare _comp;
            explicit value_compare(Compare c);

        public:
            typedef bool       result_type;
            typedef value_type first_argument_type;
            typedef value_type second_argument_type;

            bool operator()(const value_type &x, const value_type &y) const;
        };

        RBTree<value_type, value_compare, allocator_type> _tree;

    public:
        typedef typename RBTree<value_type, value_compare, allocator_type>::iterator               iterator;
        typedef typename RBTree<value_type, value_compare, allocator_type>::const_iterator         const_iterator;
        typedef typename RBTree<value_type, value_compare, allocator_type>::reverse_iterator       reverse_iterator;
        typedef typename RBTree<value_type, value_compare, allocator_type>::const_reverse_iterator const_reverse_iterator;
        typedef typename RBTree<value_type, value_compare, allocator_type>::difference_type        difference_type;
        typedef typename RBTree<value_type, value_compare, allocator_type>::size_type              size_type;

        explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
        template<typename InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);
        map(const map &src);

        ~map();

        map                                  &operator=(const map &other);

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

        mapped_type                          &operator[](const key_type &k);

        pair<iterator, bool>                 insert(const value_type &val);
        iterator                             insert(iterator position, const value_type &val);
        template<typename InputIterator>
        void                                 insert(InputIterator first, InputIterator last,
                                    typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);

        void                                 erase(iterator position);
        size_type                            erase(const key_type &k);
        void                                 erase(iterator first, iterator last);

        void                                 swap(map &x);
        void                                 clear();

        key_compare                          key_comp() const;
        value_compare                        value_comp() const;

        iterator                             find(const key_type &k);
        const_iterator                       find(const key_type &k) const;

        size_type                            count(const key_type &k) const;

        iterator                             lower_bound(const key_type &k);
        const_iterator                       lower_bound(const key_type &k) const;

        iterator                             upper_bound(const key_type &k);
        const_iterator                       upper_bound(const key_type &k) const;

        pair<iterator, iterator>             equal_range(const key_type &k);
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;

        allocator_type                       get_allocator() const;
    };

    template<typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::value_compare::value_compare(Compare c): _comp(c) {}

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool map<Key, T, Compare, Alloc>::value_compare::operator()(const value_type &x, const value_type &y) const {
        return (_comp(x.first, y.first));
    }

    /**
     * Empty container constructor (default constructor)
     * @param comp  Binary predicate that, taking two element keys as argument, returns true if the first argument goes before
     *              the second argument in the strict weak ordering it defines, and false otherwise
     * @param alloc Allocator object
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::map(const key_compare &comp, const allocator_type &alloc):
                                        _tree(RBTree<value_type, value_compare, allocator_type>(value_compare(comp), allocator_type(alloc))) {}

    /**
     * Range constructor
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     * @param comp  Binary predicate that, taking two element keys as argument, returns true if the first argument goes before
     *              the second argument in the strict weak ordering it defines, and false otherwise
     * @param alloc Allocator object
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    template<typename InputIterator>
    map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last,
                                     const key_compare &comp, const allocator_type &alloc,
                                     typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*):
                                     _tree(RBTree<value_type, value_compare, allocator_type>(value_compare(comp), allocator_type(alloc))) {
        insert(first, last);
    }

    /**
     * Copy constructor
     * @param src Another map object of the same type
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::map(const map &src): _tree(src._tree) {}

    /**
     * Destructor
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc>::~map() {}

    /**
     * Copy container content
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    map<Key, T, Compare, Alloc> &map<Key, T, Compare, Alloc>::operator=(const map &other) {
        if (this == &other)
            return (*this);
        _tree = other._tree;
        return (*this);
    }

    /**
     * Return iterator to beginning
     * @return An iterator to the first element in the container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::begin() {
        return (_tree.begin());
    }

    /**
     * Return const iterator to beginning
     * @return A const iterator to the first element in the container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::begin() const {
        return (_tree.begin());
    }

    /**
     * Return iterator to end
     * @return An iterator to the past-the-end element in the container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::end() {
        return (_tree.end());
    }

    /**
     * Return const iterator to end
     * @return A const iterator to the past-the-end element in the container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::end() const {
        return (_tree.end());
    }

    /**
     * Return reverse iterator to reverse beginning
     * @return A reverse iterator to the reverse beginning of the sequence container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator map<Key, T, Compare, Alloc>::rbegin() {
        return (_tree.rbegin());
    }

    /**
     * Return const reverse iterator to reverse beginning
     * @return A const reverse iterator to the reverse beginning of the sequence container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator map<Key, T, Compare, Alloc>::rbegin() const {
        return (_tree.rbegin());
    }

    /**
     * Return reverse iterator to reverse end
     * @return A reverse iterator to the reverse end of the sequence container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::reverse_iterator map<Key, T, Compare, Alloc>::rend() {
        return (_tree.rend());
    }

    /**
     * Return const reverse iterator to reverse end
     * @return A const reverse iterator to the reverse end of the sequence container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_reverse_iterator map<Key, T, Compare, Alloc>::rend() const {
        return (_tree.rend());
    }

    /**
     * Test whether container is empty
     * @return true if the container size is 0, false otherwise
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    bool map<Key, T, Compare, Alloc>::empty() const {
        return (_tree.empty());
    }

    /**
     * Return container size
     * @return The number of elements in the container
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::size() const {
        return (_tree.size());
    }

    /**
     * Return maximum size
     * @return The maximum number of elements a map container can hold as content
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::max_size() const {
        return (_tree.max_size());
    }

    /**
     * Access element
     * @param k Key value of the element whose mapped value is accessed
     * @return A reference to the mapped value of the element with a key value equivalent to k
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::mapped_type &map<Key, T, Compare, Alloc>::operator[](const key_type &k) {
        ft::pair<iterator, bool> res = insert(ft::make_pair(k, mapped_type()));
        return ((*res.first).second);
    }

    /**
     * Insert elements
     * @param val Value to be copied to the inserted element
     * @return A pair, with its member pair::first set to an iterator pointing to either the newly inserted element or
     *         to the element with an equivalent key in the map. The pair::second element in the pair is set to true
     *         if a new element was inserted or false if an equivalent key already existed
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator, bool> map<Key, T, Compare, Alloc>::insert(const value_type &val) {
        return (_tree.insert(val));
    }

    /**
     * Insert elements
     * @param position Hint for the position where the element can be inserted
     * @param val      Value to be copied to the inserted element
     * @return Iterator pointing to either the newly inserted element or to the element that already had an equivalent key in the map
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::insert(map::iterator position, const map::value_type &val) {
        return (_tree.insert(position, val));
    }

    /**
     * Insert elements
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    template<typename InputIterator>
    void map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last,
                                             typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*) {
        _tree.insert(first, last);
    }

    /**
     * Erase elements
     * @param position Iterator pointing to a single element to be removed from the map
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    void map<Key, T, Compare, Alloc>::erase(iterator position) {
        _tree.erase(position);
    }

    /**
     * Erase elements
     * @param k Key of the element to be removed from the map
     * @return Number of elements erased
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::erase(const key_type &k) {
        return (_tree.erase(ft::make_pair(k, mapped_type())));
    }

    /**
     * Erase elements
     * @param first Iterator to the initial position in a range
     * @param last  Iterator to the final position in a range
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    void map<Key, T, Compare, Alloc>::erase(map::iterator first, map::iterator last) {
        _tree.erase(first, last);
    }

    /**
     * Swap content
     * @param x Another map container of the same type as this
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    void map<Key, T, Compare, Alloc>::swap(map &x) {
        _tree.swap(x._tree);
    }

    /**
     * Clear content
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    void map<Key, T, Compare, Alloc>::clear() {
        _tree.clear();
    }

    /**
     * Return key comparison object
     * @return The comparison object
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::key_compare map<Key, T, Compare, Alloc>::key_comp() const {
        return (_tree.value_comp()._comp);
    }

    /**
     * Return value comparison object
     * @return The comparison object for element values
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::value_compare map<Key, T, Compare, Alloc>::value_comp() const {
        return (_tree.value_comp());
    }

    /**
     * Get iterator to element
     * @param k Key to be searched for
     * @return An iterator to the element, if an element with specified key is found, or map::end otherwise
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::find(const key_type &k) {
        return (_tree.find(ft::make_pair(k, mapped_type())));
    }

    /**
     * Get const iterator to element
     * @param k Key to be searched for
     * @return A const iterator to the element, if an element with specified key is found, or map::end otherwise
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::find(const key_type &k) const {
        return (_tree.find(ft::make_pair(k, mapped_type())));
    }

    /**
     * Count elements with a specific key
     * @param k Key to search for
     * @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::size_type map<Key, T, Compare, Alloc>::count(const key_type &k) const {
        return (_tree.count(ft::make_pair(k, mapped_type())));
    }

    /**
     * Return iterator to lower bound
     * @param k Key to search for
     * @return An iterator to the the first element in the container whose key is not considered to go before k,
     *         or map::end if all keys are considered to go before k
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) {
        return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
    }

    /**
     * Return const iterator to lower bound
     * @param k Key to search for
     * @return A const iterator to the the first element in the container whose key is not considered to go before k,
     *         or map::end if all keys are considered to go before k
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::lower_bound(const key_type &k) const {
        return (_tree.lower_bound(ft::make_pair(k, mapped_type())));
    }

    /**
     * Return iterator to upper bound
     * @param k Key to search for
     * @return An iterator to the the first element in the container whose key is considered to go after k,
     *         or map::end if no keys are considered to go after k
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) {
        return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
    }

    /**
     * Return const iterator to upper bound
     * @param k Key to search for
     * @return An iterator to the the first element in the container whose key is considered to go after k,
     *         or map::end if no keys are considered to go after k
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::const_iterator map<Key, T, Compare, Alloc>::upper_bound(const key_type &k) const {
        return (_tree.upper_bound(ft::make_pair(k, mapped_type())));
    }

    /**
     * Get range of equal elements
     * @param k Key to search for
     * @return pair, whose member pair::first is the lower bound of the range, and pair::second is the upper bound
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    pair<typename map<Key, T, Compare, Alloc>::iterator, typename map<Key, T, Compare, Alloc>::iterator> map<Key, T, Compare, Alloc>::equal_range(const key_type &k) {
        return (_tree.equal_range(ft::make_pair(k, mapped_type())));
    }

    /**
     * Get const range of equal elements
     * @param k Key to search for
     * @return pair, whose member pair::first is the lower bound of the range, and pair::second is the upper bound
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    pair<typename map<Key, T, Compare, Alloc>::const_iterator, typename map<Key, T, Compare, Alloc>::const_iterator> map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const {
        return (_tree.equal_range(ft::make_pair(k, mapped_type())));
    }

    /**
     * Get allocator
     * @return The allocator
     */
    template<typename Key, typename T, typename Compare, typename Alloc>
    typename map<Key, T, Compare, Alloc>::allocator_type map<Key, T, Compare, Alloc>::get_allocator() const {
        return (_tree.get_allocator());
    }

}

#endif //FT_CONTAINERS_MAP_HPP
