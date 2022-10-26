#include "cmdhandler.h"
#include "util.h"
using namespace std;

// Complete
QuitHandler::QuitHandler()
{

}

// Complete
QuitHandler::QuitHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool QuitHandler::canHandle(const std::string& cmd) const
{
    return cmd == "QUIT";

}

// Complete
Handler::HANDLER_STATUS_T QuitHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    return HANDLER_QUIT;
}

// Complete
PrintHandler::PrintHandler()
{

}

// Complete
PrintHandler::PrintHandler(Handler* next)
    : Handler(next)
{

}

// Complete
bool PrintHandler::canHandle(const std::string& cmd) const
{
    return cmd == "PRINT";

}

// Complete
Handler::HANDLER_STATUS_T PrintHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    try {
        eng->display_page(ostr, name);
    }
    catch (std::exception& e) {
        return HANDLER_ERROR;
    }
    return HANDLER_OK;
}

// Add code for other handler class implementations below

AndHandler::AndHandler()
{

}


AndHandler::AndHandler(Handler* next)
    : Handler(next)
{

}


bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector <string> terms;
    string temp;
    while (instr>>temp){
        terms.push_back(temp);
    }
    AndWebPageSetCombiner* andSearch = new AndWebPageSetCombiner();

    WebPageSet result;
    result = eng->search(terms, andSearch);

    display_hits(result, ostr);

    return HANDLER_OK;
}


OrHandler::OrHandler()
{

}


OrHandler::OrHandler(Handler* next)
    : Handler(next)
{

}


bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector <string> terms;
    string temp;
    while (instr>>temp){
        terms.push_back(temp);
    }
    OrWebPageSetCombiner* orSearch = new OrWebPageSetCombiner();

    WebPageSet result;
    result = eng->search(terms, orSearch);

    display_hits(result, ostr);

    return HANDLER_OK;
}

DiffHandler::DiffHandler()
{

}


DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}


bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";

}

Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    vector <string> terms;
    string temp;
    while (instr>>temp){
        terms.push_back(temp);
    }
    DiffWebPageSetCombiner* diffSearch = new DiffWebPageSetCombiner();

    WebPageSet result;
    result = eng->search(terms, diffSearch);

    display_hits(result, ostr);

    return HANDLER_OK;
}

IncomingHandler::IncomingHandler()
{

}

IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}


bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}

Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    std::string fname = "";

    //make sure file exists
    if (!(instr>>fname)){
        std::cout << "file dne" << std::endl;
        return HANDLER_ERROR;
    }
    
    //retrieve page
    WebPage* current = eng->retrieve_page(fname);

    //make sure file exists
    if (current == NULL){
        std::cout << "not parsed" << std::endl;
        return HANDLER_ERROR;
    }

    //if file is stored and you parsed it

    display_hits(current->incoming_links(), ostr);
  
    //you just get the links from the web page and display hits
    return HANDLER_OK;
}

OutgoingHandler::OutgoingHandler()
{

}

OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}


bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}

Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr)
{
    std::string fname = "";

    //make sure file exists
    if (!(instr>>fname)){
        return HANDLER_ERROR;
    }
    
    //retrieve page
    WebPage* current = eng->retrieve_page(fname);

    //make sure file exists
    if (current == NULL){
        return HANDLER_ERROR;
    }

    //if file is stored and you parsed it
    display_hits(current->outgoing_links(), ostr);
  
    //you just get the links from the web page and display hits
    return HANDLER_OK;
}