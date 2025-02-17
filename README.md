# Data Structures in C (IAL Course)

This project implements **three fundamental data structures** as part of the **IAL (Algorithms)** course:
1. **Binary Search Tree (BST)** (Iterative & Recursive versions)
2. **Hash Table** (Chained Hashing)
3. **Stack-Based Traversal for BST**

Each structure is tested with a **Makefile-based test suite**.

## 📌 Project Overview
- **Language:** C
- **Concepts:** BST, Hash Table, Iterative & Recursive Algorithms
- **Key Features:**
  - **BST insertion, search, and deletion**
  - **Recursive vs. Iterative BST**
  - **Stack-based tree traversal**
  - **Chained Hash Table with collision handling**
  - **Automated test suite with visualization**

## 🏗️ Implemented Data Structures

### **1️⃣ Binary Search Tree (BST)**
| Variant | File | Description |
|---------|------|------------|
| **Iterative BST** | `iter/btree.c` | Avoids recursion, uses stacks |
| **Recursive BST** | `rec/btree.c` | Standard recursive implementation |

#### **BST Functions**
| Function | Description |
|----------|------------|
| `bst_init` | Initializes a BST |
| `bst_search` | Searches for a key |
| `bst_insert` | Inserts a key-value pair |
| `bst_delete` | Deletes a node |
| `bst_replace_by_rightmost` | Replaces a node with the rightmost child |
| `bst_dispose` | Deletes the entire BST |

#### **BST Traversals**
| Function | Description |
|----------|------------|
| `bst_preorder` | Preorder traversal |
| `bst_inorder` | Inorder traversal |
| `bst_postorder` | Postorder traversal |

---

### **2️⃣ Hash Table (`hashtable.c`)**
| Function | Description |
|----------|------------|
| `ht_init` | Initializes the hash table |
| `ht_insert` | Inserts a key-value pair |
| `ht_search` | Searches for a key |
| `ht_get` | Retrieves the value of a key |
| `ht_delete` | Deletes a key |
| `ht_delete_all` | Clears the entire hash table |
| `get_hash` | Hash function |

#### **Hash Table Features**
- **Chained Hashing** to handle collisions
- **Dynamically allocated nodes**
- **Custom hash function**

---

## 🛠 **Testing & Debugging**
This project includes a **test suite** for BST and Hash Table operations.

### **Testing (`test.c`)**
| Function | Description |
|----------|------------|
| `test_tree_insert_root` | Inserts a root node |
| `test_tree_insert_many` | Inserts multiple nodes |
| `test_tree_search` | Searches for a node |
| `test_tree_delete_leaf` | Deletes a leaf node |
| `test_tree_delete_root` | Deletes the root node |
| `test_table_init` | Initializes a hash table |
| `test_insert_simple` | Inserts a hash table entry |
| `test_search_exist` | Searches in hash table |
| `test_delete` | Deletes a hash table entry |

### **Visualization Utilities (`test_util.c`)**
| Function | Description |
|----------|------------|
| `bst_print_tree` | Prints BST structure |
| `ht_print_table` | Prints hash table content |

### **Makefile-Based Testing**
The `Makefile` allows easy compilation and testing:
  ```bash
  make
  ./test
```
## 📁**Project Structure**
```bash
/iter
  ├── btree.c   # Iterative BST
  ├── stack.c   # Stack utilities for BST traversal
  ├── stack.h   # Stack operations
  ├── Makefile  # Compilation script
  ├── test      # Test binary

/rec
  ├── btree.c   # Recursive BST
  ├── Makefile  # Compilation script
  ├── test      # Test binary

/hashtable
  ├── hashtable.c  # Hash table implementation
  ├── hashtable.h  # Hash table header
  ├── Makefile     # Compilation script
  ├── test         # Test binary

/test
  ├── test.c        # BST & Hash Table test cases
  ├── test_util.c   # Debugging utilities
  ├── test_util.h   # Header file for test utilities
  ├── Makefile      # Compilation script
```
## 🚀 **How to Build and Run**
### 1️⃣ **Build and Run BST Tests**
```bash
cd iter
make
./test
```
```bash
cd rec
make
./test
```
### 2️⃣ **Build and Run Hash Table Tests**
```bash
cd hashtable
make
./test
```
### 3️⃣ **Run Full Test Suite**
```bash
cd test
make
./test
```
## 📝 Author
**Dinara Garipova**  
Project for **IAL Course**  

## ⚖️ License
This project is licensed under the **MIT License** – you are free to use, modify, and distribute with attribution.
