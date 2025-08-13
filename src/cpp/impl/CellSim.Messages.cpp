#include "CellSim.Messages.hpp"

#if CELLSIM_ENV_WINDOWS
    #include <Windows.h>
#else
    #include <locale.h>
#endif

#include <ctype.h>
#include <filesystem>
#include <fstream>
#include <stdexcept>

namespace CellSim
{
    constinit bool Messages::s_loaded = false;
    ::std::map<::std::string, ::std::string> Messages::s_map;

    void Messages::s_getLanguage(char(&arr)[3])
    {
#if CELLSIM_ENV_WINDOWS
        ::LANGID langId = ::GetUserDefaultUILanguage();
        wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
        ::LCIDToLocaleName(MAKELCID(langId, SORT_DEFAULT), localeName, LOCALE_NAME_MAX_LENGTH, 0);

        for (size_t i = 0; i < 2; i++) {
            arr[i] = ::tolower(localeName[i]);
        }
        arr[2] = '\0';
#else
        ::std::string currentLocale = ::setlocale(LC_CTYPE, nullptr);
        
        char* osLocale = ::setlocale(LC_CTYPE, "");

        for (size_t i = 0; i < 2; i++) {
            arr[i] = ::tolower(osLocale[i]);
        }

        arr[2] = '\0';

        ::setlocale(LC_CTYPE, currentLocale.c_str());
#endif
        
    }

    void Messages::s_loadMessages(::std::string const& folderPath, ::std::string_view fileName)
    {
        ::std::string filePath = folderPath;
        filePath.append(fileName);
        ::std::ifstream ifs(filePath);

        if (!ifs) [[unlikely]] throw ::std::runtime_error("Failed to open the specified file: " + filePath);

        ::std::string line;

#if CELLSIM_ENV_WINDOWS
        ::std::vector<wchar_t> vec;
#endif

        while (::std::getline(ifs, line)) {
            if (line.size() == 0) continue;
#if CELLSIM_ENV_WINDOWS
            // UTF-8 -> UTF-16 -> ACP
            int wLength = ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), nullptr, 0) + 1;
            
            if (wLength == 1) [[unlikely]] throw ::std::runtime_error("Failed to convert codePage");

            if (vec.size() < (size_t)wLength) {
                vec.resize(wLength);
            }

            ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), vec.data(), (int)vec.size());

            int cLength = ::WideCharToMultiByte(CP_ACP, 0, vec.data(), wLength - 1, nullptr, 0, nullptr, nullptr) + 1;

            if (cLength == 1) [[unlikely]] throw ::std::runtime_error("Failed to convert codePage");

            line.resize(cLength - 1, '\0');
            
            ::WideCharToMultiByte(CP_ACP, 0, vec.data(), wLength - 1, line.data(), (int)(line.size() + 1), nullptr, nullptr);
#endif
            // name=value
            size_t index = line.find('=');
            if (index == ::std::string::npos)  [[unlikely]] throw ::std::runtime_error("The format of the language file is invalid.");

            if (index == line.size()) [[unlikely]] throw ::std::runtime_error("The format of the language file is invalid.");

            s_map.emplace(line.substr(0, index), line.substr(index + 1));
        }

    }

    void Messages::s_loadSingleMessage(::std::string const& folderPath, ::std::string_view fileName, ::std::string messageName)
    {
        ::std::string filePath = folderPath;
        filePath.append(fileName);
        ::std::ifstream ifs(filePath);

        if (!ifs) [[unlikely]] throw ::std::runtime_error("Failed to open the specified file: " + filePath);

        ::std::string line;
        ::std::string result;

#if CELLSIM_ENV_WINDOWS
        ::std::vector<wchar_t> vec;
#endif

        while (::std::getline(ifs, line)) {
            if (line.size() == 0) {
                result.push_back('\n');
                continue;
            }

#if CELLSIM_ENV_WINDOWS
            // UTF-8 -> UTF-16 -> ACP
            int wLength = ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), nullptr, 0) + 1;
            
            if (wLength == 1) [[unlikely]] throw ::std::runtime_error("Failed to convert codePage");

            if (vec.size() < (size_t)wLength) {
                vec.resize(wLength);
            }

            ::MultiByteToWideChar(CP_UTF8, 0, line.c_str(), (int)line.size(), vec.data(), (int)vec.size());

            int cLength = ::WideCharToMultiByte(CP_ACP, 0, vec.data(), wLength - 1, nullptr, 0, nullptr, nullptr) + 1;

            if (cLength == 1) [[unlikely]] throw ::std::runtime_error("Failed to convert codePage");

            line.resize(cLength - 1, '\0');
            
            ::WideCharToMultiByte(CP_ACP, 0, vec.data(), wLength - 1, line.data(), (int)(line.size() + 1), nullptr, nullptr);
#endif
            result.append(line);
            result.push_back('\n');
        }

        if (result.size() == 0) [[unlikely]] throw ::std::runtime_error("The format of the language file is invalid.");
        result.pop_back();

        s_map.emplace(::std::move(messageName), ::std::move(result));
    }

    void Messages::s_setMessage(::std::string_view languageName)
    {
        ::std::string languagePath = "./languages/";
        languagePath.append(languageName);

        if (!::std::filesystem::exists(languagePath)) {
            using namespace std;
            constexpr string_view en = "en"sv;

            // 無限ループ防止
            if (languageName == en) [[unlikely]] throw runtime_error("The path './languages/en/' was not found.");

            s_setMessage(en);
            return;
        }

        languagePath.push_back((char)::std::filesystem::path::preferred_separator);

        s_loadMessages(languagePath, "general.txt");
        s_loadSingleMessage(languagePath, "help.txt", "Cli.HelpOption.Message");
    }

    bool Messages::Initialize()
    {
        if (s_loaded) [[unlikely]] return false;

        char arr[3];

        s_getLanguage(arr);

        s_setMessage(arr);

        s_loaded = true;

        return true;
    }
}