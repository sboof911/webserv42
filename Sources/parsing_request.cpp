
#include "../Includes/request.hpp"
#include "../Includes/tt.hpp"

// CHECK QWERY  
std::vector<std::string> parsing_request(char* buffer)
{
    int i  = 0;
    std::string str;
    std::vector<std::string> request;
    while (buffer[i])
    {
        
        str.push_back(buffer[i]);
          if(buffer[i] == '\n' && buffer[i] != '\0')// this is too form string not send char by char
          {
            request.push_back(str);
            str.clear();
          }
          else if (buffer[i + 1] == '\0')
          {
            // std::cout << "str=> " << str << std::endl;
            request.push_back(str);
            str.clear();

          }
            //i++;
        i++;
    }
return (request);
}
int check_post_request(std::vector<std::string > request)
{
    int i = 0;
    int transfer_encoding = 0;
    int Content_length = 0;
    std::cout << "INSIDE POST REQUEST" << std::endl;
    while ( i < request.size())
    {
        if (request[i].find("transfer_encoding:") == 0)
       transfer_encoding = 1;
        if (request[i].find("Content-Length:") == 0)
     {   
        Content_length = 1;
     }
        i++;

    }
    std::cout << "=>>>>>" << Content_length << "   " << transfer_encoding << std::endl;
    if (Content_length == 1 || transfer_encoding == 1)
        return (1);
    return (0);
}
int get_request_method(std::vector<std::string > request)
{
   // std::string request;
 std::vector<std::string> method;

    size_t found = request[0].find("GET");
    if(found != string::npos)
    {
    method = split(request[0]," ",(char *)"GET");
    std::cout << method[0] << std::endl;
    return(1);
    }
    found = request[0].find("POST");
     if(found != string::npos)
    {
    method = split(request[0]," ",(char *)"POST");
    std::cout << method[0] << std::endl;
    return (2);
    }
      found = request[0].find("DELETE");
     if(found != string::npos)
    {
    method = split(request[0]," ",(char *)"DELETE");
    std::cout << method[0] << std::endl;
    return (3);
    }
    // std::cout << "Unknow REQUEST METHOD" << std::endl;
    return (0);
}

int get_location_length(std::string first_line)

{
std::string s = first_line;
std::string delimiter = " ";

size_t pos = 0;
int count = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
    if (count == 1)
    {
        return (token.size());
    }
    count++;
}
return (0);

}

int get_vrs_length(std::string first_line,int found)
{
    int count = 0;
    for (int i = found;i < first_line.length();i++)
    {

      count++;
    }
    return (count);
}

std::vector<std::string>     split_sboof(std::string s1, std::string delim)
{
    std::vector<std::string>     vector;
    std::size_t found = s1.find(delim, 1);
    std::size_t help = 0;

    while (found != std::string::npos)
    {
        if (s1.substr(help, found - help) != "/")
            vector.push_back(s1.substr(help, found - help));
        help = found;
        (delim != "/") ? help++ : help;
        found = s1.find(delim, help + 1);
    }
    vector.push_back(s1.substr(help, s1.size()));

    return (vector);
}

std::string get_request_location(std::vector<std::string > request)
{
    std::string location;
    std::vector <std::string > method;
    std::vector <std::string > parsing_helper;
  int length = 0;
  
         if(request[0].find("?") != std::string::npos)
         {
          method = split_sboof(request[0]," ");
           if((method.size() > 1) && !method[1].empty())
           {
            int savior = 0;
            size_t found = 0;
            found = method[1].find("?");
            if (found != std::string::npos)
            {
              length = method[1].size() - found;
              if (found == 1)
              return ("/");
              std::cout  << " MSIZE "  << method[1].size() << "LENGTHHHHHH ISSSSSSSS " << length << std::endl;
            }
            
            parsing_helper = split_sboof(method[1],"?");
            for(std::vector<std::string>::iterator it = parsing_helper.begin();it != parsing_helper.end();it++)
            {
              if (savior == 0 && ((*it) == "?"))
              return ("/");
              savior++;
            }
            location = parsing_helper[0];
           }
         
         }
       else
       {
      method = split_sboof(request[0]," ");
      if(method.empty() || method.size() == 1)
        return("/");
        if(!method[1].empty() && method.size() > 2 )
        location = method[1];
        else
        return "/" ; // If empty SGV To fixe 
       }
    return location;
}
int get_number_of_query(std::string first_line)
{
  int i = 0;

  int count = 0;
  while (first_line[i])
  {
    if (first_line[i] == '?')
    count++;
    i++;
  }
  return (count);
}

std::string get_request_query(std::vector<std::string > request)
{
   std::string qwery;
    std::vector <std::string > method;
    std::vector <std::string > parsing_helper;

  int count = 0;
  int length = 0;
  size_t found  = 0;

          method = split_sboof(request[0]," ");
          if(method.empty() || method.size() == 1)
          return qwery;
              if(!method[1].empty() && count == 0)
           {
             found = method[1].find("?");
                 if(found != std::string::npos )
         {
             length = method[1].size() - found;
             qwery.insert(0,method[1],found + 1,method[1].size());
           }
           }
    return qwery;
}


std::string get_request_vrs(std::string first_line)
{
   
    std::string vrs;
    std::vector <std::string > method;
    std::vector<std::string> tmp;
    std::vector<std::string> first_word;
    tmp.push_back(first_line);
    first_word = split_by_space(tmp);
    if (first_word.size() == 3)
    {
      first_word[2].pop_back();
      first_word[2].pop_back();
      return ("HTTP/1.1");
    }
    if (first_word.size() == 2)
       vrs = "HTTP/1.1";
    return "HTTP/1.1";
}

std::vector<std::string > splitv2(std::string line,std::string delim)
{
std::string s = line;
std::string delimiter = delim;
std::vector<std::string> splited;
size_t pos = 0;
int count = 0;
std::string token;
while ((pos = s.find(delimiter)) != std::string::npos) {
    token = s.substr(0, pos);
    s.erase(0, pos + delimiter.length());
    splited.push_back(token);
}
return (splited);
}
int get_request_port(std::vector<std::string> full_request)
{
  int num = 0;
  int i = 0;
  int length = 0;
   full_request.assign(full_request.begin() + 1,full_request.end());
   std::string head;
   std::string tail;
   std::vector<std::string> tmp;
   size_t found = 0;
     while ( i < full_request.size())
     {
       
        found = full_request[i].find(":");
        if(found != string::npos)
    {
      // tmp = split(full_request[i]," ",":");
      length = full_request[i].size() - found;
      head.insert(0,full_request[i],0,found);
      tail.insert(0,full_request[i],found + 2,length - 4);
      if (head == "Host")
      {
     size_t found_delim = 0;
        found_delim = tail.find(":");
        std::string new_tail;
        if ( found_delim != std::string::npos)
        {
          tmp = split_sboof(tail,":");
          tail.clear();
          tail = tmp[1];
           if(!tmp[1].empty() && isnumber(tmp[1]))
                    num = std::stoi(tmp[1]);
        }
      }
     }
     i++;
     }
  return (num);

}
 std::map<std::string, std::string> get_request_headers(std::vector <std::string > full_request)
 {
    int i = 0;
    std::map<std::string ,std::string > headers;
    std::vector <std::string > get_headers;
    std::vector <std::string > tmp;
    std::string head;
    std::string tail;
    int length = 0;
       size_t found ;
    full_request.assign(full_request.begin() + 1,full_request.end());
    while ( i < full_request.size())
    {   
        if (full_request[i].compare("\n")  == 0)
        {
        return (headers); // to TEST
        }
      found = full_request[i].find(":");
        if(found != string::npos)
    {
      length = full_request[i].size() - found;
      head.insert(0,full_request[i],0,found);
      tail.insert(0,full_request[i],found + 2,length - 4);
      if(head == "Host")
      {
        size_t found_delim = 0;
        found_delim = tail.find(":");
        std::string new_tail;
        if ( found_delim != std::string::npos)
        {
          tmp = split_sboof(tail,":");
          tail.clear();
          tail = tmp[0];
        }

      }
    headers[head] = tail;
    head.clear();
    tail.clear();

    }
    else
    return (headers);  

        i++;
    }

    return (headers);
 }

 std::string get_request_body(std::vector < std::string > full_request)
 {
    int i = 0;
    int inside = 0;
    std::string body;
    

    while ( i < full_request.size())
    {
           if (inside == 1)
        {
          body.insert(body.size(),full_request[i]);
        }
        if (full_request[i].size() == 2)
        inside = 1;
     
        i++;
    }
    return (body);
 }