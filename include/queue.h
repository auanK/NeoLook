#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

// Classe que representa um nó da fila.
template <typename type>
class node {
   private:
    type value;  // Valor armazenado no nó.
    node *next;  // Ponteiro para o próximo nó.

   public:
    // Construtor que recebe o valor do nó e o ponteiro para o próximo nó. O(1)
    node(const type &value, node *next_ptr) {
        this->value = value;
        next = next_ptr;
    }

    // Retorna o valor do nó. O(1)
    type &get_value() { 
        return this->value; 
    }

    // Retorna o ponteiro para o próximo nó. O(1)
    node *&get_next() { 
        return this->next; 
    }
};

// Classe que representa uma fila.
template <typename type>
class queue {
   private:
    node<type> *m_first;  // Ponteiro para o primeiro nó da fila.
    node<type> *m_last;   // Ponteiro para o último nó da fila.
    unsigned m_size;      // Tamanho da fila.

   public:
    // Construtor padrão, inicializa o ponteiro para o primeiro e último nó com
    // nullptr e o tamanho com 0. O(1)
    queue() {
        m_first = nullptr;
        m_last = nullptr;
        m_size = 0;
    }

    // Destrutor da classe, desaloca a memória de todos os nós da fila. O(n)
    ~queue() {
        // Percorre a fila chamando o destrutor de cada nó.
        while (m_first != nullptr) {
            node<type> *aux = m_first;
            m_first = m_first->get_next();
            delete aux;
        }
    }

    // Retorna o tamanho da fila. O(1)
    unsigned size() const { 
        return m_size; 
    }

    // Retorna true se a fila estiver vazia, false caso contrário. O(1)
    bool empty() const { 
        return m_size == 0; 
    }

    // Insere um elemento no final da fila. O(1)
    void push(const type &elem) {
        if (m_first == nullptr) {
            // Se a fila estiver vazia, criamos um novo nó e fazemos o ponteiro
            // para o primeiro e último nó apontar para ele.
            m_last = m_first = new node<type>(elem, nullptr);
        } else {
            // Se a fila não estiver vazia, criamos um novo nó e fazemos o
            // ponteiro para o último nó apontar para ele.
            m_last->get_next() = new node<type>(elem, nullptr);
            m_last = m_last->get_next();
        }
        // Atualizamos o tamanho da fila.
        m_size++;
    }

    // Remove o elemento do início da fila. O(1)
    void pop() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }

        // Criamos um nó auxiliar para não perder o ponteiro para o primeiro nó,
        // e fazemos o ponteiro para o primeiro nó apontar para o segundo nó.
        node<type> *aux = m_first;
        m_first = m_first->get_next();

        // Fazemos o ponteiro para o próximo nó do nó auxiliar apontar para
        // nullptr e desalocamos a memória do nó auxiliar.
        aux->get_next() = nullptr;
        delete aux;

        // Atualizamos o tamanho da fila, e se a fila ficou vazia, atualizamos
        // o ponteiro para o último nó.
        m_size--;
        if (m_size == 0) {
            m_last = nullptr;
        }
    }

    // Retorna o elemento do início da fila. O(1)
    type &front() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->get_value();
    }
    // Versão constante da função front. O(1)
    const type &front() const {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_first->get_value();
    }

    // Retorna o elemento do final da fila. O(1)
    type &back() {
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->get_value();
    }
    // Versão constante da função back. O(1)
    const type &back() const {
        // Lança uma exceção se a fila estiver vazia.
        if (m_size == 0) {
            throw std::runtime_error("fila vazia");
        }
        return m_last->get_value();
    }
};

#endif