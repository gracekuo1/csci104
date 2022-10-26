// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void generateAWord (std::string& in, string& remaining_char, size_t index,
const std::set<std::string>& dict, size_t num_dashes, std::set<std::string>& answers);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> answers;

    int num_dashes = 0;
    for (unsigned int i = 0; i < in.length(); i ++){
        if (in[i] == '-')
            num_dashes++;
    }

    std::string in1 = in;
    std::string floating1 = floating;
    generateAWord(in1, floating1, 0, dict, num_dashes, answers) ;
    return answers;
    
}

// Define any helper functions here
//pass in dictionary
//pass in set of answers
//pass in number of dashes and decrease every time you use one
void generateAWord (std::string& in, string& remaining_char, size_t index,
const std::set<std::string>& dict, size_t num_dashes, std::set<std::string>& answers)
{ 
    if (index == in.length()){
        //check if its in the dictionary
        if (dict.find(in)!= dict.end() && remaining_char == ""){
            //add to answers
            answers.insert(in);
            //std:: cout << in << std::endl;
        }
        return;
    }
    if (remaining_char.length() > num_dashes){ 
        return;
    }
    //if its given, put it in
    if ( in[index] != '-'){
        generateAWord(in, remaining_char, index+1, dict, num_dashes, answers);
        return;
    }
    else{
        for (char c = 'a'; c <= 'z'; c++){
            //when letter is found
            if (remaining_char.find(c) != string::npos){
                in[index] = c;
                //std:: cout << "erase " << c << " from " << remaining_char << endl;
                remaining_char.erase(remaining_char.find(c),1);
                //std:: cout << "erase "<< endl;
                generateAWord(in, remaining_char, index+1, dict, num_dashes-1, answers);
                in[index] = '-';
                remaining_char = remaining_char + c;
            }
            //when letter is not found
            else {
                in[index] = c;
                generateAWord(in, remaining_char, index+1, dict, num_dashes-1, answers);
                in[index] = '-';
            }
        }
    }

}
