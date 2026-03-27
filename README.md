# Library-Management-System-C


A comprehensive, console-based Library Management System developed using the C programming language. This project simulates a real-world library environment where multiple entities like students, authors, books, and borrowing activities are tracked and managed efficiently.

* **File-Based Architecture:** All data is stored persistently in external `.csv` files (dynamically loaded and saved during execution).
* **Dynamic Memory Management:** Utilizes pointers and linked lists for efficient data handling without relying on global or static variables.
* **Student Management:** Register students and track their penalty points. (Students with 0 points are restricted from borrowing).
* **Book & Author Operations:** Add, edit, delete, and link books to their respective authors using ISBNs.
* **Borrowing System:** Safely borrow and return books. The system automatically calculates penalties for late returns based on current date inputs and updates borrowing logs.

## Technologies Used
* **Language:** C
* **Concepts:** Structs, Pointers, Linked Lists, File I/O (CSV parsing), Dynamic Memory Allocation.

## File Structure
* `main.c` - The core application containing the business logic and user interface menus.
* `books.csv` - Stores book details, ISBNs, and available copies.
* `yazarlar.csv` / `KitapYazar.csv` - Stores author profiles and maps books to their authors.
* `Ogrenciler.csv` - Contains student records and their current standing (points).
* `log.csv` - Historical logs of all borrowing and returning transactions.

## How to Run
1. Clone this repository to your local machine:
   ```bash
   git clone [https://github.com/YourUsername/Library-Management-System-C.git](https://github.com/YourUsername/Library-Management-System-C.git)
