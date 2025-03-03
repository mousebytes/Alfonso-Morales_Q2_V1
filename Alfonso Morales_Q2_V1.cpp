#include<iostream>
#include<fstream>
#include<unordered_map>
#include<cmath>
#include<vector>
#include<string>
#include<set> // for deleting dupe words
#include<cctype> // for isalnum
// not using namespace std just for practice


// cosine similarity prototypes
void cosine_similarity(std::string file1, std::string file2); // A dot B = ||A|| * ||B|| * cos(theta)
std::string normalize_words(std::string word);
std::unordered_map<std::string, int> word_counter(std::string file_name);

// levenshtein distance prototypes
void levenshtein_distance();

// jaccard similarity prototypes
void jaccard_similarity();






int main(void)
{
    std::string word = "hello, my fRiend 123";
    std::cout << normalize_words(word) << "\n";
    





    return 0;
}








// cosine similarity implementations
void cosine_similarity(std::string file1, std::string file2)
{
    std::unordered_map<std::string, int> word_freq1 = word_counter(file1); // put words as keys in ordered map from file 1
    std::unordered_map<std::string, int> word_freq2 = word_counter(file2); // put words as keys in ordered map from file 2

    // use a set to delete dupe words and get the unique words
    std::set<std::string> unique_words;

    for(auto p : word_freq1) // for every pair in word_freq1
    {
        unique_words.insert(p.first); // insert the key into the set
    }
    for(auto p : word_freq2) // for every pair in word_freq2
    {
        unique_words.insert(p.first); // insert the key into the set
    }

    double dot_prod = 0.0, mag1=0.0,mag2=0.0;

    for(std::string word: unique_words) // for every word in the set
    {
        int count1 = word_freq1[word]; // 0 if word doesnt exist in file1
        int count2 = word_freq2[word];  // 0 if word doesnt exist in file2

        // calculate the dot procuct using (write this later)
        dot_prod += count1*count2;

    }

}


std::string normalize_words(std::string word) // normalize a word for the unordered_map key
{
    std::string normalized;

    for(char c : word ) // for every char in passed word string
    {
        if(isalnum(c)) // add if letter or num
            normalized += tolower(c); // move to lowercase
    }

    return normalized; // return normalzied word
}

std::unordered_map<std::string, int> word_counter(std::string file_name)
{
    std::unordered_map<std::string, int> word_freq;
    std::ifstream file(file_name);
    std::string word;

    if(!file) // if the file's unopened
    {
        std::cerr<<"file not opened\n"; // return an error
        return word_freq; // return empty map
    }

    while(file>>word) // input string operator >> to put words from file into word var
    {
        std::string normalized_word = normalize_words(word); // normalize the word
        word_freq[normalized_word]++; // then increment the word's key
    }

    file.close(); // close input file
    return word_freq; // return the map

}



// jaccard similarity implementations
void jaccard_similarity()
{

}

// levenshtein distance implementations
void levenshtein_distance()
{

}

