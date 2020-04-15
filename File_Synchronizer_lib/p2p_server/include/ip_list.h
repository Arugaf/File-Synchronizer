#ifndef FILE_SYNCHRONIZER_IP_LIST_H
#define FILE_SYNCHRONIZER_IP_LIST_H

#include <string>

class ip_list{

public:

    ip_list();

    ~ip_list();

    vector <std::string> return_ip_list();

    int get_ip_list();

private:

    vector <std::string> ip_list;

};

#endif //FILE_SYNCHRONIZER_IP_LIST_H
