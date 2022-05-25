#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include "md_parser.h"
#include "util.h"

using namespace std;

typedef enum { NORMALTEXT, LINKTEXT, ISLINK, LINKURL } PARSE_STATE_T;

void MDParser::parse(std::istream& istr, std::set<std::string>& allSearchableTerms, std::set<std::string>& allOutgoingLinks)
{

    // Remove any contents of the sets before starting to parse.
    allSearchableTerms.clear();
    allOutgoingLinks.clear();
    
    //Initialize a string to store values
    string term = "";
    
    //Get the first character from the string
    char c = istr.get();
    
    //Checks if term should be an outgoing link
    bool preceding = false;
    bool isLink = false;
    
    //read until the string fails
    while(!istr.fail()){
        
        //if the incoming character is not alphanumeric
        if(!isalnum(c) && !isLink){
            
            //checks if we might have a link
            //else if term should be inserted into allSearchableTerms
            if(c == ']') preceding = true;
            else if(preceding && c == '('){
                isLink = true;
                preceding = false;
            }
            
            //if not empty searchable term
            if(term != ""){
                //converts term to standard case then add it
                term = conv_to_lower(term);
                allSearchableTerms.insert(term);
                
                //cleans term to start a new sequence
                term = "";
            }
        }
        //if we've determined that we are getting a link
        else if(isLink && (c == ')') && (term != "")){
            
            term = conv_to_lower(term);
            allOutgoingLinks.insert(term);
            
            term = "";
            
            //switches isLink to false after a getting a link
            isLink = false;
        }
        //nothing to be done then add into the term string
        else term += c;
        
        //continue onto the next character
        c = istr.get();
    }
    
    /* Making sure the last term is being added in, as well into the
    correct set */
    if(term != ""){
        if(isLink){
            if (term != ")"){
                term = conv_to_lower(term);
                allOutgoingLinks.insert(term);
            }
        }
        else{
            term = conv_to_lower(term);
            allSearchableTerms.insert(term);
        }
    }
}

// To be completed
std::string MDParser::display_text(std::istream& istr)
{
    //Initialize a string to store values
    std::string retval;
    
    //Checks if term should be displayed
    bool preceding = false;
    bool isLink = false;
    
    //Get the first character from the string
    char c = istr.get();
    
    //read until the string fails
    while(!istr.fail()){
        if(c == ']') preceding = true;
        else if(c == '(' && preceding){
            isLink = true;
            preceding = false;
        }
        
        if(!isLink){
            retval += c;
        }
        else if(c == ')'){
            isLink = false;
        }
        c = istr.get();
    }
    return retval;
}


