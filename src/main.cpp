#include <iostream>

#include "../include/queue.h"

using namespace std;

int main() {
    queue<string> person;
    person.push("a");
    person.push("b");
    person.push("c");
    person.push("d");

    while (!person.empty()) {
        cout << person.front() << endl;
        person.pop();
    }
}

