# 🗳️ Voting Management System (C Project)
![C](https://img.shields.io/badge/Language-C-blue.svg)
![Status](https://img.shields.io/badge/Project-Active-success.svg)
![Open Source](https://img.shields.io/badge/Open%20Source-Yes-brightgreen.svg)
![Platform](https://img.shields.io/badge/Platform-Terminal-lightgrey.svg)
![Build](https://img.shields.io/badge/Build-Passing-success.svg)

A **console-based Voting Management System** developed in **C language**, designed to simulate a secure and structured voting process. This project demonstrates core concepts of **C programming**, **data structures**, **file handling basics**, and **user/admin role management** with a professional terminal UI using ANSI colors.

---

## 📌 Project Overview

This project provides two major roles:

* **Admin Panel** – Manage candidates and view election results
* **User Panel** – Allow voters to cast votes securely using a validated College ID

The system ensures:

* One person can vote only once
* Only valid College IDs are accepted
* Results are calculated automatically

---

## 🚀 Features

### 🔐 Admin Panel

* Password-protected access
* Add new candidates
* Delete existing candidates
* View live election results
* Display winner automatically

### 👤 User Panel

* College ID validation (Format: `ABC1234567`)
* Duplicate vote prevention
* Simple candidate selection
* Secure vote casting

### 🎨 User Interface

* ANSI color-coded output
* Styled menus and borders
* Loading animation for better UX

---

## 🧠 Concepts & Technologies Used

* **Programming Language:** C
* **Core Concepts:**

  * Structures (`struct`)
  * Arrays
  * Functions
  * String handling (`string.h`)
  * Conditional statements & loops
* **System Libraries:**

  * `stdio.h`
  * `stdlib.h`
  * `string.h`
  * `unistd.h`
* **Terminal Styling:** ANSI Escape Codes

---

## 🏗️ Data Structures Used

### Candidate Structure

```c
struct Candidate {
    char name[50];
    char symbol[10];
    int votes;
};
```

### Voter Storage

```c
char voted_ids[MAX_VOTERS][20];
```

* Prevents duplicate voting
* Stores up to 100 voter IDs

---

## 🛂 College ID Validation Rules

✔ Exactly **10 characters**
✔ First **3 uppercase letters (A–Z)**
✔ Last **7 digits (0–9)**

Example:

```
ABC1234567
```

---

## ⚙️ How the System Works

1. Program starts with **Main Menu**
2. User selects:

   * Admin Panel
   * User Panel
3. Admin can manage candidates
4. User enters College ID
5. System validates ID
6. Vote is cast securely
7. Results are calculated and displayed

---

## ▶️ How to Compile and Run

### Linux / macOS

```bash
gcc voting_system.c -o voting
./voting
```

> ⚠️ `system("clear")` is Linux/macOS specific

### Windows (Optional Change)

Replace:

```c
system("clear");
```

With:

```c
system("cls");
```

---

## 🔑 Admin Credentials

```text
Username: Admin
Password: ayush123
```

> ⚠️ Password is hardcoded for learning purposes

---

## 🧪 Limitations

* Data is not stored permanently (no file/database)
* Admin password is hardcoded
* Works only in terminal environment

---

## 🔮 Future Enhancements

* File handling for permanent storage
* Encryption for admin password
* Dynamic memory allocation
* Graphical User Interface (GUI)
* Online voting integration
* Result visualization (charts)

---

## 📚 Learning Outcomes

* Practical understanding of C programming
* Hands-on experience with structures and arrays
* Input validation techniques
* Role-based system design
* Console UI design using ANSI codes


---

## ⭐ Acknowledgement

This project is created for **academic and learning purposes**, inspired by real-world voting systems to understand core programming logic and system design.

---


## ✨*If you found this project useful, don’t forget to star ⭐ the repository!*
