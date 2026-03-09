// COMSC-210 | Lab 19 | Gillian Rhett

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
};

class Movie {
    string title;
    Review* reviews;

    //Automate it such that review comments are read from an external file, 
    //and the movie rating is a random double (one decimal place) between 1.0 and 5.0.


    public:
    // constructor
    Movie(string t = "", Review* r = nullptr) {
        title = t;
        reviews = r;
    }

    // destructor
    ~Movie() {
        Review* current = reviews;
        while (current) {
            reviews = current->next;
            delete current;
            current = reviews;
        }
        reviews = nullptr;
    }

    // TODO copy constructor for rule of 3
    Movie(const Movie& orig) {
        // TODO delete the reviews linked list if there is one

        // copy the original's values to this Movie
        this->title = orig.title;
        //TODO copy the linked list

    }

    // TODO copy assignment operator for rule of 3
    Movie& operator=(const Movie& orig) {

    }

    // public member functions
    void set_title(string t) { title = t; }

    const string get_title() { return title; }

    const void display_movie_info() {
        cout << "Title: " << title << endl;
        cout << "Reviews:" << endl;
        // TODO display the reviews
    }
};

int main() {
    // TODO read from the file
    
    /*
    
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

    */

    return 0;
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