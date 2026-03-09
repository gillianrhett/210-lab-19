// COMSC-210 | Lab 18 | Gillian Rhett

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

struct Review {
    float rating;
    string comment;
    Review* next;
};

void push_front(Review*&, float, string);
void push_back(Review*&, float, string);

int main() {
    // Ask the user which mode to use, new nodes at the head or the tail of the linked list.
    cout << "Which linked list method should we use?\n";
    cout << "\t[1] New nodes are added at the head of the linked list\n";
    cout << "\t[2] New nodes are added at the tail of the linked list\n";
    cout << "Choice: ";
    string sChoice;
    int iChoice = 0;
    while (!(iChoice == 1 || iChoice ==2)) {
        cin >> sChoice;
        try { iChoice = stoi(sChoice); }
        catch (invalid_argument& e) {
            iChoice = 0;
        }
        if (!(iChoice == 1 || iChoice ==2))
            cout << "Enter a number 1 or 2: ";
    }
    // Obtain two pieces of data from the user, the rating and the comments. Store these in the linked list.
    // start the linked list
    Review* reviews = nullptr;
    string sRating;
    float fRating;
    string comment;
    char another = 'Y';
    while (another == 'Y' || another == 'y') {
        fRating = -1.0;
        cout << "Enter review rating 0-5: ";
        while (!(0.0 <= fRating && fRating <= 5.0)) {
            cin >> sRating;
            try {
                fRating = stof(sRating);
            }
            catch(invalid_argument& e) {
                fRating = -1.0;
                cin.clear();
            }
            if (!(0.0 <= fRating && fRating <= 5.0))
                cout << "Enter a number 0.0 - 5.0: ";
        }
        cout << "Enter review comments: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, comment);
        if(iChoice == 1)
            push_front(reviews, fRating, comment);
        else
            push_back(reviews, fRating, comment);
        cout << "Enter another review? Y/N: ";
        cin >> another;
    }

    // After all reviews have been input, traverse the linked list to output the data and calculate/output the average review.
    cout << "Outputting all reviews:" << endl;
    Review* eachReview = reviews;
    int count = 0;
    float sum = 0.0;
    if (eachReview) { // if the list is not empty, display contents
        while (eachReview) {
            cout << fixed << setprecision(2) << "\t> Review #" << count + 1 << ": " << eachReview->rating << ": " << eachReview->comment << endl;
            ++count;
            sum += eachReview->rating;
            eachReview = eachReview->next;
        }
        cout << "\t> Average: " << fixed << setprecision(2) << sum / count << endl;
    }
    else
        cout << "There are no reviews to display." << endl;

    // delete the list to deallocate the memory
    // (I know the program is ending anyway but this is good practice)
    Review* current = reviews;
    while (current) {
        reviews = current->next;
        delete current;
        current = reviews;
    }
    reviews = nullptr;

    return 0;
}

void push_front(Review* &head, float rating, string comment) {
    // make the new node
    Review* newnode = new Review;
    newnode->rating = rating;
    newnode->comment = comment;
    newnode->next = nullptr;
    
    if (head) { // if the list is not empty, prepend the new node
        newnode->next = head;
        head = newnode;
    }
    else { // newnode will be the first node
        head = newnode;
    }
}

void push_back(Review* &head, float rating, string comment) {
    // make the new node
    Review* newnode = new Review;
    newnode->rating = rating;
    newnode->comment = comment;
    newnode->next = nullptr;
    
    if (head) { // if the list is not empty
        // traverse the list to get to the last node
        Review* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        // link the new node to the end of the list
        current->next = newnode;
    }
    else { // if the list is empty, make this new node is the first item
        head = newnode;
    }
}