#ifndef FT_CONTAINERS_STACK_HPP
# define FT_CONTAINERS_STACK_HPP

# include "vector.hpp"

namespace ft {

    /**
     * LIFO stack
     * @tparam T         Type of the elements
     * @tparam Container Type of the internal underlying container object where the elements are stored
     */
    template< typename T, typename Container = ft::vector<T> >
    class stack {
    public:
        typedef T         value_type;
        typedef Container container_type;
        typedef size_t    size_type;

    protected:
        container_type c;

    public:
        explicit stack(const container_type &ctnr = container_type());

        bool             empty() const;
        size_type        size() const;

        value_type       &top();
        const value_type &top() const;

        void             push(const value_type &val);
        void             pop();

        friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c == rhs.c);
        }

        friend bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c != rhs.c);
        }

        friend bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c > rhs.c);
        }

        friend bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c >= rhs.c);
        }

        friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c < rhs.c);
        }

        friend bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs) {
            return (lhs.c <= rhs.c);
        }
    };

    /**
     * Construct stack
     * @param ctnr Container object
     */
    template<typename T, typename Container>
    stack<T, Container>::stack(const container_type &ctnr): c(ctnr) {}

    /**
     * Test whether container is empty
     * @return true if the underlying container's size is 0, false otherwise
     */
    template<typename T, typename Container>
    bool stack<T, Container>::empty() const {
        return (c.empty());
    }

    /**
     * Return size
     * @return The number of elements in the underlying container
     */
    template<typename T, typename Container>
    typename stack<T, Container>::size_type stack<T, Container>::size() const {
        return (c.size());
    }

    /**
     * Access next element
     * @return A reference to the top element in the stack
     */
    template<typename T, typename Container>
    typename stack<T, Container>::value_type &stack<T, Container>::top() {
        return (c.back());
    }

    /**
     * Access next element
     * @return A const reference to the top element in the stack
     */
    template<typename T, typename Container>
    const typename stack<T, Container>::value_type &stack<T, Container>::top() const {
        return (c.back());
    }

    /**
     * Insert element
     * @param val Value to which the inserted element is initialized
     */
    template<typename T, typename Container>
    void stack<T, Container>::push(const value_type &val) {
        c.push_back(val);
    }

    /**
     * Remove top element
     */
    template<typename T, typename Container>
    void stack<T, Container>::pop() {
        c.pop_back();
    }

}

#endif //FT_CONTAINERS_STACK_HPP
