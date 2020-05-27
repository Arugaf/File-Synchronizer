#include "LogParser.h"

#include <fstream>
#include <vector>

#include <boost/spirit/include/qi.hpp>

using boost::spirit::qi::phrase_parse;
using boost::spirit::qi::rule;
using boost::spirit::qi::lit;

void FileSynchronizer::LogParser::ShowLogHead(int count) {
    std::string record;
    std::string end;
    std::ifstream record_file("track.json");

    std::vector<std::string> v;


    while(std::getline(record_file, record, '}')) {
        std::getline(record_file, end, '}');
        record += "}\n}";
        v.push_back(record);
        std::cout << record << std::endl;
    }

    rule<std::string::iterator> actions = (
            lit('"') >> lit("file")[([&](){std::cout << "g" << std::endl;})]
            );

    for (auto& it : v) {
        auto iterator = it.begin();

        phrase_parse(iterator, it.end(), actions, boost::spirit::ascii::space);
    }

}
