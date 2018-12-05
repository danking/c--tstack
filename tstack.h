#include <vector>
#include <memory>
#include <cassert>
#include <stdint.h>

template<typename Value>
class Transaction {
  size_t constexpr static INVALID_INDEX = SIZE_MAX;
public:
  std::shared_ptr<Transaction> tprev {};
  std::shared_ptr<Transaction> prev {};
  size_t prev_index {};
  std::vector<Value> data {};
  Transaction() = default;
  explicit Transaction(std::shared_ptr<Transaction> t)
    :tprev{std::move(t)} {
      if (tprev->data.size() == 0) {
        this->prev = tprev->prev;
        this->prev_index = tprev->prev_index;
      } else {
        init_prev(tprev);
      }
    }
  void init_prev(std::shared_ptr<Transaction> t) {
    this->prev = t;
    this->prev_index = t == nullptr ? INVALID_INDEX : t->data.size()-1;
  }
  void push(Value i) {
    data.push_back(i);
  }
  Value top() {
    if (data.size() == 0) {
      assert(prev != nullptr);
      assert(prev_index != INVALID_INDEX);
      return prev->data[prev_index];
    } else {
      Value x = data.back();
      return x;
    }
  }
  Value pop() {
    if (data.size() == 0) {
      assert(prev != nullptr);
      assert(prev_index != INVALID_INDEX);
      if (prev_index == 0) {
        Value top = prev->data[prev_index];
        init_prev(prev->prev);
        return top;
      } else {
        return prev->data[prev_index--];
      }
    } else {
      Value x = data.back();
      data.pop_back();
      return x;
    }
  }
};

template<typename Value>
class TStack {
  std::shared_ptr<Transaction<Value>> t;
public:
  TStack() :t{std::make_shared<Transaction<Value>>()} {}
  void push(Value i) {
    t->push(i);
  }
  Value top() {
    return t->top();
  }
  Value pop() {
    return t->pop();
  }
  void begin() {
    t = std::make_shared<Transaction<Value>>(t);
  }
  void commit() {
    t->tprev = t->tprev->tprev;
  }
  void rollback() {
    t = t->tprev;
  }
};
