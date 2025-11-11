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
 * genap.

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

Program ini basically nyimulasikan fitur timeline di aplikasi MyTelu pakai struktur data Double Linked List (DLL) buat nyimpen data postingan yang isinya ID, konten, jumlah like, dan username. Pertama, program bikin list kosong, terus nambahin 10 postingan secara urut berdasarkan ID lewat insertPostByID. Setelah semua data masuk, program nampilin semua postingan pakai printAllPosts, lalu ngefilter postingan per user lewat printPostsByUsername. Abis itu, program cari postingan dengan like terbanyak pakai printMostLikedPost, terus nguji fitur like dan unlike lewat updatePostLikes, biar bisa liat perubahan di postingan terpopuler. Terakhir, program hapus postingan pertama dan terakhir di list pakai deleteFirst dan deleteLast, lalu nampilin sisa postingan buat ngecek apakah operasi hapusnya berhasil, sebelum program selesai jalan.

[DLL.h]
File ini isinya struktur dasar dari Double Linked List buat nge-handle data postingan di MyTelu. Tiap node nyimpen info kayak ID, isi postingan, jumlah like, dan username. Di sini juga disiapin berbagai fungsi bantu buat ngatur data, misalnya nambah postingan secara urut (insertPostByID), nampilin semua postingan (printAllPosts), nampilin postingan dari user tertentu (printPostsByUsername), nyari postingan paling populer (printMostLikedPost), dan update jumlah like/unlike (updatePostLikes). Selain itu, ada juga fungsi dasar DLL kayak bikin list baru, nambah atau hapus elemen di awal/akhir list, ngecek panjang list, nyari elemen tertentu, sampai misahin list jadi dua bagian lewat splitList.

[DLL.cpp]
File ini isinya implementasi semua fungsi utama dari Double Linked List tadi. Di sini ada fungsi buat bikin list baru (createNewList), nambah data di awal (insertFirst), di akhir (insertLast), atau di tengah (insertAfter), dan juga nyari data berdasarkan ID (findElement). Ada juga fungsi buat nampilin isi list (printList, printAllPosts), hapus elemen pertama atau terakhir (deleteFirst, deleteLast), dan masukin postingan biar tetap urut (insertPostByID). Fitur tambahan kayak printPostsByUsername bisa nampilin postingan per user, printMostLikedPost buat nyari postingan dengan like paling banyak, dan updatePostLikes buat nambah atau ngurangin jumlah like tanpa bikin nilainya minus. Intinya, file ini yang ngatur semua logika utama biar sistem timeline MyTelu bisa jalan lancar.

cmiw
3. Output Program
![Output](./Screenshot%202025-11-11%20145036.png)






