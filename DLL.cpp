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