// hsls_playground.hh
#pragma once
#include <cassert>
#include <cstdint>
#include <experimental/memory_resource>

#define NSLS_ASSERT(condition) assert(condition)

namespace nsls
{
using Byte = unsigned char;

using Boolean = bool;

using Integer8  = std::int8_t;
using Integer16 = std::int16_t;
using Integer32 = std::int32_t;
using Integer64 = std::int64_t;
using Integer   = std::int64_t;

using Natural8  = std::uint8_t;
using Natural16 = std::uint16_t;
using Natural32 = std::uint32_t;
using Natural64 = std::uint64_t;
using Natural   = std::uint64_t;

using Real32 = float;
using Real64 = double;
using Real   = double;

using Size = std::size_t;

namespace pmr = std::experimental::pmr;

template<typename T>
constexpr T declval = std::declval<T>();

template<typename T>
using Allocator = pmr::polymorphic_allocator<T>;

template<typename T>
using InitializerList = std::initializer_list<T>;

template<typename T>
using ReverseIterator = std::reverse_iterator<T>;

template <typename T>
        struct Range;

template<typename T>
struct Matrix;

template<typename T>
struct MatrixRef;

template<typename T>
struct MatrixIterator;

template<typename T>
struct Vector;

template<typename T>
struct VectorRef;

template<typename T>
struct VectorRefIterator;

template<typename T>
struct VectorRefIterator
{
    // TYPES
    using Element         = T;
    using ElementRef      = T&;
    using ElementConstRef = const T&;
    using ElementPtr      = T*;
    using ElementConstPtr = const T*;

    using Difference = Size;

    // CREATORS
    constexpr VectorRefIterator(ElementPtr begin, ElementPtr end) noexcept;

    constexpr VectorRefIterator(
            ElementPtr begin, ElementPtr end, Size stepSize) noexcept;

    constexpr VectorRefIterator(const VectorRefIterator& original) noexcept =
            default;

    constexpr VectorRefIterator(VectorRefIterator&& original) noexcept =
            default;

    ~VectorRefIterator() noexcept = default;

    // MANIPULATORS
    constexpr auto
    operator=(const VectorRefIterator& original) noexcept = default;

    constexpr auto operator=(VectorRefIterator&& original) noexcept = default;

    constexpr auto operator*() noexcept -> ElementRef;

    constexpr auto operator-> () noexcept -> ElementPtr;

    constexpr auto operator[](Size index) noexcept -> ElementRef;

    constexpr auto operator++() noexcept -> VectorRefIterator&;

    constexpr auto operator--() noexcept -> VectorRefIterator&;

    constexpr auto operator+=(Size offset) noexcept -> VectorRefIterator&;

    constexpr auto operator-=(Size offset) noexcept -> VectorRefIterator&;

    // ACCESSORS
    constexpr auto operator*() const noexcept -> ElementConstRef;

    constexpr auto operator-> () const noexcept -> ElementConstPtr;

    constexpr auto operator[](Size index) const noexcept -> ElementConstRef;

    // FREE OPERATORS
    template<typename U>
    friend constexpr auto
    operator+(const VectorRefIterator<U>& iter, Size offset)
            -> VectorRefIterator<U>;

    template<typename U>
    friend constexpr auto
    operator+(Size offset, const VectorRefIterator<U>& iter)
            -> VectorRefIterator<U>;

    template<typename U>
    friend constexpr auto
    operator-(const VectorRefIterator<U>& iter, Size offset)
            -> VectorRefIterator<U>;

    template<typename U>
    friend constexpr auto
    operator-(const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Difference;

    template<typename U>
    friend constexpr auto
    operator<(const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

    template<typename U>
    friend constexpr auto operator<=(
            const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator>(const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

    template<typename U>
    friend constexpr auto operator>=(
            const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

    template<typename U>
    friend constexpr auto operator==(
            const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

    template<typename U>
    friend constexpr auto operator!=(
            const VectorRefIterator<U>& lhs, const VectorRefIterator<U>& rhs)
            -> Boolean;

  public:
    // DATA
    ElementPtr d_begin;
    ElementPtr d_end;
    Size       d_stepSize;
};

template<typename T>
struct VectorRef
{
    // TYPES
    using Element         = T;
    using ElementRef      = T&;
    using ElementConstRef = const T&;
    using ElementPtr      = T*;
    using ElementConstPtr = const T*;

    using Iterator             = ElementPtr;
    using ConstIterator        = ElementConstPtr;
    using ReverseIterator      = nsls::ReverseIterator<Iterator>;
    using ConstReverseIterator = nsls::ReverseIterator<ConstIterator>;

    using InitializerList = nsls::InitializerList<Element>;

    // CREATORS
    constexpr VectorRef(ElementPtr first, ElementPtr last) noexcept;

    constexpr VectorRef(
            ElementPtr first, ElementPtr last, Size stepSize) noexcept;

    constexpr VectorRef(InitializerList initializer) noexcept;

    constexpr VectorRef(const VectorRef& original) noexcept = default;

    constexpr VectorRef(VectorRef&& original) noexcept = default;

    ~VectorRef() noexcept = default;

    // MANIPULATORS
    constexpr auto operator=(const VectorRef& original) noexcept
            -> VectorRef&  = default;

    constexpr auto operator=(VectorRef&& original) noexcept
            -> VectorRef&  = default;

    constexpr auto operator+=(const VectorRef& rhs) noexcept -> VectorRef&;

    constexpr auto operator-=(const VectorRef& rhs) noexcept -> VectorRef&;

    constexpr auto operator*=(ElementConstRef rhs) noexcept -> VectorRef&;

    constexpr auto operator/=(ElementConstRef rhs) noexcept -> VectorRef&;

    constexpr auto operator[](Size index) noexcept -> ElementRef;

    constexpr auto begin() noexcept -> Iterator;

    constexpr auto end() noexcept -> Iterator;

    constexpr auto rbegin() noexcept -> ReverseIterator;

    constexpr auto rend() noexcept -> ReverseIterator;

    constexpr auto size() noexcept -> Size;

    constexpr void swap(VectorRef& other);

    // ACCESSORS
    constexpr auto operator[](Size index) const noexcept -> ElementConstRef;

    auto operator-() const -> Vector<T>;

    auto operator+() const -> Vector<T>;

    constexpr auto begin() const noexcept -> ConstIterator;

    constexpr auto end() const noexcept -> ConstIterator;

    constexpr auto cbegin() const noexcept -> ConstIterator;

    constexpr auto cend() const noexcept -> ConstIterator;

    constexpr auto rbegin() const noexcept -> ConstReverseIterator;

    constexpr auto rend() const noexcept -> ConstReverseIterator;

    constexpr auto crbegin() const noexcept -> ConstReverseIterator;

    constexpr auto crend() const noexcept -> ConstReverseIterator;

    // FREE OPERATORS
    template<typename U>
    friend auto operator+(const VectorRef<U>& lhs, const VectorRef<U>& rhs)
            -> Vector<U>;

    template<typename U>
    friend auto operator-(const VectorRef<U>& lhs, const VectorRef<U>& rhs)
            -> Vector<U>;

    template<typename U>
    friend auto operator*(const U& lhs, const VectorRef<U>& rhs) -> Vector<U>;

    template<typename U>
    friend auto operator*(const VectorRef<U>& lhs, const U& rhs) -> Vector<U>;

    template<typename U>
    friend auto operator/(const U& lhs, const VectorRef<U>& rhs) -> Vector<U>;

    template<typename U>
    friend auto operator/(const VectorRef<U>& lhs, const U& rhs) -> Vector<U>;

    template<typename U>
    friend constexpr auto
    operator<(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator<=(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator>(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator>=(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator==(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

    template<typename U>
    friend constexpr auto
    operator!=(const VectorRef<U>& lhs, const VectorRef<U>& rhs) noexcept
            -> Boolean;

  private:
    // DATA
    ElementPtr d_begin;
    ElementPtr d_end;
    Size       d_stepSize;
};

template<typename T>
struct Vector
{
    // TYPES
    using Allocator = nsls::Allocator<T>;

    using Element         = T;
    using ElementRef      = T&;
    using ElementConstRef = const T&;
    using ElementPtr      = T*;
    using ElementConstPtr = const T*;

    using Iterator             = ElementPtr;
    using ConstIterator        = ElementConstPtr;
    using ReverseIterator      = nsls::ReverseIterator<Iterator>;
    using ConstReverseIterator = nsls::ReverseIterator<ConstIterator>;

    using VectorRef = nsls::VectorRef<T>;

    // CREATORS
    explicit Vector(const Allocator& allocator = Allocator());

    explicit Vector(Size count, const Allocator& allocator = Allocator());

    Vector(Size             count,
           ElementConstRef  value,
           const Allocator& allocator = Allocator());

    explicit Vector(
            InitializerList<Element> initializer,
            const Allocator&         allocator = Allocator());

    template<typename InputIter>
    Vector(InputIter        first,
           InputIter        last,
           const Allocator& allocator = Allocator());

    Vector(const Vector& original, const Allocator& allocator = Allocator());

    Vector(const VectorRef& originalRef,
           const Allocator& allocator = Allocator());

    Vector(Vector&& original, const Allocator& allocator = Allocator());

    Vector(VectorRef&& originalRef, const Allocator& allocator = Allocator());

    ~Vector() noexcept;

    // MANIPULATORS
    auto operator=(const Vector& original) -> Vector&;

    auto operator=(const VectorRef& originalRef) -> Vector&;

    auto operator=(Vector&& original) -> Vector&;

    auto operator=(VectorRef&& originalRef) -> Vector&;

    auto operator+=(const Vector& rhs) -> Vector&;

    auto operator-=(const Vector& rhs) -> Vector&;

    auto operator*=(ElementConstRef rhs) -> Vector&;

    auto operator/=(ElementConstRef rhs) -> Vector&;

    auto operator[](Size index) -> ElementRef;

    auto assign(Size count, ElementConstRef value) -> Vector&;

    template<typename InputIter>
    auto assign(InputIter first, InputIter last) -> Vector&;

    auto assign(InitializerList initializer) -> Vector&;

    auto begin() -> Iterator;

    auto end() -> Iterator;

    auto rbegin() -> ReverseIterator;

    auto rend() -> ReverseIterator;

    auto size() -> Size;

    void swap(Vector& other);

    void swap(VectorRef& otherRef);

    void reset();

    operator VectorRef();

    // ACCESSORS
    auto operator[](Size index) const -> ElementConstRef;

    auto operator-() const -> Vector;

    auto operator+() const -> Vector;

    auto begin() const -> ConstIterator;

    auto end() const -> ConstIterator;

    auto cbegin() const -> ConstIterator;

    auto cend() const -> ConstIterator;

    auto rbegin() const -> ConstReverseIterator;

    auto rend() const -> ConstReverseIterator;

    auto crbegin() const -> ConstReverseIterator;

    auto crend() const -> ConstReverseIterator;

    auto size() const -> Size;

    operator const VectorRef() const;

    // FREE OPERATORS
    template<typename U>
    friend auto operator+(const Vector<U>& lhs, const Vector<U>& rhs)
            -> Vector<U>;

    friend auto operator-(const Vector& lhs, const Vector& rhs) -> Vector;

    friend auto operator*(ElementConstRef lhs, const Vector& rhs) -> Vector;

    friend auto operator*(const Vector& lhs, ElementConstRef rhs) -> Vector;

    friend auto operator/(ElementConstRef lhs, const Vector& rhs) -> Vector;

    friend auto operator/(const Vector& lhs, ElementConstRef rhs) -> Vector;

    friend auto operator<(const Vector& lhs, const Vector& rhs) -> Boolean;

    friend auto operator<=(const Vector& lhs, const Vector& rhs) -> Boolean;

    friend auto operator>(const Vector& lhs, const Vector& rhs) -> Boolean;

    friend auto operator>=(const Vector& lhs, const Vector& rhs) -> Boolean;

    friend auto operator==(const Vector& lhs, const Vector& rhs) -> Boolean;

    friend auto operator!=(const Vector& lhs, const Vector& rhs) -> Boolean;

  private:
    // DATA
    Allocator  d_allocator;
    ElementPtr d_begin;
    ElementPtr d_end;
};

template<typename T>
struct Matrix
{
    // TYPES
    using Allocator = nsls::Allocator<T>;

    using Element         = T;
    using ElementRef      = T&;
    using ElementConstRef = const T&;
    using ElementPtr      = T*;
    using ElementConstPtr = const T*;

    using Vector         = nsls::Vector<T>;
    using VectorRef      = nsls::VectorRef<T>;
    using VectorConstRef = const nsls::VectorRef<T>;

    // CREATORS

    // MANIPULATORS

    // ACCESSORS

  public:
    // DATA
    Allocator  d_allocator;
    ElementPtr d_begin;
    ElementPtr d_end;
    Size       d_numRows;
};

template<typename T>
Vector<T>::Vector(const Allocator& allocator = Allocator());
: d_allocator(allocator)
, d_begin(nullptr)
, d_end(nullptr)
{
}

template<typename T>
Vector<T>::~Vector() noexcept
{
    if (d_begin == d_end) {
        return; // RETURN
    }

    for (ElementPtr it = d_begin; it != d_end; ++it) {
        d_allocator.destroy(it);
    }

    d_allocator.deallocate(d_begin, d_end - d_begin);
}
}
