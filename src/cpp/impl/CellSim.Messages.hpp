#ifndef CELLSIM_MESSAGES_HPP
#define CELLSIM_MESSAGES_HPP

#include "base.hpp"

#include <map>
#include <string>
#include <string_view>

namespace CellSim
{
    class Messages final {
        private:

        static bool s_loaded;
        static ::std::map<::std::string, ::std::string> s_map;
        
        static void s_getLanguage(char(&arr)[6]);

        static void s_loadMessages(::std::string const& folderPath, ::std::string_view fileName);
        static void s_loadSingleMessage(::std::string const& folderPath, ::std::string_view fileName, ::std::string_view messageName);

        static void s_setMessage(::std::string_view languageName);

        public:

        static ::std::string const& Get(::std::string const& name);

        static bool Initialize();
    };
}

namespace CellSim
{
    inline ::std::string const& Messages::Get(::std::string const& name)
    {
        return s_map[name];
    }
}

#endif //!CELLSIM_MESSAGES_HPP