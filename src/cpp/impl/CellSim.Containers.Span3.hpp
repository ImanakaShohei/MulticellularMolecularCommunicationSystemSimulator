#ifndef CELLSIM_CONTAINERS_SPAN3_HPP
#define CELLSIM_CONTAINERS_SPAN3_HPP

#include "base.hpp"
#include "CellSim.Containers.Span2.hpp"

namespace CellSim::Containers
{
    template <class T>
    class Span3 {
        private:

        size_t m_lengthX;
        size_t m_lengthY;
        size_t m_lengthZ;

        T* m_ptr;

        public:

        Span3() = default;
        constexpr Span3(size_t lengthX, size_t lengthY, size_t lengthZ, T* ptr) noexcept;

        [[nodiscard]] constexpr Span2<T> operator[](size_t index) const noexcept;

        [[nodiscard]] constexpr T& At(size_t index1, size_t index2, size_t index3) const noexcept;

        [[nodiscard]] constexpr size_t Length() const noexcept;
        [[nodiscard]] constexpr size_t LengthX() const noexcept;
        [[nodiscard]] constexpr size_t LengthY() const noexcept;
        [[nodiscard]] constexpr size_t LengthZ() const noexcept;
    };
}

namespace CellSim::Containers
{
    template <class T>
    constexpr Span3<T>::Span3(size_t lengthX, size_t lengthY, size_t lengthZ, T* ptr) noexcept
        : m_lengthX(lengthX)
        , m_lengthY(lengthY)
        , m_lengthZ(lengthZ)
        , m_ptr(ptr)
    {
    }

    template <class T>
    constexpr Span2<T> Span3<T>::operator[](size_t index) const noexcept
    {
        return Span2(m_lengthY, m_lengthZ, m_ptr);
    }

    template <class T>
    constexpr T& Span3<T>::At(size_t index1, size_t index2, size_t index3) const noexcept
    {
        return *(m_ptr + ((index1 * m_lengthX + index2) * m_lengthY + index3));
    }

    template <class T>
    constexpr size_t Span3<T>::Length() const noexcept
    {
        return m_lengthX * m_lengthY * m_lengthZ;
    }

    template <class T>
    constexpr size_t Span3<T>::LengthX() const noexcept
    {
        return m_lengthX;
    }

    template <class T>
    constexpr size_t Span3<T>::LengthY() const noexcept
    {
        return m_lengthY;
    }

    template <class T>
    constexpr size_t Span3<T>::LengthZ() const noexcept
    {
        return m_lengthZ;
    }
}

#endif //!CELLSIM_CONTAINERS_SPAN3_HPP