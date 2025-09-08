#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- CO1: Arrays - Menu Management ----------
#define MAX_ITEMS 100
struct MenuItem {
    int id;
    char name[50];
    float price;
};
struct MenuItem menu[MAX_ITEMS];
int menuCount = 0;

void addMenuItem(int id, char name[], float price) {
    menu[menuCount].id = id;
    strcpy(menu[menuCount].name, name);
    menu[menuCount].price = price;
    menuCount++;
}

void displayMenu() {
	int i =0;
    printf("\n--- Menu ---\n");
    for ( i = 0; i < menuCount; i++) {
        printf("ID: %d, Name: %s, Price: %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

// ---------- CO2: Search & Sort ----------
void bubbleSortByPrice() {
	int i,j;
    for ( i = 0; i < menuCount - 1; i++) {
        for ( j = 0; j < menuCount - i - 1; j++) {
            if (menu[j].price > menu[j + 1].price) {
                struct MenuItem temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
}

int binarySearchById(int id) {
    int low = 0, high = menuCount - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (menu[mid].id == id) return mid;
        else if (menu[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ---------- CO3: Stack - Undo Order ----------
#define MAX_STACK 50
struct Order {
    int orderId;
    int itemId;
    int quantity;
};
struct Order orderStack[MAX_STACK];
int top = -1;

void pushOrder(struct Order o) {
    if (top < MAX_STACK - 1)
        orderStack[++top] = o;
    else
        printf("Stack Overflow\n");
}

void popOrder() {
    if (top >= 0) {
        struct Order o = orderStack[top--];
        printf("Undo Order ID %d\n", o.orderId);
    } else {
        printf("Stack Underflow\n");
    }
}

// ---------- CO4: Queue - Order Queue ----------
#define MAX_QUEUE 50
struct Order orderQueue[MAX_QUEUE];
int front = -1, rear = -1;

void enqueueOrder(struct Order o) {
    if (rear == MAX_QUEUE - 1)
        printf("Queue Full\n");
    else {
        if (front == -1) front = 0;
        orderQueue[++rear] = o;
    }
}

void dequeueOrder() {
    if (front == -1 || front > rear)
        printf("Queue Empty\n");
    else {
        struct Order o = orderQueue[front++];
        printf("Processing Order ID %d\n", o.orderId);
    }
}

// ---------- CO5: Linked List - Order History ----------
struct OrderNode {
    int orderId;
    char itemName[50];
    struct OrderNode* next;
};
struct OrderNode* head = NULL;

void addOrderHistory(int orderId, char name[]) {
    struct OrderNode* newNode = (struct OrderNode*)malloc(sizeof(struct OrderNode));
    newNode->orderId = orderId;
    strcpy(newNode->itemName, name);
    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else {
        struct OrderNode* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void displayOrderHistory() {
    struct OrderNode* temp = head;
    printf("\n--- Order History ---\n");
    while (temp != NULL) {
        printf("Order ID: %d, Item: %s\n", temp->orderId, temp->itemName);
        temp = temp->next;
    }
}

// ---------- CO6: Tree - Food Category Tree ----------
struct Category {
    char name[50];
    struct Category* left;
    struct Category* right;
};

struct Category* createCategory(char name[]) {
    struct Category* newCat = (struct Category*)malloc(sizeof(struct Category));
    strcpy(newCat->name, name);
    newCat->left = newCat->right = NULL;
    return newCat;
}

void preorder(struct Category* root) {
    if (root) {
        printf("%s ", root->name);
        preorder(root->left);
        preorder(root->right);
    }
}


// ---------- Main Menu ----------
int main() {
    // Sample Menu Items
    addMenuItem(101, "Burger", 150);
    addMenuItem(102, "Pizza", 200);
    addMenuItem(103, "Tea", 15);
    addMenuItem(104, "Pasta", 250);
 	addMenuItem(105, "Momos", 150);
	
	int choice;
    struct Order o;

    struct Category* root = createCategory("Food");
    root->left = createCategory("Drinks");
    root->right = createCategory("Snacks");

    do {
        printf("\n--- Cafeteria Management ---\n");
        printf("1. Display Menu\n2. Sort Menu by Price\n3. Search Item by ID\n4. Place Order\n5. Undo Order\n");
        printf("6. Serve Next Order\n7. Display Order History\n8. Food Category Tree \n0. Exit\n");
        printf("Enter your choice : \n");
		scanf("%d", &choice);
        int i;

        switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                bubbleSortByPrice();
                printf("Sorted by Price\n");
                displayMenu();
                break;
            case 3: {
                int id;
                printf("Enter ID to search: ");
                scanf("%d", &id);
                int index = binarySearchById(id);
                if (index != -1)
                    printf("Found: %s\n", menu[index].name);
                else
                    printf("Item not found\n");
                break;
            }
            case 4:
                printf("Enter Order ID, Item ID, Quantity: ");
                scanf("%d%d%d", &o.orderId, &o.itemId, &o.quantity);
                pushOrder(o); // for undo
                enqueueOrder(o); // for processing
                addOrderHistory(o.orderId, menu[binarySearchById(o.itemId)].name); // for history
                break;
            case 5:
                popOrder();
                break;
            case 6:
                dequeueOrder();
                break;
            case 7:
                displayOrderHistory();
                break;
            case 8:
                printf("Category Tree (Preorder): ");
                preorder(root);
                printf("\n");
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid Choice\n");
        }
    } while (choice != 0);

    return 0;
}

