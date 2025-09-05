#ifndef CELLSIM_CELLS_CELLBEHAVIORPTR_HPP
#define CELLSIM_CELLS_CELLBEHAVIORPTR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    /// @brief CellBehaviorポインタ
    /// @attention このクラスはスレッドセーフではありません
    class CellBehaviorPtr final {
        private:

        constexpr CellBehaviorPtr(
            CellBehavior* ptr
        ) noexcept;

        CellBehavior* m_ptr;

        void m_copyFrom(
            CellBehaviorPtr const& right
        );

        void m_delete() noexcept;

        public:

        [[nodiscard]] static CellBehaviorPtr FromType(
            CellBehaviorType type
        );

        static CellBehaviorPtr FromPointer(
            ::std::nullptr_t
        ) = delete;

        /// @brief 生ポインタから作成
        /// @param ptr ポインタ
        /// @return オブジェクト
        /// @exception std::invalid_argument: ptrがnullptrのとき
        [[nodiscard]] static CellBehaviorPtr FromPointer(
            CellBehavior* ptr
        );

        /// @brief nullptr
        [[nodiscard]] static CellBehaviorPtr Null() noexcept;

        CellBehaviorPtr(
            CellBehaviorPtr const& right
        );

        constexpr CellBehaviorPtr(
            CellBehaviorPtr&& right
        ) noexcept;

        ~CellBehaviorPtr();

        CellBehaviorPtr& operator=(
            CellBehaviorPtr const& right
        );

        CellBehaviorPtr& operator=(
            CellBehaviorPtr&& right
        ) noexcept;

        /// @brief 生ポインターを取得
        [[nodiscard]] constexpr CellBehavior* operator->() const noexcept;
        [[nodiscard]] constexpr CellBehavior& operator*() const noexcept;

        /// @brief 生ポインターを取得
        [[nodiscard]] constexpr CellBehavior* Get() const noexcept;
    };

    [[nodiscard]] constexpr bool operator==(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr bool operator!=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr bool operator<(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr bool operator<=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr bool operator>(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr bool operator>=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;

    [[nodiscard]] constexpr ::std::strong_ordering operator<=>(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept;
}

namespace CellSim::Cells
{

    inline void CellBehaviorPtr::m_copyFrom(
        CellBehaviorPtr const& right
    )
    {
        if (right.m_ptr->IsReusable()) {
            m_ptr = right.m_ptr;
            m_ptr->AddOwner();
            return;
        }

        m_ptr = right.m_ptr->CreateClone();
    }

    inline void CellBehaviorPtr::m_delete() noexcept
    {
        m_ptr->RemoveOwner();

        if (m_ptr->HasOwner()) return;

        delete m_ptr;
    }

    inline CellBehaviorPtr CellBehaviorPtr::Null() noexcept
    {
        return CellBehaviorPtr(static_cast<CellBehavior*>(nullptr));
    }

    constexpr CellBehaviorPtr::CellBehaviorPtr(
        CellBehavior* ptr
    ) noexcept
        : m_ptr(ptr)
    {
    }

    inline CellBehaviorPtr::CellBehaviorPtr(
        CellBehaviorPtr const& right
    )
        : m_ptr(nullptr)
    {
        if (right.m_ptr == nullptr) return;
        m_copyFrom(right);
    }

    constexpr CellBehaviorPtr::CellBehaviorPtr(
        CellBehaviorPtr&& right
    ) noexcept
        : m_ptr(right.m_ptr)
    {
        right.m_ptr = nullptr;
    }

    inline CellBehaviorPtr::~CellBehaviorPtr()
    {
        if (m_ptr == nullptr) return;

        m_delete();
    }

    inline CellBehaviorPtr& CellBehaviorPtr::operator=(
        CellBehaviorPtr const& right
    )
    {
        if (m_ptr != nullptr) {
            m_delete();
            m_ptr = nullptr;
        }
        
        if (right.m_ptr != nullptr) m_copyFrom(right);

        return *this;
    }

    inline CellBehaviorPtr& CellBehaviorPtr::operator=(
        CellBehaviorPtr&& right
    ) noexcept
    {
        if (m_ptr != nullptr) m_delete();
        
        m_ptr = right.m_ptr;

        right.m_ptr = nullptr;

        return *this;
    }

    constexpr CellBehavior* CellBehaviorPtr::operator->() const noexcept
    {
        return m_ptr;
    }

    constexpr CellBehavior& CellBehaviorPtr::operator*() const noexcept
    {
        return *m_ptr;
    }

    constexpr bool operator==(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() == right.Get();
    }

    constexpr bool operator!=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() != right.Get();
    }

    constexpr bool operator<(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() < right.Get();
    }

    constexpr bool operator<=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() <= right.Get();
    }

    constexpr bool operator>(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() > right.Get();
    }

    constexpr bool operator>=(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() >= right.Get();
    }

    constexpr ::std::strong_ordering operator<=>(
        CellBehaviorPtr const& left,
        CellBehaviorPtr const& right
    ) noexcept
    {
        return left.Get() <=> right.Get();
    }
}

#endif //!CELLSIM_CELLS_CELLBEHAVIORPTR_HPP