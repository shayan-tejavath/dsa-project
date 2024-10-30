#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for Rope
typedef struct RopeNode {
    char *str;  // Pointer to the string
    int weight; // Weight of the node (length of left child)
    struct RopeNode *left;   // Left child
    struct RopeNode *right;  // Right child
} RopeNode;

// Function prototypes
RopeNode* createRopeNode(const char *str);
void freeRope(RopeNode *node);
RopeNode* concatRopes(RopeNode *left, RopeNode *right); // O(log n)
void printRope(RopeNode *node); // O(n)
RopeNode* insertRope(RopeNode *root, int idx, const char *str); // O(log n)
RopeNode* deleteRope(RopeNode *root, int start, int len); // O(log n)
RopeNode* splitRope(RopeNode *node, int idx); // O(log n)
RopeNode* joinMultipleRopes(RopeNode **ropes, int count); // O(log n)
RopeNode* substringSlice(RopeNode *root, int start, int len); // O(log n)

// Create a new RopeNode
RopeNode* createRopeNode(const char *str) {
    RopeNode *node = (RopeNode*)malloc(sizeof(RopeNode));
    node->str = strdup(str);
    node->left = node->right = NULL;
    node->weight = strlen(str); // Set weight to length of the string
    return node;
}

// Free the Rope
void freeRope(RopeNode *node) {
    if (node) {
        free(node->str);
        freeRope(node->left);
        freeRope(node->right);
        free(node);
    }
}

// Concatenate two ropes
RopeNode* concatRopes(RopeNode *left, RopeNode *right) {
    RopeNode *node = createRopeNode(""); // Create a new node
    node->left = left;
    node->right = right;
    node->weight = left ? left->weight : 0; // Set weight (O(log n))
    return node;
}

// Print the Rope (in-order traversal)
void printRope(RopeNode *node) {
    if (node) {
        printRope(node->left);
        printf("%s", node->str);
        printRope(node->right);
    }
}

// Split the rope at a given index
RopeNode* splitRope(RopeNode *node, int idx) {
    // O(log n)
    if (!node) return NULL;

    if (idx < 0 || idx > node->weight) {
        return NULL; // Invalid index
    }

    // If the split index is in the left child
    if (idx < (node->left ? node->left->weight : 0)) {
        RopeNode *leftPart = splitRope(node->left, idx);
        RopeNode *rightPart = concatRopes(leftPart, node->right);
        return rightPart; // Return the right part after split
    } else {
        // If the split index is in the right child
        RopeNode *rightPart = splitRope(node->right, idx - (node->left ? node->left->weight : 0));
        RopeNode *leftPart = concatRopes(node->left, rightPart);
        return leftPart; // Return the left part after split
    }
}

// Insert a string into the rope at a given index
RopeNode* insertRope(RopeNode *root, int idx, const char *str) {
    // O(log n)
    RopeNode *newNode = createRopeNode(str);
    RopeNode *leftPart = splitRope(root, idx);
    RopeNode *rightPart = splitRope(leftPart, 0); // Get the right part
    return concatRopes(concatRopes(leftPart, newNode), rightPart); // Concatenate
}

// Delete a substring from the rope
RopeNode* deleteRope(RopeNode *root, int start, int len) {
    // O(log n)
    RopeNode *leftPart = splitRope(root, start);
    RopeNode *rightPart = splitRope(leftPart, len); // Get the part to delete
    freeRope(rightPart); // Free the deleted part
    return leftPart; // Return the remaining rope
}

// Join multiple ropes into one
RopeNode* joinMultipleRopes(RopeNode **ropes, int count) {
    if (count == 0) return NULL;
    
    RopeNode *result = ropes[0]; // Start with the first rope
    for (int i = 1; i < count; i++) {
        result = concatRopes(result, ropes[i]); // Concatenate each rope
    }
    return result; // Return the joined rope
}

// Substring slice of the rope
RopeNode* substringSlice(RopeNode *root, int start, int len) {
    // O(log n)
    RopeNode *leftPart = splitRope(root, start);
    RopeNode *slice = splitRope(leftPart, len); // Get the substring of specified length
    freeRope(leftPart); // Free the left part
    return slice; // Return the sliced rope
}

// Main function to test Rope operations
int main() {
    RopeNode *rope = NULL;
    int choice, idx, len, count;
    char inputStr[100];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Concatenate\n");
        printf("3. Join Multiple Ropes\n");
        printf("4. Substring Slice\n");
        printf("5. Delete\n");
        printf("6. Print Rope\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                printf("Enter string to insert: ");
                scanf("%[^\n]", inputStr);
                printf("Enter index to insert at: ");
                scanf("%d", &idx);
                rope = insertRope(rope, idx, inputStr);
                printf("After insertion: ");
                printRope(rope);
                break;

            case 2:
                printf("Enter string to concatenate: ");
                scanf("%[^\n]", inputStr);
                rope = concatRopes(rope, createRopeNode(inputStr));
                printf("After concatenation: ");
                printRope(rope);
                break;

            case 3:
                printf("Enter number of ropes to join: ");
                scanf("%d", &count);
                RopeNode **ropes = malloc(count * sizeof(RopeNode*));
                for (int i = 0; i < count; i++) {
                    printf("Enter string for rope %d: ", i + 1);
                    scanf("%s", inputStr);
                    ropes[i] = createRopeNode(inputStr);
                }
                rope = joinMultipleRopes(ropes, count);
                free(ropes); // Free the temporary ropes array
                printf("After joining multiple ropes: ");
                printRope(rope);
                break;

            case 4:
                printf("Enter starting index for substring slice: ");
                scanf("%d", &idx);
                printf("Enter length of substring slice: ");
                scanf("%d", &len);
                RopeNode *slicedRope = substringSlice(rope, idx, len);
                printf("Sliced Rope: ");
                printRope(slicedRope);
                freeRope(slicedRope); // Free the sliced rope
                break;

            case 5:
                printf("Enter starting index for deletion: ");
                scanf("%d", &idx);
                printf("Enter length of substring to delete: ");
                scanf("%d", &len);
                rope = deleteRope(rope, idx, len);
                printf("After deletion: ");
                printRope(rope);
                break;

            case 6:
                printf("Current Rope: ");
                printRope(rope);
                break;

            case 7:
                freeRope(rope);
                exit(0);
                break;

            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    return 0;
}