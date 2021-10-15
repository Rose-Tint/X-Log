#ifndef X_LOG_FORMAT_CHAROUTPUTITER_HPP
#define X_LOG_FORMAT_CHAROUTPUTITER_HPP


namespace xlog
{
    class CharOutputIter final
    {
        char_t* c;
      public:
        CharOutputIter(const CharOutputIter&);
        CharOutputIter& operator=(const CharOutputIter&);
        ~CharOutputIter();

        void swap(CharOutputIter&);
        char_t operator*();
        CharOutputIter& operator++();
    };

    template<>
    struct std::iterator_traits<CharOutputIter>
    {
        typedef char_t value_type;
        typedef std::ptrdiff_t difference_type;
        typedef value_type* pointer;
        typedef value_type& reference;
        typedef std::output_iterator_tag iterator_category;
    };
}

#endif