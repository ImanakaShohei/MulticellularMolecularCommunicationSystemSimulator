#ifndef CELLSIM_IO_DIRECTORYCREATER_HPP
#define CELLSIM_IO_DIRECTORYCREATER_HPP

#include "base.hpp"
#include <filesystem>

namespace CellSim::IO
{
    class DirectoryCreater final {
        private:
        public:

        static void Create(
            ::std::filesystem::path const& p
        );
    };
}

#endif //!CELLSIM_IO_DIRECTORYCREATER_HPP