# Changes.md

## 1. Replace lambda-based deletion

### Reason

The original `ScopeTable::Delete()` relied on a lambda expression and `mylist::remove_if()`. To simplify the implementation and avoid lambda functions, move the deletion logic into the `mylist` class.

### Changes

#### Add to `mylist`

```cpp
bool remove(const string& key, int& pos) {
    Node* curr = head;
    Node* prev = nullptr;
    pos = 1;

    while (curr) {
        if (curr->data.getName() == key) {
            if (prev)
                prev->next = curr->next;
            else
                head = curr->next;

            delete curr;
            return true;
        }

        prev = curr;
        curr = curr->next;
        pos++;
    }

    return false;
}
```

#### Update `ScopeTable::Delete()`

Replace the existing implementation with:

```cpp
bool Delete(string name) {
    unsigned int hash = SDBMHash(name);
    int bucketIdx = hash + 1;
    int pos;

    if (table[hash].remove(name, pos)) {
        out << "\tDeleted '" << name
            << "' from ScopeTable# " << scope_id
            << " at position " << bucketIdx
            << ", " << pos << endl;
        return true;
    }

    out << "\tNot found in the current ScopeTable" << endl;
    return false;
}
```

### Benefits

* Removes lambda expressions.
* Keeps all linked-list manipulation inside `mylist`.
* Improves encapsulation.
* Makes `ScopeTable::Delete()` shorter and easier to read.

---

## 2. Use more readable constructors

### Reason

Prefer readability over constructor initializer lists.

### Changes

Replace constructors such as:

```cpp
SymbolInfo(string name, string type, string extraInfo = "")
    : name(name), type(type), extraInfo(extraInfo) {}
```

with

```cpp
SymbolInfo(string name, string type, string extraInfo = "") {
    this->name = name;
    this->type = type;
    this->extraInfo = extraInfo;
}
```

Apply the same style to constructors in `ScopeTable`, `SymbolTable`, and other classes where appropriate.

### Benefits

* Easier for beginners to read.
* Makes member assignments explicit.
* Consistent constructor style throughout the project.

---

## 3. Remove unused `mylist` functions

After introducing `mylist::remove()`, several functions become unused.

### Remove

```cpp
template <typename Pred>
Node* find_if(Pred pred);
```

```cpp
template <typename Pred>
bool remove_if(Pred pred);
```

```cpp
Node* getHead();
```

### Keep

* `begin()`
* `end()`
* `push_back()`
* `for_each()`
* `remove()`
* Copy constructor
* Copy assignment operator
* Destructor

### Benefits

* Eliminates dead code.
* Simplifies the linked-list implementation.
* Makes the public interface smaller and easier to understand.
