# 🧮 Numerical Analysis Method Toolkit in C

A comprehensive, performance-oriented Numerical Analysis Library written entirely in pure C. This project features a custom expression parser using stack data structures to evaluate dynamic mathematical equations, alongside robust implementations of foundational numerical methods for linear algebra, calculus, and root-finding.

---

## 🚀 Core Features & Algorithms Implemented

### 🔢 1. Mathematical Parser Engine
* **Infix-to-Postfix Parser:** Custom stack implementation to convert human-readable mathematical strings into Postfix (Reverse Polish Notation) equations.
* **Function Support:** Parses variables (`x`), constants (`e`), standard operators (`+`, `-`, `*`, `/`, `^`), and advanced functions like trigonometric (sin, cos, tan) and inverse trigonometric actions (arcsin, arccos, arctan).

### 📐 2. Root-Finding Solvers
* **Bisection Method:** Brackets and converges on roots with automated interval validation checks.
* **Regula Falsi (False Position Method):** Implements linear interpolation to approximate roots within specified error margins.
* **Newton-Raphson Method:** Approximates roots efficiently by computing numerical derivatives via forward differences.

### 💼 3. Linear Algebra Core
* **Matrix Inversion ($N \times N$):** Computes determinants and handles structural matrix inversion via minor and cofactor matrices.
* **Cholesky Decomposition:** Decomposes symmetric, positive-definite matrices into a lower triangular matrix ($L$).
* **Gauss-Seidel Iteration:** Iteratively solves linear equation systems with automated row-pivoting to guarantee diagonal dominance.

### 📉 4. Numerical Calculus & Approximation
* **Numerical Differentiation:** Supports Forward, Backward, and Central difference schemes for dynamic mathematical expressions.
* **Numerical Integration:** Offers customizable interval options utilizing **Trapezoidal Rule**, **Simpson's 1/3 Rule**, and **Simpson's 3/8 Rule**.
* **Gregory-Newton Forward Interpolation:** Polynomial interpolation for equally spaced data points.

---

## 🛠️ Tech Stack & Concepts

* **Language:** C (C99 Standard)
* **Core Concepts:** Stack Data Structures, Dynamic Memory Allocation (`malloc`/`calloc`), Numerical Approximation, String Tokenization, and Matrix Manipulation.

---

## 💻 Compilation & Execution

To compile and execute the numerical toolkit using standard C compilers (GCC/Clang):

```bash
# Compile the library
gcc main.c -o numerical_toolkit -lm

# Run the program
./numerical_toolkit