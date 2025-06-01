#ifndef CELLSIM_CELLS_CELLBEHAVIORPTR_HPP
#define CELLSIM_CELLS_CELLBEHAVIORPTR_HPP

#include "base.hpp"
#include "CellSim.Cells.CellBehavior.hpp"

namespace CellSim::Cells
{
    /// @brief CellBehaviorポインタ
    /// @attention このクラスはスレッドセーフではありません
    class CellBehaviorPtr {
        private:

        using DeleterType = void(*)(CellBehavior*);

        template <class TBehavior> requires ::std::derived_from<TBehavior, CellBehavior>
        static void DefaultDeleter(CellBehavior* p) noexcept;

        template <class TBehavior> requires ::std::derived_from<TBehavior, CellBehavior>
        CellBehaviorPtr(TBehavior* ptr);

        CellBehavior* m_ptr;
        DeleterType m_deleter;

        void m_copyFrom(CellBehaviorPtr const& right);
        void m_delete() noexcept;

        public:

        [[nodiscard]] static CellBehaviorPtr FromType(CellBehaviorType type);

        CellBehaviorPtr(CellBehaviorPtr const& right);
        constexpr CellBehaviorPtr(CellBehaviorPtr&& right) noexcept;

        ~CellBehaviorPtr();

        CellBehaviorPtr& operator=(CellBehaviorPtr const& right);
        CellBehaviorPtr& operator=(CellBehaviorPtr&& right) noexcept;

        [[nodiscard]] constexpr CellBehavior* operator->() const noexcept;
        [[nodiscard]] constexpr CellBehavior& operator*() const noexcept;
    };
}

namespace CellSim::Cells
{
    template <class TBehavior> requires ::std::derived_from<TBehavior, CellBehavior>
    void CellBehaviorPtr::DefaultDeleter(CellBehavior* p) noexcept
    {
        delete static_cast<TBehavior*>(p);
    }

    void CellBehaviorPtr::m_copyFrom(CellBehaviorPtr const& right)
    {
        if (right.m_ptr->HasState()) {
            m_ptr = right.m_ptr;
            m_ptr->AddOwner();
            return;
        }

        m_ptr = right.m_ptr->CreateClone();
    }

    void CellBehaviorPtr::m_delete() noexcept
    {
        m_ptr->RemoveOwner();

        if (m_ptr->HasOwner()) return;

        m_deleter(m_ptr);
    }

    template <class TBehavior> requires ::std::derived_from<TBehavior, CellBehavior>
    CellBehaviorPtr::CellBehaviorPtr(TBehavior* ptr)
        : m_ptr(ptr)
        , m_deleter(DefaultDeleter<TBehavior>)
    {
    }

    inline CellBehaviorPtr::CellBehaviorPtr(CellBehaviorPtr const& right)
        : m_ptr()
        , m_deleter(right.m_deleter)
    {
        m_copyFrom(right);
    }

    constexpr CellBehaviorPtr::CellBehaviorPtr(CellBehaviorPtr&& right) noexcept
        : m_ptr(right.m_ptr)
        , m_deleter(right.m_deleter)
    {
        right.m_ptr = nullptr;
    }

    inline CellBehaviorPtr::~CellBehaviorPtr()
    {
        if (m_ptr == nullptr) return;

        m_delete();
    }

    inline CellBehaviorPtr& CellBehaviorPtr::operator=(CellBehaviorPtr const& right)
    {
        m_delete();
        m_copyFrom(right);
        m_deleter = right.m_deleter;

        return *this;
    }

    inline CellBehaviorPtr& CellBehaviorPtr::operator=(CellBehaviorPtr&& right)
    {
        m_delete();
        
        m_ptr = right.m_ptr;
        m_deleter = right.m_deleter;

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
}

#endif //!CELLSIM_CELLS_CELLBEHAVIORPTR_HPP