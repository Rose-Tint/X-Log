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

    struct std::iterator_traits<CharOutputIter>
    {
        typedef char_t value_type;
        typedef std::ptrdiff_t difference_type;
        typedef char_t* pointer;
        typedef char_t& reference;
        typedef std::output_iterator_tag iterator_category;
    };
}

#endif