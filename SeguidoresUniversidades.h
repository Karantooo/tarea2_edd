#include <string>

enum opcion_de_clave{
    se_usa_user_id,
    se_usa_user_name
};

class SeguidoresUniversidades{
    public:
        std::string university;
        long long user_id;
        std::string user_name;
        int number_tweets;
        int friends_count;
        int followers_count;
        std::string created_at;

};