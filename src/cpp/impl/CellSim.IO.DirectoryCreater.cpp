#include "CellSim.IO.DirectoryCreater.hpp"

namespace CellSim::IO
{
    void DirectoryCreater::Create(
        ::std::filesystem::path const& p
    )
    {
        if (::std::filesystem::exists(p)) return;

        ::std::filesystem::path parent = p.parent_path();

        if (!parent.empty() && !::std::filesystem::exists(parent)) Create(parent);

        ::std::filesystem::create_directory(p);
    }
}