#pragma once
#include <cstddef> // size_t
#include <stdexcept>
#include <concepts>
#include <iostream>

template <typename T>
concept EqualityComparable = requires(const T& a, const T& b) {
	{ a == b } -> std::convertible_to<bool>;
};

template <typename T>
requires EqualityComparable<T>
class Vector {
private:
	T* data_;
	size_t size_;
	size_t capacity_;

	void resize_capacity(size_t new_capacity) {
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < size_; ++i)
			new_data[i] = data_[i];
		delete[] data_;
		data_ = new_data;
		capacity_ = new_capacity;
	}

public:
	class Iterator {
	private:
		T* current_;

	public:
		Iterator(T* ptr) : current_(ptr) {}
		T& operator*() { return *current_; }
		Iterator& operator++() {
			++current_;
			return *this;
		}
		bool operator!=(const Iterator& other) const {
			return current_ != other.current_;
		}
	};

	class ConstIterator {
	private:
		const T* current_;

	public:
		ConstIterator(const T* ptr) : current_(ptr) {}
		const T& operator*() const { return *current_; }
		ConstIterator& operator++() {
			++current_;
			return *this;
		}
		bool operator!=(const ConstIterator& other) const {
			return current_ != other.current_;
		}
	};

	Vector() : data_(nullptr), size_(0), capacity_(0) {}

	~Vector() {
		delete[] data_;
	}

	size_t size() const { return size_; }
	size_t capacity() const { return capacity_; }
	bool empty() const { return size_ == 0; }

	void push_back(const T& value) {
		if (size_ == capacity_) {
			// Double capacity, or start at 1 if empty
			resize_capacity(capacity_ == 0 ? 1 : capacity_ * 2);
		}
		data_[size_++] = value;
	}

	T& at(size_t index) {
		try {
			if (index < size_) {
				return data_[index];
			} else {
				throw std::out_of_range("index out of range");
			}
		} catch (const std::exception& e) {
			std::cerr << "Error: " << e.what() << std::endl;
			throw;
		}
	}

	T& operator[](size_t index) {
		return data_[index];
	}

	const T& operator[](size_t index) const {
		return data_[index];
	}

	bool operator==(const Vector& other) const {
		if (size_ != other.size_)
			return false;
		for (size_t i = 0; i < size_; ++i) {
			if (data_[i] != other.data_[i])
				return false;
		}
		return true;
	}

	Iterator begin() { return Iterator(data_); }
	Iterator end()   { return Iterator(data_ + size_); }

	ConstIterator begin() const { return ConstIterator(data_); }
	ConstIterator end()   const { return ConstIterator(data_ + size_); }

	Vector(const Vector&) = delete;
	Vector& operator=(const Vector&) = delete;
};
