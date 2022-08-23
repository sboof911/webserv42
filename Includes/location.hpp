#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "server.hpp"
#include <iostream>
#include <vector>

class cgi;
class location
{
    
protected:
    std::string                 _name;
    std::string                 _locations_path;
    std::vector<std::string>    _allow_methods;
    std::string                 _root;
    
    long long int               _client_max_body_size;
    std::vector<std::string>    _index;
    bool                        _autoindex;
    std::string                 _upload_path;
public:
    location();
    ~location();
    location (const location &obj);
    location &operator=(location const &copy);
    location(std::vector<std::string > text_vector,int index,int nb_server);
    std::string                 get_upload_path() const;
    std::string                 get_name() const;
    std::string                 get_locations_path() const;
    std::vector<std::string>    get_methods() const;
    unsigned int                get_methods_size() const;
    std::string                 get_root() const;
    bool                        get_autoindex() const;
    long long int               get_client_max_body_size() const;
    unsigned int                get_index_size() const;
    std::vector<std::string>    get_index() const;
};
#endif