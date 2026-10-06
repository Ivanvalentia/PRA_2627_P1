#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdexcept>

template <typename T> 
class List {
    public:
      // ... aquí los métodos virtuales puros

	virtual ~List() {}

    virtual void insert(std::size_t index, const T& element) = 0;
    virtual void add(const T& element) = 0;
    virtual T remove(std::size_t index) = 0;
    virtual T get(std::size_t index) const = 0;
    virtual int search(const T& element) const = 0;
    virtual bool empty() const = 0;
    virtual std::size_t size() const = 0;
    virtual void clear() = 0;
};

#endif
