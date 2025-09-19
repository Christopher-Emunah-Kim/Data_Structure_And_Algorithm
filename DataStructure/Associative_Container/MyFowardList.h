#pragma once
#include <cstddef>   
#include <utility>  
#include <type_traits>


template <typename T>
class MyForwardList
{
    struct Node {
        T value;         
        Node* next;        

        Node(const T& v, Node* n) 
            : value(v), next(n) 
        {}

        Node(T&& v, Node* n) noexcept
            : value(std::move(v)), next(n) 
        {
        }
    };

public:
    MyForwardList() = default;

    MyForwardList(const MyForwardList& other)
    {
      
    }

    MyForwardList(MyForwardList&& other) noexcept
        : m_head(other.m_head), m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_size = 0;
    }

    ~MyForwardList() { clear(); }

    MyForwardList& operator=(const MyForwardList& other)
    {
        if (this == &other) 
            return *this;

        MyForwardList tmp(other);

        swap(tmp);

        return *this;
    }

    MyForwardList& operator=(MyForwardList&& other) noexcept
    {
        if (this == &other) 
            return *this;

        clear();
        m_head = other.m_head;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_size = 0;

        return *this;
    }


    inline Node* head_node() const noexcept { return m_head; }

    inline std::size_t size()  const noexcept { return m_size; }
    inline bool        empty() const noexcept { return m_size == 0; }

    inline T& front() { return m_head->value; }   
    inline const T& front() const { return m_head->value; }  


public:
    void push_front(const T& value)
    {
        m_head = new Node(value, m_head);
        ++m_size;
    }

    void push_front(T&& value)
    {
        m_head = new Node(std::move(value), m_head);
        ++m_size;
    }

    void push_back(const T& value)
    {
        if (!m_head) 
        {
            m_head = new Node(value, nullptr);
            m_size = 1;
            return;
        }

        Node* cur = m_head;
        while (cur->next) cur = cur->next; 
        cur->next = new Node(value, nullptr);
        ++m_size;
    }

    void push_back(T&& value)
    {
        if (!m_head) 
        {
            m_head = new Node(std::move(value), nullptr);
            m_size = 1;
            return;
        }
        Node* cur = m_head;
        while (cur->next) cur = cur->next;
        cur->next = new Node(std::move(value), nullptr);
        ++m_size;
    }

    void insert_after(Node* node, const T& value)
    {
        if (!node)
            return;

        node->next = new Node(value, node->next);
        ++m_size;
    }

    //이해가 잘 안됨 Emplace는..
    template <class... Args>
    void emplace_after(Node* node, Args&&... args)
    {
        if (!node) 
            return;

        node->next = new Node(T(std::forward<Args>(args)...), node->next);
        ++m_size;
    }

    template <class... Args>
    void emplace_front(Args&&... args)
    {
        m_head = new Node(T(std::forward<Args>(args)...), m_head);
        ++m_size;
    }

    void pop_front()
    {
        if (!m_head) 
            return;

        Node* tmp = m_head;
        m_head = m_head->next;
        delete tmp;
        --m_size;
    }

    void erase_after(Node* node)
    {
        if (!node || !node->next) 
            return;

        Node* victim = node->next;
        node->next = victim->next;
        delete victim;
        --m_size;
    }

    void remove(const T& value)
    {
        while (m_head && m_head->value == value) 
        {
            pop_front();
        }

        Node* cur = m_head;
        while (cur && cur->next) 
        {
            if (cur->next->value == value) 
            {
                erase_after(cur);
            }
            else 
            {
                cur = cur->next;
            }
        }
    }

    //조건자 기준 삭제. Pred는 bool<T>타입 함수 객체를 만들어줘야함.
    template <class Pred>
    void remove_if(Pred pred)
    {
        while (m_head && pred(m_head->value)) {
            pop_front();
        }
        Node* cur = m_head;

        while (cur && cur->next) 
        {
            if (pred(cur->next->value)) 
                erase_after(cur);
            else 
                cur = cur->next;
        }
    }

    void unique()
    {
        if (!m_head) 
            return;

        Node* cur = m_head;

        while (cur->next) 
        {
            if (cur->value == cur->next->value) 
            {
                erase_after(cur);
            }
            else
            {
                cur = cur->next;
            }
        }
    }

    void reverse() noexcept
    {
        Node* prev = nullptr;
        Node* cur = m_head;

        while (cur) 
        {
            Node* nxt = cur->next;
            cur->next = prev;
            prev = cur;
            cur = nxt;
        }
        m_head = prev;
    }

    //블로그 참고. 삽입 정렬 형태.
    void sort()
    {
        if (!m_head || !m_head->next) 
            return;

        Node* sorted = nullptr; 

        while (m_head) 
        {
            Node* node = m_head;
            m_head = m_head->next;

            if (!sorted || node->value < sorted->value) 
            {
                node->next = sorted;
                sorted = node;
            }
            else 
            {
                Node* s = sorted;

                while 
                    (s->next && !(node->value < s->next->value)) 
                {
                    s = s->next;
                }
                node->next = s->next;
                s->next = node;
            }
        }
        m_head = sorted;
    }

    Node* find(const T& value) const noexcept
    {
        Node* cur = m_head;

        while (cur)
        {
            if (cur->value == value) 
                return cur;

            cur = cur->next;
        }
        return nullptr;
    }

    void clear() noexcept
    {
        while (m_head)
        {
            pop_front();
        }
    }

    void swap(MyForwardList& other) noexcept
    {
        std::swap(m_head, other.m_head);
        std::swap(m_size, other.m_size);
    }


private:
    Node* m_head = nullptr;
    std::size_t m_size = 0;
};
