#ifndef QUEUE_H
#define QUEUE_H

template <typename type>
class node {
   private:
    type value;
    node *next;

   public:
    node(const type &value, node *next_ptr) {
        this->value = value;
        next = next_ptr;
    }

    ~node() { 
        delete next; 
    }
};

template <typename type>
class queue {
   private:
    node<type> *m_first;
    node<type> *m_last;
    unsigned m_size;

   public:
    queue() {
        m_first = nullptr;
        m_last = nullptr;
        m_size = 0;
    }

    void push(const type &elem) {
        if (m_first == nullptr) {
            m_last = m_first = new node<type>(elem, nullptr);
        } else {
            m_last->next = new node<type>(elem, nullptr);
            m_last = m_last->next;
        }
        m_size++;
    }

    void pop() {
        if (m_size == 0) {
            return;
        }

        node<type> *aux = m_first;
        m_first = m_first->next;
        aux->next = nullptr;
        delete aux;

        m_size--;
        if (m_size == 0) {
            m_last = nullptr;
        }
    }

    type &front() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->value;
    }

    const type &front() const {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->value;
    }

    type &back() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->value;
    }

    const type &back() const {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->value;
    }

    unsigned size() const { 
        return m_size; 
    }

    bool empty() const { 
        return m_size == 0; 
    }

    ~queue() { 
        delete m_first; 
    }
};

#endif