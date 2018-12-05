#include <vector>
#include <memory>
#include <cassert>

class Transaction {
  size_t constexpr static INVALID_INDEX = ((size_t)0)-1;
public:
  std::shared_ptr<Transaction> tprev {};
  std::shared_ptr<Transaction> prev {};
  size_t prev_index {};
  std::vector<int> data {};
  Transaction() = default;
  explicit Transaction(std::shared_ptr<Transaction> prev)
    :tprev{std::move(prev)} {
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
  void push(int i) {
    data.push_back(i);
  }
  int top() {
    if (data.size() == 0) {
      assert(prev != nullptr);
      assert(prev_index != INVALID_INDEX);
      return prev->data[prev_index];
    } else {
      int x = data.back();
      return x;
    }
  }
  int pop() {
    if (data.size() == 0) {
      assert(prev != nullptr);
      assert(prev_index != INVALID_INDEX);
      if (prev_index == 0) {
        int top = prev->data[prev_index];
        init_prev(prev->prev);
        return top;
      } else {
        return prev->data[prev_index--];
      }
    } else {
      int x = data.back();
      data.pop_back();
      return x;
    }
  }
};

class TStack {
  std::shared_ptr<Transaction> t;
public:
  TStack() :t{std::make_shared<Transaction>()} {}
  void push(int i) {
    t->push(i);
  }
  int top() {
    return t->top();
  }
  int pop() {
    return t->pop();
  }
  void begin() {
    t = std::make_shared<Transaction>(t);
  }
  void commit() {
    t->tprev = t->tprev->tprev;
  }
  void rollback() {
    t = t->tprev;
  }
};
