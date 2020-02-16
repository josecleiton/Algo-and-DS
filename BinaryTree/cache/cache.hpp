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
#include <memory>
#include <vector>

template <typename T>
bool cmp(const std::pair<std::time_t, std::unique_ptr<T>>& l,
         const std::pair<std::time_t, std::unique_ptr<T>>& r) {
   return l.first >= r.first;
}

template <typename T>
class Cache {
   std::vector<std::pair<std::time_t, std::unique_ptr<T>>> mHeap;
   const std::size_t mMax;
   const std::time_t mGap;

  public:
   Cache(const std::size_t& max, const std::time_t gap) : mMax(max), mGap(gap) { mHeap.reserve(mMax); }
   inline T* push(const T& obj) {
      if(mHeap.size() + 1 > mMax) {
         printf("Cleaned: %d\n", cleanUp(std::time(nullptr)));
      }
      mHeap.emplace_back(
          std::make_pair(std::time(nullptr), std::make_unique<T>(obj)));
      auto res = mHeap.back().second.get();
      std::push_heap(mHeap.begin(), mHeap.end(), cmp<T>);
      return res;
   }

   unsigned cleanUp(const std::time_t now) {
      const auto& root = mHeap.front();
      std::pop_heap(mHeap.begin(), mHeap.end());
      mHeap.pop_back();
      if(now - root.first > mGap) {
         return cleanUp(now) + 1;
      }
      return 1;
   }
};

