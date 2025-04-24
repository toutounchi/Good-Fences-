# 🧮 PA2.1 – Good Fences  
**UBC CPSC Computational Geometry Assignment – Convex Hulls & Polygon Intersections**

## 📌 Overview

This project explores two classic computational geometry problems using C++:

- **Constructing a Convex Hull** using the **Graham Scan** algorithm  
- **Finding the Intersection of Two Convex Polygons** using the **Sutherland–Hodgman** algorithm

The fictional scenario: UBC equips students with laser-bound armbands to keep them near classrooms—like digital cattle. Each department defines a “secure zone” using these algorithms.

## 🎯 Learning Goals

- Implement fundamental geometry algorithms
- Build and use a custom stack data structure
- Apply angle-based sorting in 2D space
- Visualize and calculate intersections between convex polygons
- Practice sketching and geometric reasoning in problem solving

---

## 🧠 Problem Description

Each department at UBC has a set of essential buildings (e.g., classrooms, feeding areas) represented as 2D points. You must:

- **Part 1**: Compute the **Convex Hull** surrounding those buildings (i.e., the laser perimeter).
- **Part 2**: Given two department perimeters (convex polygons), compute their **intersection**.

---

## 📁 Project Structure

good-fences/ ├── stack.cpp / stack.h # Stack implementation (template-based) ├── convexhull.cpp / convexhull.h # Graham Scan-based convex hull functions ├── convexintersection.cpp / .h # Sutherland-Hodgman polygon intersection ├── main.cpp # Optional test/driver file └── README.md # This file

---

## 🧩 Key Algorithms

### 📦 `stack.cpp`
| Function | Description |
|---------|-------------|
| `Push(const T& item)` | Pushes item onto stack |
| `T Pop()` | Removes and returns top item |
| `T Peek()` | Returns top item without removing |
| `bool IsEmpty() const` | Returns true if stack is empty |
| `size_t Capacity() const` | Returns current capacity |
| `size_t Size() const` | Returns number of items |
| `void Resize(size_t n)` | Resizes the stack’s internal container |

---

### 📐 `convexhull.cpp`
| Function | Description |
|----------|-------------|
| `SortByAngle(vector<pair<int,int>>& v)` | Sorts points based on angle from pivot |
| `bool CCW(pair p1, p2, p3)` | Checks if three points make a counter-clockwise turn |
| `vector<pair<int,int>> GetConvexHull(vector<pair<int,int>>& v)` | Computes convex hull from point set |

---

### 🔷 `convexintersection.cpp`
| Function | Description |
|----------|-------------|
| `bool Inside(pair p1, sp1, sp2)` | Checks if point is inside polygon edge |
| `pair ComputeIntersection(...)` | Computes intersection between a segment and an edge |
| `vector<pair<int,int>> GetConvexIntersection(...)` | Returns intersection polygon from two convex inputs |

---

## ⚙️ Implementation Notes

- Input coordinates are all **positive integers**
- Origin `(0, 0)` is **top-left** (like PNG images)
- Treat axes normally: increasing `x` → right, increasing `y` → down
- You can define helper functions within `.cpp` files
- Aim for **efficiency** in both time and memory usage

---

## 🚀 Getting Started

You can get the starter code from your course portal, then move it to your home directory on UBC’s remote Linux environment. Compile using:

```bash
g++ -std=c++17 -Wall -Wextra -o goodfences main.cpp stack.cpp convexhull.cpp convexintersection.cpp

Then, run your test cases or use provided samples from your lab.

📎 References
📚 Graham Scan - Wikipedia

📚 Sutherland–Hodgman Algorithm - Wikipedia

⚠️ Disclaimer
This assignment is for academic learning and practice only. All geometry is simulated and no actual laser-fencing of students is endorsed or implemented.
