# DoublyLinkedLists

In this project, I have implemented a special kind of doubly-linked lists inside a class called Exam_database.

Conceptually, an Exam_database stores (name, score) pairs, where name is the name of a person who wrote an exam, and score 
is the score they got on it. For simplicity, we’ll assume names are not empty and contain no spaces. Also, a given name occurs 
at most once in an Exam_database. A score can be any int (even negative!).

Internally, Exam_database should store (name, score) pairs in a private Node struct/class. Each Node should have at least 
these 4 pointers:

A pointer to the next node whose name occurs alphabetically after the current one.
A pointer to the previous node whose name occurs alphabetically before the current one.
A pointer to the next node with the next higher score after this one.
A pointer to the previous node with the next lower score before this one.

The idea is that the two alphabetical-order pointers form a doubly-linked list ordered by names, and the two score-order pointers 
form a different doubly- linked list ordered by scores. The (name, score) nodes should only occur once — don’t just implement 
two separate doubly-linked lists.

In addition to the Node struct/class, Exam_database needs two head pointers and two tail pointers. One head points to the exam node 
whose name comes first alphabetically, and the other head points to the exam node with the lowest score. Similarly, one tail points 
to the alphabetically last node, and the other tail points to the node with the highest score.

With these nodes and pointers, it is now easy to print out the list in forward order, or reverse order, by name or by score: 
just follow the correct pointers. For example, if you start at the exam with the highest score and follow the next lowest exam 
pointers, you will traverse the exams from highest score to lowest score.
