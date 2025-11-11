[UTS Struktur Data]

Identitas Pengumpul

Nama: Abu Abdirrahman Humaid Al-Atsaryy

NIM: 103122400020

Kelas: Struktur Data

1. Kode Program

Berikut adalah kode program untuk menyimpan data postingan pada fitur timeline menggunakan struktur data double linked list. Data postingan terdiri dari : ID post, Konten post, jumlah like, dan username.

```File: main.cpp
 * Author: Abu Abdirrahman Humaid Al-Atsary
 * NIM: 103122400020
 * Deskripsi: Program untuk menentukan apakah sebuah bilangan
 * yang diinput oleh user adalah ganjil atau genap.
 */

#include <iostream>
#include "DLL.h"
using namespace std;

int main() {
    List timeline;
    createNewList(timeline);

    infotype post1 = {1, "Hello World!", 5, "user1"};
    infotype post2 = {2, "Learning C++ is fun.", 10, "user2"};
    infotype post3 = {3, "Data Structures are important.", 7, "user1"};
    infotype post4 = {4, "Pointers are tricky.", 3, "user3"};
    infotype post5 = {5, "Memory Management in C++.", 8, "user2"};
    infotype post6 = {6, "Object-Oriented Programming.", 12, "user1"};
    infotype post7 = {7, "Templates and STL.", 4, "user3"};
    infotype post8 = {8, "C++17 Features.", 6, "user2"};
    infotype post9 = {9, "Debugging Techniques.", 9, "user1"};
    infotype post10 = {10, "Best Practices in C++.", 11, "user3"};

    insertPostByID(timeline, createElement(post1));
    insertPostByID(timeline, createElement(post2));
    insertPostByID(timeline, createElement(post3));
    insertPostByID(timeline, createElement(post4));
    insertPostByID(timeline, createElement(post5));
    insertPostByID(timeline, createElement(post6));
    insertPostByID(timeline, createElement(post7));
    insertPostByID(timeline, createElement(post8));
    insertPostByID(timeline, createElement(post9));
    insertPostByID(timeline, createElement(post10));

    cout << "=== Semua Postingan ===" << endl;
    printAllPosts(timeline);
    cout << endl;

    cout << "=== Postingan berdasarkan Username ===" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "=== Postingan oleh user-" << i << " ===" << endl;
        printPostsByUsername(timeline, "user" + to_string(i));
        cout << endl;
    }
    cout << endl;
    
    cout << "\n=== Postingan Terpopuler ===" << endl;
    printMostLikedPost(timeline);

    cout << "\nMengupdate like untuk post ID dengan Postingan Terpopuler (like):" << endl;
    updatePostLikes(timeline, post6, true);
    printMostLikedPost(timeline);

    cout << "\nMengupdate like untuk post ID Postingan Terpopuler (unlike):" << endl;
    updatePostLikes(timeline, post6, false);
    printMostLikedPost(timeline);
    cout << endl;

    cout << "Delete Postingan Pertama dan Terakhir:" << endl;
    address p;
    deleteFirst(timeline, p);
    deleteLast(timeline, p);
    printAllPosts(timeline);
    cout << endl;

    cout << "=== Akhir dari Program ===" << endl;
    return 0;
}
```
```File: DLL.h
#include <iostream>
#include <string>

#define first(L) (L).first
#define last(L) (L).last
#define next(P) (P)->next
#define prev(P) (P)->prev
#define info(P) (P)->info
#define NIL NULL

using namespace std;

typedef struct {
    int id;  
    string content;
    int likes;
    string username;
} infotype;

typedef struct tNode *address;
typedef struct tNode {
    infotype info;
    address next;
    address prev;
} Node;

typedef struct {
    address first;
    address last;
} List;

// Deklarasi fungsi MyTelu
void insertPostByID(List &L, address p);
void printPostsByUsername(List a, string username);
void printMostLikedPost(List a);
void updatePostLikes(List &a, infotype x, bool like);
void printAllPosts(List a);


// Fungsi dasar DLL
address createElement(infotype data);
void createNewList(List &a);
bool isEmpty(List a);
void insertFirst(List &a, address p);
void insertAfter(List &a, infotype x, address p);
void insertLast(List &a, address p);
void deleteFirst(List &a, address &p);
void deleteLast(List &a, address &p);
int length(List a);
address findElement(List a, infotype x);
void printList(List a);

// Fungsi tambahan
void splitList(List a, List &b, List &c);


```

```File: DLL.cpp
#include "DLL.h"
#include <iostream>
using namespace std;

address createElement(infotype data) {
    address p = new Node;
    info(p) = data;
    next(p) = NIL;
    prev(p) = NIL;
    return p;
}

void createNewList(List &L) {
    first(L) = NIL;
    last(L) = NIL;
}

bool isEmpty(List a) {
    return first(a) == NIL && last(a) == NIL;
}

void insertFirst(List &a, address p) {
    if (isEmpty(a)) {
        first(a) = p;
        last(a) = p;
    } else {
        next(p) = first(a);
        prev(first(a)) = p;
        first(a) = p;
    }
}

void insertLast(List &a, address p) {
    if (isEmpty(a)) {
        first(a) = p;
        last(a) = p;
    } else {
        next(last(a)) = p;
        prev(p) = last(a);
        last(a) = p;
    }
}

address findElement(List a, infotype x) {
    address p = first(a);
    while (p != NIL) {
        if (info(p).id == x.id) {
            return p;
        }
        p = next(p);
    }
    return NIL;
}

void insertAfter(List &a, infotype x, address p) {
    address Q = findElement(a, x);
    if (Q != NIL) {
        if (Q == last(a)) {
            insertLast(a, p);
        } else {
            next(p) = next(Q);
            prev(next(Q)) = p;
            next(Q) = p;
            prev(p) = Q;
        }
    } else {
        cout << "Elemen dengan ID " << x.id << " tidak ditemukan" << endl;
    }
}

void printList(List a) {
    address p = first(a);
    if (isEmpty(a)) {
        cout << "List kosong" << endl;
    } else {
        while (p != NIL) {
            cout << info(p).id << " ";
            p = next(p);
        }
        cout << endl;
    }
}

void insertPostByID(List &L, address p) {
    if (isEmpty(L)) {
        insertFirst(L, p);
    } else {
        address q = first(L);
        while (q != NIL && info(q).id < info(p).id) {
            q = next(q);
        }
        if (q == first(L)) {
            insertFirst(L, p);
        } else if (q == NIL) {
            insertLast(L, p);
        } else {
            insertAfter(L, info(prev(q)), p);
        }
    }
}


void printPostsByUsername(List a, string username) {
    address p = first(a);
    while (p != NIL) {
        if (info(p).username == username) {
            cout << "ID: " << info(p).id
                 << ", Konten: " << info(p).content
                 << ", Likes: " << info(p).likes << endl;
        }
        p = next(p);
    }
}

void printMostLikedPost(List a) {
    address p = first(a);
    address mostLiked = NIL;
    while (p != NIL) {
        if (mostLiked == NIL || info(p).likes > info(mostLiked).likes) {
            mostLiked = p;
        }
        p = next(p);
    }
    if (mostLiked != NIL) {
        cout << "ID: " << info(mostLiked).id
             << ", Konten: " << info(mostLiked).content
             << ", Likes: " << info(mostLiked).likes << endl;
    }
}


void updatePostLikes(List &a, infotype x, bool like) {
    address p = findElement(a, x);
    if (p != NIL) {
        if (like)
            info(p).likes++;
        else if (info(p).likes > 0 && !like) // biar gak minus hehehehe :3
            info(p).likes--;
    } else {
        cout << "Postingan dengan ID " << x.id << " tidak ditemukan." << endl;
    }
}

void deleteFirst(List &a, address &p) {
    if (!isEmpty(a)) {
        p = first(a);
        if (first(a) == last(a)) {
            first(a) = NIL;
            last(a) = NIL;
        } else {
            first(a) = next(first(a));
            prev(first(a)) = NIL;
        }
        next(p) = NIL;
        prev(p) = NIL;
    }
}
void printAllPosts(List a) {
    address p = first(a);
    if (isEmpty(a)) {
        cout << "Tidak ada postingan." << endl;
    } else {
        while (p != NIL) {
            cout << "ID: " << info(p).id
                 << ", Username: " << info(p).username
                 << ", Likes: " << info(p).likes
                 << ", Konten: " << info(p).content << endl;
            p = next(p);
        }
    }
}
void deleteLast(List &a, address &p) {
    if (!isEmpty(a)) {
        p = last(a);
        if (first(a) == last(a)) {
            first(a) = NIL;
            last(a) = NIL;
        } else {
            last(a) = prev(last(a));
            next(last(a)) = NIL;
        }
        next(p) = NIL;
        prev(p) = NIL;
    }
}

```


2. Penjelasan Kode

**[main.cpp]**
fungsi main():
fungsi ini merupakan operasi inti yang dimana akan menjalankan programnya dengan pendukung library yang sudah dibuat.

Program ini atas mensimulasikan fitur timeline aplikasi MyTelu menggunakan struktur data Double Linked List (DLL) untuk menyimpan data postingan yang berisi ID, konten, jumlah like, dan username. Pertama, program membuat list kosong, lalu menambahkan 10 postingan secara terurut berdasarkan ID menggunakan insertPostByID. Setelah itu, semua postingan ditampilkan dengan printAllPosts, diikuti tampilan postingan yang difilter per pengguna menggunakan printPostsByUsername. Program kemudian menampilkan postingan dengan jumlah like terbanyak melalui printMostLikedPost, memperbarui jumlah like dan unlike pada postingan tertentu lewat updatePostLikes, dan kembali menampilkan postingan terpopuler setelah perubahan. Selanjutnya, program menghapus postingan pertama dan terakhir dari list dengan deleteFirst dan deleteLast, lalu menampilkan sisa postingan untuk memastikan operasi berhasil sebelum program berakhir.

**[DLL.h]**
kode ini merupakan implementasi struktur data Double Linked List (DLL) dalam bahasa C++ untuk mensimulasikan fitur timeline aplikasi MyTelu. Setiap node menyimpan informasi postingan berupa ID, konten, jumlah like, dan username. Program menyediakan berbagai fungsi untuk mengelola daftar postingan, seperti menambahkan postingan secara berurutan berdasarkan ID (insertPostByID), menampilkan semua postingan (printAllPosts), menampilkan postingan milik pengguna tertentu (printPostsByUsername), mencari postingan dengan jumlah like terbanyak (printMostLikedPost), serta memperbarui jumlah like dan unlike (updatePostLikes). Selain itu, terdapat fungsi dasar DLL seperti membuat list baru, menambah dan menghapus elemen di awal atau akhir, menghitung panjang list, mencari elemen tertentu, dan memisahkan list menjadi dua bagian dengan splitList.

**[DLL.cpp]**
Kode ini merupakan implementasi fungsi-fungsi utama dari Double Linked List (DLL) untuk mendukung pengelolaan data postingan pada aplikasi MyTelu. Program menyediakan operasi dasar seperti membuat list baru (createNewList), menambah elemen di awal (insertFirst), akhir (insertLast), atau di tengah list (insertAfter), serta mencari elemen berdasarkan ID (findElement). Selain itu, terdapat fungsi untuk menampilkan semua data (printList, printAllPosts), menghapus elemen pertama dan terakhir (deleteFirst, deleteLast), dan memasukkan postingan secara berurutan berdasarkan ID (insertPostByID). Fungsi tambahan seperti printPostsByUsername menampilkan postingan milik pengguna tertentu, printMostLikedPost mencari postingan dengan jumlah likes terbanyak, dan updatePostLikes memperbarui jumlah likes atau unlikes tanpa membuat nilainya negatif. Secara keseluruhan, file ini menjadi bagian logika utama yang mengatur bagaimana setiap postingan tersimpan dan dimanipulasi dalam struktur data ganda yang terhubung dua arah.
cmiw
3. Output Program
![Output](./Screenshot%202025-11-11%20145036.png)






