#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include "searcheng.h"
#include "util.h"

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


SearchEng::SearchEng()
{
    
}

SearchEng::~SearchEng()
{
    
    // deletes all existing webpages from the heap to prevent memory loss
    database::iterator it;
    for(it = webpages_.begin(); it != webpages_.end(); ++it){
        delete it->second;
    }
    
    //deletes all existing parsers from heap to prevent memory loss
    parserbase::iterator itr;
    for(itr = parsers_.begin(); itr != parsers_.end(); ++itr){
        delete itr->second;
    }

}

void SearchEng::register_parser(const std::string& extension, PageParser* parser)
{
    if (parsers_.find(extension) != parsers_.end())
    {
        throw std::invalid_argument("parser for provided extension already exists");
    }
    parsers_.insert(make_pair(extension, parser));
}

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

void SearchEng::read_page(const string& filename)
{
    
    //checks if the files exists
    ifstream ifile(filename);
    if(ifile.fail()) throw std::invalid_argument("filename does not exist");
    
    //checks if there is a parser for this file extension
    string file_ext = extract_extension(filename);
    if(parsers_.find(file_ext) == parsers_.end()) throw std::logic_error("extension exists, but no parser was found");
    
    //if the webpage is already finished then don't do anything
    if(isComplete.find(filename) != isComplete.end()) return;
    
    //read and add the new WebPage, checks if the webpage is completely new or unfinished
    database::iterator itt = webpages_.find(filename);
    WebPage* newPage;
    if(itt == webpages_.end()){
        newPage = new WebPage();
        newPage->filename(filename);
        webpages_.insert(make_pair(filename, newPage));
    }
    else{
        newPage = itt->second;
    }
    
    //initiates the parsing
    PageParser* pp = parsers_[file_ext];
    set<string> allterms;
    set<string> outgoing;
    pp->parse(ifile, allterms, outgoing);
    
    //adds all searchable terms into the WebPage Object
    newPage->all_terms(allterms);
    
    //adds all of its outgoing links
    for(set<string>::iterator it = outgoing.begin(); it != outgoing.end(); ++it){
        
        database::iterator itr = webpages_.find(*it);
        
        //if the outgoing did do exist, create then add, also creates an incoming link for the new page and created page
        if(itr == webpages_.end()){
            WebPage* dnePage = new WebPage();
            dnePage->filename(*it);
            webpages_.insert(make_pair(*it, dnePage));
            dnePage->add_incoming_link(newPage);
            newPage->add_outgoing_link(dnePage);
        }
        else{
            newPage->add_outgoing_link(itr->second);
            itr->second->add_incoming_link(newPage);
        }
    }
    //adds all of its incoming links
    for(database::iterator it = webpages_.begin(); it != webpages_.end(); ++it){
        WebPageSet incom = it->second->outgoing_links();
        if(incom.find(newPage) != incom.end()){
            newPage->add_incoming_link(it->second);
            
        }
    }
    
    //adds itself to a all alike term WebPageSet to be combined when the term is called
    for(set<string>::iterator it = allterms.begin(); it != allterms.end(); ++it){
        string term = conv_to_lower(*it);
        map<string, WebPageSet>::iterator itr = to_combine.find(term);
        
        //if the term doesn't exist yet create a new key and value to store
        //else since it exists just at to its value
        if(itr == to_combine.end()){
            WebPageSet newSet;
            newSet.insert(newPage);
            to_combine.insert(make_pair(term, newSet));
        }
        else{
            itr->second.insert(newPage);
        }
    }
    
    //puts it in the finished category so if the same file appears, the function should just return
    isComplete.insert(filename);

}

WebPage* SearchEng::retrieve_page(const std::string& page_name) const
{
    
    //checks if the file exists if not return NULL
    if(webpages_.find(page_name) == webpages_.end()){
        return NULL;
    }
    
    return webpages_.find(page_name)->second;
}

void SearchEng::display_page(std::ostream& ostr, const std::string& page_name) const
{
    
    //uses two separate iterators to check if page exists in data base
    //and if there is parser for the files extension
    string file_ext = extract_extension(page_name);
    if(webpages_.find(page_name) == webpages_.end()) throw std::invalid_argument("page name does not exist");
    else if(parsers_.find(file_ext) == parsers_.end()) throw std::logic_error("file extension cannot be parsed");
    
    //gets the file to be loaded into the parser
    PageParser* pp;
    pp = parsers_.find(file_ext)->second;
    ifstream ifile(page_name);
    
    //displays the contents of the page/file
    ostr << pp->display_text(ifile);
}

WebPageSet SearchEng::search(const std::vector<std::string>& terms, WebPageSetCombiner* combiner) const
{
    
    //initializes return value(first set)and second set to be combined
  
    WebPageSet re;
    WebPageSet secondSet;
    set<WebPageSet> combining;
    
    //grabs all the sets to be combined
    for(unsigned int i = 0; i < terms.size(); ++i){
        map<string, WebPageSet>::const_iterator it = to_combine.find(terms.at(i));
        if(it != to_combine.end()){ //checks if the term exists
            combining.insert(it->second);
        }
    }
    
    //starts combining each set with given combiner type
    for(set<WebPageSet>::iterator it = combining.begin(); it != combining.end(); ++it){
        if(it == combining.begin()) re = *it; //the first set needs to be loaded for combining
        else{
            secondSet = *it;
            re = combiner->combine(re, secondSet);
        }
    }
    
    //sends back to the handler
    return re;

}

