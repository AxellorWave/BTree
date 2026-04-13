#include <iostream>

template< class T, size_t K >
struct BTree {
  T val[K];
  BTree< T, K > * childs[K + 1];
  BTree< T, K > * parent;
};

template< class T, size_t K >
struct BTreeIt {
  size_t s;
  BTree< T, K > * current;
};

template< class T, size_t K >
T value(BTreeIt< T, K > it)
{
  return it.current->val[it.s];
}

template< class T, size_t K >
BTree< T, K > * minimum(BTree< T, K > * root)
{
  if (!root) {
    return nullptr;
  }
  while (root->childs[0]) {
    root = root->childs[0];
  }
  return root;
}

template< class T, size_t K >
BTree< T, K > * maximum(BTree< T, K > * root)
{
  if (!root) {
    return nullptr;
  }
  while (root->childs[K]) {
    root = root->childs[K];
  }
  return root;
}

template< class T, size_t K >
BTreeIt< T, K > next(BTreeIt< T, K > it)
{
  BTree< T, K > * next = it.current;
  size_t s = it.s;
  if (!next) {
    return it;
  }

  if (s < K - 1) {
    if (next->childs[s + 1]) {
      next = next->childs[s + 1];
      next = minimum(next);
      s = 0;
    } else {
      ++s;
    }
  } else {
    if (next->childs[s + 1]) {
      next = next->childs[s + 1];
      next = minimum(next);
      s = 0;
    } else {
      BTree< T, K > * parent = next->parent;
      while (parent) {
        if (parent->childs[K] != next) {
          for (size_t i = 0; i < K; ++i) {
            if (parent->childs[i] == next) {
              s = i;
              break;
            }
          }
          break;
        }
        next = parent;
        parent = next->parent
      }
      next = parent;
    }
  }
  return {s, next};
}

template< class T, size_t K >
BTreeIt< T, K > prev(BTreeIt< T, K > it)
{
  BTree< T, K > * next = it.current;
  size_t s = it.s;
  if (!next) {
    return it;
  }

  if (s != 0) {
    if (next->childs[s]) {
      next = next->childs[s];
      next = maximum(next);
      s = K - 1;
    } else {
      --s;
    }
  } else {
    if (next->childs[0]) {
      next = next->childs[0];
      next = maximum(next);
      s = K - 1;
    } else {
      BTree< T, K > * parent = next->parent;
      while (parent) {
        if (parent->childs[0] != next) {
          for (size_t i = K; i > 0; --i) {
            if (parent->childs[i] == next) {
              s = i - 1;
              break;
            }
          }
          break;
        }
        next = parent;
        parent = next->parent
      }
      next = parent;
    }
  }
  return {s, next};
}

template< class T, size_t K >
bool hasNext(BTreeIt< T, K > it)
{
  return next(it).current;
}

template< class T, size_t K >
bool hasNext(BTreeIt< T, K > it)
{
  return prev(it).current;
}

int main()
{}
