#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/catch_message.hpp>
#include <cstdint>
#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("Other List Function Check", "[functions_list]") {

    SECTION("Test 'PushBack' function") {
        List test_list;
        test_list.PushBack(1);
        CHECK(test_list.PopBack() == 1);
    }

    SECTION("Test 'PushFront' function") {
        List test_list;
        test_list.PushFront(2);
        CHECK(test_list.PopFront() == 2);
    }

    SECTION("Test 'PopBack' function") {
        List test_list;
        CHECK_THROWS(test_list.PopBack());
    }

    SECTION("Test 'PopFront' function") {
        List test_list;
        CHECK_THROWS(test_list.PopFront());
    }

    SECTION("Complex Test") {
        List test_list;
        test_list.PushBack(1);
        test_list.PushFront(2);
        test_list.PushBack(3);
        test_list.PushFront(4);
        test_list.PopBack();
        test_list.PopFront();
        test_list.PushBack(5);
        test_list.PushFront(6);
        CHECK(test_list.PopFront() == 6);
    }
}

int main(int argc, char* argv[]) {
   return Catch::Session().run(argc,argv);
}