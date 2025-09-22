#pragma once

template <typename T>
class MyVector
{
private:
	T* data;
	size_t capacity;
	size_t size;
	const size_t BLOCK_SIZE = 4; // 추가 메모리 블록 크기

public:
	MyVector() : data(nullptr), capacity(0), size(0) {}
	~MyVector() { delete[] data; }

	void push_back(const T& value)
	{
		if (size >= capacity)
		{
			capacity += BLOCK_SIZE;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		data[size++] = value;
	}

	void emplace_back(T&& value)
	{
		if (size >= capacity)
		{
			capacity += BLOCK_SIZE;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		data[size++] = std::move(value);
	}

	void insert(size_t index, const T& value)
	{
		if (index > size) return; // 범위 검사
		if (size >= capacity)
		{
			capacity += BLOCK_SIZE;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		for (size_t i = size; i > index; --i)
		{
			data[i] = data[i - 1];
		}
		data[index] = value;
		++size;
	}

	void emplace(size_t index, T&& value)
	{
		if (index > size) return; // 범위 검사
		if (size >= capacity)
		{
			capacity += BLOCK_SIZE;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		for (size_t i = size; i > index; --i)
		{
			data[i] = data[i - 1];
		}
		data[index] = std::move(value);
		++size;
	}

	void pop_back()
	{
		if (size > 0)
		{
			--size;
		}
	}

	void erase(size_t index)
	{
		if (index >= size) return; // 범위 검사
		for (size_t i = index; i < size - 1; ++i)
		{
			data[i] = data[i + 1];
		}
		--size;
	}

	void resize(size_t newSize)
	{
		if (newSize > capacity)
		{
			capacity = newSize;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
		size = newSize;
	}

	void reserve(size_t newCapacity)
	{
		if (newCapacity > capacity)
		{
			capacity = newCapacity;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
	}

	void shrink_to_fit()
	{
		if (size < capacity)
		{
			capacity = size;
			T* newData = new T[capacity];
			for (size_t i = 0; i < size; ++i)
			{
				newData[i] = data[i];
			}
			delete[] data;
			data = newData;
		}
	}

	void clear()
	{
		delete[] data;
		data = nullptr;
		capacity = 0;
		size = 0;
	}



	T* begin() { return data; }

	T* end() { return data + size; }

	const T* begin() const { return data; }

	const T* end() const { return data + size; }

	const T* cbegin() const { return data; }

	const T* cend() const { return data + size; }

	const T& front() const { return data[0]; }

	const T& back() const { return data[size - 1]; }

	T& front() { return data[0]; }

	T& back() { return data[size - 1]; }

	size_t getCapacity() const { return capacity; }

	size_t getSize() const { return size; }

	bool isEmpty() const { return size == 0; }

	T& operator[](size_t index) { return data[index]; }

	const T& operator[](size_t index) const { return data[index]; }
};
