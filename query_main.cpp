#include <iostream>
#include <fstream>
#include <string>

#include "query.hpp"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " (results_file)" << std::endl;
        return 1;
    }

    QueryEngine qe;

    // load the index into the query engine
    qe.load_index(std::string(argv[1]));

    // loop asking for queries
    qe.query_loop();

    return 0;
}
