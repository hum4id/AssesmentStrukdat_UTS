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