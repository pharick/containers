#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

namespace ft {
    template<typename T, typename Alloc> class vector;
};

# include <memory>
# include <stdexcept>
# include "algorithm.hpp"
# include "iterators/vector_iterator.hpp"

namespace ft {

    /**
     * Sequence containers representing arrays that can change in size
     * @tparam T     Type of the elements
     * @tparam Alloc Type of the allocator object used to define the storage allocation model
     */
    template< typename T, typename Alloc = std::allocator<T> >
    class vector {
    public:
        typedef T                                                   value_type;
        typedef Alloc                                               allocator_type;
        typedef typename allocator_type::reference                  reference;
        typedef typename allocator_type::const_reference            const_reference;
        typedef typename allocator_type::pointer                    pointer;
        typedef typename allocator_type::const_pointer              const_pointer;
        typedef vector_iterator<T, T*, T&>                          iterator;
        typedef vector_iterator<T, const T*, const T&>              const_iterator;
        typedef ft::reverse_iterator<iterator>                      reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                const_reverse_iterator;
        typedef typename iterator_traits<iterator>::difference_type difference_type;
        typedef size_t                                              size_type;

    private:
        allocator_type _alloc;
        size_type      _capacity;
        size_type      _size;
        pointer        _data;

        void           _realloc(size_type n);

    public:
        explicit vector(const allocator_type &alloc = allocator_type());
        explicit vector(size_type n, const value_type &val = value_type(),
                        const allocator_type &alloc = allocator_type());
        template<typename InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);
        vector(const vector &src);

        ~vector();

        vector &operator=(const vector &other);

        iterator               begin();
        const_iterator         begin() const;

        iterator               end();
        const_iterator         end() const;

        reverse_iterator       rbegin();
        const_reverse_iterator rbegin() const;

        reverse_iterator       rend();
        const_reverse_iterator rend() const;

        size_type              size() const;
        size_type              max_size() const;
        void                   resize(size_type n, value_type val = value_type());

        size_type              capacity() const;
        bool                   empty() const;
        void                   reserve(size_type n);

        reference              operator[](size_type n);
        const_reference        operator[](size_type n) const;

        reference              at(size_type n);
        const_reference        at(size_type n) const;

        reference              front();
        const_reference        front() const;

        reference              back();
        const_reference        back() const;

        template<typename InputIterator>
        void                   assign(InputIterator first, InputIterator last,
                                      typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);
        void                   assign(size_type n, const value_type &val);

        void                   push_back(const value_type &val);
        void                   pop_back();

        iterator               insert(iterator position, const value_type &val);
        void                   insert(iterator position, size_type n, const value_type &val);
        template<typename InputIterator>
        void                   insert(iterator position, InputIterator first, InputIterator last,
                                      typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type * = NULL);

        iterator               erase(iterator position);
        iterator               erase(iterator first, iterator last);

        void                   swap(vector &src);
        void                   clear();

        allocator_type         get_allocator() const;
    };

    template<typename T, typename Alloc>
    void vector<T, Alloc>::_realloc(size_type n) {
        if (n <= _capacity)
            return;

        pointer _new_data = _alloc.allocate(n);

        for (size_type i = 0; i < _size; i++) {
            _alloc.construct(_new_data + i, _data[i]);
            _alloc.destroy(_data + i);
        }

        _alloc.deallocate(_data, _capacity);
        _data = _new_data;
        _capacity = n;
    }

    /**
     * Empty container constructor (default constructor)
     * @param alloc Allocator object
     */
    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(const allocator_type &alloc): _alloc(alloc), _capacity(0), _size(0) {
        _data = _alloc.allocate(_capacity);
    }

    /**
     * Fill constructor
     * @param n   Initial container size
     * @param val Value to fill the container with
     * @param alloc Allocator object
     */
    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(vector::size_type n, const value_type &val,
                             const allocator_type &alloc): _alloc(alloc), _capacity(n), _size(0) {
        _data = _alloc.allocate(_capacity);
        insert(begin(), n, val);
    }

    /**
     * Range constructor
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     * @param alloc Allocator object
     */
    template<typename T, typename Alloc>
    template<typename InputIterator>
    vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type &alloc,
                             typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*): _alloc(alloc), _capacity(0), _size(0) {
        _data = _alloc.allocate(_capacity);
        insert(begin(), first, last);
    }

    /**
     * Copy constructor
     * @param src Another vector object of the same type
     */
    template<typename T, typename Alloc>
    vector<T, Alloc>::vector(const vector &src): _alloc(src._alloc), _capacity(src._capacity), _size(0) {
        _data = _alloc.allocate(_capacity);
        insert(begin(), src.begin(), src.end());
    }

    template<typename T, typename Alloc>
    vector<T, Alloc>::~vector() {
        clear();
        _alloc.deallocate(_data, _capacity);
    }

    template<typename T, typename Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &other) {
        if (this == &other)
            return (*this);

        clear();

        _alloc = other._alloc;
        _capacity = other._capacity;

        insert(begin(), other.begin(), other.end());

        return (*this);
    }

    /**
     * Return iterator to beginning
     * @return An iterator to the beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::begin() {
        return (iterator(_data));
    }

    /**
     * Return const iterator to beginning
     * @return A const iterator to the beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::begin() const {
        return (const_iterator(_data));
    }

    /**
     * Return iterator to end
     * @return An iterator to the element past the end of the sequence
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::end() {
        return (iterator(_data + _size));
    }

    /**
     * Return const iterator to end
     * @return A const iterator to the element past the end of the sequence
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_iterator vector<T, Alloc>::end() const {
        return (const_iterator(_data + _size));
    }

    /**
     * Return reverse iterator to reverse beginning
     * @return A reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rbegin() {
        return (reverse_iterator(end()));
    }

    /**
     * Return const reverse iterator to reverse beginning
     * @return A const reverse iterator to the reverse beginning of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rbegin() const {
        return (const_reverse_iterator(end()));
    }

    /**
     * Return reverse iterator to reverse end
     * @return A reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reverse_iterator vector<T, Alloc>::rend() {
        return (reverse_iterator(begin()));
    }

    /**
     * Return const reverse iterator to reverse end
     * @return A const reverse iterator to the reverse end of the sequence container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reverse_iterator vector<T, Alloc>::rend() const {
        return (const_reverse_iterator(begin()));
    }

    /**
     * Return size
     * @return The number of elements in the container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const {
        return (_size);
    }

    /**
     * Return maximum size
     * @return The maximum number of elements a vector container can hold as content
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const {
        return (_alloc.max_size());
    }

    /**
     * Resizes the container so that it contains n elements
     * @param n   New container size, expressed in number of elements
     * @param val Object whose content is copied to the added elements in case that
     *            n is greater than the current container size
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::resize(vector::size_type n, value_type val) {
        if (n > _capacity)
            _realloc(n);

        for (size_type i = n; i < _size; i++) {
            _alloc.destroy(_data + i);
        }

        for (size_type i = _size; i < n; i++) {
            _alloc.construct(_data + i, val);
        }

        _size = n;
    }

    /**
     * Return size of allocated storage capacity
     * @return The size of the currently allocated storage capacity in the vector
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const {
        return (_capacity);
    }

    /**
     * Test whether vector is empty
     * @return true if the container size is 0, false otherwise
     */
    template<typename T, typename Alloc>
    bool vector<T, Alloc>::empty() const {
        return (_size == 0);
    }

    /**
     * Request a change in capacity
     * @param n Minimum capacity for the vector
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::reserve(vector::size_type n) {
        if (n > _capacity)
            _realloc(n);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](vector::size_type n) {
        return (_data[n]);
    }

    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](vector::size_type n) const {
        return (_data[n]);
    }

    /**
     * Access element
     * @param n Position of an element in the container
     * @return The element at the specified position in the container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::at(vector::size_type n) {
        if (n >= _size)
            throw std::out_of_range("Out of Range error: vector");
        return ((*this)[n]);
    }

    /**
     * Access element
     * @param n Position of an element in the container
     * @return The element at the specified position in the container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(vector::size_type n) const {
        if (n < 0 || n >= _size)
            throw std::out_of_range("Out of Range error: vector");
        return ((*this)[n]);
    }

    /**
     * Access first element
     * @return A reference to the first element in the vector container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::front() {
        return (_data[0]);
    }

    /**
     * Access first element
     * @return A const reference to the first element in the vector container
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const {
        return (_data[0]);
    }

    /**
     * Access last element
     * @return A reference to the last element in the vector
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::reference vector<T, Alloc>::back() {
        return (_data[_size - 1]);
    }

    /**
     * Access last element
     * @return A const reference to the last element in the vector
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const {
        return (_data[_size - 1]);
    }

    /**
     * Assign vector content
     * @param first Input iterator to the initial position in a range
     * @param last  Input iterator to the final position in a range
     */
    template<typename T, typename Alloc>
    template<typename InputIterator>
    void vector<T, Alloc>::assign(InputIterator first, InputIterator last,
                                  typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*) {
        clear();
        insert(begin(), first, last);
    }

    /**
     * Assign vector content
     * @param n   New size for the container
     * @param val Value to fill the container with
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::assign(vector::size_type n, const value_type &val) {
        clear();
        insert(begin(), n, val);
    }

    /**
     * Add element at the end
     * @param val Value to be copied to the new element
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::push_back(const value_type &val) {
        insert(end(), val);
    }

    /**
     * Delete last element
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::pop_back() {
        erase(end() - 1);
    }

    /**
     * Insert elements
     * @param position Position in the vector where the new element are inserted
     * @param val      Value to be copied to the inserted elements
     * @return An iterator that points to the first of the newly inserted element
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(vector::iterator position, const value_type &val) {
        difference_type offset = position - begin();

        if (_size + 1 > _capacity)
            _realloc(ft::max(ft::min(_capacity * 2, max_size()), 1ul));

        position = begin() + offset;

        for (vector::iterator it = end() - 1; it >= position; it--) {
            *(it + 1) = *it;
        }

        _alloc.construct(position.base(), val);
        _size++;
        return (position);
    }

    /**
     * Insert elements
     * @param position Position in the vector where the new elements are inserted
     * @param n        Number of elements to insert
     * @param val      Value to be copied to the inserted elements
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::insert(vector::iterator position, vector::size_type n, const value_type &val) {
        difference_type offset = position - begin();

        if (_size + n > _capacity)
            _realloc(ft::max(ft::min(_capacity * 2, max_size()), _size + n));

        position = begin() + offset;

        for (vector::iterator it = end() - 1; it >= position; it--) {
            *(it + n) = *it;
        }

        for (vector::iterator it = position; it < position + n; it++) {
            _alloc.construct(it.base(), val);
        }

        _size += n;
    }

    /**
     * Insert elements
     * @param position Position in the vector where the new elements are inserted
     * @param first    Input iterator to the initial position in a range
     * @param last     Input iterator to the final position in a range
     */
    template<typename T, typename Alloc>
    template<typename InputIterator>
    void vector<T, Alloc>::insert(vector::iterator position, InputIterator first, InputIterator last,
                                  typename ft::enable_if<!ft::is_integral<InputIterator>::value && ft::is_input_iterator_tag<typename InputIterator::iterator_category>::value>::type*) {
        difference_type offset = position - begin();
        difference_type n = ft::distance(first, last);

        if (_size + n > _capacity)
            _realloc(ft::max(ft::min(_capacity * 2, max_size()), _size + n));

        position = begin() + offset;

        for (vector::iterator it = end() - 1; it >= position; it--) {
            *(it + n) = *it;
        }

        for (vector::iterator it = position; it < position + n; it++) {
            _alloc.construct(it.base(), *first);
            first++;
        }

        _size += n;
    }

    /**
     * Erase elements
     * @param position Iterator pointing to a single element to be removed from the vector
     * @return An iterator pointing to the new location of the element that followed
     *         the last element erased by the function call
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator position) {
        _alloc.destroy(position.base());

        for (iterator it = position; it < end() - 1; it++) {
            *it = *(it + 1);
        }

        _size--;
        return (position);
    }

    /**
     * Erase elements
     * @param first Iterator to the initial position in a range
     * @param last  Iterator to the final position in a range
     * @return An iterator pointing to the new location of the element that followed
     *         the last element erased by the function call
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(vector::iterator first, vector::iterator last) {
        difference_type n = ft::distance(first, last);

        for (iterator it = first; it != last; it++) {
            _alloc.destroy(it.base());
        }

        for (iterator it = last; it < end(); it++) {
            *(it - n) = *it;
        }

        _size -= n;
        return (first);
    }

    /**
     * Swap content
     * @param src Another vector container of the same type
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::swap(vector &src) {
        allocator_type _alloc_tmp = _alloc;
        size_type      _capacity_tmp = _capacity;
        size_type      _size_tmp = _size;
        pointer        _data_tmp = _data;

        _alloc = src._alloc;
        _capacity = src._capacity;
        _size = src._size;
        _data = src._data;

        src._alloc = _alloc_tmp;
        src._capacity = _capacity_tmp;
        src._size = _size_tmp;
        src._data = _data_tmp;
    }

    /**
     * Clear content
     */
    template<typename T, typename Alloc>
    void vector<T, Alloc>::clear() {
        erase(begin(), end());
    }

    /**
     * Get allocator
     * @return The allocator
     */
    template<typename T, typename Alloc>
    typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const {
        return (_alloc);
    }

    template<typename T, typename Alloc>
    bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
        typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end() && *it1 == *it2) {
            it1++;
            it2++;
        }

        return (it1 == lhs.end() && it2 == rhs.end());
    }

    template<typename T, typename Alloc>
    bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(lhs == rhs));
    }

    template<typename T, typename Alloc>
    bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        typename vector<T, Alloc>::const_iterator it1 = lhs.begin();
        typename vector<T, Alloc>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end() && *it1 == *it2) {
            it1++;
            it2++;
        }

        return ((it1 == lhs.end() && it2 != rhs.end()) ||
                (it1 != lhs.end() && it2 != rhs.end() && *it1 < *it2));
    }

    template<typename T, typename Alloc>
    bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(rhs < lhs));
    }

    template<typename T, typename Alloc>
    bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (rhs < lhs);
    }

    template<typename T, typename Alloc>
    bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
        return (!(lhs < rhs));
    }

    template<typename T, typename Alloc>
    void swap(vector<T,Alloc> &x, vector<T,Alloc> &y) {
        x.swap(y);
    }

}

#endif //FT_CONTAINERS_VECTOR_HPP
