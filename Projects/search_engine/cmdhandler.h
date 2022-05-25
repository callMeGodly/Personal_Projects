#ifndef CMDHANDLER_H
#define CMDHANDLER_H
#include "handler.h"
#include "searcheng.h"
#include "combiners.h"

/**
 * Handles the QUIT command - COMPLETED in cmdhandler.cpp
 */
class QuitHandler : public Handler
{
public:
    QuitHandler();
    QuitHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the PRINT command
 */
class PrintHandler : public Handler
{
public:
    PrintHandler();
    PrintHandler(Handler* next);

protected:
  
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};


/**
 * Handles the INCOMING command
 */
class IncomingHandler : public Handler
{
public:
    IncomingHandler();
    IncomingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};

/**
 * Handles the OUTGOING command
 */
class OutgoingHandler : public Handler
{
public:
    OutgoingHandler();
    OutgoingHandler(Handler* next);

protected:

    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
};


/***********  Declare the classes for other command handling:          *******/
/***********    AND, OR, and DIFF handlers                             *******/
/*********** Then define their implementation in cmdhandler.cpp        *******/

//AND Handler class definition
class AndHandler : public Handler{
public:
    AndHandler(); //constructor;
    ~AndHandler(); //destructor
    AndHandler(Handler* next);

protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

private:
    
    //composition of a WebPageSetCombiner to be passed into searcheng search function
    WebPageSetCombiner* combiner_ = new AndWebPageSetCombiner;
    std::vector<std::string> searchTerms_;
};


//OR Handler class definition
class OrHandler : public Handler{
public:
    OrHandler(); //constructor
    ~OrHandler(); //destructor
    OrHandler(Handler* next);

protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);
    
private:
    
    //composition of a WebPageSetCombiner to be passed into searcheng search function
    WebPageSetCombiner* combiner_ = new OrWebPageSetCombiner;
    std::vector<std::string> searchTerms_;
};


//DIFF Handler class definition
class DiffHandler : public Handler{
public:
    DiffHandler(); //constructor
    ~DiffHandler(); //destructor
    DiffHandler(Handler* next);

protected:
    virtual bool canHandle(const std::string& cmd) const;
    virtual HANDLER_STATUS_T process(SearchEng* eng, std::istream& instr, std::ostream& ostr);

private:
    
    //composition of a WebPageSetCombiner to be passed into searcheng search function
    WebPageSetCombiner* combiner_ = new DiffWebPageSetCombiner;
    std::vector<std::string> searchTerms_;
};



#endif
