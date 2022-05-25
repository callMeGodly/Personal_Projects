#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include <set>

#include "pageparser.h"

class MDParser : public PageParser {
public:

    void parse(std::istream& istr,
               std::set<std::string>& allSearchableTerms,
               std::set<std::string>& allOutgoingLinks);


    std::string display_text(std::istream& filename);

};

#endif
