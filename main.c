#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

typedef struct Author{
	char name[MAX];
	char surename[MAX];
	int id;
	struct Author *next;
	}Author;

 typedef struct student{
 	char name[MAX];
 	char surename[MAX];
 	int points;
 	int stdNumber;
 	struct student* next;
 	struct student* prev;
 }Student;

typedef struct copy {
    char labelNumber[15];
    int ownerId;
    int available;
    struct copy* next;
} Copy;

typedef struct book{
	char name[MAX];
    char isbn[13];
    int copyCount;
    struct book *next;
    struct copy *copies;
}Book;

typedef struct date{
	int day;
	int month;
	int year;
}Date;

typedef struct borrowSystem {
    int stdId;
    char labelNumber[20]; 
    int operation;          
    Date date;
} BorrowSystem;


typedef struct BookAuthor{
	char isbn[20];
	int authorId;
}BookAuthor;

Author* findAuthor(Author* head, int idNumber);
Student* findStudent(Student* head, int stdNumber);
Book* findBook(Book* head, char isbn[]);
Date inputDate();
int daysBetween(Date d1, Date d2);
void printCopy(Copy* head);

Author* registerAuthor(Author* head, int count){
	Author* newAuthor = (Author*)malloc(sizeof(Author));
	newAuthor->next = NULL;
	char name[MAX];
	char surename[MAX];
	printf("Enter the name of the author: \n");
	scanf("%s", newAuthor->name);
	printf("Enter the surename of the author: \n");
	scanf("%s", newAuthor->surename);
	newAuthor->id  = count+1;
	if(head==NULL){
		head = newAuthor;
		return head;
	}
	else{
		Author* temp = head;
		while(temp ->next !=NULL){
			temp = temp->next;
		}
		temp->next = newAuthor;
		return head;
	}
}

void deleteAuthor(Author** head, BookAuthor* links, int linkCount) {
    printf("Enter the ID of the author you want to delete: ");
    int nrId, i;
    int updated = 0;
    scanf("%d", &nrId);

    Author* temp = *head;
    Author* prev = NULL;

    while (temp != NULL) {
        if (temp->id == nrId) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("Author with ID %d deleted successfully.\n", nrId);


            for (i = 0; i < linkCount; i++) {
                if (links[i].authorId == nrId) {
                    links[i].authorId = -1;
                    updated++;
                }
            }
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("? Author with ID %d not found.\n", nrId);
}



Author* editAuthor(Author* head) {
    printf("Enter the ID of the author you want to edit:\n");
    int nrId;
    scanf("%d", &nrId);
    Author* author = findAuthor(head, nrId);
    if (author == NULL) {
        printf("Author not found!\n");
        return head;
    }
    printf("Enter new name or press 0 to keep to same ");
    char newName[MAX];
    scanf("%s", newName);
    if (strcmp(newName, "0") != 0) {
        strcpy(author->name, newName);
    }

    printf("Enter new surname or press 0 to keep same: ");
    char newSurname[MAX];
    scanf("%s", newSurname);
    if (strcmp(newSurname, "0") != 0) {
      strcpy(author->surename, newSurname);

    }

    printf("Author updated successfully!\n");
    return head;
}
Author* findAuthor(Author* head, int idNumber) {
    Author* temp = head;
    while (temp != NULL) {
        if (temp->id == idNumber) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void listAuthors(Author* head){
	printf("LIST OF AUTHORS REGISTERED...\n");
	if(head == NULL){
		printf("There are no authors registered :( \n");
	}
	Author* temp = head;
	while(temp!= NULL){
		printf("ID %d ", temp->id);
		printf("NAME : %s ", temp->name);
		printf("%s" , temp ->surename);
		printf("\n");
		temp= temp->next;
	}
}
void saveAuthorsToFile(Author* head) {
    FILE* file = fopen("yazarlar.csv", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    Author* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s\n", temp->id, temp->name, temp->surename);
        temp = temp->next;
    }
    fclose(file);
}
Author* loadAuthorsFromFile(int* count) {
    FILE* file = fopen("yazarlar.csv", "r");
    if (file == NULL) {
        printf("No existing authors found. Starting fresh.\n");
        return NULL;
    }

    Author* head = NULL;
    Author* tail = NULL;

    while (!feof(file)) {
        Author* newAuthor = (Author*)malloc(sizeof(Author));
        if (fscanf(file, "%d,%[^,],%s\n", &newAuthor->id, newAuthor->name, newAuthor->surename) == 3) {
            newAuthor->next = NULL;
            if (head == NULL) {
                head = newAuthor;
                tail = newAuthor;
            } else {
                tail->next = newAuthor;
                tail = newAuthor;
            }

            if (newAuthor->id > *count) {
                *count = newAuthor->id;
            }
        } else {
            free(newAuthor);
        }
    }

    fclose(file);
    return head;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Student* findStudent(Student* head, int stdNumber) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->stdNumber == stdNumber) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

Student* registerStudent(Student* head, int stdNumber) {
    if (findStudent(head, stdNumber) != NULL) {
        printf("A student with number %d already exists! Registration canceled.\n", stdNumber);
        return head;
    }

    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter name: ");
    scanf("%s", newStudent->name);
    printf("Enter surname: ");
    scanf("%s", newStudent->surename);

    newStudent->points = 100;
    newStudent->stdNumber = stdNumber;
    newStudent->next = NULL;
    newStudent->prev = NULL;

    if (head == NULL) {
        return newStudent;
    } else {
        Student* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
        newStudent->prev = temp;
        return head;
    }
}

Student* deleteStudent(Student* head) {
    printf("Enter the student number to delete: ");
    int stdNumber;
    scanf("%d", &stdNumber);

    Student* student = findStudent(head, stdNumber);
    if (student == NULL) {
        printf("Student not found.\n");
        return head;
    }

    if (student->prev != NULL) {
        student->prev->next = student->next;
    } else {
        head = student->next;
    }

    if (student->next != NULL) {
        student->next->prev = student->prev;
    }

    free(student);
    printf("Student deleted successfully.\n");
    return head;
}
void listStudents(Student* head) {
    printf("\nLIST OF STUDENTS:\n");
    if (head == NULL) {
        printf("No students registered.\n");
        return;
    }

    Student* temp = head;
    while (temp != NULL) {
        printf("Student No: %d | Name: %s %s | Points: %d\n", temp->stdNumber, temp->name, temp->surename, temp->points);
        temp = temp->next;
    }
}

Student* editStudent(Student* head) {
    printf("Enter student number to edit: ");
    int stdNumber;
    scanf("%d", &stdNumber);

    Student* student = findStudent(head, stdNumber);

    if (student == NULL) {
        printf("Student not found.\n");
        return head;
    }

    printf("Enter new name or 0 to keep the same: ");
    char newName[MAX];
    scanf("%s", newName);
    if (strcmp(newName, "0") != 0) {
        strcpy(student->name, newName);
    }

    printf("Enter new surname or 0 to keep the same: ");
    char newSurname[MAX];
    scanf("%s", newSurname);
    if (strcmp(newSurname, "0") != 0) {
        strcpy(student->surename, newSurname);
    }

    printf("Student updated successfully.\n");
    return head;
}
void listPenalizedStudents(Student* head) {
    int found = 0;
    printf("\nPenalized Students (Points < 0):\n");
    while (head != NULL) {
        if (head->points < 0) {
            printf("Student No: %d | Name: %s %s | Points: %d\n",
                   head->stdNumber, head->name, head->surename, head->points);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("No penalized students.\n");
}

void saveStudentsToFile(Student* head) {
    FILE* file = fopen("Ogrenciler.csv", "w");
    if (file == NULL) {
        printf("Error opening Ogrenciler.csv for writing.\n");
        return;
    }

    Student* temp = head;
    while (temp != NULL) {
        fprintf(file, "%d,%s,%s,%d\n", temp->stdNumber, temp->name, temp->surename, temp->points);
        temp = temp->next;
    }

    fclose(file);
}
Student* loadStudentsFromFile() {
    FILE* file = fopen("Ogrenciler.csv", "r");
    if (file == NULL) {
        printf("No existing students found. Starting fresh.\n");
        return NULL;
    }

    Student* head = NULL;
    Student* tail = NULL;

    while (!feof(file)) {
        Student* newStudent = (Student*)malloc(sizeof(Student));
        if (fscanf(file, "%d,%[^,],%[^,],%d\n", &newStudent->stdNumber, newStudent->name, newStudent->surename, &newStudent->points) == 4) {
            newStudent->next = NULL;
            newStudent->prev = NULL;

            if (head == NULL) {
                head = newStudent;
                tail = newStudent;
            } else {
                tail->next = newStudent;
                newStudent->prev = tail;
                tail = newStudent;
            }
        } else {
            free(newStudent);
        }
    }

    fclose(file);
    return head;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Book* registerBook(Book* head, int count) {
    char isbn[20];
    printf("Enter ISBN number of the book: \n");
    scanf("%s", isbn);

    if (findBook(head, isbn) != NULL) {
        printf("A book with ISBN %s already exists so not able to register\n", isbn);
        return head;
    }

    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    newBook->next = NULL;
    strcpy(newBook->isbn, isbn);
    printf("Enter the name of the book: \n");
    scanf("%s", newBook->name);
    printf("Enter how many copies the book has: \n");
    scanf("%d", &newBook->copyCount);

    newBook->copies = NULL;
    Copy* last = NULL;
    int i;
	for (i = 0; i < newBook->copyCount; i++) {
        Copy* newCopy = (Copy*)malloc(sizeof(Copy));
        sprintf(newCopy->labelNumber, "%s_%d", isbn, i + 1);
        newCopy->ownerId = 0;
        newCopy->available = 1;
        newCopy->next = NULL;

        if (newBook->copies == NULL) {
            newBook->copies = newCopy;
        } else {
            last->next = newCopy;
        }
        last = newCopy;
    }

    if (head == NULL) {
        return newBook;
    } else {
        Book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
        return head;
    }
}

Book* findBook(Book* head, char isbn[]) {
    Book* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void listBooks(Book* head) {
    if (head == NULL) {
        printf("No books registered.\n");
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        printf("\n-----------------------------\n");
        printf("Book Name      : %s\n", temp->name);
        printf("ISBN           : %s\n", temp->isbn);
        printf("Copy Count     : %d\n", temp->copyCount);
        printf("Copies Info:\n");

        printCopy(temp->copies);
        temp = temp->next;
    }
}
Book* deleteBook(Book* head) {
    char isbn[20];
    printf("Enter the ISBN of the book to delete: ");
    scanf("%s", isbn);

    Book* temp = head;
    Book* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            Copy* copy = temp->copies;
            while (copy != NULL) {
                Copy* toDelete = copy;
                copy = copy->next;
                free(toDelete);
            }

            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }

            free(temp);
            printf("Book deleted successfully.\n");
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Book not found.\n");
    return head;
}


void printCopy(Copy* head) {
    Copy* temp = head;
    if (temp == NULL) {
        printf("No copies available.\n");
        return;
    }
    while (temp != NULL) {
        printf(" - Label Number: %s\n", temp->labelNumber);
        if (temp->ownerId == 0)
            printf("   Owner       : Rafta\n");
        else
            printf("   Owner       : Student ID %d\n", temp->ownerId);
        printf("   Available   : %s\n", temp->available ? "Yes" : "No");
        temp = temp->next;
    }
}
void addCopies(Book* head) {
    char isbn[20];
    int n, i;
    printf("Enter the ISBN of the book to add copies: ");
    scanf("%s", isbn);

    Book* book = findBook(head, isbn);
    if (book == NULL) {
        printf("Book not found.\n");
        return;
    }

    printf("Enter number of copies to add: ");
    scanf("%d", &n);

    int startingIndex = book->copyCount + 1;
    Copy* last = book->copies;

    if (last != NULL) {
        while (last->next != NULL) {
            last = last->next;
        }
    }

    for (i = 0; i < n; i++) {
        Copy* newCopy = (Copy*)malloc(sizeof(Copy));
        if (newCopy == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        snprintf(newCopy->labelNumber, sizeof(newCopy->labelNumber), "%s_%d", book->isbn, startingIndex + i);
        newCopy->ownerId = 0;
        newCopy->available = 1;
        newCopy->next = NULL;

        if (book->copies == NULL) {
            book->copies = newCopy;
        } else {
            last->next = newCopy;
        }
        last = newCopy;
        book->copyCount++;
    }
    printf("%d copies added successfully.\n", n);
}

void deleteCopy(Book* head) {
    char isbn[20], label[20];
    printf("Enter the ISBN of the book: ");
    scanf("%s", isbn);
    printf("Enter the label number of the copy to delete: ");
    scanf("%s", label);

    Book* book = findBook(head, isbn);
    if (book == NULL) {
        printf("Book not found.\n");
        return;
    }

    Copy* temp = book->copies;
    Copy* prev = NULL;

    while (temp != NULL) {
        if (strcmp(temp->labelNumber, label) == 0) {
            if (prev == NULL) {
                book->copies = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            book->copyCount--;
            printf("Copy deleted successfully.\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Copy not found.\n");
}
Book* editBook(Book* head) {
    printf("Enter the ISBN of the book to edit: ");
    char isbn[20];
    scanf("%s", isbn);

    Book* book = findBook(head, isbn);
    if (book == NULL) {
        printf("Book not found.\n");
        return head;
    }
    printf("Enter new name of the book or 0 to keep the same: ");
    char newName[MAX];
    scanf("%s", newName);
    if (strcmp(newName, "0") != 0) {
        strcpy(book->name, newName);
    }
    printf("Book updated successfully.\n");
    return head;
}
void showBookDetails(Book* bookList) {
    char isbn[20];
    int found = 0;

    printf("Enter book ISBN to search: ");
    scanf("%s", isbn);

    Book* temp = bookList;
    while (temp != NULL) {
        if (strcmp(temp->isbn, isbn) == 0) {
            printf("\nBook Found:\n");
            printf("Name: %s\n", temp->name);
            printf("ISBN: %s\n", temp->isbn);
            printf("Copy Count: %d\n", temp->copyCount);
            printCopy(temp->copies);
            found = 1;
        }
        temp = temp->next;
    }

    if (!found)
        printf("Book not found.\n");
}

void saveBooksToFile(Book* head) {
    FILE* file = fopen("books.csv", "w");
    if (!file) {
        printf("Error opening books.csv for writing.\n");
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s,%s,%d\n", temp->isbn, temp->name, temp->copyCount);

        Copy* copy = temp->copies;
        while (copy != NULL) {
            fprintf(file, "COPY,%s,%d,%d\n", copy->labelNumber, copy->ownerId, copy->available);
            copy = copy->next;
        }

        temp = temp->next;
    }
    fclose(file);
}
Book* loadBooksFromFile() {
    FILE* file = fopen("books.csv", "r");
    if (!file) {
        printf("No books.csv found.\n");
        return NULL;
    }

    Book* head = NULL;
    Book* tail = NULL;
    char line[128];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "COPY", 4) != 0) {
            Book* newBook = (Book*)malloc(sizeof(Book));
            newBook->copies = NULL;
            newBook->next = NULL;
            sscanf(line, "%[^,],%[^,],%d\n", newBook->isbn, newBook->name, &newBook->copyCount);

            if (head == NULL) {
                head = tail = newBook;
            } else {
                tail->next = newBook;
                tail = newBook;
            }
        } else {
            Copy* newCopy = (Copy*)malloc(sizeof(Copy));
            sscanf(line, "COPY,%[^,],%d,%d\n", newCopy->labelNumber, &newCopy->ownerId, &newCopy->available);
            newCopy->next = NULL;

            if (tail->copies == NULL) {
                tail->copies = newCopy;
            } else {
                Copy* c = tail->copies;
                while (c->next != NULL)
                    c = c->next;
                c->next = newCopy;
            }
        }
    }

    fclose(file);
    return head;
}

////////////////////////////////////////////////////////////////////////////////////////////


BookAuthor* createRelationship(BookAuthor* array, Author* authorHead, int* count, int* capacity, char isbn[],Book* bookList) {
    int n, i;
    if (findBook(bookList, isbn) == NULL) {
        printf("Book with ISBN '%s' does not exist. Relationship creation cancelled.\n", isbn);
        return array;
    }

    printf("Enter how many authors wrote this book: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        int authorId;
        printf("Enter author ID #%d: ", i + 1);
        scanf("%d", &authorId);


        if (*count >= *capacity) {
            *capacity = (*capacity == 0) ? 10 : (*capacity * 2);
            array = realloc(array, (*capacity) * sizeof(BookAuthor));
            if (array == NULL) {
                printf("? Memory allocation failed.\n");
                exit(1);
            }
        }


        if (findAuthor(authorHead, authorId) == NULL) {
            printf("Author with ID %d does not exist. Skipping this author.\n", authorId);
            continue;
        }

        array[*count].authorId = authorId;
        strcpy(array[*count].isbn, isbn);
        (*count)++;
    }

    printf("Relationship(s) created successfully.\n");
    return array;
}

void showAuthorDetails(Author* authorList, BookAuthor* links, int linkCount, Book* bookList) {
    int id,i;
    printf("Enter author ID: ");
    scanf("%d", &id);

    Author* a = findAuthor(authorList, id);
    if (a == NULL) {
        printf("Author not found.\n");
        return;
    }

    printf("Author: %s %s | ID: %d\n", a->name, a->surename, a->id);
    printf("Books written:\n");
    int found = 0;
    for ( i = 0; i < linkCount; i++) {
        if (links[i].authorId == id) {
            Book* b = findBook(bookList, links[i].isbn);
            if (b != NULL) {
                printf("- %s (ISBN: %s)\n", b->name, b->isbn);
                found = 1;
            }
        }
    }
    if (!found)
        printf("No books found for this author\n");
}


void saveBookAuthorToFile(BookAuthor* arr, int count) {
    FILE* f = fopen("KitapYazar.csv", "w");
    if (!f) {
        printf("Couldn't open KitapYazar.csv\n");
        return;
    }
    int i;
    for (i = 0; i < count; i++) {
        fprintf(f, "%s,%d\n", arr[i].isbn, arr[i].authorId);
    }

    fclose(f);
    printf("BookAuthor links saved to KitapYazar.csv\n");
}

BookAuthor* updateBookAuthors(BookAuthor* links, Author* authorList, int* count, int* capacity, char isbn[],Book* bookList) {

    int i;
    for (i = 0; i < *count; i++) {
        if (strcmp(links[i].isbn, isbn) == 0) {
            links[i].authorId = -1;
        }
    }

    printf("Updating authors for book with ISBN %s \n", isbn);
    return createRelationship(links, authorList, count, capacity, isbn,bookList);
}

BookAuthor* loadBookAuthorFromFile(int* count, int* capacity) {
    FILE* f = fopen("KitapYazar.csv", "r");
    if (!f) {
        printf("No KitapYazar.csv file found. Starting fresh.\n");
        *count = 0;
        *capacity = 10;
        return malloc(*capacity * sizeof(BookAuthor));
    }

    *count = 0;
    *capacity = 10;
    BookAuthor* arr = malloc(*capacity * sizeof(BookAuthor));

    while (!feof(f)) {
        if (*count >= *capacity) {
            *capacity *= 2;
            arr = realloc(arr, *capacity * sizeof(BookAuthor));
        }
        fscanf(f, "%[^,],%d\n", arr[*count].isbn, &arr[*count].authorId);
        (*count)++;
    }

    fclose(f);
    return arr;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Date inputDate() {
    Date d;
    printf("Enter day: ");
    scanf("%d", &d.day);
    printf("Enter month: ");
    scanf("%d", &d.month);
    printf("Enter year: ");
    scanf("%d", &d.year);
    return d;
}
int dateToDays(Date d) {
    return d.year * 365 + d.month * 30 + d.day;
}
int daysBetween(Date d1, Date d2) {
    int days1 = dateToDays(d1);
    int days2 = dateToDays(d2);
    return abs(days2 - days1);
}

void borrowBook(Student* studentList, Book* bookList, BorrowSystem* logs, int* logCount, int* logCapacity) {
    int stdNumber;
    char label[20];

    printf("Enter student number: ");
    scanf("%d", &stdNumber);

    Student* student = findStudent(studentList, stdNumber);
    if (student == NULL || student->points < 0) {
        printf("Student not found or has negative points.\n");
        return;
    }

    printf("Enter label number of the copy (e.g., ISBN_1): ");
    scanf("%s", label);

    Copy* foundCopy = NULL;
    Book* book = bookList;
    while (book != NULL) {
        Copy* copy = book->copies;
        while (copy != NULL) {
            if (strcmp(copy->labelNumber, label) == 0 && copy->available == 1) {
                foundCopy = copy;
                copy = NULL; 
            } else {
                copy = copy->next;
            }
        }
        if (foundCopy == NULL) {
            book = book->next;
        } else {
            book = NULL;  // ndal loopin e jashtëm
        }
    }

    if (foundCopy == NULL) {
        printf("Copy not available or not found.\n");
        return;
    }

    Date d = inputDate();
    foundCopy->available = 0;
    foundCopy->ownerId = stdNumber;

    if (*logCount >= *logCapacity) {
        *logCapacity *= 2;
        logs = realloc(logs, (*logCapacity) * sizeof(BorrowSystem));
    }

    logs[*logCount].stdId = stdNumber;
    strcpy(logs[*logCount].labelNumber, foundCopy->labelNumber);
    logs[*logCount].operation = 0;
    logs[*logCount].date = d;
    (*logCount)++;

    printf("Book copy borrowed successfully by student %d on %02d.%02d.%d.\n", stdNumber, d.day, d.month, d.year);
    saveBooksToFile(bookList);

}

void returnBook(Student* studentList, Book* bookList, BorrowSystem* logs, int* logCount, int* logCapacity) {
    int stdNumber;
    char label[20];

    printf("Enter student number: ");
    scanf("%d", &stdNumber);

    Student* student = findStudent(studentList, stdNumber);
    if (student == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter label number (e.g., ISBN_1): ");
    scanf("%s", label);

    Copy* foundCopy = NULL;
    Book* book = bookList;
    while (book != NULL) {
        Copy* copy = book->copies;
        while (copy != NULL) {
            if (strcmp(copy->labelNumber, label) == 0 &&
                copy->available == 0 &&
                copy->ownerId == stdNumber) {
                foundCopy = copy;
                copy = NULL;
            } else {
                copy = copy->next;
            }
        }
        if (foundCopy == NULL) {
            book = book->next;
        } else {
            book = NULL;
        }
    }

    if (foundCopy == NULL) {
        printf("This copy is not borrowed by student %d.\n", stdNumber);
        return;
    }

    Date returnDate = inputDate();
    Date borrowDate = {0, 0, 0};
    int i = *logCount - 1;
    int foundBorrow = 0;

    while (i >= 0 && foundBorrow == 0) {
        if (logs[i].stdId == stdNumber &&
            strcmp(logs[i].labelNumber, label) == 0 &&
            logs[i].operation == 0) {
            borrowDate = logs[i].date;
            foundBorrow = 1;
        }
        i--;
    }

    if (!foundBorrow) {
        printf("Could not find matching borrow record.\n");
        return;
    }

    int delay = daysBetween(borrowDate, returnDate);
    if (delay > 15) {
        student->points -= 10;
        printf("Returned late by %d days. 10 points deducted.\n", delay);
    }

    foundCopy->available = 1;
    foundCopy->ownerId = 0;

    if (*logCount >= *logCapacity) {
        *logCapacity *= 2;
        logs = realloc(logs, (*logCapacity) * sizeof(BorrowSystem));
    }

    logs[*logCount].stdId = stdNumber;
    strcpy(logs[*logCount].labelNumber, label);
    logs[*logCount].operation = 1;
    logs[*logCount].date = returnDate;
    (*logCount)++;

    printf("Book returned successfully on %02d.%02d.%d.\n", returnDate.day, returnDate.month, returnDate.year);
    saveBooksToFile(bookList);
}



void listStudentsThatStillBorrowBook(Book* bookList, Student* studentList) {
    printf("\nStudents currently borrowing books:\n");
    int found = 0;

    while (bookList != NULL) {
        Copy* temp = bookList->copies;
        while (temp != NULL) {
            if (temp->available == 0 && temp->ownerId != 0) {
                Student* student = findStudent(studentList, temp->ownerId);
                if (student != NULL) {
                    printf("Student No: %d | Name: %s %s | Book Label: %s\n",
                           student->stdNumber, student->name, student->surename, temp->labelNumber);
                    found = 1;
                }
            }
            temp = temp->next;
        }
        bookList = bookList->next;
    }

    if (!found) {
        printf("No students currently borrowing books.\n");
    }
}


void showStudentDetails(Student* studentList, BorrowSystem* logs, int logCount) {
    int id;
    printf("Enter student ID: ");
    scanf("%d", &id);

    Student* s = findStudent(studentList, id);
    if (s == NULL) {
        printf("Student not found.\n");
        return;
    }

    printf("Student: %s %s | ID: %d | Points: %d\n", s->name, s->surename, s->stdNumber, s->points);
    printf("Borrow History:\n");

    int i = 0;
    while (i < logCount) {
        if (logs[i].stdId == id) {
            printf("Copy: %s | Operation: %s | Date: %02d.%02d.%04d\n",
                   logs[i].labelNumber,
                   logs[i].operation == 0 ? "Borrowed" : "Returned",
                   logs[i].date.day, logs[i].date.month, logs[i].date.year);
        }
        i++;
    }
}

void listBooksOnShelf(Book* bookList) {
    printf("\nBooks currently on shelf:\n");
    while (bookList != NULL) {
        Copy* copy = bookList->copies;
        while (copy != NULL) {
            if (copy->available == 1) {
                printf("Book: %s | Label: %s | Status: Available\n", bookList->name, copy->labelNumber);
            }
            copy = copy->next;
        }
        bookList = bookList->next;
    }
}
void listLateReturnedBooks(BorrowSystem* logs, int logCount) {
    printf("\nLate Returned Books (Returned after 15 days):\n");

    int i, j;
    for (i = 0; i < logCount; i++) {
        if (logs[i].operation == 1) {  // nëse është kthim
            int found = 0;
            for (j = i - 1; j >= 0 && found == 0; j--) {
                if (logs[j].operation == 0 &&
                    strcmp(logs[j].labelNumber, logs[i].labelNumber) == 0 &&
                    logs[j].stdId == logs[i].stdId) {
                    
                    int delay = daysBetween(logs[j].date, logs[i].date);
                    if (delay > 15) {
                        printf("Student %d | Copy: %s | Delay: %d days\n",
                               logs[i].stdId, logs[i].labelNumber, delay);
                    }
                    found = 1;
                }
            }
        }
    }
}


void saveLogsToFile(BorrowSystem* logs, int count) {
    FILE* f = fopen("log.csv", "w");
    if (!f) {
        printf("Error opening log.csv\n");
        return;
    }

    int i = 0;
    while (i < count) {
        fprintf(f, "%d,%s,%d,%02d-%02d-%04d\n",
                logs[i].stdId,
                logs[i].labelNumber,
                logs[i].operation,
                logs[i].date.day,
                logs[i].date.month,
                logs[i].date.year);
        i++;
    }

    fclose(f);
}


BorrowSystem* loadLogsFromFile(int* count, int* capacity) {
    FILE* f = fopen("log.csv", "r");
    if (!f) {
        printf("No log.csv found.\n");
        *count = 0;
        *capacity = 10;
        return malloc(*capacity * sizeof(BorrowSystem));
    }

    *count = 0;
    *capacity = 10;
    BorrowSystem* logs = malloc(*capacity * sizeof(BorrowSystem));

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        if (*count >= *capacity) {
            *capacity *= 2;
            logs = realloc(logs, (*capacity) * sizeof(BorrowSystem));
        }

        sscanf(line, "%d,%[^,],%d,%d-%d-%d\n",
               &logs[*count].stdId,
               logs[*count].labelNumber,
               &logs[*count].operation,
               &logs[*count].date.day,
               &logs[*count].date.month,
               &logs[*count].date.year);
        logs[*count].labelNumber[strcspn(logs[*count].labelNumber, "\r\n")] = 0;

        (*count)++;
    }

    fclose(f);
    return logs;
}


///////////////////////////////////////////////////////////////////////////////////////
void freeAuthors(Author* head) {
    Author* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void freeStudents(Student* head) {
    Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void freeCopies(Copy* head) {
    Copy* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void freeBooks(Book* head) {
    Book* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        freeCopies(temp->copies);
        free(temp);
    }
}
void freeBorrowSystem(BorrowSystem* logs) {
    if (logs != NULL) {
        free(logs);
    }
}
void freeBookAuthor(BookAuthor* array) {
    if (array != NULL) {
        free(array);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
typedef void* (*RegisterFunction)(void*, int);
typedef void* (*EditFunction)(void*);
typedef void* (*DeleteFunction)(void*);
void* callRegister(RegisterFunction func, void* list, int val) {
    return func(list, val);
}

void* callEdit(EditFunction func, void* list) {
    return func(list);
}

void* callDelete(DeleteFunction func, void* list) {
    return func(list);
}

int main() {
   
    Author* authorList = NULL;
    Student* studentList = NULL;
    Book* bookList = NULL;
    BookAuthor* bookAuthorLinks = NULL;
    BorrowSystem* borrowLogs = NULL;

    int authorCount = 0;
    int studentCount = 0;
    int bookAuthorCount = 0;
    int bookAuthorCapacity = 0;
    int borrowLogCount = 0;
    int borrowLogCapacity = 10;

    authorList = loadAuthorsFromFile(&authorCount);
    studentList = loadStudentsFromFile();
    bookAuthorLinks = loadBookAuthorFromFile(&bookAuthorCount, &bookAuthorCapacity);
    borrowLogs = loadLogsFromFile(&borrowLogCount, &borrowLogCapacity);
    bookList = loadBooksFromFile();

    int choice;

    do {
        printf("\n**************STUDENT OPERATIONS***************** \n");
        printf("1.  Register Student\n");
        printf("2.  Delete Student\n");
        printf("3.  Edit Student\n");
        printf("4.  Show Student Info\n");
        printf("5.  List Students with Borrowed Books\n");
        printf("6.  List Penalized Students\n");
        printf("7.  List All Students\n");
        printf("8.  Borrow Book\n");
        printf("9.  Return Book\n");

        printf("\n**************BOOK OPERATIONS *******************\n");
        printf("10. Register Book\n");
        printf("11. Delete Book\n");
        printf("12. Edit Book\n");
        printf("13. List Books\n");
        printf("14. Add Book Copies\n");
        printf("15. Delete Copy\n");
        printf("16. List Books on Shelf\n");
        printf("17. List Late Returned Books\n");
        printf("18. Create Book-Author Relationship\n");
        printf("19. Update Authors of a Book\n");

        printf("\n*************AUTHOR OPERATION******************** \n");
        printf("20. Register Author\n");
        printf("21. Delete Author\n");
        printf("22. Edit Author\n");
        printf("23. List Authors\n");
        printf("24. Show Author Details (Books by Author)\n");
        printf("25. Show Book Details\n");

        printf("\n26. Save All and Exit\n");
        printf("=========================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int stdNo;
                printf("Enter student number (8 digits): ");
                scanf("%d", &stdNo);
                studentList = callRegister((RegisterFunction)registerStudent, studentList, stdNo);
                saveStudentsToFile(studentList);
                break;
            }
            case 2:
                studentList = callDelete((DeleteFunction)deleteStudent, studentList);
                saveStudentsToFile(studentList);
                break;
            case 3:
                studentList = callEdit((EditFunction)editStudent, studentList);
                saveStudentsToFile(studentList);
                break;
            case 4:
                showStudentDetails(studentList, borrowLogs, borrowLogCount);
                break;
            case 5:
                 listStudentsThatStillBorrowBook(bookList, studentList);
                break;
            case 6:
                listPenalizedStudents(studentList);
                break;
            case 7:
                listStudents(studentList);
                break;
            case 8:
                borrowBook(studentList, bookList, borrowLogs, &borrowLogCount, &borrowLogCapacity);
                saveLogsToFile(borrowLogs, borrowLogCount);
				break;
            case 9:
                returnBook(studentList, bookList, borrowLogs, &borrowLogCount, &borrowLogCapacity);
                saveLogsToFile(borrowLogs, borrowLogCount);
                saveStudentsToFile(studentList);
                break;

            case 10:
                bookList = callRegister((RegisterFunction)registerBook, bookList, 0);
                saveBooksToFile(bookList);
			    break;
            case 11:
                bookList = callDelete((DeleteFunction)deleteBook, bookList);
                break;
            case 12:
                bookList = callEdit((EditFunction)editBook, bookList);
                break;
            case 13:
                listBooks(bookList);
                break;
            case 14:
                addCopies(bookList);
                break;
            case 15:
                deleteCopy(bookList);
                break;
            case 16:
                listBooksOnShelf(bookList);
                break;
            case 17:
                listLateReturnedBooks(borrowLogs, borrowLogCount);
                break;
            case 18: {
                char isbn[20];
                printf("Enter ISBN to relate authors: ");
                scanf("%s", isbn);
                bookAuthorLinks = createRelationship(bookAuthorLinks, authorList, &bookAuthorCount, &bookAuthorCapacity, isbn,bookList);
                saveBookAuthorToFile(bookAuthorLinks, bookAuthorCount);
                break;
            }
            case 19: {
                char isbn[20];
                printf("Enter ISBN to update authors: ");
                scanf("%s", isbn);
                bookAuthorLinks = updateBookAuthors(bookAuthorLinks, authorList, &bookAuthorCount, &bookAuthorCapacity, isbn,bookList);
                saveBookAuthorToFile(bookAuthorLinks, bookAuthorCount);
                break;
            }

            case 20:
                authorList = callRegister((RegisterFunction)registerAuthor, authorList, authorCount++);
                saveAuthorsToFile(authorList);
                break;
            case 21:
                deleteAuthor(&authorList, bookAuthorLinks, bookAuthorCount);
                saveAuthorsToFile(authorList);
                saveBookAuthorToFile(bookAuthorLinks, bookAuthorCount);
                break;
            case 22:
                authorList = callEdit((EditFunction)editAuthor, authorList);
                saveAuthorsToFile(authorList);
                break;
            case 23:
                listAuthors(authorList);
                break;
            case 24:
                showAuthorDetails(authorList, bookAuthorLinks, bookAuthorCount, bookList);
                break;
            case 25:
                showBookDetails(bookList);
                break;

            case 26:
                printf("Saving data and exiting...\n");
                saveAuthorsToFile(authorList);
                saveStudentsToFile(studentList);
                saveBookAuthorToFile(bookAuthorLinks, bookAuthorCount);
                saveLogsToFile(borrowLogs, borrowLogCount);
                saveBooksToFile(bookList);
				break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 26);

    freeAuthors(authorList);
    freeStudents(studentList);
    freeBooks(bookList);
    freeBookAuthor(bookAuthorLinks);
    freeBorrowSystem(borrowLogs);

    return 0;
}

