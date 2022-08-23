#include "../Includes/location.hpp"
#include "../Includes/tt.hpp"
#include <sstream>
// ADD ERR DOUBLON
location::location() : _name(""),
                        _locations_path(""),
                        _allow_methods(std::vector<std::string>()),
                        _root(""),
                        _client_max_body_size(-1),  
                        _index(std::vector<std::string>()),
                        _autoindex(false),
                        _upload_path("")
                        
{

}

location::~location()
{

}

location::location(const location &obj)
{
    if (this != &obj)
    {
        *this = obj;
    }
}


location    &location::operator=(location const &rhs)
{
    this->_locations_path = rhs._locations_path;
    this->_allow_methods = rhs._allow_methods;
    this->_root = rhs._root;
    this->_autoindex = rhs._autoindex;
    this->_client_max_body_size = rhs._client_max_body_size;
    this->_index = rhs._index;
    this->_upload_path = rhs._upload_path;
    return *this;
}

std::string extract_location_name(std::vector<std::string> text_vector,int index)
{
std::vector<std::string> parser;
std::string name;
    int i = 0;
    int y = 0;
    int count = 0;
    while ( i < text_vector.size())
    {  
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
             parser = split(text_vector[i]," ",(char *)"upload_path");
                }
        }
    i++;
    }

        /**
         * @brief 
         * 
         *
        }
        y = 0;
        while (y < parser.size())
        {
            if (parser[y].compare("upload_path") == 0)
            {   
                server_upload_path = split (text_vector[i]," ","upload_path");

                inside = 1;
            }
            y++;
        }
    i++;
    }
    return (server_upload_path[1]);*/
    return (name);
}



std::string extract_location_path(std::vector<std::string> text_vector,int index,int nb_server)
{
std::vector<std::string> parser;
std::string location_path;
    int i = 0;
    int y = 0;
    int count = 0;
    int find_right_server = 0;
    while ( i < text_vector.size())
    {  
           if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
             parser = split(text_vector[i]," ",(char *)"location");
            return (parser[1]);
            }
        count++;
        }
        }
    i++;
    }
    return (location_path);
}

std::vector<std::string> extract_location_allowed_methods(std::vector<std::string> text_vector,int index,int nb_server)
{
std::vector<std::string> parser;
std::vector<std::string> allowed_methods;
std::vector <std::string > correct_methods;
std::vector<std::string > tmp;
int find_right_server = 0;
    int i = 0;
    int y = 0;
    int count = 0;
    int z = 0;
    while ( i < text_vector.size())
    {  
      if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
        }
        if ( find_right_server == nb_server)
        {

          if(text_vector[i].find("location") != std::string::npos)
        {

            if ( count == index )
                {

                    y = i;
        while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
             {

             int found = 0;
             found = text_vector[y].find("allow_methods") ;
           if (found != std::string::npos)
            {
                 tmp.push_back(text_vector[y]);
                 allowed_methods = split_by_space(tmp);
                 int i = 0;
                 for(std::vector<std::string>::iterator it2 = allowed_methods.begin();it2 != allowed_methods.end();it2++)
                 {
                    if ( i > 0)
                    correct_methods.push_back(*it2);
                    i++;
                 }
                 if(correct_methods.empty())
                 {
                    std::cout << " Error ! Allowed methdos defined in location but no value is put in it ! " << std::endl;
                    exit(1);
                 }
                // tmp.push_back(text_vector[y]);
                // if (!allowed_methods.empty() && allowed_methods.size() > 1)
                // {
                // if (allowed_methods[1] == "GET")
                // correct_methods.push_back("GET");
                // else if (allowed_methods[1] == "POST")
                // correct_methods.push_back("POST");
                // else if (allowed_methods[1] == " DELETE")
                // correct_methods.push_back("DELETE");
                // }
                //  allowed_methods.erase(std::remove(allowed_methods.begin(),allowed_methods.end(),"allow_methods"));
                // for(std::vector<std::string>::iterator it = allowed_methods.begin();it != allowed_methods.end();it++)
                // correct_methods.push_back(*it);
                // if(!tmp[0].empty())  
                // tmp.erase(tmp.begin());
                // allowed_methods = split(text_vector[y]," ","allow_methods");
                // allowed_methods.erase(allowed_methods.beg/in());
                // allowed_methods.push_back("GET");
                // allowed_methods.push_back("POST");
                // allowed_methods.push_back("DELETE");
                // allowed_methods.erase(std::remove(allowed_methods.begin(),allowed_methods.end(),"allow_methods"));
            //   correct_methods = allowed_methods;
                // tmp.clear();
                // std::vector<std::string>::iterator pos = std::find(allowed_methods.begin(),allowed_methods.end(),"allow_methods");
                // if(pos != allowed_methods.end())
                // allowed_methods.erase(std::remove(allowed_methods.begin(),allowed_methods.end(),"allow_methods"));
                // correct_methods.assign(allowed_methods.begin() + 1,allowed_methods.end());
                for(std::vector<std::string>::iterator it = correct_methods.begin();it != correct_methods.end();it++)
             { 
                    //  std::cout << "it :" << *it << std::endl;
                     specified_methods(*it);
            
            }
                return(correct_methods);
               
            }
            y++;
             }
                }
        count++;
       
        }
        }
    i++;
    }
    return (allowed_methods);
}
std::string extract_location_root(std::vector<std::string> text_vector,int index,int nb_server)
{
std::vector<std::string> parser;
std::string location_path;
std::vector <std::string > tmp;
    int i = 0;
    int y = 0;
    int count = 0;
    int find_right_server = 0;
   while ( i < text_vector.size())
    {  
                      if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                 while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
                    {
             parser = split(text_vector[y]," ",(char *)"root");
             if(!parser.empty())
             {

             
             tmp = parser;
             tmp.erase(tmp.begin());
             if (tmp.size() > 0)
             {
                return (tmp[0]);
             }
             else
             {
                std::cout << " root is defined but no value is put in it !  returning(./)for now  location index : " << index << " server index : " << nb_server << std::endl;
                exit(1);
                // return("./");
             }
             }
            y++;
            }
                }
        count++;
        }
        }
    i++;
    }
  //  std::cerr << " No root found in location !" << std::endl;
    return (location_path);
}

long long int extract_location_max_body_size(std::vector<std::string> text_vector,int index,int nb_server)
{
// TO ADD IS NUMBER HERE + SAME FOR SERVER
std::vector<std::string> parser;
std::vector<std::string> location_limit;
std::string location_path;
std::vector<std::string > tmp;
 std::stringstream ss;
    int i = 0;
    int y = 0;
    int count = 0;
    int num = 0;
    int inside = 0;
    int find_right_server = 0;
   while ( i < text_vector.size())
    {  
                      if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {

          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
                    {
       
             parser = split(text_vector[y]," ",(char *)"client_max_body_size");
             inside = 1;
                if (!parser.empty())
                {
                    tmp = parser;
                    tmp.erase(tmp.begin());
                    if(tmp.size() > 0)
                    {
                ss << tmp[0];
                ss >> num;
                //std::cout << "COUCOU AKI" << std::endl;
                    return (num);
                    }
                    else
                    {
                        std::cout << "location client max body size defined but nothing is put in it ! location index : " << index << " server index : " << nb_server << std::endl;
                    exit(1);
                    }
                }
            y++;
            }
                }
        count++;
        }
        }
    i++;
    }
    // std::cerr << " No client_max_body_size  !" << std::endl;
    return (num);
}
std::vector<std::string> extract_location_index(std::vector<std::string> text_vector,int index,int nb_server)
{

  std::vector<std::string> parser;
  std::vector <std::string> server_index;
  std::vector <std::string> correct_index;
std::vector<std::string> location_limit;

    int i = 0;
    int y = 0;
    int inside = 0;
    int count = 0;
    int find_right_server = 0;
   while ( i < text_vector.size())
    {  
         if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {

          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
                    while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
                    {

             parser = split(text_vector[y]," ",(char *)"index");
                if (!parser.empty())
                {
                    int i = 0;
                    std::vector<std::string> tmp = parser;
                    for(std::vector<std::string>::iterator it = tmp.begin();it != tmp.end();it++)
                    {
                    if (i > 0 )
                    correct_index.push_back(*it);
                    i++;
                    }
                    // correct_index.assign(parser.begin() + 1,parser.end());
                    return (correct_index);
                }
            y++;
            }
                }
        count++;
        }
        }
    i++;
    }
    // std::cout << " No Index in location !" << std::endl;
    return (server_index);
}
bool extract_location_autoindex(std::vector<std::string > text_vector,int index,int nb_server)
{

 std::vector<std::string> parser;
    int i = 0;
    int y = 0;
    int inside = 0;
    bool autoindex = false;
    int count = 0;
    int find_right_server = 0;
std::vector<std::string> location_limit;
std::vector <std::string > tmp;
   while ( i < text_vector.size())
    {  
         if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {
            if ( count == index )
                {
                    y = i;
           while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
                    {
             parser = split(text_vector[y]," ",(char *)"autoindex");
             if(!parser.empty())
             {

             
             tmp = parser;
             tmp.erase(tmp.begin());
             if (tmp.size() > 0)
             {
                    if(tmp[0].compare("on") == 0)
                    return (true);
                    else
                    return (false);
             }
             else
             {
                std::cout << "autoindex is defined but no value is put in it ! return false for now , location " << index << " server : " << nb_server << std::endl;
                return(false);
             }
                
            }
            y++;

            //     return(false);
                }
                }
        count++;
        }
        }
    i++;
    }
            //  std::cout << " No autoindex found " << std::endl;

    return (false);
}

std::string extract_location_upload_path(std::vector<std::string> text_vector,int index,int nb_server)
{
std::vector<std::string> parser;
std::string location_path;
std::vector<std::string> location_limit;

//str = delim.c_str();
    int i = 0;
    int y = 0;
    int count = 0;
    int find_right_server = 0;
    std::vector<std::string > tmp;
   while ( i < text_vector.size())
    {  
          if(text_vector[i].compare("server") == 0)
     {
           find_right_server++;
    }
        if ( find_right_server == nb_server)
        {
          if(text_vector[i].find("location") != std::string::npos)
        {
             //std::cout << "BRRRRRRRR" << std::endl;

            if ( count == index )
                {
            // std::cout << "HHHHHHHHHH" << std::endl;

                    y = i;
             while ( y < text_vector.size() && text_vector[y].find("}") == std::string::npos)
             {
             parser = split(text_vector[y]," ",(char *)"upload_path");
            if(parser.size()> 0)
            {
            tmp = parser;
             tmp.erase(tmp.begin());
             if(tmp.size() > 0)
             {
             location_path = tmp[0];
             }
             else
             {
               std::cout << "upload path is defined byut no value is put in it ! location index : " << index << " server index " << nb_server << std::endl;
           return(location_path);
             }
             }
             //std::cout << "PLEASE WOORK FFS" << std::endl;
           
            y++;
            }
                }
              count++;
                }
        
        }
    i++;
    }
    return (location_path);
}

location::location(std::vector<std::string> text_vector,int index,int nb_server)
{
    // std::vector <std::string> allowed_methods;
    // allowed_methods.push_back("GET");
    // allowed_methods.push_back("DELETE");
    // allowed_methods.push_back("POST");
    std::vector<std::string> tmp;
    this->_index = tmp;
    this->_name = extract_location_path(text_vector,index, nb_server);
     this->_locations_path = extract_location_path(text_vector,index,nb_server);
    //  this->_allow_methods = allowed_methods;
    this->_allow_methods = extract_location_allowed_methods(text_vector,index,nb_server);
     this->_root = extract_location_root(text_vector,index,nb_server);
    this->_client_max_body_size = extract_location_max_body_size(text_vector,index,nb_server);
    this->_index = extract_location_index(text_vector,index,nb_server);
    this->_autoindex = extract_location_autoindex(text_vector,index,nb_server);
    this->_upload_path = extract_location_upload_path(text_vector,index,nb_server);
//      std::cout << "----------------------------********************************* ------------------"  << std::endl;

//    // std::cout << this->_locations_path << std::endl;
//      std::cout << "-----------------------Location name  | Index :  " << index << " <<  ------------------"  << std::endl;
//     std::cout << this->_name << std::endl;
// //      std::cout << "-----------------------Location index  | Index :  " << index << " <<  ------------------"  << std::endl;
// //      for (std::vector<std::string>::iterator it2 = this->_index.begin();it2 != this->_index.end();it2++)
// //         std::cout << *it2 << std::endl;
//     std::cout << "-----------------------Location PATH  | Index :  " << index << " <<  ------------------"  << std::endl;
  
//     std::cout << this->_locations_path << std::endl;
//    std::cout << "-----------------------Location allowed moethods | Index :  " << index << " <<  ------------------"  << std::endl;
//      for (std::vector<std::string>::iterator it1 = this->_allow_methods.begin();it1 != this->_allow_methods.end();it1++)
//          std::cout << *it1 << std::endl;
//      std::cout << "-----------------------Location Root | Index :  " << index << " <<  ------------------"  << std::endl;
//     std::cout << this->_root << std::endl;
//          std::cout << "-----------------------Location Max Body Size | Index :  " << index << " <<  ------------------"  << std::endl;
//     std::cout << this->_client_max_body_size << std::endl;
    //  std::cout << "-----------------------Location index  | Index :  " << index << " <<  ------------------"  << std::endl;
    //  for (std::vector<std::string>::iterator it2 = this->_index.begin();it2 != this->_index.end();it2++)
    //      std::cout << *it2 << std::endl;
//         std::cout << "-----------------------location  AutoIndex    : ------------------"  << std::endl;
//         if (this->_autoindex == true)
//         std::cout << "autoindex on  location : " << index  << " server : " << nb_server << std::endl;
//         else if (this->_autoindex == false)
//         std::cout << "autoindex off  location :" << index << " server : " << nb_server << std::endl;
// //         
//    std::cout << "-----------------------Location _upload_path | Index :  " << index << " <<  ------------------"  << std::endl;
//     std::cout << this->_upload_path << std::endl;
      
         
}


std::string location::get_upload_path() const
{
    return (this->_upload_path);
}

std::string location::get_name() const
{
    return (this->_name);
}

std::string location::get_locations_path() const
{
    return (this->_locations_path);
}

std::vector<std::string> location::get_methods() const
{
    return (this->_allow_methods);
}

unsigned int location::get_methods_size() const
{
    return (this->_allow_methods.size());
}
std::string location::get_root() const
{
    return (this->_root);
}
    bool                        location::get_autoindex() const
    {
        return (this->_autoindex);
    }

    long long int               location::get_client_max_body_size() const
    {
        return (this->_client_max_body_size);
    }

    unsigned int                location::get_index_size() const
    {
        return (this->_index.size());
    }
    std::vector<std::string>    location::get_index() const
    {
        return(this->_index);   
    }
