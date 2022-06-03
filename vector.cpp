#include <iostream>
#include <initializer_list>

template <typename T>
class Vector
{
public:
  Vector();
  Vector(const Vector<T>&);
  Vector(Vector<T>&&);
  Vector(size_t);
  Vector(size_t,T);
  Vector(std::initializer_list<T>);
  ~Vector();
  Vector& operator=(const Vector<T>&);
  Vector& operator=(Vector<T>&&);
  void push_back(const T&);
  void push_back(T&&);
  void pop_back();
  void insert(size_t pos,const T&);
  void insert(size_t,T&&);
  bool empty() const;
  size_t size() const;
  size_t capacity() const;
  void clear();
  void resize(size_t);
  void erase(size_t);
  T& at(size_t);
  const T& at(size_t) const;
  T& operator[](size_t);
  const T& operator[](size_t) const;
  void shrink_to_fit();
private:
  size_t m_cap;
  size_t m_size;
  T* m_buf;
};

template <typename T>
Vector<T>::Vector():m_cap{1},m_size{},m_buf{}
{
    
}

template <typename T>
Vector<T>::Vector(const Vector <T>& oth):
m_cap{oth.m_cap},
m_size{oth.m_size},
m_buf{}
{
	if(!oth.empty())
	{
		m_buf = new T[m_cap];
	for(int i = 0;i < m_size;++i)
	{
		m_buf[i] = oth.m_buf[i];
	}
	}
}

template <typename T>
Vector<T>::Vector(Vector&& tmp):
    m_cap{tmp.m_cap},
    m_size{tmp.m_size},
    m_buf{tmp.m_buf}
    {
        tmp.m_cap = 0;
        tmp.m_size = 0;
        tmp.m_buf = nullptr;
    }

template <typename T>
Vector<T>::Vector(size_t count,T val):
    m_cap{count},
    m_size{count},
    m_buf{new T[m_cap]}
    {
    for(int i = 0;i < m_size;i++)
    {
        m_buf[i] = val;
    }
}

template <typename T>
Vector<T>::Vector(size_t count):
    m_cap{count},
    m_size{count},
    m_buf{new T[m_cap]}
    {
        
    }

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init):
    m_cap(init.size()),
    m_size(m_cap),
    m_buf(new T[m_cap])
    {
        int i = 0;
        for(auto it = init.begin();it != init.end();++it)
        {
            m_buf[i++] = *it;
        }
    }

template <typename T>
Vector<T>::~Vector()
    {
        if(m_buf)
        {
            delete[] m_buf;
        }
    }

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& oth)
    {
        if(this == &oth)
        {
            return *this;
        }
        if(this->m_buf)
        {
            delete[] m_buf;
        }
        m_cap = oth.m_cap;
        m_size = oth.m_size;
        m_buf = new T[m_cap];
        for(int i = 0;i < m_size;i++)
        {
            m_buf[i] = oth.m_buf[i];
        }
        return *this;
    }
    
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& tmp)
    {
        std::swap(m_cap,tmp.m_cap);
        std::swap(m_size,tmp.m_size);
        std::swap(m_buf,tmp.m_buf);
        return *this;
    }

template <typename T>
void Vector<T>::push_back(const T& val)
{
	if(this -> empty())
	{
		m_buf = new T[m_cap];
		m_buf[m_size++] = val; 
	}
	else
	{
		if(m_size < m_cap)
		{
			m_buf[m_size++] = val;
		}
		else
		{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(int i = 0;i < m_size;++i)
			{
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			m_buf[m_size++] = val;
		}
	}
}

template <typename T>
void Vector<T>::push_back(T&& val)
{
	if(this -> empty())
	{
		m_buf = new T[m_cap];
		m_buf[m_size++] = std::move(val); 
	}
	else
	{
		if(m_size < m_cap)
		{
			m_buf[m_size++] = std::move(val);
		}
		else
		{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(int i = 0;i < m_size;++i)
			{
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			m_buf[m_size++] = std::move(val);
		}
	}
}

template <typename T>
void Vector<T>::pop_back()
{
	if(!this -> empty())
	{
		m_buf[m_size--] = T{};
	}
}

template <typename T>
void Vector<T>::insert(size_t pos,const T& val)
{
	if(this -> empty())
	{
		m_buf = new T[m_cap];
		m_buf = val;
	}
	else
	{
		if(m_size != m_cap)
		{
			for(int i = m_size - 1;i >= pos;--i)
			{
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = val;
			++m_size;
		}
		else
		{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(int i = 0;i < pos;++i)
			{
				tmp[i] = m_buf[i];
			}
			tmp[pos] = val;
			for(int i = m_size;i > pos;--i)
			{
				tmp[i] = m_buf[i - 1];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

template <typename T>
void Vector<T>::insert(size_t pos,T&& val)
{
	if(this -> empty())
	{
		m_buf = new T[m_cap];
		m_buf = std::move(val);
	}
	else
	{
		if(m_size != m_cap)
		{
			for(int i = m_size - 1;i >= pos;--i)
			{
				m_buf[i + 1] = m_buf[i];
			}
			m_buf[pos] = std::move(val);
			++m_size;
		}
		else
		{
			m_cap *= 2;
			T* tmp = new T[m_cap];
			for(int i = 0;i < pos;++i)
			{
				tmp[i] = m_buf[i];
			}
			tmp[pos] = std::move(val);
			for(int i = m_size;i > pos;--i)
			{
				tmp[i] = m_buf[i - 1];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
			++m_size;
		}
	}
}

template <typename T>
bool Vector<T>::empty() const
{
	return !m_buf;
}

template <typename T>
size_t Vector<T>::size() const
{
	return m_size;
}

template <typename T>
size_t Vector<T>::capacity() const
{
	return m_cap;
}

template <typename T>
void Vector<T>::clear()
{
	if(!this -> empty())
	{
		delete[] m_buf;
		m_cap = 1;
		m_size = 0;
	}
}

template <typename T>
void Vector<T>::resize(size_t cap)
{
	if(m_cap < cap)
	{
		m_cap = cap;
		if(this -> empty())
		{
			m_buf = new T[m_cap];
		}
		else
		{
			T* tmp = new T[m_cap];
			for(int i = 0;i < m_size;++i)
			{
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
		}
	}
}

template <typename T>
T& Vector<T>::at(size_t index)
{
	if(index >= m_size)
	{
		throw std::out_of_range("");
	}
	return m_buf[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const
{
	if(index >= m_size)
	{
		throw std::out_of_range("");
	}
	return m_buf[index];
}

template <typename T>
T& Vector<T>::operator[](size_t ind)
{
	return m_buf[ind];
}

template <typename T>
const T& Vector<T>::operator[](size_t ind) const
{
	return m_buf[ind];
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
	if(!this -> empty())
	{
		if(m_size != m_cap)
		{
			m_cap = m_size;
			T* tmp = new T[m_cap];
			for(int i = 0;i < m_size;++i)
			{
				tmp[i] = m_buf[i];
			}
			delete[] m_buf;
			m_buf = tmp;
			tmp = nullptr;
		}
	}
}

template<typename T>
void Vector<T>::erase(size_t pos)
{
	if(!this -> empty())
	{
		for(int i = m_size - 1;i > pos;--i)
		{
			m_buf[i - 1] = m_buf[i];
		}
		--m_size;
	}
}

int main()
{
    Vector<int> obj;
    obj.push_back(7);
    obj.push_back(9);
    obj.push_back(11);
    obj.pop_back();
    std::cout << "Vector size: " << obj.size() << std::endl << "Vector capacity: " << obj.capacity() << std::endl
    << "At() function: " << obj.at(1);
}
