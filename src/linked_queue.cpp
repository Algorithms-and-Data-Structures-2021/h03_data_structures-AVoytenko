#include "linked_queue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

    void LinkedQueue::Enqueue(Element e) {

        auto node = new SinglyNode(e, nullptr);
        if (size_ == 0) {
            front_ = node;
            back_ = front_;
        }
        else {
            back_->next = node;
            back_ = node;
        }
        size_++;
    }

    void LinkedQueue::Dequeue() {
        if (size_ == 0) {
            throw std::logic_error("could not dequeue from empty queue");
        }

        auto node = front_;
        front_ = front_->next;
        if (!front_) {
            back_ = nullptr;
        }
        size_--;
        delete node;
    }

    void LinkedQueue::Clear() {

        auto node = front_;
        for (int i = 0; i < size_; i++) {
            auto current_node = node->next;
            delete node;
            node = current_node;
        }
        front_ = nullptr;
        back_ = nullptr;
        size_ = 0;
    }

// === РЕАЛИЗОВАНО ===

    LinkedQueue::~LinkedQueue() {
        Clear();
    }

    std::optional<Element> LinkedQueue::front() const {
        return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
    }

    std::optional<Element> LinkedQueue::back() const {
        return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
    }

    bool LinkedQueue::IsEmpty() const {
        return size_ == 0;
    }

    int LinkedQueue::size() const {
        return size_;
    }

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

    std::ostream &operator<<(std::ostream &os, const LinkedQueue &queue) {
        os << "size: " << queue.size_ << '\n';
        for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->next) {
            if (current_node == queue.front_) os << "[FRONT] ";
            if (current_node == queue.back_) os << "[BACK] ";
            os << enum2str(current_node->data) << '\n';
        }
        return os;
    }

}  // namespace itis