// THIS FILE COMPARES 2 .txt FILES FOR THEIR SIMILARITIES USING SEVERAL COMPARISON ALGORITHMS


#include<iostream> // i love io stream
#include<fstream> // for opening files
#include<unordered_map> // for holding keys
#include<cmath> // for sqrt
#include<string> // woooorrrddddssss
#include<set> // for deleting dupe words
#include<cctype> // for isalnum
#include<vector>
// not using namespace std just for practice




// cosine similarity prototypes
void cosine_similarity(std::string file1, std::string file2); // A dot B = ||A|| * ||B|| * cos(theta)

// levenshtein distance prototypes
void levenshtein_distance(std::string file1, std::string file2); 

// jaccard index prototypes
void jaccard_index(std::string file1, std::string file2);

// general use prototypes
std::string normalize_words(std::string word);
std::unordered_map<std::string, int> word_counter(std::string file_name);
std::pair<std::vector<std::string>,std::vector<std::string>> return_vecs_words_from_files(std::string file1, std::string file2);




int main(void)
{
    std::cout << "***** COSINE SIMILARITY *****\n";
    cosine_similarity("text1.txt", "text2.txt"); 

    std::cout << "\n\n***** JACCARD SIMILARITY *****\n";
    jaccard_index("text1.txt", "text2.txt");

    std::cout << "\n\n***** LEVENSHTEIN DISTANCE *****\n";
    levenshtein_distance("text1.txt", "text2.txt");


    return 0;
}

void cosine_similarity(std::string file1, std::string file2) // (A * B) / (|A| X |B|)
{
    /*
        LOGIC:
        USE MAPS TO STORE WORDS AND THEIR FREQUENCY
        FIND DOT PRODUCT BY MULTIPLYING KEY VALUES TO THE OTHER MAPS KEY VALUE
        FIND MAGNITUDE -> SQRT(SUM OF VALS OF ALL KEYS)
    */
    std::unordered_map<std::string, int> word_freq1 = word_counter(file1); // populate word freq 1 using word counter function
    std::unordered_map<std::string, int> word_freq2 = word_counter(file2); // populate word freq 2 using word counter function
    std::set<std::string> unique_words; // set to store unique words since sets don't hold multiple vals (they arent a multiset like a map)

    for(std::pair<std::string, int> p : word_freq1) // insert keys from word_freq1 into unique words
        unique_words.insert(p.first);
    for(std::pair<std::string, int> p : word_freq2) // insert keys from word_freq2 into unique words
        unique_words.insert(p.first);

    int dot_product = 0;

    for(auto p : word_freq1) 
    {
        if(word_freq2.find(p.first)!=word_freq2.end()) // considers the words that exist in both maps
            dot_product+= p.second * word_freq2[p.first]; // adding to the dot product (the vals of the keys that exist in both maps) (Only need the keys that exist in both since dot prods would be 0 if they didn't exist in one or another)
    }

    float magnitudeA_pre_sqrt = 0.0, magnitudeB_pre_sqrt = 0.0; // gonna store magnitudes before applying square root, so not true magnitudes

    for(std::string s : unique_words) // put all vals from unique keys into their respective magnitude variables
    {
        if(word_freq1.find(s) != word_freq1.end()) // if s exists in w_f1
            magnitudeA_pre_sqrt += word_freq1[s] * word_freq1[s];
        if(word_freq2.find(s) != word_freq2.end()) // if s exists in w_f2
            magnitudeB_pre_sqrt += word_freq2[s] * word_freq2[s];
    }

    if(magnitudeA_pre_sqrt ==0 || magnitudeB_pre_sqrt==0)
    {
        std::cout << "\nCosine Similarity Score: 0%";
        return;
    }

    float similarity_score = (dot_product)/(sqrt(magnitudeA_pre_sqrt) * sqrt(magnitudeB_pre_sqrt));

    std::cout << "\nCosine Similarity Score: " << similarity_score * 100 << "%";

    std::cout << "\n\nWords that exist in file1, but not in file 2: \t";
    for(std::string s : unique_words)
    {
     if(word_freq2.find(s)==word_freq2.end())
         std::cout << s << ", ";
    }

   std::cout << "\nWords that exist in file2, but not in file 1: \t";
   
   for(std::string s : unique_words)
   {
    if(word_freq1.find(s)==word_freq1.end())
        std::cout << s << ", ";
   }
}





// jaccard similarity implementations
void jaccard_index(std::string file1, std::string file2) // JACCARD SIMILARITY = INTERSECTION OF A AND B DIVIDED BY UNION OF A AND B
{
    /*
    TODO: ASK IF THEY WANT DUPES OR NOT FOR THIS ITERATION OF JACCARD INDEX -- DONE USE MULTISETS
    LOGIC: USE A MAP TO STORE WORDS AND THEIR FREQUENCY IN FILE 1 AND 2 --DONE
    USE A MAP TO STORE UNION --DONE
    USE A MAP TO STORE INTERSECTION --DONE
    JACCARD FORMULA: INTERSECTION / UNION --DONE
    */
    std::unordered_map<std::string, int> word_freq1 = word_counter(file1); // put words as keys in ordered map from file 1
    std::unordered_map<std::string, int> word_freq2 = word_counter(file2); // put words as keys in ordered map from file 2
    std::unordered_map<std::string, int> union_map;
    std::unordered_map<std::string, int> intersection_map;
    std::set<std::string> unique_words;
    float similarity_score = 0.0, numerator = 0.0, denominator = 0.0;

    for(auto p : word_freq1) // for every pair in word_freq1
    {
        unique_words.insert(p.first); // insert the key into the set
    }
    for(auto p : word_freq2) // for every pair in word_freq2
    {
        unique_words.insert(p.first); // insert the key into the set
    }


   for(auto p : word_freq1) // for every pair in word_freq1
   {
        if(word_freq2.find(p.first)!=word_freq2.end()) // place every word that exists in both files into the intersection map
        {
            intersection_map[p.first] = std::min(p.second, word_freq2[p.first]); // insert every word that exists in both word_freq1&2 as a key / whichever value is lower will be placed as the intersection map val
            // note that this only emplaces words that exist in both files
            union_map[p.first] = std::max(p.second, word_freq2[p.first]); // insert every word that exists in both word_freq1&2 as a key / whichever value is higher will be placed as the union map val
        }
        
   }
   for(auto p: word_freq1)
    {
        if(union_map.find(p.first)==union_map.end()) // if the word doesn't exist in the union map but exists in file 1 then emplace its val in the word key
            union_map[p.first] = p.second;
    }

   for(auto p: word_freq2)
    {
        if(union_map.find(p.first)==union_map.end())
            union_map[p.first] = p.second; // if the word doesn't exist in the union map but exists in file 2 then emplace its val in the word key
    }
   
   for(auto p : intersection_map)
   {
        numerator += p.second; // increment numerator with vals from intersection map
   }

   for(auto p: union_map)
   {
        denominator += p.second; // increment denom for every unique word in union set
   }

   if(denominator!=0.0)
   {
        std::cout << "\nJaccard Index: " << (numerator/denominator) * 100<< "%";
   }
   else
   {
        std::cout << "\nJaccard Index: 0%";
   }

   std::cout << "\n\nWords that exist in file1, but not in file 2: \t";
    for(std::string s : unique_words)
    {
     if(word_freq2.find(s)==word_freq2.end())
         std::cout << s << ", ";
    }

   std::cout << "\nWords that exist in file2, but not in file 1: \t";
   
   for(std::string s : unique_words)
   {
    if(word_freq1.find(s)==word_freq1.end())
        std::cout << s << ", ";
   }
   

   

}

// levenshtein distance implementations
void levenshtein_distance(std::string file1, std::string file2)
{
    // holds the wrods from both fioes
    std::pair<std::vector<std::string>,std::vector<std::string>> word_list = return_vecs_words_from_files(file1,file2);
    int total_levenshtein_distance = 0;

    
    int length_pair_1 = word_list.first.size();
    int length_pair_2 = word_list.second.size();

    if(length_pair_1 >= length_pair_2) // handle cases where lengths are dissimilar through conditionals
    {
        for(int i = 0; i < length_pair_2;++i)
        {
            if(word_list.first[i] != word_list.second[i]) // check if the words aren't the same -- if they arent then increase levenshtein by 1
                total_levenshtein_distance++;
        }

        // this will populate the rest of the levenshtein distances with just hte length of the leftover words
        for(int i = length_pair_2; i < length_pair_1;++i)
        {
            total_levenshtein_distance ++;
        }
    }
    else
    {
        for(int i = 0; i < length_pair_1;++i)
        {
            if(word_list.first[i] != word_list.second[i]) // check if the words aren't the same -- if they arent then increase levenshtein by 1
                total_levenshtein_distance++;
        }

        // this will populate the rest of the levenshtein distances with just hte length of the leftover words
        for(int i = length_pair_1; i < length_pair_2;++i)
        {
            total_levenshtein_distance ++;
        }
    }

    std::cout << "\nLevenshtein Distance: " << total_levenshtein_distance;

}

// General Use Functions
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

// push words from docs into a pair of vectors for levenshtein
std::pair<std::vector<std::string>,std::vector<std::string>> return_vecs_words_from_files(std::string file1, std::string file2) // this function is done
{
    std::pair<std::vector<std::string>,std::vector<std::string>> words_from_files;
    std::ifstream file_1(file1), file_2(file2);
    std::string word;

    if(!file_1 && !file_2) // if both files aren't opened then send back an empty pair
    {
        std::cerr<<"file1&2 not opened\n"; // return an error
        return words_from_files;
    }


    if(file_1) // if file 1 is opened then write all words from file 1 into pair.first
    {
        while(file_1>>word)
        {
            std::string normalized_word = normalize_words(word);
            words_from_files.first.push_back(normalized_word);
        }
    }
    

    if(file_2) // if file 2 is opened then write all words from file 2 into pair.second
    {
        while(file_2>>word)
        {
            std::string normalized_word = normalize_words(word);
            words_from_files.second.push_back(normalized_word);
        }
    }

    file_1.close();
    file_2.close();

    return words_from_files;

}