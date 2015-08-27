#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class LRUCache{
 public:
  struct Entry {
    int key;
    int value;
    Entry* prev;
    Entry* next;
  };
  
  const int capacity_;
  int count_;
  vector<Entry> nodes_;
  unordered_map<int, Entry*> map_;
  Entry* head_;
  Entry* tail_;
  
  LRUCache(int capacity)
      : capacity_(capacity),
        count_(0),
        head_(nullptr),
        tail_(nullptr)
  {
    nodes_.resize(capacity);
  }
    
  int get(int key) {
    if (map_.count(key)) {
      Entry* entry = map_[key];

      detach(entry);
      attach_to_head(entry);

      return entry->value;
    } else {
      return -1;
    }
  }
    
  void set(int key, int value) {
    Entry* entry;
    
    if (map_.count(key)) {
      entry = map_[key];
      entry->value = value;
      detach(entry);
    } else if (count_ < capacity_) {
      entry = &nodes_[count_];
      count_++;
    } else {
      entry = tail_;
      map_.erase(entry->key);
      detach(entry);
    }
    
    entry->key = key;
    entry->value = value;
    attach_to_head(entry);
    map_[key] = entry;
  }
  
 private:
  void detach(Entry* entry) {
    Entry* a = entry->prev;
    Entry* b = entry->next;
    if (entry == head_) {
      head_ = b;
    }
    if (entry == tail_) {
      tail_ = a;
    }
    if (a) {
      a->next = b;
    }
    if (b) {
      b->prev = a;
    }
  }
  
  void attach_to_head(Entry* entry) {
    Entry* oldhead = head_;
    head_ = entry;
    if (oldhead == nullptr) {
      tail_ = entry;
    }

    if (oldhead) {
      oldhead->prev = head_;
    }
    head_->next = oldhead;
    head_->prev = nullptr;
  }
};

int main() {
  return 0;
}
