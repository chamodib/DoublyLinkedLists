// Exam_database.h

// Name : <Chamodi Basnayake>


#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;

class Exam_database {
private:

    struct Node {
        string name;
        int score;

        Node *next_name;
        Node *prev_name;
        Node *next_score;
        Node *prev_score;
    };

    Node *head_name;
    Node *head_score;
    Node *tail_name;
    Node *tail_score;

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty Exam_database
    // Note:
    //    you can use an initialization with this constructor
    Exam_database() {
        head_score = nullptr;
        head_name = nullptr;
        tail_score = nullptr;
        tail_name = nullptr;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    destructs Exam_database, i.e. ensures all memory (or other resources)
    //    owned by this object are properly deleted
    ~Exam_database() {
        //Iterate through the score list and delete each node
        while (head_score != nullptr) {
            Node *n = head_score;
            delete_node(n);
        }
    }

    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    adds (name, score) to this object; if a pair in the database already
    //    has the name, then its corresponding score is set to score
    void add_exam(const string &name, int score) {
        //Throw errors if name is invalid (if zero length & have spaces)
        if (name.length() == 0) {
            cmpt::error ("Error: Empty string");
        } else {
            for (int i = 0; i < name.length(); i++) {
                if (name[i] == ' ') {
                    cmpt::error ("Error: String has spaces");
                }
            }
        }

        //Checks if list is empty 
        if (is_emtpy()) {
            //Creating the first element of list, and pointing all heads and tails to it
            Node *new_node = new Node{name, score, nullptr, nullptr, nullptr, nullptr};
            head_name = new_node;
            tail_name = new_node;
            head_score = new_node;
            tail_score = new_node;

        //The list has elements    
        } else {
            //find_closest_name returns a pointer to node with same name, or with next biggest name
            Node *closest_name = find_closest_name(name);
            Node* new_node = nullptr;

            //If list has no names bigger than name (reached the tail of the list), insert new Node as tail in name list
            if (closest_name == nullptr) { 
                //Create a new node at the end of the list and rearrange pointers              
                new_node = new Node{name, score, nullptr, tail_name, nullptr, nullptr};
                tail_name->next_name = new_node;
                tail_name = new_node;
            //If the same name exists in the list, update score and remove existing Node from score list    
            } else if (closest_name->name == name) {     
                new_node = closest_name;
                // update score and remove from score list,
                remove_from_score_list(new_node);
                new_node->score = score;
                new_node->next_score = nullptr;
                new_node->prev_score = nullptr;
            //If list has names bigger than "name", insert new node before closest_name in name list
            } else {                                    
                new_node = new Node{name, score, closest_name,closest_name->prev_name,nullptr,nullptr};
                closest_name->prev_name = new_node;

                //Insert new Node as a head
                if(new_node->prev_name == nullptr){     // insert at head
                    head_name = new_node;
                }else{
                    new_node->prev_name->next_name = new_node;
                }
            }
            //Insert the Node into the score list
            insert_to_score_list(new_node);
        }
    }


    
    // Pre-condition:
    //    name is non-empty and contains no spaces
    //    use cmpt::error to throw an exception if this is not satisfied
    // Post-condition:
    //    deletes the (name, score) pair from this Exam_database; if there is no
    //    pair with the given name, then this does nothing
    void remove_exam(const string& name) {
        //Throw errors if name is invalid (if zero length & have spaces)
        if (name.length() == 0) {
            cmpt::error ("Error: Empty string");
        } else {
            for (int i = 0; i < name.length(); i++) {
                if (name[i] == ' ') {
                    cmpt::error ("Error: String has spaces");
                }
            }
        }

        //Check if list is empty
        if (is_emtpy()) {
            cout << "There are no elements to be removed" << endl;    
        } else {
            //find_closest_name returns pointer to Node containing same name or the next biggest name
            Node*closest_name = find_closest_name(name);
            //If it returns nullptr (reached the end of the list), the name doesn't exist in list
            if (closest_name == nullptr) {
                cout << "This name (" << name << ") doesn't exist in list" << endl;
            //If the same name or a name bigger exists    
            } else {
                //Check if the Node has a same name, if so, delete that Node    
                if (closest_name->name == name) {
                    delete_node(closest_name);
                //The names are not identical, name also doesn't exist       
                } else {
                    cout << "This name (" << name << ") doesn't exist in list" << endl;
                }    
            }
        }            
    }




    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in alphabetical order by name
    void print_by_name() const {
        Node* nameHead_dup = head_name;
        cout << "PRINT: NAMES IN ALPHABETICAL ORDER" << endl;

        //Check if list is empty, if not print all items 
        if (is_emtpy()) {
            cout << "The list is empty." << endl;
        } else {
        //If only one time, print that item
            if (nameHead_dup == tail_name) {
                cout << nameHead_dup->name << " , " << nameHead_dup->score << endl;
        //If many elements, print all items
            } else {
                while (nameHead_dup != tail_name) {
                    cout << nameHead_dup->name << " , " << nameHead_dup->score << endl;
                    nameHead_dup = nameHead_dup->next_name;

                    if(nameHead_dup == tail_name){
                        cout << nameHead_dup->name << " , " << nameHead_dup->score << endl;
                    }
                }
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs in reverse alphabetical order
    //    by name
    void print_by_name_rev() const {
        Node* nameTail_dup = tail_name;
        cout << "PRINT: NAMES IN REVERSE ALPHABETICAL ORDER" << endl;

        //Check if list is empty, if not print all items
        if (is_emtpy()) {
            cout << "The list is empty." << endl;
        } else {
            //If only one time, print that item
            if (nameTail_dup == head_name) {
            cout << nameTail_dup->name << " , " << nameTail_dup->score << endl;
            //If many elements, print all items
            } else {
                while (nameTail_dup != head_name) {
                    cout << nameTail_dup->name << " , " << nameTail_dup->score << endl;
                    nameTail_dup = nameTail_dup->prev_name;

                    if (nameTail_dup == head_name) {
                        cout << nameTail_dup->name << " , " << nameTail_dup->score << endl;
                    }
                }
            }
        } 
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from smallest to biggest by score
    void print_by_score_ascending() const {
        Node* scoreHead_dup = head_score;
        cout << "PRINT: SCORES IN ASCENDING ORDER" << endl;

        //Check if list is empty, if not print all items
        if (is_emtpy()) {
            cout << "The list is empty." << endl;
        } else {

            //If only one time, print that item
            if (scoreHead_dup == tail_score) {
                cout << scoreHead_dup->score << " , " << scoreHead_dup->name << endl;
            //If many elements, print all items    
            } else {
                while (scoreHead_dup != tail_score) {
                    cout << scoreHead_dup->score << " , " << scoreHead_dup->name << endl;
                    scoreHead_dup = scoreHead_dup->next_score;

                    if(scoreHead_dup == tail_score) {
                        cout << scoreHead_dup->score << " , " << scoreHead_dup->name << endl;
                    }
                }
            }
        }    
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    print (to cout) all (name, score) pairs from biggest to smallest by score
    void print_by_score_descending() const {
        Node* scoreTail_dup = tail_score;
        cout << "PRINT: SCORES IN DESCENDING ORDER" << endl;

        //Check if list is empty, if not print all items
        if (is_emtpy()) {
            cout << "The list is empty." << endl;
        } else {
            //If only one time, print that item
            if (scoreTail_dup == head_score) {
                cout << scoreTail_dup->score << " , " << scoreTail_dup->name << endl;
            //If many elements, print all items    
            } else {
                while (scoreTail_dup != head_score) {
                    cout << scoreTail_dup->score << " , " << scoreTail_dup->name << endl;
                    scoreTail_dup = scoreTail_dup->prev_score;

                    if (scoreTail_dup == head_score) {
                        cout << scoreTail_dup->score << " , " << scoreTail_dup->name << endl;
                    }
                }
            }
        }    
    }


    ////////////////////////////////////// HELPER FUNCTIONS ////////////////////////////////////////

    //Check if the list is empty
    bool is_emtpy() const {
        return head_name == nullptr;
    }

    //Return a pointer to Node with same name or the next biggest name on list
    Node* find_closest_name(const string name) const {        
        Node *nameHead_dup = head_name;

        //Loop through list to compare each Node's name
        while (nameHead_dup != nullptr) {
            //If name > nameHead_dup, point nameHead_dup to next name
            if (nameHead_dup->name < name) {
                nameHead_dup = nameHead_dup->next_name;
            //If name <= nameHead_dup, return pointer to value    
            } else {
                return nameHead_dup;
            }
        }
        //Return nullptr when reached the end of the list (name isn't found on list, all list names < name)
        return nullptr;
    }

    //Remove a score from the score list
    void remove_from_score_list(Node *n) {
        //If n is not the head 
        if (n->prev_score != nullptr) {
            //If neither prev or next scores null (middle node)
            if (n->next_score != nullptr) {       
                n->prev_score->next_score = n->next_score;
                n->next_score->prev_score = n->prev_score;
            //If only next score null (a tail)   
            } else {                            
                n->prev_score->next_score = nullptr;
                tail_score = n->prev_score;
            }
        //If prev is nullptr    
        } else { 
            //If only prev score null (a head)
            if (n->next_score != nullptr) {       
                n->next_score->prev_score = nullptr;
                head_score = n->next_score;
            //If both scores null (only element in list)   
            } else {                            
                head_score = nullptr;
                tail_score = nullptr;
            }
        }
    }


    //Remove name from namelist
    void remove_from_name_list(Node *n) {
        //If n is not the head of name list, do:
        if (n->prev_name != nullptr) {
            //If prev and next not null (middle node), do:
            if (n->next_name != nullptr) {       
                n->prev_name->next_name = n->next_name;
                n->next_name->prev_name = n->prev_name;
            //If only next null (tail), do else    
            } else {                            
                n->prev_name->next_name = nullptr;
                tail_name = n->prev_name;
            }
        //If prev = null, do:    
        } else {
            //If only prev null (head)
            if (n->next_name != nullptr) {       
                n->next_name->prev_name = nullptr;
                head_name = n->next_name;
            //If both null (only element in list)    
            } else {                           
                head_name = nullptr;
                tail_name = nullptr;
            }
        }
    }

    //Insert a node in score list in order
    void insert_to_score_list(Node* n) {
        //Create duplicate of head_score to iterate through score list
        Node* scoreHead_dup = head_score;

        while (scoreHead_dup != nullptr) {
            //If the name of the list Node < n->score, then iterate to the next score of list
            if (scoreHead_dup->score < n->score) {
                scoreHead_dup = scoreHead_dup->next_score;
            //If scoreHead_dup->score >= n->score, then insert Node n here     
            } else {                               //  
                n->next_score = scoreHead_dup;
                //check if scoreHead_dup is not a head
                if (scoreHead_dup->prev_score != nullptr) {    
                    n->prev_score = scoreHead_dup->prev_score;
                    n->prev_score->next_score = n;
                //If it's a head    
                }else{                                        
                    head_score = n;
                }

                scoreHead_dup->prev_score = n;
                return;
            }
        }       
        // Exits loop if scoreHead_dup is on a tail or list is empty

        //Check if empty list or scoreHead_dup is on the tail of the list 
        if (head_score == nullptr) {     
            head_score = n;
        //If scoreHead_dup reaches end of the list, insert Node n as tail    
        } else {            
            tail_score->next_score = n;
            n->prev_score = tail_score;
        }

        tail_score = n;
    }

    //Fully delete a node from list
    void delete_node(Node *n) {
        //Rearrange pointers, remove node from score list
        remove_from_score_list(n);
        //Rearrange pointers, remove node from name list
        remove_from_name_list(n);

        //Delete node
        delete n;
    }


}; // class Exam_database


/////////////////////////////////////////////////////////////////////////
//
// CITATIONS
// ------------

// - Received helped from the TA on the following:
//        -Debugging a segmentation fault in remove_exam method, when removing an element from the list that doesn't exist
//
// - Received help from a friend: Sachini Herath on:
//        - Idea on how to rearrange score list when an element with the same name is added
//        - Destructor: Gave me the idea of the while loops in destructor, and creating the delete_node method to assist it
//        - add_exam: On what helper methods can be created to make implementation and debugging easier


///////////////////////////////////////////////////////////////////////
