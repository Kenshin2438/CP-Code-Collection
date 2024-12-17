#pragma once

#include <array>
#include <memory>
#include <queue>

namespace kenshin::DS {

  class AhoCorasick {
   private:
    struct node {
      int dep {0};

      std::array<std::shared_ptr<node>, 26> children {};
      std::shared_ptr<node> fail {};
    };
    std::shared_ptr<node> root = std::make_shared<node>(0);

   public:
    void insert(const std::string& word) noexcept {
      auto p = root;
      for (const char& ch : word) {
        const int idx {ch - 'a'};
        if (p->children[idx] == nullptr) {
          p->children[idx] = std::make_shared<node>(p->dep + 1);
        }
        p = p->children[idx];
      }
    }

    void build_automaton() noexcept {
      std::queue<std::shared_ptr<node>> Q;
      root->fail = root;
      for (int i = 0; i < 26; i++) {
        if (root->children[i] != nullptr) {
          root->children[i]->fail = root;
          Q.emplace(root->children[i]);
        } else {
          root->children[i] = root;
        }
      }
      while (! Q.empty()) {
        auto p = Q.front();
        Q.pop();
        for (int i = 0; i < 26; i++) {
          if (p->children[i] != nullptr) {
            p->children[i]->fail = p->fail->children[i];
            Q.emplace(p->children[i]);
          } else {
            p->children[i] = p->fail->children[i];
          }
        }
      }
    }
  };

}  // namespace kenshin::DS
