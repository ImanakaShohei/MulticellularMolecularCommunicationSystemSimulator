#ifndef CELLSIM_CONTAINERS_SPAN2_HPP
#define CELLSIM_CONTAINERS_SPAN2_HPP

#include "base.hpp"

#include <span>

namespace CellSim::Containers
{
    template <class T>
    class Span2 {
        private:

        size_t m_length1;
        size_t m_length2;

        T* m_ptr;

        public:

        constexpr Span2(size_t length1, size_t length2, T* ptr) noexcept;

        [[nodiscard]] constexpr ::std::span<T> operator[](size_t index) const noexcept;

        [[nodiscard]] constexpr T& At(size_t index1, size_t index2) const noexcept;

        [[nodiscard]] constexpr size_t Length() const noexcept;
    };
}

namespace CellSim::Containers
{
    template <class T>
    constexpr Span2<T>::Span2(size_t length1, size_t length2, T* ptr) noexcept
        : m_length1(length1)
        , m_length2(length2)
        , m_ptr(ptr)
    {
    }

    template <class T>
    constexpr ::std::span<T> Span2<T>::operator[](size_t index) const noexcept
    {
        return ::std::span<T>(m_ptr + m_length1 * index, m_length2);
    }

    template <class T>
    constexpr T& Span2<T>::At(size_t index1, size_t index2) const noexcept
    {
        return *(m_ptr + (index1 * m_length1 + index2));
    }

    template <class T>
    constexpr size_t Span2<T>::Length() const noexcept
    {
        return m_length1;
    }
}

#endif //!CELLSIM_CONTAINERS_SPAN2_HPP