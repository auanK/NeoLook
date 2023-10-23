#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template <typename type>

// Classe que representa um nó da fila.
class node {
   private:
    type value;  // Valor armazenado no nó.
    node *next;  // Ponteiro para o próximo nó.

   public:
    // Construtor que recebe o valor do nó e o ponteiro para o próximo nó.
    node(const type &value, node *next_ptr) {
        this->value = value;
        next = next_ptr;
    }

    // Retorna o valor do nó.
    type &get_value() { return this->value; }

    // Retorna o ponteiro para o próximo nó.
    node *&get_next() { return this->next; }
};

template <typename type>
class queue {
   private:
    node<type> *m_first;  // Ponteiro para o primeiro nó da fila.
    node<type> *m_last;   // Ponteiro para o último nó da fila.
    unsigned m_size;      // Tamanho da fila.

   public:
    // Construtor padrão, inicializa o ponteiro para o primeiro e último nó com
    // nullptr e o tamanho com 0.
    queue() {
        m_first = nullptr;
        m_last = nullptr;
        m_size = 0;
    }

    // Destrutor da classe, desaloca a memória de todos os nós da fila.
    ~queue() {
        // Percorre a fila chamando o destrutor de cada nó.
        while (m_first != nullptr) {
            node<type> *aux = m_first;
            m_first = m_first->get_next();
            delete aux;
        }
    }

    // Retorna o tamanho da fila.
    unsigned size() const { return m_size; }

    // Retorna true se a fila estiver vazia, false caso contrário.
    bool empty() const { return m_size == 0; }

    // Insere um elemento no final da fila.
    void push(const type &elem) {
        if (m_first == nullptr) {
            m_last = m_first = new node<type>(elem, nullptr);
        } else {
            m_last->get_next() = new node<type>(elem, nullptr);
            m_last = m_last->get_next();
        }
        m_size++;
    }

    // Remove o elemento do início da fila.
    void pop() {
        if (m_size == 0) {
            return;
        }

        node<type> *aux = m_first;
        m_first = m_first->get_next();
        aux->get_next() = nullptr;
        delete aux;

        m_size--;
        if (m_size == 0) {
            m_last = nullptr;
        }
    }

    // Retorna o elemento do início da fila.
    type &front() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->get_value();
    }

    // Retorna o elemento do início da fila(versão const).
    const type &front() const {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->get_value();
    }

    type &back() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->get_value();
    }

    // Retorna o elemento do final da fila.
    const type &back() const {
        // Lança uma exceção se a fila estiver vazia.
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->get_value();
    }
};

#endif