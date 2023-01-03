// / This code defines a binary search tree data structure
// for storing student records. Each node in the tree represents
// a student with a code, name, and mark. The tree is sorted by the
// mark field, with nodes containing lower marks being stored in the
// left subtree and nodes containing higher or equal marks being stored
// in the right subtree.

// / The "newNode" function is used to allocate memory for
// a new tree node and initialize its fields. The "insert" function is used
// to insert a new student record into the tree. It takes a pointer to a tree
// root node and the code, name, and mark for the new student as arguments.
// If the root is NULL, it creates a new root node for the tree. Otherwise,
// it compares the mark of the new student with the mark of the current node
// and inserts the new node into the left or right subtree accordingly.

// / The "csvintotree" function reads student records
// from a CSV file and inserts them into the tree using the insert function.
// The "printInOrder" function traverses the tree in-order and prints the code,
// name, and mark for each student. The" create_marks_csv "function creates
// a new CSV file with sample student records.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct s_tree
{
    int code;
    char l_name[32];
    float mark;
    struct s_tree *left;
    struct s_tree *right;
};

struct s_tree *newNode(int code, char *name, float mark)
{
    // Allocate memory for the new node
    struct s_tree *node = (struct s_tree *)malloc(sizeof(struct s_tree));

    // Copy the code, name, and mark to the node
    node->code = code;
    strcpy(node->l_name, name);
    node->mark = mark;

    // Initialize the left and right children to NULL
    node->left = NULL;
    node->right = NULL;

    return node;
}

void printInOrder(struct s_tree *root)
{
    struct s_tree *temp = root;
    if (temp != NULL)
    {
        printInOrder(root->left);
        printf("====================");
        printf("\n %d ", temp->code);
        printf("-%s", temp->l_name);
        printf(":%.2f\n", temp->mark);
        printf("====================");
        printInOrder(root->right);
    }
}
void insert(struct s_tree **root, int code, char name[20], float mark)
{

    if (*root == NULL)
    {
        *root = newNode(code, name, mark);
        return;
    }

    // If the code is less than the code of the current node, insert the new
    // node into the left subtree
    if (mark < (*root)->mark)
    {
        insert(&((*root)->left), code, name, mark);
    }
    // If the code is greater than or equal to the code of the current node,
    // insert the new node into the right subtree
    else
    {
        insert(&((*root)->right), code, name, mark);
    }
}

void csvintotree(struct s_tree *root)
{

    int count, Code;
    char L_Name[20];
    float Mark;
    // create_marks_csv();
    FILE *fp = fopen("data.csv", "r");
    char *wrds[40];
    if (!fp)
        printf("Can't open file\n");

    else
    {
        // Here we have taken size of
        // array 1024 you can modify it
        char b[1000];

        int row = 0;
        int column = 0;

        while (fgets(b, 1000, fp))
        {
            column = 0;
            row++;

            // To avoid printing of column
            // names in file can be changed
            // according to need
            if (row == 1)
                continue;

            // Splitting the data
            char *value = strtok(b, "; ");

            while (value)
            {
                // Column 1
                if (column == 0)
                {
                    Code = atoi(value);
                    // printf("\n Name :");
                    // printf("\n  ======  %s ========\n ", value);
                }

                // Column 2
                if (column == 1)
                {
                    strcpy(L_Name, value);
                    // printf("\n \tAccount No. :");
                    // printf("\n  ======  %s ========\n ", value);
                }

                // Column 3
                if (column == 2)
                {
                    Mark = atof(value);
                    // printf(" \n \tAmount :");
                    // printf("\n  ======  %f ======== \n", Mark);
                }

                value = strtok(NULL, "; ");
                column++;
            }
            insert(root, Code, L_Name, Mark);
        }

        // Close the file
        fclose(fp);
    }
    getchar();
}
// function for creating and writing in file
void create_marks_csv()
{
    FILE *fp;
    int i, count, Code;
    char L_Name[20];
    float Mark;

    fp = fopen("data.csv", "w");

    fprintf(fp, "Code, L_Name ,Mark");
    printf("How many student's marks do you want to save :");
    scanf("%d", &count);

    for (i = 1; i <= count; i++)
    {
        // printf("Enter student Code : ");
        // scanf("%d", &Code);
        printf("Enter last name : ");
        scanf(" %s", &L_Name);
        printf("Enter mark : ");
        scanf("%f", &Mark);

        fprintf(fp, "\n %d;%s;%f", i, L_Name, Mark);
    }
    fclose(fp);

    printf("\n data.csv file created");
}

void delet(struct s_trre **a)
{
    *a = NULL;
}

struct s_tree *search(struct s_tree *root, int code)
{
    if (root == NULL || root->code == code)
    {
        return root;
    }

    if (code < root->code)
    {
        return search(root->left, code);
    }
    else
    {
        return search(root->right, code);
    }
}
struct s_tree *searchResult(struct s_tree *root, int code)
{
    struct s_tree *result = search(root, code);
    if (result == NULL)
    {
        printf(" \nStudent with mark  not found\n");
    }
    else
    {
        printf("\nStudent with mark  found: code = %d, name = %s, mark = %.2f\n", result->code, result->l_name, result->mark);
    }
}
void bfs(struct s_tree *root)
{
    if (root == NULL)
        return;
    bfs(root->left);
    printf("code: %d, l_name: %s, mark: %f\n", root->code, root->l_name, root->mark);
    bfs(root->right);
}

void dfs(struct s_tree *root)
{
    if (root == NULL)
        return;

    printf("code: %d, l_name: %s, mark: %f\n", root->code, root->l_name, root->mark);
    dfs(root->left);
    dfs(root->right);
}
int main()
{
    // create_marks_csv();
    // csvintotree(&root);
    // printInOrder(root);
    // searchResult(root, 8);
    // delet(&root);
    // bfs(root);
    // dfs(root);

    int Number;
    struct s_tree *root = NULL;
    int option;
    while (1)
    {
        printf("\n *******************************************************\n");
        printf("\n *  list of the students in a binary search tree BST:  *\n");
        printf("\n *    1. Create The file data.csv                      *\n");
        printf("\n *    2. The file data.csv in to BST                   *\n");
        printf("\n *    3. Display                                       *\n");
        printf("\n *    4. delet                                        *\n");
        printf("\n *    5. SERCH                                         *\n");
        printf("\n *    6. BFS                                            *\n");
        printf("\n *    7. DFS                                            *\n");
        printf("\n *    8. Quit                                          *\n");
        printf("\n *******************************************************\n");
        printf("\n Choose an option [1-8] : ");
        scanf("%d", &option);
        switch (option)
        {
        case 1: /* Create The file data.csv  */

            create_marks_csv();
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 2: /* The file data.csv in to BST  */
            csvintotree(&root);
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 3: /*  Display  */
            printInOrder(root);
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 4:
            delet(&root);
            printInOrder(root);
            printf("\n Press any key to continue... ");
            getch();
            break;

        case 5:
            printf("Enter the code   : ");
            scanf("%d", &Number);
            searchResult(root, Number);
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 6:
            bfs(root);
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 7:

            dfs(root);
            printf("\n Press any key to continue... ");
            getch();
            break;
        case 8:
            printf(" \n ================");
            printf(" \n *    THE END   *");
            printf(" \n ================");
            return 0;
            break;
        default:
            printf("Invalid Option. Please Try again.");
            getch();
        }
    }
    return 0;
}
