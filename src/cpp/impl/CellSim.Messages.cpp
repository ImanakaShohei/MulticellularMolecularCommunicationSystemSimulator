#include "CellSim.Messages.hpp"

#if CELLSIM_ENV_WINDOWS
    #include <Windows.h>
#else
    #include <locale.h>
#endif

#include <ctype.h>
#include <filesystem>
#include <stdexcept>

namespace CellSim
{
    void Messages::s_getLanguage(char(&arr)[6])
    {
#if CELLSIM_ENV_WINDOWS
        ::LANGID langId = ::GetUserDefaultUILanguage();
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
        ::LCIDToLocaleName(MAKELCID(langId, SORT_DEFAULT), localeName, LOCALE_NAME_MAX_LENGTH, 0);

        for (size_t i = 0; i < 5; i++) {
            arr[i] = ::tolower(localeName[i]);
        }
        arr[5] = '\0';
#else
        ::std::string currentLocale = ::setlocale(LC_CTYPE, nullptr);
        
        char* osLocale = ::setlocale(LC_CTYPE, "");

        for (size_t i = 0; i < 5; i++) {
            arr[i] = osLocale[i];
        }

        arr[2] = '-';
        arr[5] = '\0';

        ::setlocale(LC_CTYPE, currentLocale.c_str());
#endif
        
    }

    void Messages::s_setMessage(::std::string_view languageName)
    {
        ::std::string languagePath = "./languages/";
        languagePath.append(languageName);

        if (!::std::filesystem::exists(languagePath)) {
            using namespace std;
            constexpr string_view us = "en-us"sv;

            // 無限ループ防止
            if (languageName == us) [[unlikely]] throw runtime_error("The path './languages/en-us/' not found.");

            s_setMessage(us);
            return;
        }

        languagePath.push_back((char)::std::filesystem::path::preferred_separator);

        s_loadMessages(languagePath, "general.lang");
        s_loadSingleMessage(languagePath, "help.lang", "");
    }
}