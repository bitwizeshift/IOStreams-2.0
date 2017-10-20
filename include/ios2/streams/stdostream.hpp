#ifndef IOSTREAM_STDOSTREAM_HPP
#define IOSTREAM_STDOSTREAM_HPP

#include <cstdio> // std::printf

namespace ios2 {

  /////////////////////////////////////////////////////////////////////////////
  /// \brief An unbuffered ostream that prints using standard C output.
  ///
  /// This ostream is an unbuffered ostream
  ///
  /// \satisfies{OStream}
  /////////////////////////////////////////////////////////////////////////////
  class stdostream
  {
    //-------------------------------------------------------------------------
    // Constructors / Destructor
    //-------------------------------------------------------------------------
  public:

    stdostream() = default;
    ~stdostream() = default;

    //-------------------------------------------------------------------------
    // Unformatted Output
    //-------------------------------------------------------------------------
  public:

    void put( char c );

    void write( const char* p, std::ptrdiff_t s );

    //-------------------------------------------------------------------------
    // Formatted Output
    //-------------------------------------------------------------------------
  public:

    stdostream& operator<<( unsigned short rhs );
    stdostream& operator<<( signed short rhs );
    stdostream& operator<<( unsigned int rhs );
    stdostream& operator<<( signed int rhs );
    stdostream& operator<<( unsigned long rhs );
    stdostream& operator<<( signed long rhs );
    stdostream& operator<<( unsigned long long rhs );
    stdostream& operator<<( signed long long rhs );
    stdostream& operator<<( float rhs );
    stdostream& operator<<( double rhs );
    stdostream& operator<<( const void* rhs );
    stdostream& operator<<( std::nullptr_t );

    //-------------------------------------------------------------------------
    // Miscellaneous
    //-------------------------------------------------------------------------
  public:

    /// \brief No-op
    ///
    /// This ostream is not buffered, and thus does not require any form of
    /// flushing logic
    void flush();
  };
} // namespace ios2

//-----------------------------------------------------------------------------
// Unformatted Output
//-----------------------------------------------------------------------------

inline void ios2::stdostream::put( char c )
{
  std::printf("%c",c);
}

inline void ios2::stdostream::write( const char* p, std::ptrdiff_t s )
{
  std::printf("%.*s",static_cast<int>(s),p);
}

//-----------------------------------------------------------------------------
// Formatted Output
//-----------------------------------------------------------------------------

inline ios2::stdostream& ios2::stdostream::operator<<( unsigned short rhs )
{
  std::printf("%hu",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( signed short rhs )
{
  std::printf("%hd",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( unsigned int rhs )
{
  std::printf("%u",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( signed int rhs )
{
  std::printf("%d",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( unsigned long rhs )
{
  std::printf("%lu",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( signed long rhs )
{
  std::printf("%ld",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( unsigned long long rhs )
{
  std::printf("%llu",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( signed long long rhs )
{
  std::printf("%lld",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( float rhs )
{
  std::printf("%f",static_cast<double>(rhs));
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( double rhs )
{
  std::printf("%f",rhs);
  return (*this);
}

inline ios2::stdostream& ios2::stdostream::operator<<( const void* rhs )
{
  std::printf("%p", rhs);
  return (*this);
}

inline ios2::stdostream &ios2::stdostream::operator<<(std::nullptr_t)
{
  std::printf("%s","null");
  return (*this);
}

//-----------------------------------------------------------------------------
// Miscellaneous
//-----------------------------------------------------------------------------

inline void ios2::stdostream::flush()
{
  // no-op
}

#endif //IOSTREAM_STDOSTREAM_HPP
