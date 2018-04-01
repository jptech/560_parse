#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <unordered_map>
#include <exception>

class QueryEngine
{
protected:
    // hash table of words -> files /w location
    // each file entry has a vector of locations
    std::unordered_map<std::string, std::map<std::string, std::vector<int>>> m_index;

public:
    QueryEngine() = default;
    ~QueryEngine() = default;

    bool load_index(std::string fname)
    {
        std::ifstream file;

        file.open(fname);

        std::string word_line;
        while(std::getline(file, word_line))
        {
            std::string word;
            std::string word_data;
            std::istringstream iss(word_line);

            iss >> word;

            while(std::getline(iss, word_data, ';'))
            {
                int colon = word_data.find(':');
                std::string s_loc;
                std::istringstream lss;
                std::vector<int> locations;

                int start = word_data.find_first_not_of(" ");
                std::string fname = word_data.substr(start, colon-start);
                std::istringstream locs(word_data.substr(colon+1));

                while(std::getline(locs, s_loc, ','))
                {
                    int loc;
                    lss.str(s_loc);
                    if(lss >> loc) locations.push_back(loc);
                    lss.clear();
                }

                m_index[word][fname] = locations;
            }
        }

        return true;
    }

    std::map<std::string, std::vector<int>> const & find_word(std::string word)
    {
        auto result = m_index.find(word);

        if(result == m_index.end())
        {
            throw std::out_of_range("");
        }
        else
        {
            return m_index.at(word);
        }
    }

    void query_loop()
    {
        std::string str;
        while(str != "q")
        {
            // prompt user for a query
            std::cout << "Please enter your word query (q to quit): ";
            std::cin >> str;

            // if the query is not a stop query, evaluate it and return the results
            if(str != "q")
            {
                try
                {
                    auto const &result = find_word(str);

                    // loop through each file with the queried word
                    for(auto &f : result)
                    {
                        std::cout << "File: " << f.first << std::endl;
                        std::cout << "\t";

                        // loop through each location of the word within the file
                        for(auto &loc : f.second)
                        {
                            std::cout << loc << " ";
                        }
                        std::cout << std::endl;
                    }
                }
                catch (std::exception e)
                {
                    std::cout << "Query for word '" << str << "' resulted in no matches" << std::endl << std::endl;
                }
            }
        }
    }

};
