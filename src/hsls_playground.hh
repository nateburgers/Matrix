// hsls_playground.hh
#pragma once
#include <cassert>
#include <cstdint>
#include <memory_resource>

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

template<typename T>
constexpr T declval = std::declval<T>();

template<typename T>
using Allocator = std::pmr::polymorphic_allocator<T>;

template<typename T>
using InitializerList = std::initializer_list<T>;

template<typename T>
using ReverseIterator = std::reverse_iterator<T>;

template<typename T>
struct GenericVector;

using IntegerVector = GenericVector<Integer>;
using NaturalVector = GenericVector<Natural>;
using RealVector    = GenericVector<Real>;
using Vector        = GenericVector<Real>;

template<typename T>
struct GenericVectorRef;

using IntegerVectorRef = GenericVectorRef<Integer>;
using NaturalVectorRef = GenericVectorRef<Natural>;
using RealVectorRef    = GenericVectorRef<Real>;
using VectorRef        = GenericVectorRef<Real>;

template<typename T>
struct GenericVectorRefIterator;

template<typename T>
struct GenericVectorRef
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

    using GenericVectorRef = nsls::GenericVectorRef<T>;

    // CREATORS
    GenericVectorRef(ElementPtr* first, ElementPtr* last);

    GenericVectorRef(ElementPtr* first, ElementPtr* last, Size stepSize);

    template<Size size>
    GenericVectorRef(Element (&elements)[size]);

    template<Size size>
    GenericVectorRef(Element(&&elements)[size]) = delete;

    GenericVectorRef(const GenericVectorRef& original);

    GenericVectorRef(GenericVectorRef&& original);

    ~GenericVectorRef() noexcept = default;

    // MANIPULATORS
    auto operator=(const GenericVectorRef& original) -> GenericVectorRef&;

    auto operator=(GenericVectorRef&& original) -> GenericVectorRef&;

    auto operator+=(const GenericVectorRef& rhs) -> GenericVectorRef&;

    auto operator-=(const GenericVectorRef& rhs) -> GenericVectorRef&;

    auto operator*=(ElementConstRef rhs) -> GenericVectorRef&;

    auto operator/=(ElementConstRef rhs) -> GenericVectorRef&;

    auto operator[](Size index) -> ElementRef;

    auto begin() -> Iterator { return *d_begin_p; }

    auto end() -> Iterator { return *d_end_p; }

    auto rbegin() -> ReverseIterator { return ReverseIterator(*d_begin_p); }

    auto rend() -> ReverseIterator { return ReverseIterator(*d_end_p); }

    auto size() -> Size { return *d_end_p - *d_begin_p; }

    void swap(GenericVectorRef& other);

    void reset();

    // ACCESSORS
    auto operator[](Size index) const -> ElementConstRef;

    auto operator-() const -> GenericVector<T>;

    auto operator+() const -> GenericVector<T>;

    auto begin() const -> ConstIterator;

    auto end() const -> ConstIterator;

    auto cbegin() const -> ConstIterator;

    auto cend() const -> ConstIterator;

    auto rbegin() const -> ConstReverseIterator;

    auto rend() const -> ConstReverseIterator;

    auto crbegin() const -> ConstReverseIterator;

    auto crend() const -> ConstReverseIterator;

    // FREE OPERATORS
    friend auto
    operator+(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> GenericVector;

    friend auto
    operator-(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> GenericVector;

    friend auto operator*(ElementConstRef lhs, const GenericVectorRef& rhs)
            -> GenericVector;

    friend auto operator*(const GenericVectorRef& lhs, ElementConstRef rhs)
            -> GenericVector;

    friend auto operator/(ElementConstRef lhs, const GenericVectorRef& rhs)
            -> GenericVector;

    friend auto operator/(const GenericVectorRef& lhs, ElementConstRef rhs)
            -> GenericVector;

    friend auto
    operator<(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

    friend auto
    operator<=(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

    friend auto
    operator>(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

    friend auto
    operator>=(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

    friend auto
    operator==(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

    friend auto
    operator!=(const GenericVectorRef& lhs, const GenericVectorRef& rhs)
            -> Boolean;

  private:
    // DATA
    ElementPtr* d_begin_p;
    ElementPtr* d_end_p;
    Size        d_stepSize;
};

template<typename T>
struct GenericVector
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

    using GenericVectorRef = nsls::GenericVectorRef<T>;

    // CREATORS
    explicit GenericVector(const Allocator& allocator = Allocator());

    explicit GenericVector(
            Size count, const Allocator& allocator = Allocator());

    GenericVector(
            Size             count,
            ElementConstRef  value,
            const Allocator& allocator = Allocator());

    explicit GenericVector(
            InitializerList<Element> initializer,
            const Allocator&         allocator = Allocator());

    template<typename InputIter>
    GenericVector(
            InputIter        first,
            InputIter        last,
            const Allocator& allocator = Allocator());

    GenericVector(
            const GenericVector& original,
            const Allocator&     allocator = Allocator());

    GenericVector(
            const GenericVectorRef& originalRef,
            const Allocator&        allocator = Allocator());

    GenericVector(
            GenericVector&&  original,
            const Allocator& allocator = Allocator());

    GenericVector(
            GenericVectorRef&& originalRef,
            const Allocator&   allocator = Allocator());

    ~GenericVector() noexcept;

    // MANIPULATORS
    auto operator=(const GenericVector& original) -> GenericVector&;

    auto operator=(const GenericVectorRef& originalRef) -> GenericVector&;

    auto operator=(GenericVector&& original) -> GenericVector&;

    auto operator=(GenericVectorRef&& originalRef) -> GenericVector&;

    auto operator+=(const GenericVector& rhs) -> GenericVector&;

    auto operator-=(const GenericVector& rhs) -> GenericVector&;

    auto operator*=(ElementConstRef rhs) -> GenericVector&;

    auto operator/=(ElementConstRef rhs) -> GenericVector&;

    auto operator[](Size index) -> ElementRef;

    auto assign(Size count, ElementConstRef value) -> GenericVector&;

    template<typename InputIter>
    auto assign(InputIter first, InputIter last) -> GenericVector&;

    auto assign(InitializerList initializer) -> GenericVector&;

    auto begin() -> Iterator;

    auto end() -> Iterator;

    auto rbegin() -> ReverseIterator;

    auto rend() -> ReverseIterator;

    auto size() -> Size;

    void swap(GenericVector& other);

    void swap(GenericVectorRef& otherRef);

    void reset();

    operator GenericVectorRef();

    // ACCESSORS
    auto operator[](Size index) const -> ElementConstRef;

    auto operator-() const -> GenericVector;

    auto operator+() const -> GenericVector;

    auto begin() const -> ConstIterator;

    auto end() const -> ConstIterator;

    auto cbegin() const -> ConstIterator;

    auto cend() const -> ConstIterator;

    auto rbegin() const -> ConstReverseIterator;

    auto rend() const -> ConstReverseIterator;

    auto crbegin() const -> ConstReverseIterator;

    auto crend() const -> ConstReverseIterator;

    auto size() const -> Size;

    operator const GenericVectorRef() const;

    // FREE OPERATORS
    friend auto operator+(const GenericVector& lhs, const GenericVector& rhs)
            -> GenericVector;

    friend auto operator-(const GenericVector& lhs, const GenericVector& rhs)
            -> GenericVector;

    friend auto operator*(ElementConstRef lhs, const GenericVector& rhs)
            -> GenericVector;

    friend auto operator*(const GenericVector& lhs, ElementConstRef rhs)
            -> GenericVector;

    friend auto operator/(ElementConstRef lhs, const GenericVector& rhs)
            -> GenericVector;

    friend auto operator/(const GenericVector& lhs, ElementConstRef rhs)
            -> GenericVector;

    friend auto operator<(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

    friend auto operator<=(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

    friend auto operator>(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

    friend auto operator>=(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

    friend auto operator==(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

    friend auto operator!=(const GenericVector& lhs, const GenericVector& rhs)
            -> Boolean;

  private:
    // DATA
    Allocator  d_allocator;
    ElementPtr d_begin;
    ElementPtr d_end;
};

template<typename T>
GenericVector<T>::GenericVector(const Allocator& allocator = Allocator());
: d_allocator(allocator)
, d_begin(nullptr)
, d_end(nullptr)
{
}

template<typename T>
GenericVector<T>::~GenericVector()
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
