#ifndef FTEXTSTREAM_H
#define FTEXTSTREAM_H

#include <stdio.h>

#include <qiodevice.h>
#include <qgstring.h>

/** @brief Simplified and optimized version of QTextStream */
class FTextStream
{
  public:
    FTextStream();
    FTextStream( QIODevice * );
    FTextStream( QGString * );
    FTextStream( FILE * );
    virtual ~FTextStream();

    QIODevice	*device() const;
    void	 setDevice( QIODevice * );
    void	 unsetDevice();

    FTextStream &operator<<( char );
    FTextStream &operator<<( const char *);
    FTextStream &operator<<( const QCString & );
    FTextStream &operator<<( signed short );
    FTextStream &operator<<( unsigned short );
    FTextStream &operator<<( signed int );
    FTextStream &operator<<( unsigned int );
    FTextStream &operator<<( signed long );
    FTextStream &operator<<( unsigned long );
    FTextStream &operator<<( float );
    FTextStream &operator<<( double );

  private:
    QIODevice *m_dev;
    bool m_owndev;
    FTextStream &output_int( ulong n, bool neg );

  private:	// Disabled copy constructor and operator=
#if defined(Q_DISABLE_COPY)
    FTextStream( const FTextStream & );
    FTextStream &operator=( const FTextStream & );
#endif
};

inline FTextStream &FTextStream::operator<<( char c)
{
  if (m_dev) m_dev->putch(c);
  return *this;
}

inline FTextStream &FTextStream::operator<<( const char* s)
{
  uint len = qstrlen( s );
  if (m_dev) m_dev->writeBlock( s, len );
  return *this;
}

inline FTextStream &FTextStream::operator<<( const QCString &s)
{
  if (m_dev) m_dev->writeBlock( s, s.length() );
  return *this;
}

typedef FTextStream & (*FTSFUNC)(FTextStream &);// manipulator function

inline FTextStream &operator<<( FTextStream &s, FTSFUNC f )
{ return (*f)( s ); }

inline FTextStream &endl( FTextStream & s)
{
  return s << '\n';
}

#endif // FTEXTSTREAM_H
