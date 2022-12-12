#include <iostream>
#include <cstdlib>
#include <vector>
#include <optional>

#include <utility>
#include <exception>
#include <thread>
#include <mutex>
#include <memory>
#include <future>

using namespace std;

const int MyStack_SIZE = 20;

struct empty_stack : std::exception {
    const char* what() const throw();
};

template<typename T>
struct Stack {
    T* data;
    size_t size = 0;

    Stack() {
        data = new T[MyStack_SIZE];
    }

    Stack(Stack const& lMyStack) {
        data = new T[MyStack_SIZE];
        for (int i = 0; i < lMyStack.size; i++) {
            data[i] = lMyStack.data[i];
        }
        size = lMyStack.size;
    }

    Stack(Stack&& rMyStack) {
        data = rMyStack.data;
        size = rMyStack.size;

        rMyStack.data = nullptr;
        rMyStack.size = 0;
    }

    Stack& operator=(Stack const& lMyStack) {
        if (data == nullptr) {
            data = new T[MyStack_SIZE];
        }
        for (int i = 0; i < lMyStack.size; i++) {
            data[i] = lMyStack.data[i];
        }
        size = lMyStack.size;

        return this;
    }

    Stack& operator=(Stack&& rMyStack) {
        data = rMyStack.data;
        size = rMyStack.size;

        rMyStack.data = nullptr;
        rMyStack.size = 0;

        return this;
    }

    void Push(const T& value) {
        if (size >= MyStack_SIZE) {
            cout << "throw Stack overflow" << endl;
        }
        else {
            data[size] = value;
            size++;
        }
    }

    T Pop() {
        if (size <= 0) {
            cout << "size cant be less than 0" << endl;
        }
        else {
            size--;
            return data[size];
        }
    }

    T Peek() {
        if (size <= 0) {
            cout << "size cant be less than 0" << endl;
        }
        else {
            return data[size - 1];
        }
    }

    bool Empty() {
        return size == 0;
    }

    bool Full() {
        return size >= MyStack_SIZE;
    }

    operator bool() {
        return size != 0;
    }

    ~Stack() {

        delete[] data;
    }
};




template<typename T>
class threadSafeMyStack {
private:
    Stack<T> data;
    mutable std::mutex mut;
    std::condition_variable dataCond;

public:
    threadSafeMyStack() {}

    threadSafeMyStack(const threadSafeMyStack& other) {
        std::lock_guard<std::mutex> lock(other.mut);
        data = other.data;
    }

    threadSafeMyStack(threadSafeMyStack&& other) {
        std::lock_guard<std::mutex> lock(other.mut);
        data = std::move(other.data);
    }

    threadSafeMyStack& operator=(const threadSafeMyStack&) = delete;

    void wait_and_push(T elem) {
        std::unique_lock<std::mutex> lock(mut);
        dataCond.wait(lock, [this] {return !data.Full(); });
        data.Push(elem);
        std::cout << data.size << std::endl;
        dataCond.notify_one();
    }


    T wait_and_pop() {
        std::unique_lock<std::mutex> lock(mut);
        dataCond.wait(lock, [this] {return !data.Empty(); });
        auto res = data.Pop();
        std::cout << data.size << std::endl;
        dataCond.notify_one();
        return res;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mut);
        return data.Empty();
    }

};

int main() {
    threadSafeMyStack<int> stack;

    std::vector<std::future<void>> results;

    results.push_back(
            std::async(std::launch::async, [&stack] {
                for (;;) {
                    stack.wait_and_push(10);
                    std::chrono::milliseconds timespan(30);
                    std::this_thread::sleep_for(timespan);
                }
            }));

    results.push_back(
            std::async(std::launch::async, [&stack] {
                for (;;) {
                    stack.wait_and_pop();
                    std::chrono::milliseconds timespan(120);
                    std::this_thread::sleep_for(timespan);
                }
            }));

    results.push_back(
            std::async(std::launch::async, [&stack] {
                for (;;) {
                    stack.wait_and_pop();
                    std::chrono::milliseconds timespan(180);
                    std::this_thread::sleep_for(timespan);
                }
            }));

    results.push_back(
            std::async(std::launch::async, [&stack] {
                for (;;) {
                    stack.wait_and_pop();
                    std::chrono::milliseconds timespan(240);
                    std::this_thread::sleep_for(timespan);
                }
            }));
}