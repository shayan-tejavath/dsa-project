#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for Rope
typedef struct RopeNode {
    char *str;  // Pointer to the string (leaf nodes only)
    int weight; // Weight of the node (length of left child)
    struct RopeNode *left;   // Left child
    struct RopeNode *right;  // Right child
} RopeNode;

// Function prototypes
RopeNode* createRopeNode(const char *str);
void freeRope(RopeNode *node);
RopeNode* concatRopes(RopeNode *left, RopeNode *right);
void printRope(RopeNode *node);
RopeNode* insertRope(RopeNode *root, int idx, const char *str);
RopeNode* appendRope(RopeNode *rope, const char *str);
RopeNode* deleteRope(RopeNode *rope, int idx, int length);
RopeNode* concatenateRopes(RopeNode *rope1, RopeNode *rope2); // Concatenation function

// Create a new RopeNode
RopeNode* createRopeNode(const char *str) {
    RopeNode *node = (RopeNode*)malloc(sizeof(RopeNode));
    node->str = strdup(str);
    node->left = node->right = NULL;
    node->weight = strlen(str);
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
    RopeNode *node = (RopeNode*)malloc(sizeof(RopeNode));
    node->left = left;
    node->right = right;
    node->weight = (left ? left->weight : 0) + (right ? right->weight : 0);
    node->str = NULL; // Do not store the string here
    return node;
}

// Print the Rope (in-order traversal)
void printRope(RopeNode *node) {
    if (node) {
        printRope(node->left);
        if (node->str) { // Only print strings at leaf nodes
            printf("%s", node->str);
        }
        printRope(node->right);
    }
}

// Insert a string at a specific index
RopeNode* insertRope(RopeNode *root, int idx, const char *str) {
    if (idx < 0 || (root && idx > root->weight)) {
        printf("Invalid index\n");
        return root;
    }

    RopeNode *newNode = createRopeNode(str);
    if (!root) {
        return newNode; // If the rope is empty, return the new node
    }

    // Split the rope into two parts: left and right
    RopeNode *leftPart = NULL;
    RopeNode *rightPart = NULL;

    // Traverse to split at the desired index
    int totalWeight = root->weight;

    if (idx <= totalWeight) {
        // If the index is in the left part
        leftPart = root->left;
        rightPart = root->right;
    } else {
        // If the index is in the right part
        leftPart = root;
        rightPart = NULL;
    }

    // Concatenate the left part, new node, and right part
    return concatRopes(leftPart, concatRopes(newNode, rightPart));
}

// Append a string to the end of the rope
RopeNode* appendRope(RopeNode *rope, const char *str) {
    RopeNode *newNode = createRopeNode(str);
    return concatRopes(rope, newNode); // Concatenate the existing rope with the new node
}

// Delete a substring from the rope
RopeNode* deleteRope(RopeNode *rope, int idx, int length) {
    if (!rope || idx < 0 || length <= 0) {
        return rope; // Invalid input
    }

    // Calculate the total length of the rope
    int totalLength = rope->weight;

    if (idx >= totalLength) {
        return rope; // Nothing to delete
    }

    // Adjust length if it exceeds the total length
    if (idx + length > totalLength) {
        length = totalLength - idx; // Trim length
    }

    // Create left and right parts
    RopeNode *leftPart = NULL;
    RopeNode *rightPart = NULL;

    // Calculate left part (up to idx)
    int leftWeight = 0; // To track the weight of the left part
    RopeNode *current = rope;

    while (current) {
        if (leftWeight + current->weight > idx) {
            // Split logic: we need to add part of the current node
            int splitIdx = idx - leftWeight; // Index to split in current node
            // Create a new node for the left part with the substring
            if (splitIdx > 0) {
                leftPart = concatRopes(leftPart, createRopeNode(strndup(current->str, splitIdx)));
            }
            break; // Stop as we have created the left part
        }
        leftPart = concatRopes(leftPart, createRopeNode(strdup(current->str)));
        leftWeight += current->weight;
        current = current->right; // Move to the next node
    }

    // Calculate right part (from idx + length)
    int rightWeight = idx + length; // Start from the end of the deletion
    current = rope;

    while (current) {
        if (rightWeight <= leftWeight) {
            // No need to create the right part if we're within the left
            break;
        }
        // Skip the current node if we're before the deletion index
        if (leftWeight + current->weight <= idx) {
            leftWeight += current->weight;
            current = current->right; // Move to next node
            continue;
        }

        // If we reach here, we need to start adding to the right part
        int startIdx = leftWeight; // Index at which we start adding to right part
        if (rightWeight > startIdx) {
            int splitIdx = rightWeight - startIdx; // How much to take from current node
            if (splitIdx < current->weight) {
                rightPart = concatRopes(rightPart, createRopeNode(strndup(current->str + splitIdx, current->weight - splitIdx)));
            }
        }
        // We can move to the next node
        leftWeight += current->weight;
        current = current->right;
    }

    // Concatenate the left part and right part
    RopeNode *newRope = concatRopes(leftPart, rightPart);

    freeRope(rope); // Free the original rope
    return newRope; // Return the modified rope
}

// Concatenate two ropes
RopeNode* concatenateRopes(RopeNode *rope1, RopeNode *rope2) {
    return concatRopes(rope1, rope2);
}

// Main function to test Rope operations
int main() {
    RopeNode *rope = NULL;
    int choice;
    char inputStr[100];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Append\n");
        printf("3. Concatenate Ropes\n");
        printf("4. Delete\n");
        printf("5. Print Rope\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                printf("Enter string to insert: ");
                scanf("%[^\n]", inputStr);
                rope = insertRope(rope, 0, inputStr); // Simple insertion at the beginning
                printf("After insertion: ");
                printRope(rope);
                break;

            case 2:
                printf("Enter string to append: ");
                scanf("%[^\n]", inputStr);
                rope = appendRope(rope, inputStr);
                printf("After appending: ");
                printRope(rope);
                break;

            case 3:
                {
                    printf("Enter the  rope string: ");
                    scanf("%[^\n]", inputStr);
                    RopeNode *rope1 = createRopeNode(inputStr);
                    
                 
                    
                    // Concatenate the current rope with the new ropes
                    rope = (concatenateRopes(rope, rope1));
                    printf("After concatenation: ");
                    printRope(rope);
                    freeRope(rope1);
                    
                }
                break;

            case 4:
                printf("Enter index to delete from: ");
                int idx, length;
                scanf("%d", &idx);
                printf("Enter length to delete: ");
                scanf("%d", &length);
                 printRope(rope);
                rope = deleteRope(rope, idx, length);
                printf("After deletion: ");
                printRope(rope);
                break;

            case 5:
                printf("Current Rope: ");
                printRope(rope);
                break;

            case 6:
                freeRope(rope);
                exit(0);
        }
    }
    return 0;
}
