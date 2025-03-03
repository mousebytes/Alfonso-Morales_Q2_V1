#include<iostream>
#include<fstream>
#include<unordered_map>
#include<cmath>
#include<vector>
#include<string>
// not using namespace std just for practice


// cosine similarity prototypes
void cosine_similarity(); // A dot B = ||A|| * ||B|| * cos(theta)
std::string normalize_words(std::string word);


// levenshtein distance prototypes
void levenshtein_distance();

// jaccard similarity prototypes
void jaccard_similarity();






int main(void)
{
    std::string word = "Hello world";
    std::cout << normalize_words(word) << "\n";
    





    return 0;
}








// cosine similarity implementations
void cosine_similarity()
{

}
std::string normalize_words(std::string word) // normalize a word for the unordered_map key
{
    std::string normalized;

    for(char c : word ) // for every char in passed word string
    {
        if(isalpha(c)) // check if it's a letter
            normalized += tolower(c); // move to lowercase
    }

    return normalized;
}


// jaccard similarity implementations
void jaccard_similarity()
{

}

// levenshtein distance implementations
void levenshtein_distance()
{

}

