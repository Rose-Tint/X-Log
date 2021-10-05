# X-Log
### Documentation
##### Everything is contained in the namespace 'xlog'

***

#### *namespace* fs

> If <filesystem\> or <experimental/filesystem\> depending on if one has already been included or most available if neither has been included

***

#### *template alias* ilist<T\> = std::initializer_list<T\>

***

#### *typedef* buffer_t   = std::streambuf*
#### *typedef* PreFilter  = void (*)(FormatInfo&)
#### *typedef* Filter     = bool (*)(const FormatInfo&)
#### *typedef* PostFilter = void (*)(FormatInfo&)

***

#### *class* Logger
* Constructors:
    * explicit Logger(std::string, Format)  
    * explicit Logger(std::string, buffer_t, Format)  
    * explicit Logger(std::string, fs::path, Format)  
    * explicit Logger(std::string, fs::recursive_directory_iterator, Format)  
    * explicit Logger(std::string, ilist<buffer_t\>, Format)  
    * explicit Logger(std::string, ilist<fs::path\>, Format)  
* Static Methods
    * void log_all(std::string, const int&, FormatInfo)
    * void add_ext(std::string)
    * void set_termination_stream(buffer_t)
    * void set_termination_msg(const std::string&)
* Non-Static Methods:
    * void rename(std::string rn)
    * void register_buffer(buffer_t)
    * void add_path(fs::path)
    * void add_handler(Handler)
    * void set_format(Format)
    * void log(const std::string&, const int&, FormatInfo)
* Deleted
    * Logger()
    * Logger(const Logger&)
    * Logger(Logger&&)
    * Logger& operator=(const Logger&)
    * Logger& operator=(Logger&&)

#### *class* Handler
* Constructors
    * explicit Handler(unsigned int, PreFilter = nullptr, Filter = def_filter, PostFilter = nullptr)
* Non-Static Methods
    * void set_prefilter(PreFilter)
    * void set_filter(Filter)
    * void set_postfilter(PostFilter)
    * void rm_prefilter()
    * void rm_filter()
    * void rm_postfilter()
    * const unsigned int& get_lvl() const
    * bool operator()(FormatInfo&) const

#### *struct* FormatInfo
* Members
    * std::string file
    * int line
    * std::unordered_map<std::string, std::string> args
    * int lvl
    * std::string msg
    * std::string lgr


