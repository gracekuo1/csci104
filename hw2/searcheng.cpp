#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"

using namespace std;

// Helper function that will extract the extension of a filename
std::string extract_extension(const std::string& filename);

std::string extract_extension(const std::string& filename)
{
    size_t idx = filename.rfind(".");
    if (idx == std::string::npos) {
        return std::string();
    }
    return filename.substr(idx + 1);
}


// To be updated as needed 
SearchEng::SearchEng()
{
    fname = "";
    term = "";
}

// To be completed
SearchEng::~SearchEng()
{

}

// Complete
void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

// Complete
void SearchEng::read_pages_from_index(const std::string& index_file)
{
    ifstream ifile(index_file.c_str());
    if(ifile.fail()) {
        cerr << "Unable to open index file: " << index_file << endl;
    }

    // Parse all the files
    string filename;
    while(ifile >> filename) {
#ifdef DEBUG
        cout << "Reading " << filename << endl;
#endif
        read_page(filename);
    }
    ifile.close();
}

// To be completed
void SearchEng::read_page(const string& filename)
{
    string ext = extract_extension(filename);
    std::ifstream ifs (filename);

    if ( ifs.fail() ) {
        throw std::invalid_argument("filename dne");
    }

    if (parsers_.find(ext) == parsers_.end())
        throw std::logic_error("parser dne");
    PageParser* pp = parsers_.find(ext)->second;
  

    //create two string sets terms, links
    StringSet terms =  StringSet();
    StringSet links =  StringSet();

    //pass into parse
    pp->parse(ifs, terms, links);

    //if the webpage doesn't exit, make a webpage
    map<string, WebPage*>::iterator it_page = file_pages.find(filename);
    if (it_page == file_pages.end()){
        file_pages.insert(make_pair(filename, new WebPage(filename)));
        //file_pages[filename] = new WebPage(filename);
    }

    //set this webpage terms to this term
    WebPage* thisPage = file_pages[filename];
    thisPage-> all_terms(terms);

    //iterate through both those sets
    //terms set, add the webpage you have to the webpage set associated that term
    for(StringSet::iterator it= terms.begin(); it != terms.end(); ++it){
        term_webpages[*it].insert(thisPage);
    }
    
    //links set
    for (StringSet::iterator it2= links.begin(); it2 != links.end(); ++it2){
        const map <string, WebPage*>::iterator it3 = file_pages.find(*it2);

        if (it3 == file_pages.end()){
            file_pages.insert(make_pair(*it2, new WebPage(*it2)));

            //file_pages[*it2] = new WebPage();
        }
        //page that we have an outgoing link to
        WebPage* thatPage = file_pages[*it2];
        thatPage->add_incoming_link(thisPage);
        thisPage->add_outgoing_link(thatPage);
        
    }
    //webpage class has outgoing and incoming link
    //you add outgoing link to the link sets
    //add_outgoign_link to from 1 - 2 
    //add_incoming_link to 2 - 1

}

// To be completed
WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    if (file_pages.find(page_name) == file_pages.end()){
        return NULL;
    }
    return file_pages.find(page_name)->second;
}

// To be completed
void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{

    string ext = extract_extension(page_name);
    std::ifstream ifs (ext);

    //maek sure its not an invalid page and you parsed through it
    if (file_pages.find(page_name) == file_pages.end()){
        throw std::logic_error("invalid page");
    }

    //make sure parser for extension exists
    if (parsers_.find(ext) == parsers_.end())
        throw std::logic_error("parser dne");

    //check if page exists
    ifs.open (page_name, std::ifstream::in);
    if ( ifs.fail() ) {
        throw std::invalid_argument("filename dne");
    }

    //get a parser for the page
    PageParser* pp = parsers_.find(ext)->second;

    std::string ans = pp->display_text(ifs);
    std::cout << "HUHHH "<< std::endl;
    std::cout << "ans: " << ans << std::endl;
    ostr << ans;

}

// To be completed
WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    //declare set
    WebPageSet result;

    //if termms size = 0, return empty set
    if (terms.size() == 0)
        return result;

    result = term_webpages.find(terms[0])->second;

    //interate through terms
    for (size_t i = 1; i < terms.size(); i ++){
        if (term_webpages.find(terms[i]) != term_webpages.end()){
            result = combiner->combine(result, term_webpages.find(terms[i])->second);
        }
        
    }

    return result;

}

// Add private helper function implementations here