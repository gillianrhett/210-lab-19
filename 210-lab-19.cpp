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
    Review* next = nullptr;
};

class Movie {
    string title;
    Review* reviews = nullptr;

    public:
    // constructor
    Movie(string t = "", Review* r = nullptr) {
        title = t;
        reviews = r;
    }

    // destructor
    ~Movie() {
        Review* current = reviews;
        while (current != nullptr) {
            reviews = current->next;
            delete current;
            current = reviews;
        }
        reviews = nullptr;
    }

    // copy constructor for rule of 3
    Movie(const Movie& orig) {
        // copy the original's values to this Movie
        this->title = orig.title;
        
        // copy the reviews
        Review* current = this->reviews;
        if(orig.reviews != nullptr) {
            current = orig.reviews;
            while(current) {
                this->append_review(current->rating, current->comment);
                current = current->next;
            }
        }
        // (else orig has no reviews so this->reviews should remain nullptr)
    }

    // copy assignment operator for rule of 3
    Movie& operator=(const Movie& orig) {
    // copy the original's values to this Movie
        // copy the title
        this->title = orig.title;
        
        // copy the reviews
        // first delete the reviews linked list if there is one
        Review* current = this->reviews;
        while (current != nullptr) {
            this->reviews = current->next;
            delete current;
            current = this->reviews;
        }
        this->reviews = nullptr;
        
        // then copy the original linked list into this Movie
        if(orig.reviews != nullptr) {
            current = orig.reviews;
            while(current) {
                this->append_review(current->rating, current->comment);
                current = current->next;
            }
        }
        // (else orig has no reviews so this->reviews should remain nullptr)

        return *this;
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
        if (eachReview != nullptr) { // if the list is not empty, display contents
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

    void prepend_review(float r, string c) {
        // make the new node
        Review* newnode = new Review;
        newnode->rating = r;
        newnode->comment = c;
        newnode->next = nullptr;
        
        if (this->reviews != nullptr) { // if the list is not empty, prepend the new node
            newnode->next = this->reviews;
            this->reviews = newnode;
        }
        else { // newnode will be the first node
            this->reviews = newnode;
        }
    }

    void append_review(float r, string c) { 
    // needed for the copy constructor and copy assignment operator to copy reviews in the same order as the original
        // make the new node
        Review* newnode = new Review;
        newnode->rating = r;
        newnode->comment = c;
        newnode->next = nullptr;
        
        if (this->reviews != nullptr) { // if the list is not empty
            // traverse the list to get to the last node
            Review* current = this->reviews;
            while (current->next != nullptr) {
                current = current->next;
            }
            // link the new node to the end of the list
            current->next = newnode;
        }
        else { // if the list is empty, make this new node is the first item
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
        // now we have a valid file open, read from the file into a new Movie object
        cout << "Enter the movie title: ";
        getline(cin, tempInput);
        Movie newMovie(tempInput, nullptr);
        lineCount = 0;
        inFile.clear();
        inFile.seekg(ios::beg);
        while (!inFile.eof()) { // read each line of the file
            getline(inFile, tempInput);
            if(!inFile.eof()) {
                if (lineCount % 2 == 0) // even lines have ratings, odd lines have comments
                    try {
                        rating = stof(tempInput);
                    }
                    catch(const exception& e) {
                        rating = 0.0; // if it's not a float, put 0 instead
                        inFile.clear();
                    }
                else
                    comment = tempInput;
                ++lineCount;

                newMovie.prepend_review(rating, comment);
            }
        }
        inFile.close();
        // done adding reviews, add (a copy of) this movie to the vector
        movies.push_back(newMovie);
        cout << "Enter another movie (Y/N)? ";
        getline(cin, another);
    }

    // done getting input, display the info about the movies
    for (Movie m : movies) {
        m.display_movie_info();
    }

    return 0;
}