#include<iostream>

using namespace std;


struct Node{
	int val;
	Node * next;
};

Node* reverseN(Node* head, int N , Node* father){
	Node* current = head;
	Node* pre = NULL;

	for(int i=1;i<=N && current!=NULL;i++){
		Node* tmp = current->next;
		current->next = pre;
		pre = current;
		current = tmp;
	}
	head->next = current;
	if(father != NULL)
		father->next = pre;
	return pre;
}

Node* reverseParts(Node* head, int parts){
	Node* ret = reverseN(head,parts,NULL);

	Node* start = head;
	while(start->next != NULL){
		Node* father = start;
		start = start->next;
		reverseN(start,parts,father);
	}

	return ret;
}

int main()
{
	Node * head = NULL;

	for(int i=8;i>=1;i--){
		Node * cur = new Node();
		cur->val = i;
		cur->next = head;
		head = cur;
	}

	Node * cur = head;

	while(cur!=NULL){
		cout<<cur->val<<" ";
		cur = cur->next;
	}
	cout<<endl;

	head = reverseParts(head,3);

	cur = head;
	while(cur!=NULL){
		cout<<cur->val<<" ";
		cur = cur->next;
	}
	cout<<endl;

	system("pause");
}