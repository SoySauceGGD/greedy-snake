#include<iostream>

using namespace std;

struct Node{
    int valu;
    Node *next;
};

class LinkedList{
    private:
        Node *head, *tail;

        Node* newNode(){
            Node *node = new Node;
            node->next = NULL;
            node->valu = -1;
            return node;
        }

    public:
        LinkedList(){
            Node *node = newNode();
            head = node;
            tail = node;
        }

        void pushback(int a){
            Node *node = newNode();
            node->valu = a;
            tail->next = node;
            tail = node;
        }

        void print(){
            if(head == tail){
                cout << "List is empty!\n";
                return;
            }

            for(Node *i = head->next; i != NULL; i = i->next)
                cout << i->valu << " ";
            cout << "\n";
        }
};

int main(){
    LinkedList list;

    int n;
    cout << "1 = pushback, 2 = print\n";
    while(cin >> n){
        switch(n){
            case 1:
                int a; cin >> a;
                list.pushback(a);
                continue;

            case 2:
                list.print();
                continue;

            default:
                continue;
        }   
    }
}
