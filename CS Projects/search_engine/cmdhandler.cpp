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


//incoming handler
IncomingHandler::IncomingHandler(){
    
}
IncomingHandler::IncomingHandler(Handler* next)
    : Handler(next)
{

}
bool IncomingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "INCOMING";

}
Handler::HANDLER_STATUS_T IncomingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    
    //checks if the pages exists or not, if not return HANDLER_ERROR
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    //checks if we have such file that can be retrieved
    WebPage* fileff = eng->retrieve_page(name);
    if(fileff == NULL) return HANDLER_ERROR;
    
    //if so get its incoming links then print the number and contents by each line
    WebPageSet retval = fileff->incoming_links();
    display_hits(retval, ostr);
    
    return HANDLER_OK;
}

//outgoing handler
OutgoingHandler::OutgoingHandler(){
    
}
OutgoingHandler::OutgoingHandler(Handler* next)
    : Handler(next)
{

}
bool OutgoingHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OUTGOING";

}
Handler::HANDLER_STATUS_T OutgoingHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    
    //checks if the pages exists or not, if not return HANDLER_ERROR
    string name;

    if (!(instr >> name)) {
        return HANDLER_ERROR;
    }
    
    //checks if we have such file that can be retrieved
    WebPage* fileff = eng->retrieve_page(name);
    if(fileff == NULL) return HANDLER_ERROR;
    
    //if so get its outgoing links then print the number and contents by each line
    WebPageSet retval = fileff->outgoing_links();
    display_hits(retval, ostr);
    
    return HANDLER_OK;
}

//AND handler
AndHandler::AndHandler(){
    
}
AndHandler::~AndHandler(){
    
    delete combiner_;
}
AndHandler::AndHandler(Handler* next)
    : Handler(next)
{

}
bool AndHandler::canHandle(const std::string& cmd) const
{
    return cmd == "AND";

}
Handler::HANDLER_STATUS_T AndHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    
    string name;

    //gets the terms
    while (instr >> name) {
        searchTerms_.push_back(name);
    }
    
    //retrieves the pages that contains such terms then returns into WebPageSet to be displayed
    WebPageSet retval = eng->search(searchTerms_, combiner_);
    display_hits(retval, ostr);
    
    return HANDLER_OK;
}

//OR handler
OrHandler::OrHandler(){
    
}
OrHandler::~OrHandler(){
    
    delete combiner_;
}
OrHandler::OrHandler(Handler* next)
    : Handler(next)
{

}
bool OrHandler::canHandle(const std::string& cmd) const
{
    return cmd == "OR";

}
Handler::HANDLER_STATUS_T OrHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    
    string name;

    //gets the terms
    while (instr >> name) {
        searchTerms_.push_back(name);
    }
    
    //retrieves the pages that contains such terms then returns into WebPageSet to be displayed
    WebPageSet retval = eng->search(searchTerms_, combiner_);
    display_hits(retval, ostr);
    
    return HANDLER_OK;
}

//DIFF handler
DiffHandler::DiffHandler(){
    
}
DiffHandler::~DiffHandler(){
    
    delete combiner_;
}
DiffHandler::DiffHandler(Handler* next)
    : Handler(next)
{

}
bool DiffHandler::canHandle(const std::string& cmd) const
{
    return cmd == "DIFF";

}
Handler::HANDLER_STATUS_T DiffHandler::process(SearchEng* eng, std::istream& instr, std::ostream& ostr){
    
    string name;

    //gets the terms
    while (instr >> name) {
        searchTerms_.push_back(name);
    }
    
    //retrieves the pages that contains such terms then returns into WebPageSet to be displayed
    WebPageSet retval = eng->search(searchTerms_, combiner_);
    display_hits(retval, ostr);
    
    return HANDLER_OK;
}

