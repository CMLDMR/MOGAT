#ifndef DB_H
#define DB_H

#include <iostream>

namespace DB {

    static const std::string DB{"MOGAT"};

    namespace News {
        static std::string title{"title"};
        static std::string html{"html"};
        static std::string clickCount{"readCount"};
        static std::string icon{"icon"};
        static std::string published{"published"};
        namespace publishState {
        static bool ON{true};
        static bool OFF{false};
        }

        static std::string author{"author"};
        static std::string publishedDate{"date"};

        static std::string collection{"News"};
    }


    namespace User {
        static std::string username{"username"};
        static std::string password{"pwd"};
        static std::string name{"name"};
        static std::string collection{"Users"};
    }
}

#endif // DB_H
