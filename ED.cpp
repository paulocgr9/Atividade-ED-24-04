#include <iostream>

using std::cout;
using std::endl;
using std::string;

// Lista duplamente encadeada

// Criando nova estrutura para um nó, para fazer lista duplamente encadeada
typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void deleteNode(Node**, Node*);
void displayList(Node*);
void insertBefore(Node**, Node*, int);
Node* searchNodebyValue(Node**, int);
void deleteNodebyValue(Node**, int);

// Driver Code
int main()
{
    // Lista duplamente encadeada
    Node* head = nullptr;
    displayList(head);
    cout << "====================================" << endl;

    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    insertEnd(&head, 10);
    insertEnd(&head, 13);
    displayList(head);
    cout << "====================================" << endl;
	insertAfter(head->ptrNext->ptrNext->ptrNext, 911);
	displayList(head);
    deleteNode(&head, head->ptrNext->ptrNext->ptrNext->ptrNext);
	displayList(head);
    cout << "====================================" << endl;
	insertBefore(&head, head->ptrNext->ptrNext->ptrNext, 99);
	insertBefore(&head, head, 333);
	displayList(head);
	deleteNode(&head, head);
	displayList(head);
    cout << "====================================" << endl;

	Node* node1 = searchNodebyValue(&head, 0);
	Node* node2 = searchNodebyValue(&head, 10);
	Node* node3 = searchNodebyValue(&head, 13);
	Node* node4 = searchNodebyValue(&head, 14);
	cout << node1->iPayload << endl;
	cout << node2->iPayload << endl;
	cout << node3->iPayload << endl;
    cout << "====================================" << endl;

	displayList(head);

	deleteNodebyValue(&head, 0);
	displayList(head);

	deleteNodebyValue(&head, 10);
	displayList(head);
	deleteNodebyValue(&head, 13);
	displayList(head);

	deleteNodebyValue(&head, 14);
	displayList(head);

    return 0;
}

Node* createNode(int iPayload)
{
    Node* temp = (Node*) malloc(sizeof(Node));     
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;

    return temp;
}

void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Nao foi possivel realizar displayList" << endl;
        return;
    }

    if (node->ptrPrev != nullptr)
    {
        cout << "Meio da Lista: Nao foi possivel realizar displayList" << endl;
        return;
    }

    Node* temp = node;

    cout << "Payload: ";

    //Percorremos a lista até o fim (ptrNext do último é NULL) 
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }

    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
	// newNode->ptrPrev = nullptr;
	
	if (*head != nullptr)
	{
		(*head)->ptrPrev = newNode;
		newNode->ptrNext = (*head);
		(*head) = newNode;
		return;
	}
	
	(*head) = newNode;
	
}

void insertEnd(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    //newNode->ptrNext = nullptr;

    if (*head == nullptr)
    {
        //newNode->ptrPrev = nullptr;   
        (*head) = newNode;
        return;            
    }

    Node* temp = (*head);

    //Percorremos a lista até o fim (ptrNext do último é NULL) 
    while (temp->ptrNext != nullptr) temp = temp->ptrNext;

    newNode->ptrPrev = temp; //newNode aponta para o fim da lista
    temp->ptrNext = newNode; //antigo último elemento aponta para o novo nó

}

void insertAfter(Node* ptrLocation, int iPayLoad)
{
	if (ptrLocation == nullptr)
	{
		cout << "Location é NULL" << endl;
	}
	
	Node* newNode = createNode(iPayLoad);
	
	// Corrigir nó a ser inserido
	newNode->ptrNext = ptrLocation->ptrNext;
	newNode->ptrPrev = ptrLocation;
	
	// Corrigir o ponto de inserção
	ptrLocation->ptrNext = newNode;
	
	if (newNode->ptrNext != nullptr) newNode->ptrNext->ptrPrev = newNode;
}

void deleteNode(Node** head, Node* ptrDelete)
{
	if (*head == nullptr || ptrDelete == nullptr)
	{
		cout << " Não foi possível remover." << endl;
		return;
	}
	
	// Caso o ptrDelete seja o primeiro elemento da lista
	if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;

	// Se o ptrDelete não é o último nó
	if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;

	// Se o ptrDelete não é o primeiro nó
	if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;
	
	free(ptrDelete);
}

// Exercício 1: Elaborar o método void insertBefore(Node**, int);
// Exercício 2: Elaborar a função void deleteNodebyValue(Node**, int);
// Exercício 3: Elaborar a função Node* searchNodebyValue(Node**, int);

void insertBefore(Node** head, Node* ptrLocation, int iPayLoad)
{
	if (ptrLocation == nullptr)
	{
		cout << "Location é NULL" << endl;
	}
	
	Node* newNode = createNode(iPayLoad);
	
	// Corrigir nó a ser inserido	
	newNode->ptrPrev = ptrLocation->ptrPrev;
	newNode->ptrNext = ptrLocation;
	
	// Corrigir o ponto de inserção
	ptrLocation->ptrPrev = newNode;

	// Conecta ao anterior e caso seja o primeiro torna-o o head
	if (newNode->ptrPrev != nullptr)
	{
		newNode->ptrPrev->ptrNext = newNode;
	}
	else
	{
		(*head) = newNode;
	}

}

Node* searchNodebyValue(Node** head, int iValue)
{
	if (head == nullptr)
	{
		cout << "A lista passada está vazia." << endl;
	}
	
	// Percorrer a lista duplamente encadeada até encontrar o valor desejado
	Node* ptrCurrent = *head;
	while (ptrCurrent != nullptr)
	{
		if (ptrCurrent->iPayload == iValue) return ptrCurrent;
		ptrCurrent = ptrCurrent->ptrNext;
	}
	
	// Caso o valor não seja encontrado
	if (ptrCurrent == nullptr) cout << "O valor não foi encontrado" << endl;

	return nullptr;
}

void deleteNodebyValue(Node** head, int iValue)
{
	// Procura um nó com o dado valor
	Node* node = searchNodebyValue(head, iValue);

	// Deleta o nó encontrado
	deleteNode(head, node);

	return;
}