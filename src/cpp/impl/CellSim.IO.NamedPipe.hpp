#ifndef CELLSIM_IO_NAMEDPIPE_HPP
#define CELLSIM_IO_NAMEDPIPE_HPP

#include "base.hpp"

#if CELLSIM_ENV_WINDOWS
    #include <Windows.h>
#elif CELLSIM_ENV_UNIX

#endif

namespace CellSim::IO
{
    /// @brief 名前付きパイプ
    class NamedPipe final {
        friend Cli::CliMain;
        private:
        static NamedPipe s_in;
        static NamedPipe s_out;

#if CELLSIM_ENV_WINDOWS
        ::HANDLE m_pipeHandle;
#elif CELLSIM_ENV_UNIX

#endif

        public:
    };
}

#endif //!CELLSIM_IO_NAMEDPIPE_HPP