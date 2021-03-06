/** ======================================================================== **\
	Iterator

| License:
Copyright (c) 2016 Double V

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1.	The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgement in the product documentation would be
	appreciated but is not required.
2.	Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
3.	This notice may not be removed or altered from any source distribution.
\** ======================================================================== **/


// I remove this constant because the compiler automatically generates it.
// github.com/Zeex/pawn/issues/107
#if defined _inc_iterator
	#undef _inc_iterator
#endif

#if defined _TDW_S_ITERATOR_INC_
	#endinput
#endif

#define _TDW_S_ITERATOR_INC_


#define ITER_NEW: ITER_0:ITER_1:
#define ITER_0:ITER_1:new%1$ %1
#define ITER_1:%1$ %1

#define foreach_string%0(%1:%2)\
	for(new %1=%2[0],%2@Iter=0;_:ITER_NEW:%1$!='\0';\
		_:ITER_NEW:%1$=%2[++%2@Iter])
