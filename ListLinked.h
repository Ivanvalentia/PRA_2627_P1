#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
		Node<T>* first;
		int n;

    public:

        ListLinked():first(nullptr){}
		~ListLinked() override {
        while (first != nullptr) {
            Node<T>* aux = first;
            first = first->next;
            delete aux;
        }
    }

   
    T operator[](int index) const override {
        if (index < 0 || index >= n) {
            throw std::out_of_range("Índice fuera de rango");
        }
        Node<T>* aux = first;
        for (int i = 0; i < index; ++i) {
            aux = aux->next;
        }
        return aux->data;
    }

    
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posición de inserción inválida");
        }

        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* aux = first;
            for (int i = 0; i < pos - 1; ++i) {
                aux = aux->next;
            }
            aux->next = new Node<T>(e, aux->next);
        }
        n++;
    }

    void append(T e) override {
        insert(n, e);
    }

    
    void prepend(T e) override {
        insert(0, e);
    }

  
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posición de borrado inválida");
        }

        Node<T>* aux = first;
        T dataRemoved;

        if (pos == 0) {
            first = first->next;
            dataRemoved = aux->data;
            delete aux;
        } else {
            Node<T>* prev = first;
            for (int i = 0; i < pos - 1; ++i) {
                prev = prev->next;
            }
            aux = prev->next;
            prev->next = aux->next;
            dataRemoved = aux->data;
            delete aux;
        }

        n--;
        return dataRemoved;
    }

    
    T get(int pos) const override {
        return (*this)[pos];
    }

    
    int search(T e) const override {
        Node<T>* aux = first;
        int i = 0;
        while (aux != nullptr) {
            if (aux->data == e) {
                return i;
            }
            aux = aux->next;
            i++;
        }
        return -1;
    }

   
    bool empty() const override {
        return n == 0;
    }

    
    int size() const override {
        return n;
    }

    
    friend std::ostream& operator<<(std::ostream& out, const ListLinked<T>& list) {
        out << "[";
        Node<T>* aux = list.first;
        while (aux != nullptr) {
            out << aux->data;
            if (aux->next != nullptr) {
                out << ", ";
            }
            aux = aux->next;
        }
        out << "]";
        return out;
    }
};

#endif
