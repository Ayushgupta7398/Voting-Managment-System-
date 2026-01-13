
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()

#define MAX_CANDIDATES 10
#define MAX_VOTERS 100

// ANSI Colors An ANSI Escape Code is a sequence of characters starting with \033 (or 0x1B in hexadecimal) 
#define RESET   "\033[0m" // normal text  is an escape sequence that represents the ASCII escape character (ESC).w
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Candidate Structure
struct Candidate {
    char name[50];
    char symbol[10];
    int votes;
};
/*if MAX_VOTERS is 100, it can store IDs for 100 voters.
[20]: Each voter's ID can be up to 19 characters long plus 1 for the null terminator (\0).*/
struct Candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;
char voted_ids[MAX_VOTERS][20];
int voter_count = 0;

// Function Prototypes
void admin_panel();
void user_panel();
void add_candidate();
void delete_candidate();
void cast_vote(char*);
void display_results();
void loading_effect();
int is_valid_id(char*);
int has_voted(char*);
void print_border();
void main_menu();

int main() {
    int choice;
    while (1) {
        main_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: admin_panel(); break;
            case 2: user_panel(); break;
            case 3: printf(YELLOW "Exiting..." RESET "\n"); return 0;
            default: printf(RED "Invalid choice! Try again.\n" RESET);
        }
    }
    return 0;
}

// Stylish Menu
void main_menu() {
    system("clear"); // Clear screen (Linux/macOS specific)
    print_border();
    printf("| " BOLD CYAN "  Voting Management System  " RESET " |\n");
    print_border();
    printf("| 1. Admin Panel                        |\n");
    printf("| 2. User Panel                         |\n");
    printf("| 3. Exit                               |\n");
    print_border();
}

// Print Border
void print_border() {
    printf("+----------------------------------+\n");
}

// Loading Effect
void loading_effect() {
    printf("Processing");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);/*fflush(stdout) makes sure the dot appears immediately, without waiting for a newline.*/
        sleep(1);
    }
    printf("\n");
}

// Admin Panel
void admin_panel() {
    char password[20];
    printf(YELLOW "Enter Admin Password: " RESET);
    scanf("%s", password);
    getchar();

    if (strcmp(password, "ayush123") != 0) {
        printf(RED "Incorrect Admin Password!\n" RESET);
        return;
    }

    int choice;
    while (1) {
        printf("\n" BOLD MAGENTA "Admin Panel\n" RESET);
        print_border();
        printf("1. Add Candidate\n");
        printf("2. Delete Candidate\n");
        printf("3. View Results\n");
        printf("4. Logout\n");
        print_border();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: add_candidate(); break;
            case 2: delete_candidate(); break;
            case 3: display_results(); break;
            case 4: return;
            default: printf(RED "Invalid choice!\n" RESET);
        }
    }
}

// Add Candidates
void add_candidate() {
    if (candidate_count >= MAX_CANDIDATES) {
        printf(RED "Candidate list is full!\n" RESET);
        return;
    }
    printf("\nEnter Candidate Name: ");
    fgets(candidates[candidate_count].name, 50, stdin);/*fgets() is used to read a line of text (up to 50 characters) from the user and store it in candidates[candidate_count].name.*/
    candidates[candidate_count].name[strcspn(candidates[candidate_count].name, "\n")] = 0;
    /*Using strcspn (or a similar method) is important to clean the input string by removing the newline character*/
    printf("Enter Candidate Symbol: ");
    fgets(candidates[candidate_count].symbol, 10, stdin);
    candidates[candidate_count].symbol[strcspn(candidates[candidate_count].symbol, "\n")] = 0;
    
    candidates[candidate_count].votes = 0;
    candidate_count++;
    printf(GREEN "Candidate Added Successfully!\n" RESET);
}

// Delete Candidate
void delete_candidate() {
    char name[50];
    printf("Enter Candidate Name to Delete: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i].name, name) == 0) {
            for (int j = i; j < candidate_count - 1; j++) {
                candidates[j] = candidates[j + 1];
            }
            candidate_count--;
            printf(GREEN "Candidate Deleted Successfully!\n" RESET);
            return;
        }
    }
    printf(RED "Candidate Not Found!\n" RESET);
}

// User Panel
void user_panel() {
    char voter_id[20];
    printf(YELLOW "Enter College ID (e.g.,1234567 ABC): " RESET);
    scanf("%s", voter_id);
    getchar();// to read the newline character left in the buffer by scanf.

    if (!is_valid_id(voter_id)) {
        printf(RED "Invalid ID Format! The first three letters must be uppercase.\n" RESET);
        return;
    }
    if (has_voted(voter_id)) {
        printf(RED "Fake Voter! You have already voted.\n" RESET);
        return;
    }
    cast_vote(voter_id);
}

// Validate College ID (First 3 uppercase letters)
int is_valid_id(char *id) {
    if (strlen(id) != 10) return 0;

    // Ensure first 3 are uppercase letters
    for (int i = 0; i < 3; i++) {
        if (id[i] < 'A' || id[i] > 'Z') return 0;
    }

    // Ensure last 7 are digits
    for (int i = 3; i < 10; i++) {
        if (id[i] < '0' || id[i] > '9') return 0;
    }

    return 1;
}

// Check If Already Voted
int has_voted(char *id) {
    for (int i = 0; i < voter_count; i++) {
        if (strcmp(voted_ids[i], id) == 0) {
            return 1; // Already voted
        }
    }
    return 0;
}

// Cast Vote
void cast_vote(char *voter_id) {
    printf("\n" BOLD CYAN "Candidates:\n" RESET);
    print_border();
    for (int i = 0; i < candidate_count; i++) {
        printf("%d. %s (%s)\n", i + 1, candidates[i].name, candidates[i].symbol);
    }
    print_border();
    
    int choice;
    printf("Enter Candidate Number to Vote: ");
    scanf("%d", &choice);
    
    if (choice < 1 || choice > candidate_count) {
        printf(RED "Invalid Choice!\n" RESET);
        return;
    }
    
    candidates[choice - 1].votes++;
    strcpy(voted_ids[voter_count++], voter_id);
    printf(GREEN "Vote Casted Successfully!\n" RESET);
}

// Display Results
void display_results() {
    printf("\n" BOLD CYAN "Election Results:\n" RESET);
    print_border();
    int max_votes = 0;
    char winner[50] = "No Winner";
/*-15 specifies that the string should be printed in a field that is 15 characters wide and left-justified (because of the minus sign).*/
/*-6 specifies that the integer should be printed in a field that is 6 characters wide and left-justified.*/
    for (int i = 0; i < candidate_count; i++) {
        printf("| %-15s | %-6d |\n", candidates[i].name, candidates[i].votes);
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
            strcpy(winner, candidates[i].name);
        }
    }
    print_border();
    printf("\n" BOLD GREEN "Winner: **%s**\n" RESET, winner);
}
