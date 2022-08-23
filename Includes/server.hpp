#ifndef SERVER_HPP
#define SERVER_HPP
//#include "config_file.hpp"
#include "location.hpp"
#include "Cgi.hpp"
#include <string>
#include <iostream>
#include <netinet/in.h>

#include <sys/socket.h> // For socket functions
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <map>


class location;
class cgi;
class server
{
    private :
        bool        response_chuncked;

    public:
        bool        get_response_chunked() { return (response_chuncked);}
        void        set_response_chunked( bool ld ) { response_chuncked = ld;}

protected:
    std::vector<std::string>                _name;
    int                                     _listen_port;
    std::string                             _listen_host;
    std::vector<std::string>                _allowed_methods;
    std::vector<std::string>                _index;
    std::string                             _upload_path;
    // std::vector<std::vector<std::string> >  _error_pages;
    std::map <std::string ,std::string >      _error_pages;
    std::map <std::string, std::string >      _redirections;
    // std::vector<std::vector<std::string> >  _redirections;
    std::string                             _root;
    std::vector<location>                   _location;
    std::vector<cgi>                        _cgi;
    long long int                           _client_max_body_size;
    bool                                    _autoindex;

public:
    server();
    ~server();
    server(std::vector<std::string > text_vector,int index);
    server (const server &src);
    server &operator=(server const &rhs);
    std::string                  get_name(int) const;
    unsigned int                 get_name_size() const;
    std::string                  get_listen_host() const;
    int                          get_listen_port() const;
    std::vector<std::string>     get_allowed_methods() const;
    unsigned int                 get_allowed_methods_size() const;
    std::vector<std::string>     get_index() const;
    unsigned int                 get_index_size() const;
    // std::vector<std::string>     get_error_pages(int i) const;
    // std::vector<std::vector<std::string> >     get_error_pages() const{return _error_pages;};/
    std::map<std::string,std::string >     get_error_pages() const{return _error_pages;};
    std::map <std::string,std::string >   get_redirections() const { return _redirections;};
    unsigned int                 get_error_pages_size() const;
    unsigned int                 get_redirections_size() const;
    // std::vector<std::string>     get_redirections(int i) const;
    // std::vector<std::vector<std::string> > get_redirections() const;
    std::string                  get_root() const;
    std::string                  get_upload_path() const;
    std::vector<location>        get_location() const;
    location                     get_location(int i) const;
    unsigned int                 get_location_size() const;
    cgi                          get_cgi(int i) const;
    unsigned int                 get_cgi_size() const;
    long long int                get_client_max_body_size() const;
    bool                         get_autoindex() const;

    std::vector<cgi>             get_cgi() const;

    sockaddr_in                  get_sock_ader();
};
#endif