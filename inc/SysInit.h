#ifndef SYSINIT_H
#define SYSINIT_H

#ifdef __cplusplus
extern "C"
{
#endif

void    SysInit( void );

#ifndef NDEBUG
int	SysInitTest( void );
#endif	// NDEBUG

#ifdef __cplusplus
}
#endif

#endif	// SYSINIT_H
