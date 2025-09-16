#include "CellSim.Settings.Config.CellBehavior.User.hpp"
#include "CellSim.Users.UserCellBehavior.hpp"
#include "impl/CellSim.Cells.CellBehaviorPtr.hpp"
#include "impl/CellSim.Messages.hpp"

#include <nlohmann/json.hpp>
#include <stdexcept>

using namespace nlohmann;
using namespace CellSim;
using namespace CellSim::Cells;
using namespace CellSim::Users;

namespace CellSim::Settings
{
    CellBehaviorPtr Config::CellBehavior::User::FromJson(
        json const& config
    )
    {
        if (config.is_null()) [[unlikely]] {
            throw ::std::invalid_argument(
                ""
            );
        }

        // TODO: ここに処理を追加します

        return CellBehaviorPtr::FromPointerUnsafe(
            new UserCellBehavior()
        );
    }
}