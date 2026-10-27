#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include <cstddef>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
        Node<T>* first;
        std::size_t n;

    public:
        ListLinked() : first(nullptr), n(0) {}

        ~ListLinked() override {
            clear();
        }

        T operator[](std::size_t index) const {
            if (index >= n) {
                throw std::out_of_range("Índice fuera de rango");
            }
            Node<T>* aux = first;
            for (std::size_t i = 0; i < index; ++i) {
                aux = aux->next;
            }
            return aux->data;
        }

        void insert(std::size_t index, const T& element) override {
            if (index > n) {
                throw std::out_of_range("Posición de inserción inválida");
            }

            if (index == 0) {
                first = new Node<T>(element, first);
            } else {
                Node<T>* aux = first;
                for (std::size_t i = 0; i < index - 1; ++i) {
                    aux = aux->next;
                }
                aux->next = new Node<T>(element, aux->next);
            }
            n++;
        }

        void add(const T& element) override {
            append(element);
        }

        void append(const T& element) override {
            insert(n, element);
        }

        void prepend(const T& element) override {
            insert(0, element);
        }

        T remove(std::size_t index) override {
            if (index >= n) {
                throw std::out_of_range("Posición de borrado inválida");
            }

            Node<T>* aux = first;
            T dataRemoved;

            if (index == 0) {
                first = first->next;
                dataRemoved = aux->data;
                delete aux;
            } else {
                Node<T>* prev = first;
                for (std::size_t i = 0; i < index - 1; ++i) {
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

        T get(std::size_t index) const override {
            return (*this)[index];
        }

        int search(const T& element) const override {
            Node<T>* aux = first;
            int i = 0;
            while (aux != nullptr) {
                if (aux->data == element) {
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

        std::size_t size() const override {
            return n;
        }

        void clear() override {
            while (first != nullptr) {
                Node<T>* aux = first;
                first = first->next;
                delete aux;
            }
            n = 0;
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
