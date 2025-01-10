#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h> 
#include <io.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "display.h"
#include "files.h"
//Code Update; Basic add and delete - 12/21/2024
//Works through scan-f 
//Task: create a function that creates a file of the family_tree when creating a family tree

#define MAX_TREES 100
struct Node* trees[MAX_TREES];
#define MAX_NAME_LENGTH 100
int tree_count = 0;

 typedef struct Node{
    
    char* name; //Name of the member
    char* business_name;
    char* role;
    struct Node* left; //pointer's
    struct Node* right;
    struct Node* parent;
    float wealth,commissioned_earned;
    int level;

 }Node;
//Function Prototypes
 int create_tree();//rheina
    void display_employees_by_level(Node* current);
    void display_commission_by_level(Node* head);
    void postorder_traversal(Node* root);
    void distribute_wealth_to_parent(Node* child_node, const char* filename);
   Node* create_node(const char* name, const char* business_name,const char* role ,float wealth, float commissioned_earned);//rheina 12/14/2024
    bool member_exists(const char* family_file, const char* member_name);//Kirt
    void print_branch(const Node* root, int depth);
    int parent_exists(FILE* file, const char* parent_name);//Rose mae
    Node* find_parent(Node* root, const char* parent_name);//Rose mae 
    Node* read_family_data(const char* filename);//Rheina
    void display_tree(Node* root, int level);//Erps
    Node* create_node_from_line(const char* line);
    void display_tree_recursive(Node* root, int level);//Monick
    int check_member_eligibility(const char *member_name, const char *family_file, float min_capital);//Erps
    void generate_job_outcome(const char *family_name, const char *member_name, const char *job_type, float monthly_salary, int requires_degree);//Erps
    void print_menu();//Rheina 
    // Create a function that creates a file of the family_tree when creating a family tree
    void create_family_tree_file(const char* family_name);
    Node* insert_node(Node* root, Node* new_node);
    void print_tree(Node* root);
    void preorder_traversal(Node* root);
    void inorder_traversal(Node* root);
    void delete_member_from_file(const char* filename, const char* member_name);
    Node* search_member(Node* root, const char* name);
    Node* store_family_data(const char* filename);
    float generate_investment_profit(float investment, int investment_type, float loss_margin);
    void employee_invest(Node* employee,const char* company_name, const char* file_name);
    void update_member_in_file(const char* filename, Node* member);
  
   void log_investment_progress(const char* company_name, Node* employee, int investment_type, float investment, float profit, float commission);
  
   
 //MAIN METHOD 
    
    int main (){

    int choice_66,enter;
    srand(time(NULL));
    int choice;
    char family_name[MAX_NAME_LENGTH];
    char fam_name  [265];
    Node* head = NULL;
    char family_filename[150],member_name[100];
    Node* employee = NULL;
    

    
    while (1) {
        

        
        display_menu();
        
    
    
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle user's choice
        switch (choice) {
            
            case 1:
            //Company option
            printf("Starting A Company \n");
            
            create_tree(); 
            display_progress_bar_company();

            printf("\nDone Creating A Company\n: ");
            printf("\nPress 1 To Continue: ");
            scanf("%d", &enter);
             
            break;

            case 2:
            //Employee Option
            printf("\nAvailable Companies \n");
            display_family_trees();

            printf("\nEnter THe Company to store them to Nodes: ");
            while (getchar() != '\n' && getchar() != EOF);
            fgets(family_name, sizeof(family_name), stdin);
            family_name[strcspn(family_name, "\n")] = 0;

            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);

            add_family_member(); // can now stored
            
            head = store_family_data(family_filename);
            printf("\nRecruitment Done\n");

            printf("\nPress 1 To Continue: ");
            scanf("%d", &enter);
             
                break;

            case 3:
            //Layoff Option
                printf("\nAvailable Companies \n");
                display_family_trees();

                printf("\nChoose company to Layoff An Employee:");
                
                while (getchar() != '\n' && getchar() != EOF);
                fgets(family_name, sizeof(family_name), stdin);
                family_name[strcspn(family_name, "\n")] = 0;

                snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);
                print_tree(head);
                
                printf("Enter the name of the member to delete: ");
                scanf("%s", member_name);

                delete_member_from_file(family_filename,member_name);
                printf("\nPress 1 To Continue: ");
                scanf("%d", &enter);
                break;
            case 4:
            //Investment
            printf("Choose a Company To Start investing\n");
            display_family_trees();

            while (getchar() != '\n' && getchar() != EOF);
            fgets(family_name, sizeof(family_name), stdin);
            family_name[strcspn(family_name, "\n")] = 0;

            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);

            display_family_tree(family_name);
            head = store_family_data(family_filename);

            printf("\nChoose Employee To Start Investing\n");
            scanf("%s", member_name);

            employee = search_member(head, member_name);
             if (employee != NULL) {
                printf("Member found: %s, Business: %s, Role: %s, Wealth: %.2f\n",
               employee->name, employee->business_name, employee->role, employee->wealth);
                    employee_invest(employee,family_name,family_filename); // Call the investment function
                    
                } else {
                    printf("Employee '%s' not found in the family tree.\n", member_name);
                }
               
                break;
            case 5:
            char search_name[100];

            printf("Choose a Company To Search A Member\n");
            
            display_family_trees();

            scanf("%s",family_name); // Remove newline character

            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);

            head = store_family_data(family_filename);
            
            display_tree(head,0);

            printf("Enter the name of the member to search: ");
            
            while (getchar() != '\n' && getchar() != EOF);
            fgets(search_name, sizeof(search_name), stdin);
            search_name[strcspn(search_name, "\n")] = 0; // Remove newline character

            Node* found_member = search_member(head, search_name);
            if (found_member != NULL) {
            printf("\nMember found: %s, Business: %s, Role: %s, Wealth: %.2f, Level: %d\n,Recruiter: %s\n",
               found_member->name, found_member->business_name, found_member->role, found_member->wealth, found_member->level, found_member->parent->name);
             } else {
            printf("Member %s not found in the family tree.\n", search_name);
            }          

            printf("\nPress 1 To Continue: ");
            scanf("%d", &enter);
                break;
           
            case 6:
            int choice_company = 0;
            printf("Choose a Company To Access Accounting Quarters\n");
            display_family_trees();

            printf("\nEnter Company Name\n");

            scanf("%s", family_name);

            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);
            head = store_family_data(family_filename);
                
                while(choice_company != 5){
                    
                    printf("\nWelcome to The %s Accounting Quarters\n", family_name);

                    printf("\n1.Display Investment Progress\n");
                    printf("2.Distribute Wealth To Employees(CEO)\n");
                    printf("3.Distribute Profit Back To Recruiters\n");
                    printf("4.Distribute all profits back to CEO\n");
                    printf("5.Return to Menu\n");

                    printf("\nEnter Choice:\n");
                    scanf("%d",&choice_company);
                    switch(choice_company){
                        case 1:
                          
                        printf("Company Comission Members\n");
                        display_commission_by_level(head);

                        display_investment_progress(family_name);
                        printf("\nPress 1 To Continue: ");
                        scanf("%d", &enter);

                        break;

                        case 2:

                        display_progress_bar_distribution();
                        distribute_wealth_to_employees(family_filename);
                        head = store_family_data(family_filename);

                        printf("\nPress 1 To Continue: ");
                        scanf("%d", &enter);

                        break;

                        case 3:

                        print_tree(head);

                        printf("\nEnter the name of the member to search: ");
                        
                        scanf("%s", search_name);

                        Node* company_member = store_family_data(family_filename);
                            company_member = search_member(head, search_name);
                       
                            if (company_member != NULL) {
                            printf("\nMember found: %s, Business: %s, Role: %s, Wealth: $ %.2f, Level: %d\n,Recruiter: %s\n",
                            company_member->name, company_member->business_name, company_member->role, company_member->wealth, company_member->level, company_member->parent->name);
                            } else 
                                {
                                printf("Member %s not found in the family tree.\n", search_name);
                                } 
                        display_progress_bar_distribution();
                        distribute_wealth_to_parent(company_member, family_filename);
                        head = store_family_data(family_filename);

                        printf("\nPress 1 To Continue: ");
                        scanf("%d", &enter);
                        
                        break;

                        case 4:
                            display_progress_bar_distribution();
                            
                            redistribute_wealth(family_filename);
                            display_family_tree(family_name);

                            printf("\nPress 1 To Continue: ");
                            scanf("%d", &enter);

                        break;

                        case 5:

                        printf("Returning to Menu\n");
                        choice_company = 5;

                        break;

                        default:
                        printf("Invalid choice! Please try again.\n");
                        break;
                    }
                }
            


             break;
                
            case 7:
            display_family_trees();
            printf("\nEnter Company Name: ");

            scanf("%s", family_name);
            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);

            head = store_family_data(family_filename);
            
            printf("Company Comission Members\n");
            
            display_family_tree(family_name);
            display_commission_by_level(head);
            display_investment_progress(family_name);

            printf("\nPress 1 To Continue: ");
            scanf("%d", &enter);
            
            
                
                break;
            case 8:
            display_family_trees();
            delete_family_file();

            printf("\nPress 1 To Continue: ");
            scanf("%d", &enter);
                break;
            
            case 9:
    
            int input = 0;
            printf("\nCompany Hierachy\n");
            display_family_trees();
            printf("\nEnter Company Name: ");

            scanf("%s", family_name);
            snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);
            
            head = store_family_data(family_filename);

            display_tree(head,0);

            

            

            while(input != 4){
                
            printf("\n1.Inorder Travesal\n");
            printf("2.Preorder Travesal\n");
            printf("3.PostOrder Travesa\n");
            printf("4.Return Menu\n");

            printf("Enter Choice:\n");
            scanf("%d",&input);
                switch(input){
                    case 1:
                    printf("\nInorder Travesal\n");
                    inorder_traversal(head);

                    printf("\nPress 1 To Continue\n");
                    scanf("%d", &enter);
                    break;
                    
                    case 2:
                    printf("\nPreorder Travesal\n");
                    preorder_traversal(head);

                    printf("\nPress 1 To Continue\n");
                    scanf("%d", &enter);
                    break;

                    case 3:
                    printf("\nPostOrder Travesal\n");
                    postorder_traversal(head);

                     printf("\nPress 1 To Continue\n");
                    scanf("%d", &enter);
                    break;

                    case 4:
                    printf("\nReturning to Menu\n");
                    
                    break;

                    default:

                    break;

                }
            }

           

            break;
            case 10:
            exit(1);
            
            break;


            case 66:
            
            printf("We dont talk about Number 66 @!*#!@*** !@*#*!@ #elp ");
            delete_all_family_files();
            printf("Press To Continue\n");
            scanf("%d", &choice_66);


            break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
    }
//MAIN METHOD

//Operation: Read And Store Function to Binary Tree
//First Step 1; Create Node //Working 
Node* create_node(const char* name, const char* business_name,const char* role ,float wealth, float commissioned_earned) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->name = strdup(name);               // Copy the name into the node
    new_node->business_name = strdup(business_name); // Copy the business name into the node
    new_node->wealth = wealth;                   // Set wealth
    new_node->commissioned_earned = commissioned_earned; // Set commissions earned
    new_node->left = NULL;                       // Initialize left and right to NULL
    new_node->right = NULL;
    new_node->parent = NULL;  
    new_node->role =   strdup(role);
    new_node->level = -1;            // Parent is NULL initially
    return new_node;
}
Node* read_family_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    Node* root = NULL;
    char line[200];
    char name[100], business_name[100], role[100];
    float wealth, commissioned_earned;

    while (fgets(line, sizeof(line), file)) {
        // Parse the data from each line in the file
        int scanned = sscanf(line, " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &wealth, business_name, &commissioned_earned);

        if (scanned != 5) { // Expecting 5 fields: role, name, wealth, business_name, commissioned_earned
            printf("Invalid line format: %s", line);
            continue; // Skip this line if it doesn't match the expected format
        }

        // Create a new node and assign data
        Node* new_member = create_node(name, business_name, role, wealth, commissioned_earned);

        // Add this new node to the family tree (root will be set for the first member)
        if (root == NULL) {
            root = new_member; 
            root->level = 0;
            printf("\nAdded Member in Node : %s, Business: %s, Wealth: %.2f, Commissioned Earned: %.2f\n", 
                   new_member->name, new_member->business_name, new_member->wealth, new_member->commissioned_earned);
        } else {
            root = insert_node(root, new_member);
            printf("\nAdded Member in Node : %s, Business: %s, Wealth: %.2f, Commissioned Earned: %.2f\n", 
                   new_member->name, new_member->business_name, new_member->wealth, new_member->commissioned_earned);
                   print_tree(root);
        }
    }

    fclose(file);
    return root;
}
Node* insert_node(Node* root, Node* new_node) {
    if (root == NULL) {
        //For conditional para no error 
        new_node->level = 0;  
        return new_node;
    }

   // Insertion logic: Insert based on some criteria (e.g., name or wealth)
if (new_node->wealth < root->wealth) { // Example: Insert based on wealth
    if (root->left == NULL) {
        new_node->parent = root;
        new_node->level = root->level + 1;  // Assign level based on parent's level
        root->left = new_node;  // Insert as left child
    } else {
        insert_node(root->left, new_node); // Recur on the left subtree
    }
} else {
    if (root->right == NULL) {
        new_node->parent = root;
        new_node->level = root->level + 1;  // Assign level based on parent's level
        root->right = new_node;  // Insert as right child
    } else {
        insert_node(root->right, new_node); // Recur on the right subtree
    }
}

// Return the root of the modified tree
    return root;
}
void print_tree(Node* root) {
    if (root == NULL) {
        return;
    }

    printf("Member: %s, Level: %d, Wealth: %.2f , Recruiter: %s\n", root->name, root->level, root->wealth,root->parent ? root->parent->name : "NULL");
    print_tree(root->left);
    print_tree(root->right);
}
void preorder_traversal(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("Name: %s,\n",
           root->name);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}
void inorder_traversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder_traversal(root->left);
     printf("Name: %s,\n",
           root->name);
    inorder_traversal(root->right);
}
void postorder_traversal(Node* root) {
    if (root == NULL) {
        return;
    }
    
    // First, traverse the left subtree
    postorder_traversal(root->left);
    
    // Then, traverse the right subtree
    postorder_traversal(root->right);
    
    // Finally, process the root node
     printf("Name: %s,\n",
           root->name);
}
Node* search_member(Node* root, const char* name) {//Working as long as the store if first
    // Base case: if the current node is NULL, return NULL
    if (root == NULL) {
        return NULL;
    }

    // Check if the current node's name matches the search name
    if (strcmp(root->name, name) == 0) {
        return root; // Member found
    }

    // Recursively search in the left and right subtrees
    Node* found_node = search_member(root->left, name);
    if (found_node != NULL) {
        return found_node; // Found in the left subtree
    }
    return search_member(root->right, name); // Search in the right subtree
}
Node* store_family_data(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }

    Node* root = NULL;
    char line[200];
    char name[100], business_name[100], role[100];
    float wealth, commissioned_earned;

    while (fgets(line, sizeof(line), file)) {
        // Parse the data from each line in the file
        int scanned = sscanf(line, " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &wealth, business_name, &commissioned_earned);

        if (scanned != 5) { // Expecting 5 fields: role, name, wealth, business_name, commissioned_earned
            
            continue; // Skip this line if it doesn't match the expected format
        }

        // Create a new node and assign data
        Node* new_member = create_node(name, business_name, role, wealth, commissioned_earned);

        // Add this new node to the family tree (root will be set for the first member)
        if (root == NULL) {
            root = new_member; 
            root->level = 0;
            printf("\nDone Adding to Binary Nodes\n");
            
        } else {
            root = insert_node(root, new_member);    
        }
    }

    fclose(file);
    return root;
}
int create_tree() { // Rheina // Change
    // Check if the tree count exceeds the maximum allowed
    if (tree_count >= MAX_TREES) {
        printf("\nTree Capacity is Full\n");
        return tree_count;
    }

    // Prompt for family name
    char family_name[100];
    printf("\nEnter  Name of The Company: ");
    scanf("%s", family_name);

    // Ensure the "family_trees" folder exists
    #ifdef _WIN32
        mkdir("family_trees");  // For Windows
    #else
        mkdir("family_trees", 0777);  // For Linux/Unix
    #endif

    // Create the family file inside the "family_trees" folder
    char family_filename[150];
    snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);
    FILE* family_file = fopen(family_filename, "w");
    if (family_file == NULL) {
        printf("\nError creating family file in the family_trees folder\n");
        return tree_count;
    }

    // Prompt for root member details
    char root_name[100], business[100];
    int total_commissioned_earners = 0; // Default value

    // Collect root member details
    printf("\nEnter Head Member's Name: "); // Fix: Able to input white_spaces
    // Clear any leftover newline character from previous input
    while (getchar() != '\n' && getchar() != EOF);
    fgets(root_name, sizeof(root_name), stdin);
    root_name[strcspn(root_name, "\n")] = 0;  // Remove trailing newline

    // Set Starting Wealth (Current Wealth) to 100,000 Pesos
    float current_wealth = 100000.0;

    printf("Enter Head Member's Business Type: ");
    fgets(business, sizeof(business), stdin);
    business[strcspn(business, "\n")] = 0;  // Remove trailing newline
    
    printf("\nStarting Wealth $100k");

    // Write root member details to the file
    fprintf(family_file, "Head,%s,%.2f,%s,%d\n", 
            root_name, 
            current_wealth, 
            business, 
            total_commissioned_earners);  
    
    // Close the family file
    fclose(family_file);

    // Append to the family_trees.txt file
    FILE* trees_file = fopen("family_trees.txt", "a");
    if (trees_file == NULL) {
        printf("\nError opening family_trees.txt\n");
        return tree_count;
    }
    fprintf(trees_file, "%s,%s\n", family_name, family_filename);
    fclose(trees_file);

    // Increment the tree count after successfully creating the tree
    return tree_count++;
}
void delete_member_from_file(const char* filename, const char* member_name) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    FILE* temp_file = fopen("temp.txt", "w");
    if (temp_file == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[200];
    int found = 0;

    // Read the file line by line
    while (fgets(line, sizeof(line), file)) {
        char name[100];
        sscanf(line, "%*[^,],%99[^,]", name); // Extract the name field

        // Check if the name matches the member to be deleted
        if (strcmp(name, member_name) != 0) {
            fputs(line, temp_file); // Write to the temp file if it's not the target member
        } else {
            found = 1; // Mark that we found and skipped the target member
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace the original file with the temporary file
    if (found) {
        remove(filename); // Delete the original file
        rename("temp.txt", filename); // Rename the temp file to the original filename
        printf("Member '%s' successfully deleted from the file.\n", member_name);
    } else {
        printf("Member '%s' not found in the file.\n", member_name);
        remove("temp.txt"); // Cleanup: delete the temp file if no changes
    }
}
void display_family_trees(){//12/14/2024working it display tree //Rheina
    FILE* file = fopen("family_trees.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open family_trees.txt\n");
        return;
    }

    
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char family_name[100], filename[100];
        if (sscanf(line, "%[^,],%s", family_name, filename) == 2) {
            printf("- %s (File: %s)\n", family_name, filename);
        }
    }

    fclose(file);
}
void delete_all_family_files() {//Working it  but it deletes the folder :(( kapoy debug kana na lnag))
     // Open the family_trees.txt file
    FILE* trees_file = fopen("family_trees.txt", "r");
    if (trees_file == NULL) {
        printf("\nError opening family_trees.txt\n");
        return;
    }

    char line[256];
    char file_path[150];

    // Read each line from the family_trees.txt file
    while (fgets(line, sizeof(line), trees_file)) {
        char family_name[100], family_filename[110];
        if (sscanf(line, "%[^,],%s", family_name, family_filename) == 2) {
            // Construct the file path for deletion
            snprintf(file_path, sizeof(file_path), "%s", family_filename);

            // Delete the family file
            if (remove(file_path) == 0) {
                printf("Deleted: %s\n", file_path);
            } else {
                printf("Failed to delete: %s\n", file_path);
            }
        }
    }
    fclose(trees_file);

    // Clear the contents of family_trees.txt
    trees_file = fopen("family_trees.txt", "w");
    if (trees_file != NULL) {
        fclose(trees_file);
        printf("Cleared family_trees.txt\n");
    } else {
        printf("Error clearing family_trees.txt\n");
    }

    // Remove the "family_trees" folder (must be empty first)
#ifdef _WIN32
    _rmdir("family_trees");
#else
    rmdir("family_trees");
#endif

    printf("\nAll family files and records have been deleted.\n");
}
void delete_family_file() {//Working, 12/21/2024 it now delete

     char family_name[100];
    
    // Prompt user to enter the family name
    printf("\nEnter the family name to delete: \n");
    scanf("%s", family_name);

    // Construct the correct file path
    char family_filename[110];
    snprintf(family_filename, sizeof(family_filename), "family_trees/%s.txt", family_name);

    // Debug: Print the constructed file path
    printf("\nTrying to delete file: %s\n", family_filename);

    // Delete the specified family file
    if (remove(family_filename) == 0) {
        printf("Deleted family file: %s\n", family_filename);
    } else {
        printf("Failed to delete family file: %s\n", family_filename);
        return;
    }

    // Update the family_trees.txt file
    FILE* trees_file = fopen("family_trees.txt", "r");
    if (trees_file == NULL) {
        printf("\nError opening family_trees.txt\n");
        return;
    }

    FILE* temp_file = fopen("temp_family_trees.txt", "w");
    if (temp_file == NULL) {
        printf("\nError creating temporary file\n");
        fclose(trees_file);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), trees_file)) {
        char existing_family_name[100], existing_family_filename[110];
        if (sscanf(line, "%[^,],%s", existing_family_name, existing_family_filename) == 2) {
            // Write all other entries except the one to delete
            if (strcmp(existing_family_name, family_name) != 0) {
                fprintf(temp_file, "%s,%s\n", existing_family_name, existing_family_filename);
            }
        }
    }

    fclose(trees_file);
    fclose(temp_file);

    // Replace the old file with the updated one
    if (remove("family_trees.txt") == 0) {
        rename("temp_family_trees.txt", "family_trees.txt");
        printf("Updated family_trees.txt to remove %s\n", family_name);
    } else {
        printf("Error updating family_trees.txt\n");
    }
}
void add_family_member() {
    // Display all family trees
    char family_name[100];
    printf("\nEnter the name of the company to modify: ");
    scanf("%s", family_name);

    // Build the family file path
    char family_file[110];
    snprintf(family_file, sizeof(family_file), "family_trees/%s.txt", family_name);

    FILE* file = fopen(family_file, "r+");  // Open for reading and writing
    if (file == NULL) {
        printf("\nCompany tree '%s' does not exist.\n", family_name);
        return;
    }

    // Step 1: Read root member details to get remaining wealth and land
    char root_name[MAX_NAME_LENGTH], business[100];
    float root_wealth, head_commissions;
    char line[256];

    if (fgets(line, sizeof(line), file)) {
        printf("\nRaw line: %s\n", line);  // Debugging line

        // Match root format: Head,Name,Wealth,Business,Commission
        if (strncasecmp(line, "Head,", 5) == 0) {
            int num_parsed = sscanf(line, 
                                     "Head,%99[^,],%f,%99[^,],%f\n", 
                                     root_name, &root_wealth, business, &head_commissions);

            // Debugging
        }
    }

    printf("Root Member: %s\n", root_name);
    printf("Business: %s\n", business);
    printf("Remaining Wealth: %.2f\n", root_wealth);

    float remaining_wealth = root_wealth;

    // Step 2: Input new member details
    Node* new_member = (Node*)malloc(sizeof(Node));
    new_member->name = (char*)malloc(100 * sizeof(char));
    fseek(file, 0, SEEK_SET);  // Reset file pointer
    FILE* temp_file = fopen("temp.txt", "w");

    while ((getchar()) != '\n' && getchar() != EOF);  // Clear input buffer
    printf("\nEnter member details:\n");

    printf("Name: ");
    fgets(new_member->name, 100, stdin);
    size_t len = strlen(new_member->name);
    if (len > 0 && new_member->name[len - 1] == '\n') {
        new_member->name[len - 1] = '\0';
    }

    // Ask if the member is allowed to inherit from the predecessor
    printf("\nGrant Recruit Investment Money? (1 for Yes, 2 for No): ");
    int permit;
    scanf("%d", &permit);
    float inheritance_wealth = 0;

    if (permit == 1) {
        printf("Enter starting investment Money ($%.2f available): ", remaining_wealth);
        scanf("%f", &inheritance_wealth);

        if (inheritance_wealth > remaining_wealth) {
            printf("\nError: Inherited wealth exceeds remaining wealth of the root member.\n");
            free(new_member->name);
            free(new_member);
            fclose(file);
            return;
        }

        // Update the remaining wealth of the root
        remaining_wealth -= inheritance_wealth;
        root_wealth = remaining_wealth;
    }

    // Write the root line with the updated wealth only once
    rewind(file);
    int root_written = 0;  // Flag to check if head has been written
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "Head,")) {  // Match the head line
            if (!root_written) {
                fprintf(temp_file, "Head,%s,%.2f,%s,%.2f\n", root_name, root_wealth, business, head_commissions);
                root_written = 1;
            }
        } else {
            fputs(line, temp_file);  // Write other lines unchanged
        }
    }

    // Append new member details
    fprintf(temp_file, "Employee,%s,%.2f,%s,0.00\n", new_member->name, inheritance_wealth, business);

    // Close and replace the original file
    fclose(file);
    fclose(temp_file);
    remove(family_file);
    rename("temp.txt", family_file);

    printf("\nMember '%s' successfully added.\n", new_member->name);

    // Free new member memory
    free(new_member->name);
    free(new_member);
}

bool member_exists(const char* family_file, const char* member_name) {//Working
    FILE* file = fopen(family_file, "r");
    if (file == NULL) {
        printf("\nUnable to open file '%s'.\n", family_file);
        return false;
    }

    char line[200];  // Buffer to store each line
    while (fgets(line, sizeof(line), file)) {
        // Extract the first token (member name) from the line
        char* token = strtok(line, ",");
        if (token != NULL && strcmp(token, member_name) == 0) {
            fclose(file);
            return true;  // Member already exists
        }
    }

    fclose(file);
    return false;  // Member not found
}
void print_branch(const Node* root, int depth) {
    if (root == NULL) {
        return;
    }

    // Print the right subtree first for proper alignment
    print_branch(root->right, depth + 1);

    // Print the current node with indentation
    for (int i = 0; i < depth; i++) {
        printf("    "); // 4 spaces for indentation
    }

    if (depth == 0) {
        printf("ROOT: %s\n", root->name); // Highlight the root
    } else {
        printf("|-- %s\n", root->name);
    }

    // Print the left subtree
    print_branch(root->left, depth + 1);
}
void display_family_tree(const char *family_name) {//Works
  char family_file[110];
snprintf(family_file, sizeof(family_file), "family_trees/%s.txt", family_name);

FILE *file = fopen(family_file, "r");
if (file == NULL) {
    printf("\nError: Family tree '%s' does not exist or cannot be opened.\n", family_name);
    return;
}

printf("\nDisplaying Company Tree: %s\n", family_name);
printf("----------------------------------------------------\n");

char line[256];
char root_name[100], business[100];
float root_wealth = 0.0, root_land = 0.0 , commissions_earned = 0.0;
int found_root = 0;

// Search for the root member
while (fgets(line, sizeof(line), file)) {
    // Match root format: ROOT,Name,wealth,business,comission
    if (strncasecmp(line, "Head,", 5) == 0) {
        sscanf(line, "Head,%99[^,],%f,%99[^,],%f",root_name, &root_wealth,business, &commissions_earned);

        found_root = 1;
        break;
    }
}

if (!found_root) {
    printf("Error: Root member not found in the family tree.\n");
    fclose(file);
    return;
}

// Display only the required information for the root member
printf("Head Member:\n");
printf("  Full Name: %s\n", root_name);
printf("  Wealth: %.2f\n", root_wealth);
printf("  Business: %s\n", business);
printf("  Commissions Earned: %.2f\n", commissions_earned);
printf("----------------------------------------------------\n");



rewind(file); // Reset file pointer to beginning

// Display family members (only Employees)
while (fgets(line, sizeof(line), file)) {
    // Check if the line starts with "Employee,"
    if (strncasecmp(line, "Employee,", 9) == 0) {
        char name[100], business[100], role[50];
        float wealth, commissions;

        // Parse the line for Employee details
        sscanf(line, "Employee,%99[^,],%f,%99[^,],%f", name, &wealth, business, &commissions);

        // Display employee details
        printf("Employee:\n");
        printf("  Full Name: %s\n", name);
        printf("  Wealth: %.2f\n", wealth);
        printf("  Business: %s\n", business);
        printf("  Total Money Earned From Commission: %.2f\n", commissions);
        printf("----------------------------------------------------\n");
    }
}

fclose(file);
}
int parent_exists(FILE* file, const char* parent_name) {
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        // Check if the parent name appears in the line (this checks for the parent node's name)
        if (strstr(line, parent_name) != NULL) {
            return 1; // Parent exists
        }
    }
    return 0; // Parent does not exist
}
//FUNCTIONS NEEDED FOR BUSINESS CREATION AND MANAGEMENT
float generate_investment_profit(float investment, int investment_type, float loss_margin) {
    float profit_margin = 0.0;

    // Define profit and loss margins for each investment type
    switch (investment_type) {
        case 1: // Crypto
            profit_margin = ((rand() % 41) + 10) / 100.0; // 10% to 60% profit
            loss_margin += ((rand() % 21) + 10) / 100.0; // 10% to 40% loss
            break;
        case 2: // Real Estate
            profit_margin = ((rand() % 31) + 20) / 100.0; // 20% to 50% profit
            loss_margin += ((rand() % 21) + 5) / 100.0; // 5% to 25% loss
            break;
        case 3: // Business
            profit_margin = ((rand() % 21) + 15) / 100.0; // 15% to 35% profit
            loss_margin += ((rand() % 21) + 5) / 100.0; // 5% to 25% loss
            break;
        default:
            return 0.0; // Invalid investment type
    }

    // Randomly determine if the investment is a profit or a loss
    if (rand() % 2 == 0) { // 50% chance of profit
        return investment * profit_margin;
    } else { // 50% chance of loss
        return -investment * loss_margin;
    }
}
void calculate_entire_networth_family(const char *family_name) {//Requiresments  (need to calcukate inckuding the root member)
    char family_file[110]; //
    snprintf(family_file, sizeof(family_file), "family_trees/%s.txt", family_name);
   
    FILE *file = fopen(family_file, "r");
    if (file == NULL) {
        printf("\nError: Family tree '%s' does not exist or cannot be opened.\n", family_name);
        return;
    }

    float total_networth = 0.0;
    char line[256];

    // Iterate through each line in the family file
    while (fgets(line, sizeof(line), file)) {
        char role[20];
        float wealth;

        // Parse the line to extract the role and wealth
        if (sscanf(line, "%*[^,],%*[^,],%*[^,],%f,%*[^,],%*[^,]", &wealth) == 1) {
            total_networth += wealth;
        }
    }

    fclose(file);

    // Display the total net worth of the family
    printf("\nTotal Net Worth of Family '%s': %.2f\n", family_name, total_networth);
}
void employee_invest(Node* employee, const char* company_name, const char* file_name) {
    float investment;
    int investment_type;
    float loss_margin = 0.0;

    while (1) { // Start an infinite loop
        // Prompt user for investment type
        display_diamond();
        printf("\nChoose an investment type:\n");
        printf("1. Crypto\n");
        display_house();
        printf("2. Real Estate\n");

        printf("3. Business\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &investment_type);

        printf("Current wealth: $%.2f\n", employee->wealth);
        printf("How much would you like to invest? ");
        scanf("%f", &investment);

        display_progress_bar_investment();

        // Generate profit or loss based on the chosen investment type
        float profit = generate_investment_profit(investment, investment_type,loss_margin);
        
        if (profit > 0) {
            // Adjust commission rates based on employee level
            float commission_rate;
            if(employee->level == 0){
                commission_rate = 1.0;
            }
            else if (employee->level == 1) {
                commission_rate = 0.20; // 20% for level 1
            } else if (employee->level == 2) {
                commission_rate = 0.10; // 10% for level 2
            } else if (employee->level >= 3) {
                commission_rate = 0.05; // 5% for level 3 and below
            }

            float commission = profit * commission_rate;
            employee->wealth += profit; // Update wealth with profit
            employee->commissioned_earned += commission; // Update commissioned earned
            
            printf("\n-------------------------------------------------------------\n");
            printf("%s invests $%.2f in ", employee->name, investment);
            printf("chosen investment type and earns a profit of $%.2f.\n", profit);
            printf("Commission earned: $%.2f.\n", commission);
            printf("\n-------------------------------------------------------------\n");

            log_investment_progress(company_name, employee, investment_type, investment, profit, commission);
             loss_margin -= 0.001;
        } else {
            float commission_loss = 0.0;
            employee->commissioned_earned += commission_loss;
            employee->wealth += profit; // Update wealth with loss
             printf("\n-------------------------------------------------------------\n");
            printf("\n%s invests $%.2f in ", employee->name, investment);
            printf("\nchosen investment type and incurs a loss of $%.2f.\n", -profit);
            printf("\n-------------------------------------------------------------\n");
            loss_margin += 0.003;//Adjust the loss margin
            log_investment_progress(company_name, employee, investment_type, investment, profit, commission_loss);
        }

        // Ask if the user wants to invest again
        char choice;
        printf("Would you like to invest again? (y/n): ");
        scanf(" %c", &choice); // Note the space before %c to consume any leftover newline character
        update_member_in_file(file_name,employee);
        if (choice != 'y' && choice != 'Y') {
            break; // Exit the loop if the user does not want to invest again
        }
    }
}
void update_member_in_file(const char* filename, Node* member) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Temporary storage for the file data
    char lines[100][100]; // Assuming a maximum of 100 lines
    int line_count = 0;

    // Read all lines from the file
    while (fgets(lines[line_count], sizeof(lines[line_count]), file) != NULL) {
        line_count++;
    }
    fclose(file);

    // Open the file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Update the member's wealth and commission
    for (int i = 0; i < line_count; i++) {
        char role[100], member_name[100], business_name[100];
        float wealth, commission;

        // Parse the line
        int scanned = sscanf(lines[i], " %99[^,],%99[^,],%f,%99[^,],%f", role, member_name, &wealth, business_name, &commission);
        if (scanned == 5 && strcmp(member_name, member->name) == 0) {
            // Update the wealth and commission
            wealth = member->wealth;
            commission = member->commissioned_earned;
            printf("Updating %s: New Wealth: $%.2f, New Commission: $%.2f\n", member_name, wealth, commission);
        }

        // Write the updated or original line back to the file
        fprintf(file, "%s,%s,%.2f,%s,%.2f\n", role, member_name, wealth, business_name, commission);
    }

    fclose(file);
}
void display_tree(Node* root, int space){
    if (root == NULL) {
        return;
    }

    // Increase distance between levels
    space += 10;

    // Process right child first
    display_tree(root->right, space);

    // Print current node after space
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", root->name);

    // Process left child
    display_tree(root->left, space);
}
void distribute_wealth_to_employees(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return;
    }

    // Temporary storage for file lines
    char lines[100][200];
    int line_count = 0;

    // Read all lines from the file
    while (fgets(lines[line_count], sizeof(lines[line_count]), file) != NULL) {
        line_count++;
    }
    fclose(file);

    // Extract head wealth
    char head_role[50], head_name[100], head_business[100];
    float head_wealth, head_commission;
    sscanf(lines[0], " %49[^,],%99[^,],%f,%99[^,],%f", head_role, head_name, &head_wealth, head_business, &head_commission);

    printf("\nHead: %s\n", head_name);
    printf("Total Wealth Available for Distribution: %.2f\n", head_wealth);

    // Distribute wealth to employees
    float remaining_wealth = head_wealth;
    for (int i = 1; i < line_count; i++) {
        char role[50], name[100], business[100];
        float wealth, commission;

        sscanf(lines[i], " %49[^,],%99[^,],%f,%99[^,],%f", role, name, &wealth, business, &commission);

        if (strcmp(role, "Employee") == 0) {
            printf("\nEmployee: %s\n", name);
            printf("How much wealth to allocate (remaining: %.2f): ", remaining_wealth);

            float allocation;
            scanf("%f", &allocation);

            if (allocation <= remaining_wealth && allocation >= 0) {
                wealth += allocation;
                remaining_wealth -= allocation;
                printf("%s now has %.2f wealth. Remaining wealth: %.2f\n", name, wealth, remaining_wealth);

                // Update the employee's wealth in the line
                snprintf(lines[i], sizeof(lines[i]), "%s,%s,%.2f,%s,%.2f\n", role, name, wealth, business, commission);
            } else {
                printf("Invalid allocation. Cannot allocate more than the remaining wealth or a negative value.\n");
            }
        }
    }

    // Update the head's wealth after distribution
    snprintf(lines[0], sizeof(lines[0]), "%s,%s,%.2f,%s,%.2f\n", head_role, head_name, remaining_wealth, head_business, head_commission);

    // Write back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        fputs(lines[i], file);
    }

    fclose(file);
    printf("\nWealth distribution complete. File updated successfully.\n");
}
void redistribute_wealth(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Temporary storage for the file data
    char lines[100][100]; // Assuming a maximum of 100 lines
    int line_count = 0;

    // Read all lines from the file
    while (fgets(lines[line_count], sizeof(lines[line_count]), file) != NULL) {
        line_count++;
    }
    fclose(file);

    // Variables for calculating the wealth redistribution
    float head_wealth = 0;
    float employee_total_wealth = 0;
    int head_line_index = 0;

    // Parse the first line (head) separately
    char head_role[100], head_name[100], head_business[100];
    float head_commission;
    sscanf(lines[head_line_index], " %99[^,],%99[^,],%f,%99[^,],%f", head_role, head_name, &head_wealth, head_business, &head_commission);

    // Debug output to verify the parsed data
    printf("Head: %s, Wealth: %.2f\n", head_name, head_wealth);

    // Process employee lines
    for (int i = 1; i < line_count; i++) {
        char role[100], name[100], business[100];
        float wealth = 0, commission = 0;

        // Parse the employee data
        sscanf(lines[i], " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &wealth, business, &commission);

        // Debug output to verify employee data
        printf("Employee: %s, Wealth: %.2f\n", name, wealth);

        // Sum up the wealth and set it to 0
        employee_total_wealth += wealth;
        wealth = 0;

        // Update the line with the new wealth (0)
        snprintf(lines[i], sizeof(lines[i]), "%s,%s,%.2f,%s,%.2f", role, name, wealth, business, commission);
    }

    // Add employee total wealth to the head's wealth
    head_wealth += employee_total_wealth;

    // Update the head's line
    snprintf(lines[head_line_index], sizeof(lines[head_line_index]), "%s,%s,%.2f,%s,%.2f", head_role, head_name, head_wealth, head_business, head_commission);

    // Debug output to verify the new head wealth
    printf("Updated Head: %s, New Wealth: %.2f\n", head_name, head_wealth);

    // Write the updated data back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);
    }
    fclose(file);

    printf("Wealth redistribution complete!\n");
}

void log_investment_progress(const char* company_name, Node* employee, int investment_type, float investment, float profit, float commission) {
    char progress_filename[150];
    snprintf(progress_filename, sizeof(progress_filename), "%s_progress.txt", company_name); // Generate filename
    
    FILE* file = fopen(progress_filename, "a"); // Open file in append mode
    if (file == NULL) {
        printf("Error: Could not open file '%s' for writing.\n", progress_filename);
        return;
    }

    // Determine investment type as a string
    char investment_type_str[20];
    switch (investment_type) {
        case 1: strcpy(investment_type_str, "Crypto"); break;
        case 2: strcpy(investment_type_str, "Real Estate"); break;
        case 3: strcpy(investment_type_str, "Business"); break;
        default: strcpy(investment_type_str, "Unknown"); break;
    }

    // Write investment progress to the file
    fprintf(file, "Employee: %s\n", employee->name);
    fprintf(file, "Investment Type: %s\n", investment_type_str);
    fprintf(file, "Invested Amount: $%.2f\n", investment);
    if (profit > 0) {
        fprintf(file, "Profit/Loss: Profit of $%.2f\n", profit);
    } else {
        fprintf(file, "Profit/Loss: Loss of $%.2f\n", -profit); // Show loss as positive value
    }
    fprintf(file, "Commission Earned: $%.2f\n", commission);
    fprintf(file, "--------------------------------------------\n");

    fclose(file); // Close the file
    printf("Investment progress logged to '%s'.\n", progress_filename);
}
void display_investment_progress(const char* company_name) {

    char progress_filename[150];
    snprintf(progress_filename, sizeof(progress_filename), "%s_progress.txt", company_name); // Generate filename
    
    FILE* file = fopen(progress_filename, "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error: Could not open file '%s' for reading.\n", progress_filename);
        return;
    }

    char line[256]; // Buffer to hold each line read from the file
    printf("\n---- Investment Progress for %s ----\n", company_name);
    
    // Read and display each line from the file
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line); // Print each line
    }

    fclose(file); // Close the file
}
void display_commission_by_level(Node* head) {
    if (head == NULL) {
        printf("No members in the tree.\n");
        return;
    }

    // Display head member (Level 0)
    printf("Head: %s\n", head->name);
    printf("Commission: 100%%\n");  // Head gets 100% commission

    // Display employees and their commission based on their level
    printf("\nEmployee Boards :\n");

    // Use a helper function to display employees based on their level
    display_employees_by_level(head);
}
void display_employees_by_level(Node* current) {
    if (current == NULL) {
        return;
    }

    // Calculate commission based on level
    float commission_rate = 0;
    if(current->level == 0){
    commission_rate = 1.0;
    }
    else  if (current->level == 1) {
        commission_rate = 0.20;  // 20% for level 1
    } else if (current->level == 2) {
        commission_rate = 0.10;  // 10% for level 2
    } else if (current->level >= 3) {
        commission_rate = 0.05;  // 5% for level 3 and below
    }

    // Print employee information with commission
    printf("\nEmployee: %s\n", current->name);
    printf("Commission: %.0f%%\n", commission_rate * 100);
    
    // Check if the parent is NULL before accessing its name
    if (current->parent != NULL) {
        printf("Recruiter: %s\n", current->parent->name);
    } else {
        printf("Recruiter: None (This is the head)\n");
    }

    // Recursively display employees in left and right subtrees
    display_employees_by_level(current->left);
    display_employees_by_level(current->right);
}
void display_progress_bar_investment() {
    const char* messages[] = {
        "Simulating market fluctuations",
        "Processing inflations          ",
        "Modeling potential growth",
        "Projecting long-term investment growth ",
        "Simulating price fluctuations         ",
        "Finalizing results           "
    };

    int total_steps = sizeof(messages) / sizeof(messages[0]);

    for (int i = 0; i < total_steps; i++) {
        // Calculate the percentage completed
        int percentage = (i + 1) * 100 / total_steps;

        // Display the progress message
        printf("\r[%s] %s...", i == total_steps - 1 ? "####" : "", messages[i]);
        printf("\nProgress: %d%%", percentage); // Display percentage below the message
        fflush(stdout);
        sleep(1); // Simulate processing time
    }

    printf("\nDone!\n");
}
void display_progress_bar_company() {
    const char* messages[] = {
        "Forming the company structure",
        "Developing company mission",
        "Building brand identity",
        "Setting up accounting systems",
        "Simulating price fluctuations",
        "Finalizing results"
    };

    int total_steps = sizeof(messages) / sizeof(messages[0]);

    for (int i = 0; i < total_steps; i++) {
        
        printf("\r[%s] %s...", i == total_steps - 1 ? "####" : "", messages[i]);
        fflush(stdout);
        sleep(1);
    }

    printf("\nDone!\n");
}
void display_progress_bar_distribution() {
    const char* messages[] = {
       "Analyzing current wealth distribution...",
        "Identifying eligible recipients based on contribution and role...",
        "Calculating individual shares and commissions...                  ",
        "Redistributing wealth accordingly...",
        "Finalizing adjustments and updating records...",
        "Finalizing results\n"
    };

    int total_steps = sizeof(messages) / sizeof(messages[0]);

    for (int i = 0; i < total_steps; i++) {
        
        printf("\r[%s] %s...", i == total_steps - 1 ? "####" : "", messages[i]);
        fflush(stdout);
        sleep(1);
    }
   printf("\n");
   
}
void distribute_wealth_to_parent(Node* child_node, const char* filename) {
    if (child_node == NULL) {
        printf("Invalid child node.\n");
        return;
    }

    // Get the parent's name
    char* parent_name = child_node->parent ? child_node->parent->name : NULL;
    if (parent_name == NULL) {
        printf("No parent found for the child node '%s'.\n", child_node->name);
        return;
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    // Temporary storage for the file data
    char lines[100][100]; // Assuming a maximum of 100 lines
    int line_count = 0;

    // Read all lines from the file
    while (fgets(lines[line_count], sizeof(lines[line_count]), file) != NULL) {
        // Remove newline characters if present
        lines[line_count][strcspn(lines[line_count], "\n")] = 0;
        line_count++;
        if (line_count >= 100) {
            printf("Warning: Maximum line count exceeded. Some data may not be processed.\n");
            break; // Prevent buffer overflow
        }
    }
    fclose(file);

    float child_wealth = child_node->wealth;
    float parent_wealth = 0;
    char role[100], name[100], business[100];
    float commission = 0;

    // Find the child node and its wealth
    int child_index = -1;
    for (int i = 0; i < line_count; i++) {
        if (sscanf(lines[i], " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &child_wealth, business, &commission) == 5) {
            // Check if the current node is the child node by matching the child's name
            if (strcmp(name, child_node->name) == 0) {
                child_index = i;
                break;
            }
        }
    }

    if (child_index == -1) {
        printf("Child node '%s' not found.\n", child_node->name);
        return;
    }

    // Find the parent node by searching for the parent's name
    int parent_index = -1;
    for (int i = 0; i < line_count; i++) {
        if (sscanf(lines[i], " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &parent_wealth, business, &commission) == 5) {
            if (strcmp(name, parent_name) == 0) {
                parent_index = i;
                break;
            }
        }
    }

    if (parent_index == -1) {
        printf("Parent node '%s' not found.\n", parent_name);
        return;
    }

    // Update the parent's wealth
    sscanf(lines[parent_index], " %99[^,],%99[^,],%f,%99[^,],%f", role, name, &parent_wealth, business, &commission);
    parent_wealth += child_wealth;

    // Update the parent's line in the file
    snprintf(lines[parent_index], sizeof(lines[parent_index]), "%s,%s,%.2f,%s,%.2f", role, name, parent_wealth, business, commission);

    // Update the child's wealth to 0
    child_wealth = 0;

    // Update the child's line in the file
    snprintf(lines[child_index], sizeof(lines[child_index]), "%s,%s,%.2f,%s,%.2f", child_node->role, child_node->name, child_wealth, business, commission);

    // Write the updated data back to the file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    // Write the updated lines with proper newlines for every entry
    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", lines[i]);  // Always add a newline here
    }

    fclose(file);

    printf("\nWealth distribution from child '%s' to parent '%s' complete!\n", child_node->name, parent_name);
}


void display_menu() {
    const int console_width = 60;  // Adjust console width as needed
    const char *menu_items[] = {
        "1. Start A Company",
        "2. Add Employees",
        "3. Fire Employee",
        "4. Simulate Investing",
        "5. Search Company Member",
        "6. Accounting Quarters (Profit Distribution)",
        "7. Display Company Info and Logs",
        "8. Delete A Company File",
        "9. Display A Company Members Binary Relationships",
        "10. Exit"
    };
    const int num_items = sizeof(menu_items) / sizeof(menu_items[0]);

      printf("\n************************************************************");
    printf("                          \n");
    printf("                          \n");
    printf("                        \033[1;31mINVESTMENT\033[0m \033[1;32mMODEL\033[0m               \n");
    printf("                         \n");
    printf("************************************************************\n");

    printf("\n");
    for (int i = 0; i < num_items; i++) {
        int padding = (console_width - strlen(menu_items[i])) / 2;
        printf("%*s%s\n", padding, "", menu_items[i]);
    }
    printf("\n-------------------------------------------------------------\n");
}
void display_diamond() {
    printf("\033[1;34m"); // Set text color to bold blue
    printf("  .     '     ,\n");
    printf("    _________\n");
    printf(" _ /_|_____|_\\ _\n");
    printf("   '. \\   / .'\n");
    printf("     '.\\ /.'\n");
    printf("       '.'\n");
    printf("\033[0m"); // Reset text color to default
}
void display_house() {
    printf("\033[1;32m"); // Set text color to bold green
    printf("      ':.\n");
    printf("         []_____\n");
    printf("        /\\      \\\n");
    printf("    ___/  \\__/\\__\\__\n");
    printf("---/\\___\\ |''''''|__\\-- ---\n");
    printf("   ||'''| |''||''|''|\n");
    printf("   ``\"\"\"`\"`\"))\"\"`\"\"`\n");
    printf("\033[0m"); // Reset text color to default
}
