#ifndef CELLSIM_CELLS_CELLTYPE_HPP
#define CELLSIM_CELLS_CELLTYPE_HPP

#include "base.hpp"
#include "CellSim.Graphics.Color.hpp"
#include "CellSim.Model.CellSimulationModel.hpp"
#include <string>
#include <string_view>
#include <vector>

namespace CellSim::Cells
{
    /// @brief 細胞の種類
    /// @note このクラスはスレッドセーフではありません
    class CellType final {
        private:

        class s_data final {
            public:
            ::std::string Name;
            Graphics::Color Color;
            Model::CellSimulationModel::Params* SimulationModelParams;

            constexpr s_data(
                ::std::string name,
                Graphics::Color color,
                Model::CellSimulationModel::Params* simulationModelParams
            ) noexcept;

            s_data(s_data const&) = delete;
            constexpr s_data(s_data&& right) noexcept;

            ~s_data();

            s_data& operator=(s_data const&) = delete;
            constexpr s_data& operator=(s_data&& right) noexcept;
        };

        static ::std::vector<s_data> s_names;

        uint32_t m_id;

        explicit constexpr CellType(uint32_t id) noexcept;

        public:

        static bool Initialize();

        [[nodiscard]] static constexpr CellType Invalid() noexcept;

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(
            const char* name,
            Graphics::Color color,
            Model::CellSimulationModel::Params* params
        );

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(
            ::std::string name,
            Graphics::Color color,
            Model::CellSimulationModel::Params* params
        );

        /// @brief 種類を追加
        /// @param name 名前
        /// @return その名前に対応するCellType値
        [[nodiscard]] static CellType AddName(
            ::std::string_view name,
            Graphics::Color color,
            Model::CellSimulationModel::Params* params
        );

        /// @brief 指定した名前に対応するCellType値を取得
        /// @param name 名前
        /// @return nameに対応するCellType値
        /// @return 見つからない場合はInvalid()
        [[nodiscard]] static CellType FromName(::std::string_view name) noexcept;
        
        CellType() = default;

        [[nodiscard]] constexpr Graphics::Color Color() const noexcept;

        /// @brief 
        [[nodiscard]] constexpr uint32_t Id() const noexcept;

        /// @brief 名前
        [[nodiscard]] constexpr ::std::string const& Name() const noexcept;

        [[nodiscard]] constexpr Model::CellSimulationModel::Params* Params() const noexcept;
    };

    [[nodiscard]] constexpr bool operator==(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator!=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator<(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator<=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator>(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr bool operator>=(CellType left, CellType right) noexcept;
    [[nodiscard]] constexpr ::std::strong_ordering operator<=>(CellType left, CellType right) noexcept;
}

namespace CellSim::Cells
{
    constexpr CellType::s_data::s_data(
        ::std::string name,
        Graphics::Color color,
        Model::CellSimulationModel::Params* simulationModelParams
    ) noexcept
        : Name(::std::move(name))
        , Color(color)
        , SimulationModelParams(simulationModelParams)
    {
    }

    constexpr CellType::s_data::s_data(s_data&& right) noexcept
        : Name(::std::move(right.Name))
        , Color(right.Color)
        , SimulationModelParams(right.SimulationModelParams)
    {
        right.SimulationModelParams = nullptr;
    }

    inline CellType::s_data::~s_data()
    {
        if (SimulationModelParams == nullptr) return;
        delete SimulationModelParams;
    }

    constexpr CellType::s_data& CellType::s_data::operator=(s_data&& right) noexcept
    {
        if (this != &right) [[likely]] {
            Name = ::std::move(right.Name);
            Color = right.Color;
            if (SimulationModelParams != nullptr) [[likely]] delete SimulationModelParams;
            SimulationModelParams = right.SimulationModelParams;
            right.SimulationModelParams = nullptr;
        }
        return *this;
    }

    constexpr CellType::CellType(uint32_t id) noexcept
        : m_id(id)
    {
    }

    constexpr CellType CellType::Invalid() noexcept
    {
        return CellType(0);
    }

    inline CellType CellType::AddName(
        const char* name,
        Graphics::Color color,
        Model::CellSimulationModel::Params* params
    )
    {
        return AddName(
            ::std::string_view{ name },
            color,
            params
        );
    }

    constexpr Graphics::Color CellType::Color() const noexcept
    {
        return s_names[m_id].Color;
    }

    constexpr uint32_t CellType::Id() const noexcept
    {
        return m_id;
    }

    constexpr ::std::string const& CellType::Name() const noexcept
    {
        return s_names[m_id].Name;
    }

    constexpr Model::CellSimulationModel::Params* CellType::Params() const noexcept
    {
        return s_names[m_id].SimulationModelParams;
    }

    constexpr bool operator==(CellType left, CellType right) noexcept
    {
        return left.Id() == right.Id();
    }

    constexpr bool operator!=(CellType left, CellType right) noexcept
    {
        return left.Id() != right.Id();
    }

    constexpr bool operator<(CellType left, CellType right) noexcept
    {
        return left.Id() < right.Id();
    }

    constexpr bool operator<=(CellType left, CellType right) noexcept
    {
        return left.Id() <= right.Id();
    }

    constexpr bool operator>(CellType left, CellType right) noexcept
    {
        return left.Id() < right.Id();
    }

    constexpr bool operator>=(CellType left, CellType right) noexcept
    {
        return left.Id() <= right.Id();
    }

    constexpr ::std::strong_ordering operator<=>(CellType left, CellType right) noexcept
    {
        return left.Id() <=> right.Id();
    }
}

#endif //!CELLSIM_CELLS_CELLTYPE_HPP