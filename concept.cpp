template <class T>
concept HasElementType = requires (T object) { typename T: element_type; };
template <class T>
concept HasPointer = requires (T object) {typename T::pointer; };

template <class T> requires HasElementType<T> and not HasPointer<T>
std::add_pointer_t<typename T::element_type> pointer_type_of() noexcept;

template <class T> requires HasPointer<T>
typename T::pointer pointer_type_of () noexcept;

// Get type def out and use as storage value
template class<T> using_pointer_type_of_t = decltype(pointer_type_of<T>());

// Slightly reqular type, regular type needs copyable AND movable. 
template <class T>
concept SlightlyRegular =
    std::StrictTotallyOrderedWith<T, std::nullptr_t> and
    std::EqualityComparableWith<T, std::nullptr_t> and
    std::StrictTotallyOrdered<T> and
    std::EqualityComparable<T> and
    std::Constructible<T, impl::pointer_type_of_t<T>> and
    std::Movable<T>;
