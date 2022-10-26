#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

// To be completed
void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();

    // Complete your code below

    // Initialize the current term and link as empty strings.
    string term = "";
    string link = "";
    PARSE_STATE_T ps = NORMALTEXT;

    // get the first char
    char c = istr.get();

    // read until input fails
    while(!istr.fail()){
        //if text is normal or could possibly be an anchor
        if (ps == NORMALTEXT || ps == LINKTEXT) {
            //if special character
            if (!isalnum(c)){
                //if beginning bracket and its a normal text
                if (c == '[' && ps == NORMALTEXT)
                    ps = LINKTEXT; 
                //if end bracket and its has a beginning bracket
                else if (c == ']' && ps == LINKTEXT) 
                    ps = ISLINK;
                //if term has somth, add to searchable terms
                if(term != ""){
                    term = conv_to_lower(term);
                    allSearchableTerms.insert(term);
                    //cout << "term " << term << endl;
                }
                term = "";
            }
            //otherwise keep adding to term
            else
                term += c;
        } 
        //if there is a proper anchor
        else if (ps == ISLINK) {
            //if there is a url notation
            if(c == '(') 
                ps = LINKURL;
            //if there's another bracket, go back to linktext state
            else if(c == '[') 
                ps = LINKTEXT;
            //otherwise its more normal text, go back to normal state
            else {
                ps = NORMALTEXT;
                term += c;
            }
        }
        //if there is proper url notation
        else if(ps == LINKURL) {
            //if it's ending, then switch back to normal state
            if(c == ')') {
                ps = NORMALTEXT;
                //if link isn't empty, add it into links
                if(link != "") {
                    link = conv_to_lower(link);
                    allOutgoingLinks.insert(link);
                    // cout << "link " << link << endl;

                }  
                link = "";

            }
            //if it isn't a ending ), then add anything to link
            else 
                link += c;
        } 
        c = istr.get();
    }
    //if term isn't empty, add it into terms
    if(term != ""){
        term = conv_to_lower(term);
        allSearchableTerms.insert(term);
        //cout << "term " << term << endl;

    }
    //if link isn't empty, add it into links
    else if(link != ""){
        link = conv_to_lower(link);
        allOutgoingLinks.insert(link);
        cout << "link " << link << endl;
    }

    std::cout << "New File: " << std::endl;
    for(StringSet::iterator it= allOutgoingLinks.begin(); it != allOutgoingLinks.end(); ++it){
        std::cout << *it << std::endl;
    }
 
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{

    std::string retval;
    PARSE_STATE_T ps = NORMALTEXT;

    char c = istr.get();

    while (!istr.fail()) {
        if (ps == NORMALTEXT || ps == LINKTEXT) {
            //if beginning bracket and its a normal text
            if (c == '[' && ps == NORMALTEXT)
                ps = LINKTEXT; 
            //if end bracket and its has a beginning bracket
            else if (c == ']' && ps == LINKTEXT) 
                ps = ISLINK;
            retval += c;
        }
        else if (ps == ISLINK) {
            //if there is a url notation
            if(c == '(') 
                ps = LINKURL;
            //if there's another bracket, go back to linktext state
            else {
                if(c == '[')
                    ps = LINKTEXT;
                //otherwise its more normal text, go back to normal state
                else 
                    ps = NORMALTEXT;
                retval += c;
            }
        }
        else if(ps == LINKURL && c == ')') {
            //if it's ending, then switch back to normal state
            ps = NORMALTEXT;
        } 
        c = istr.get();
    }
    std::cout << "retval" <<retval << std::endl;
    return retval;
}


