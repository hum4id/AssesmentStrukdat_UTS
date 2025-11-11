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
