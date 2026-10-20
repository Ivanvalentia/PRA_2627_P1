#ifndef LISTLINKED_H
#define LISTLINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"

template <typename T> 
class ListArray : public List<T> {

    private:

		T* arr;
		int max;
		int n;
		static const int MINSIZE = 2;


		void resize(int new_size){
			T* new_arr = new T[new_size];
			for (int i = 0; i < n; ++i) {
				new_arr[i] = arr[i];
			}
        delete[] arr;
        arr = new_arr;
        max = new_size;
		}



    public:

		void prepend(const T& element) override {
			insert(0, element);
		}


        ListArray() : max(MINSIZE), n(0) {
        
			arr = new T[max];
		
		}

		~ListArray() override {
        
			delete[] arr;
		
		}

		T operator[](int index) const {
        
			if (index < 0 || index >= n) {
				throw std::out_of_range("La posicion no es valida");
			}	

			return arr[index];
    
		}


		friend std::ostream& operator<<( std::ostream &out, ListArray<T> &list) {
			out << "List => []";
			for (int i = 0; i < list.n; ++i) {
				out << "  " << list.arr[i];
			}
			out << "]";
			return out;
		}








		void insert(std::size_t index, const T& element) override {
			if (index > static_cast<std::size_t>(n)) {
				throw std::out_of_range("Fuera de rango");
			}
			if (n == max) {
				resize(max * 2);
			}
			for (int i = n; i > static_cast<int>(index); --i) {
				arr[i] = arr[i - 1];
			}
			arr[index] = element;
			n++;
		
		}

		void add(const T& element) override {
			insert(n, element);
		}

		T remove(std::size_t index) override {
			if (index >= static_cast<std::size_t>(n)) {
				throw std::out_of_range("Fuera de rango");
			}
			T removed_element = arr[index];
			for (int i = index; i < n - 1; ++i) {
				arr[i] = arr[i + 1];
			}
			n--;
			return removed_element;
		}

		T get(std::size_t index) const override {
			if (index >= static_cast<std::size_t>(n)) {
				throw std::out_of_range("Fuera de rango");
			}
			return arr[index];
		}

		int search(const T& element) const override {
			for (int i = 0; i < n; ++i) {
				if (arr[i] == element) {
					return i;
				}
			}
			return -1;
		}

		bool empty() const override {
			return n == 0;
		}


		std::size_t size() const override {
			return static_cast<std::size_t>(n);
		}

		void clear() override {
			n = 0;
		}

		void append(const T& element) override {
			insert(n, element);
		}
};
#endif
