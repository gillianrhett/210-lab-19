// COMSC-210 | Lab 19 | Gillian Rhett

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

struct Review {
    float rating;
    string comment;
    Review* next;
};

class Movie {
    string title;
    Review* reviews;

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
        // display the reviews
        int count = 0;
        float sum = 0.0;
        Review* eachReview = reviews;
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
    }

    void prepend_review (float rating, string comment) {
        // make the new node
        Review* newnode = new Review;
        newnode->rating = rating;
        newnode->comment = comment;
        newnode->next = nullptr;
        
        if (this->reviews) { // if the list is not empty, prepend the new node
            newnode->next = this->reviews;
            this->reviews = newnode;
        }
        else { // newnode will be the first node
            this->reviews = newnode;
        }
    }
};

int main() {
    // vector to store the movies in
    vector <Movie> movies;

    // read from the file
    ifstream inFile; // file object to get the items from
    string filename;
    string another = "y";
    bool validFile;
    string tempInput;
    int lineCount;
    string comment;
    float rating;
    while (another == "y" || another == "Y") {
        validFile = false; // reset for the next movie
        while (!validFile) {
            cout << "Enter the filename: ";
            getline(cin, filename);
            // try to open the file
            try {
                inFile.open(filename, ios::in);
                if(inFile.fail()) 
                    throw invalid_argument("file not found");
                else
                    validFile = true;
            }
            catch(invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        inFile.close();
        // now we have a valid file open, read from the file into a new Movie object
        cout << "Enter the movie title: ";
        getline(cin, tempInput);
        Movie newMovie(tempInput);
        lineCount = 0;
        inFile.clear();
        inFile.seekg(ios::beg);
        while (!inFile.eof()) { // read each line of the file
            getline(inFile, tempInput);
            cout << tempInput << endl; // TESTING
            if (lineCount % 2 == 0) // even lines have ratings, odd lines have comments
                try {
                    rating = stof(tempInput);
                }
                catch(const exception& e) {
                    rating = 0; // if it's not a float, put 0 instead
                    inFile.clear();
                }
            else
                comment = tempInput;
            ++lineCount;
            cout << lineCount << endl; //TESTING
            newMovie.prepend_review(rating, comment);
        }
        // done adding reviews, add (a copy of) this movie to the vector
        movies.push_back(newMovie);
        cout << "Enter another movie (Y/N)? ";
        getline(cin, another);
    }

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