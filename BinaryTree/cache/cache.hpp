/*
 * =====================================================================================
 *
 *       Filename:  cache.hpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  02/16/2020 07:03:15 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  José Cleiton Borges Correia (JCBC), jcleitonbc@gmail.com
 *   Organization:  UNEB
 *
 * =====================================================================================
 */

#include <algorithm>
#include <ctime>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename T>
class Cache {
   struct Node {
      std::time_t time;
      std::string key;
      std::unique_ptr<T> ptr;

      Node(const std::time_t& t, const std::string& s, const T& obj)
          : time(t), key(s), ptr(std::make_unique<T>(obj)) {}
      constexpr bool operator>=(const Node& r) const { return time >= r.time; }
   };

   std::vector<Node> mHeap;
   std::map<std::string_view, T*> mMap;
   const std::size_t mMax;
   const std::time_t mGap;

  public:
   Cache(const std::size_t& max, const std::time_t gap) : mMax(max), mGap(gap) {
      mHeap.reserve(mMax);
   }
   inline T* push(const T& obj, const std::string& key = "") {
      if (mHeap.size() + 1 > mMax) {
         cleanUp(std::time(nullptr));
      }
      mHeap.emplace_back(Node(std::time(nullptr), key, obj));
      auto res = mHeap.back().ptr.get();
      if (key.size()) {
         mMap[key] = res;
      }
      std::push_heap(mHeap.begin(), mHeap.end(), std::greater_equal<Node>());
      return res;
   }

   inline T* get(const std::string& key) {
      try {
         return mMap.at(key);
      } catch (std::out_of_range& e) {
         return nullptr;
      }
   }

   inline std::size_t size(void) const { return mHeap.size(); }

  private:
   unsigned cleanUp(const std::time_t now) {
      const auto& root = mHeap.front();
      const auto& key = root.key;
      if (key.size()) {
         mMap.erase(key);
      }
      std::pop_heap(mHeap.begin(), mHeap.end(), std::greater_equal<Node>());
      mHeap.pop_back();
      if (now - root.time > mGap) {
         return cleanUp(now) + 1;
      }
      return 1;
   }
};

