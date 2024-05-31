#include <string>
#include <iostream>
#pragma once

class SeguidoresUniversidades{
    public:
        std::string university;
        long long user_id;
        std::string user_name;
        long long number_tweets;
        long long friends_count;
        long long followers_count;
        std::string created_at;

};

std::ostream& operator<< (std::ostream& stream, SeguidoresUniversidades seguidor){
    stream << seguidor.university << "\n";
    stream << seguidor.user_id << "\n";
    stream << seguidor.user_name << "\n";
    stream << seguidor.number_tweets << "\n";
    stream << seguidor.friends_count << "\n";
    stream << seguidor.followers_count << "\n";
    stream << seguidor.created_at << "\n";
    return stream;
}