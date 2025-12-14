# 🧠 Quiz Game (C++ Console Application)

A **console-based Quiz Game developed in C++**, featuring multiple difficulty levels, a timed question system, and a persistent high-score mechanism.
This project is designed using **basic C++ concepts** and is suitable for **FAST University exams and semester projects**.

---

## 🚀 Features

* 🎯 **Three Difficulty Levels**

  * Easy
  * Medium
  * Hard

* ⏱️ **Timed Questions**

  * Each question has a fixed time limit
  * Unanswered questions are skipped automatically

* 🏆 **High Score System**

  * Stores highest score using file handling
  * Updates when a new record is achieved

* 🔀 **Random Question Selection**

  * Ensures different quiz experience each time

* 📂 **File Handling**

  * Questions and scores stored in external files

* 🖥️ **User-Friendly Console Interface**

---

## 🛠️ Tech Stack

* **Language:** C++
* **IDE:** Visual Studio / VS Code
* **Libraries Used:**

  * `iostream`
  * `fstream`
  * `string`
  * `cstdlib`
  * `ctime`
  * `conio.h`
  * `windows.h`

---

## ⚙️ How It Works

1. User selects a difficulty level
2. Questions are loaded from files
3. Timer starts for each question
4. User answers within the time limit
5. Score is calculated
6. High score is checked and updated
7. Final result is displayed

---

## 📁 Project Structure

```
Quiz-Game/
│
├── main.cpp
├── easy.txt
├── medium.txt
├── hard.txt
├── highscore.txt
└── README.md
```

---

## ▶️ Getting Started

### Prerequisites

* C++ Compiler (GCC / Visual Studio)

### Run the Project

```bash
g++ main.cpp -o quiz
./quiz
```

---

## 📚 Learning Outcomes

* File handling in C++
* Functions and modular programming
* Timer and delay implementation
* Random number generation
* Console-based UI design

---

## 🔮 Future Enhancements

* GUI-based version
* More question categories
* Multiplayer mode
* Online leaderboard

---

## 👨‍💻 Author

**Muhammad Uzair Latif**
FAST University
