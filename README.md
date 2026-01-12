# 🍳 Recipe Manager CLI (C++17)

A **terminal-based Recipe Management & Cooking Assistant** built in **C++17**.
This project allows users to **add, store, search, cook, delete, and get recipe suggestions** based on available ingredients — all directly from the command line.

This is a **portfolio‑ready project** demonstrating file handling, STL usage, parsing, timers, and clean program structure in C++.

---

## ✨ Features

* 📁 **File-based storage** (each recipe saved as a `.txt` file)
* ➕ Add new recipes with ingredients & steps
* 📋 View all saved recipes
* 🔍 Search recipes by name
* ❌ Delete recipes
* 👨‍🍳 **Cook mode** with step-by-step guidance
* ⏱️ Automatic **cooking timer** detection (minutes/seconds)
* 🧠 **Recipe suggestions** based on ingredients you have
* 📊 Match percentage calculation
* 💻 Cross-platform (Windows / macOS / Linux)

---

## 🛠️ Technologies Used

* **Language:** C++ (C++17 standard)
* **Libraries:**

  * `<filesystem>` for recipe storage
  * `<chrono>` & `<thread>` for timers
  * STL containers (`vector`, `set`, `algorithm`)

---

## 📂 Project Structure

```text
📁 Recipe-Manager-CLI/
│
├── recipeManager.cpp   # Main source file
└── README.md           # Project documentation
```

Each recipe is stored as an individual `.txt` file, making the system simple and transparent.

---

## ⚙️ Compilation & Execution

### 🔹 Requirements

* C++17 compatible compiler (GCC / Clang / MSVC)

### 🔹 Compile

```bash
g++ -std=c++17 recipeManager.cpp -o recipeManager
```

### 🔹 Run

```bash
./recipeManager
```

(On Windows, run `recipe.exe`)

---

## 📖 How It Works

### ➕ Add Recipe

* Enter recipe name
* Enter comma-separated ingredients
* Add cooking steps (type `done` to finish)

### 👨‍🍳 Cook Recipe

* Displays ingredients
* Walks through each step
* Detects time (e.g., `5 minutes`, `30 seconds`)
* Optional countdown timer

### 🧠 Suggest Recipes

* Enter ingredients you currently have
* Program calculates **match percentage**
* Recipes sorted by best match

---

## 🧪 Example Recipe File Format

```text
Name: Pasta

Ingredients: Pasta,Tomato Sauce,Garlic,Olive Oil

Step 1: Boil pasta for 10 minutes

Step 2: Prepare sauce for 5 minutes
```

---

## 📌 Learning Outcomes

This project demonstrates:

* File handling with `fstream`
* Directory traversal using `std::filesystem`
* Robust string parsing
* STL algorithms & containers
* Time-based operations using `chrono`
* Clean menu-driven CLI design

---

## 🤝 Contributing

Contributions, suggestions, and improvements are welcome!

1. Fork the repository
2. Create a new branch
3. Commit your changes
4. Open a Pull Request

---

## 📜 License

This project is open-source and available under the **MIT License**.

---

## 👤 Author

**Taaha omer**
Computer Science Student | C++ Enthusiast

---

⭐ If you like this project, consider giving it a star on GitHub!
