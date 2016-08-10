/** ======================================================================== **\
	String library

| Description:
This library exports several useful string functions that are not included in
the PAWN string library. Besides, it adds a new syntax.

| Version:
2.0.38

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
#if defined _inc_string
	#undef _inc_string
#endif

#if defined _TDW_STRING_INC_
	#endinput
#endif

#define _TDW_STRING_INC_


#define O@tC: O@tCt:O@tCf:
#define O@T: O@tA:O@tF:O@tD:O@tC:O@tM:O@E:

#define O@tA:O@tF:O@tD:O@tC:O@tM:O@E:%1+%2$ strcat(%1,_:A@sM:A@sN:%2,)
#define A@sM:A@sN:%2[%3], %2,%3
#define A@sN:%2, %2

#define O@tF:O@tD:O@tC:O@tM:O@E:%1??%2$ strfind(_:F@pM:F@pN:%1,_:F@I:%2,)
#define F@pM:F@pN:%1[%3],%2, %1,%2,%3
#define F@pN:%1,%2, %1,%2,0
#define F@I: F@iV:F@iT:F@iF:
#define F@iV:F@iT:F@iF:%2!!%4, %2,%4,
#define F@iT:F@iF:%2!, %2,true,
#define F@iF:%2, %2,false,

#define O@tD:O@tC:O@tM:O@E:--%1$ strdel(_:D@pT0:D@pT1:D@pT2:D@pT3:D@pT4:%1,)
#define D@pT0:D@pT1:D@pT2:D@pT3:D@pT4:%1[%2,%3], %1,%2,%3
#define D@pT1:D@pT2:D@pT3:D@pT4:%1[,%3], %1,0,%3
#define D@pT2:D@pT3:D@pT4:%1[,], %1,0,sizeof %1
#define D@pT3:D@pT4:%1[%2,], %1,%2,sizeof %1
#define D@pT4:%1, %1,0,sizeof %1

#define O@tCt:O@tCf:O@tM:O@E:%1==%2$ (P@C:%1,%2$==0)
#define O@tCf:O@tM:O@E:%1!=%2$ (P@C:%1,%2$!=0)
#define P@C:%1,%2$ strcmp(%1,_:C@IP0:C@IP1:%2,)
#define C@IP0:C@IP1:%2!, C@I0:C@I1:%2,true,
#define C@IP1:%2, C@I0:C@I1:%2,false,
#define C@I0:C@I1:%2[%4],%3, %2,%3,%4
#define C@I1:%2,%3, %2,%3

#define O@E:%1=%2$ strcpy(%1,E@S0:E@S1:%2,)
#define E@S0:E@S1:%2[%3], %2,%3
#define E@S1:%2, %2

#define s<%1> (_:O@T:%1$)


#if !defined IsPackedString
	// Checks if a string is packed.
	// Other information: //www.compuphase.com/pawn/String_Manipulation.pdf
	#define IsPackedString(%0) ((%0)[0] > 255)
#endif


enum
	e_TDW_STRING
{
	LEFT,
	RIGHT,
	BOTH
};


stock
	strcount(const string[], const find[], bool:ignorecase = false, pos = 0,
		const string_size = sizeof string)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, count, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos + find_size)) != -1
	)
		count++;
	return count;
}


stock
	find_last(const string[], const find[], bool:ignorecase = false)
{
	new find_size = strlen(find), string_size = strlen(string),
		found_pos = string_size - find_size - 1;
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos - find_size)) != -1
	)
		return found_pos;
	return -1;
}


stock
	find_first(const string[], const find[], bool:ignorecase = false, pos = 0)
{
	if (pos >= string_size)
		return 0;
	new found_pos = pos, find_size = strlen(find);
	while ((found_pos = strfind(string, find, ignorecase,
		found_pos++)) != -1
	)
		return found_pos;
	return -1;
}


stock
	strreplace(string[], const find[], const replacement[],
		bool:ignorecase = false, bool:replace_all = false, const pos = 0,
		string_size = sizeof string)
{
	new found_pos = pos, current_string_len = strlen(string),
		find_size = strlen(find), replacement_len = strlen(replacement);
	while ((found_pos = strfind(string, find, ignorecase, found_pos)) != -1)
	{
		if ((current_string_len -= find_size) + replacement_len >= string_size)
			return 0;
		strdel(string, found_pos, found_pos + find_size);
		strins(string, replacement, found_pos, string_size);
		found_pos += replacement_len;
		current_string_len += replacement_len;
		if (_:replace_all == 0)
			break;
	}
	return 1;
}


stock
	memcmp(const string1[], const string2[], n)
{
	// Converts the value to bytes.
	#emit load.s.pri n // pri = n
	#emit shl.c.pri 2 // pri <<= 2
	#emit stor.s.pri n // n = pri
	// Addresses..
	#emit load.s.pri string1 // pri = string1
	#emit load.s.alt string2 // alt = string2
	// Compare the memory blocks
	#emit cmps n
	// Returns zero if the blocks are equal.
	#emit retn
	// For workaround the warning.
	return 0;
}


stock
	strexplode(dest[][], const string[], const delimiter[] = " ",
		bool:ignorecase = false, pos = 0, dest_size_major = sizeof dest,
		dest_size_minor = sizeof dest[], string_size = sizeof string)
{
	if (pos >= string_size)
		return -1;
	new current_index_major, found_pos = pos, last_pos,
		delimiter_len = strlen(delimiter);
	while (current_index_major != dest_size_major)
	{
		if ((found_pos = strfind(string, delimiter, ignorecase, found_pos)
			) == -1)
		{
			strmid(dest[current_index_major], string, last_pos, string_size,
				dest_size_minor);
			break;
		}
		strmid(dest[current_index_major], string, last_pos, found_pos,
			dest_size_minor);
		last_pos = (found_pos += delimiter_len);
		current_index_major++;
	}
	return last_pos;
}


stock
	strtrim(string[], const delimiter = ' ', e_TDW_STRING:algo = BOTH)
{
	new pos, bool:is_packed = IsPackedString(string);
	if (algo & LEFT)
	{
		new chr;
		if (is_packed)
		{
			while ((chr = string{pos++}) != '\0')
				if (chr != delimiter)
					break;
		}
		else
		{
			while ((chr = string[pos++]) != '\0')
				if (chr != delimiter)
					break;
		}
		strdel(string, 0, pos - 1);
	}
	if (algo & RIGHT)
	{
		new len = strlen(string);
		pos = len;
		if (is_packed)
		{
			while (pos-- != 0)
				if (string{pos} != delimiter)
					break;
		}
		else
		{
			while (pos-- != 0)
				if (string[pos] != delimiter)
					break;
		}
		strdel(string, pos + 1, len);
	}
	return 1;
}


stock
	strerase(string[], const start_pos, n, string_size = sizeof string)
{
	new bool:is_packed = IsPackedString(string);
	if (is_packed)
		// As default, i.e. if the string isn't packed, value of
		// string_size is capacity of the string + cell(for zero). But,
		// if it packed string, the value is only the string capacity,
		// so i do this:
		string_size++;
	if (_:(0 <= start_pos && start_pos < string_size) == 0)
		return 0;
	if (_:(0 < n && n <= string_size - start_pos) == 0)
		return 0;
	new i = start_pos, iterations = string_size - n;
	if (is_packed)
	{
		while (i < iterations)
			string{i} = string{i++ + n};
		while (i < string_size)
			string{i++} = '\0';
	}
	else
	{
		while (i < iterations)
			string[i] = string[i++ + n];
		while (i < string_size)
			string[i++] = '\0';
	}
	string_size -= n;
	return string_size;
}


// Returns the length of the new destination string.
stock
	strcpy(dest[], const string[], dest_size = sizeof dest)
{
	return
		(IsPackedString(dest) ? dest{0} = '\0' : dest[0] = '\0'),
		strcat(dest, string, dest_size);
}


stock
	IsEmptyString(const string[])
{
	return (IsPackedString(string) ? (string{0}) : (string[0])) == '\0';
}



static stock
	swap(&value1, &value2)
{
	// loads the values from the reference.
	#emit lref.s.pri value1 // pri = [value1]
	#emit lref.s.alt value2 // alt = [value2]
	#emit sref.s.alt value1 // [value1] = alt
	#emit sref.s.pri value2 // [value2] = pri
	return 0;
}


// Returns number of swapped elements.
stock
	strswap(string1[], string2[])
{
	new i,string1_size = strlen(string1), string2_size = strlen(string2),
		max_iters = (string1_size > string2_size) ? string2_size : string1_size;
	while(i != max_iters)
	{
		swap(string1[i], string2[i]);
		i++;
	}
	return i;
}


stock
	find_first_of(const string[], const chars[])
{
	new chr, i_string, j_chars, chars_len = strlen(chars);
	if (IsPackedString(string))
	{
		if (IsPackedString(chars))
		{
			while ((chr = string{i_string++}) != '\0')
			{
				do
				{
					if (chr != chars{j_chars})
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
		else
		{
			while ((chr = string{i_string++}) != '\0')
			{
				do
				{
					if (chr != chars[j_chars])
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
	}
	else
	{
		if (IsPackedString(chars))
		{
			while ((chr = string[i_string++]) != '\0')
			{
				do
				{
					if (chr != chars{j_chars})
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
		else
		{
			while ((chr = string[i_string++]) != '\0')
			{
				do
				{
					if (chr != chars[j_chars])
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
	}
	return 0;
}


stock
	find_first_not_of(const string[], const chars[])
{
	new chr, i_string, j_chars, chars_len = strlen(chars);
	if (IsPackedString(string))
	{
		if (IsPackedString(chars))
		{
			while ((chr = string{i_string++}) != '\0')
			{
				while (j_chars <= chars_len)
				{
					if (chars{j_chars++} == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
		else
		{
			while ((chr = string{i_string++}) != '\0')
			{
				while (j_chars <= chars_len)
				{
					if (chars[j_chars++] == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
	}
	else
	{
		if (IsPackedString(chars))
		{
			while ((chr = string[i_string++]) != '\0')
			{
				while (j_chars <= chars_len)
				{
					if (chars{j_chars++} == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
		else
		{
			while ((chr = string[i_string++]) != '\0')
			{
				while (j_chars <= chars_len)
				{
					if (chars[j_chars++] == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
	}
	return 0;
}


stock
	find_last_of(const string[], const chars[])
{
	new chr, i_string = strlen(string), j_chars, chars_len = strlen(chars);
	if (IsPackedString(string))
	{
		if (IsPackedString(chars))
		{
			while (i_string-- != 0)
			{
				do
				{
					if (string{i_string} != chars{j_chars})
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
		else
		{
			while (i_string-- != 0)
			{
				do
				{
					if (string{i_string} != chars[j_chars])
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
	}
	else
	{
		if (IsPackedString(chars))
		{
			while (i_string-- != 0)
			{
				do
				{
					if (string[i_string] != chars{j_chars})
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
		else
		{
			while (i_string-- != 0)
			{
				do
				{
					if (string[i_string] != chars[j_chars])
						continue;
					return i_string;
				}
				while (++j_chars <= chars_len);
				j_chars = 0;
			}
		}
	}
	return 0;
}


stock
	find_last_not_of(const string[], const chars[])
{
	new chr, i_string = strlen(string), j_chars, chars_len = strlen(chars);
	if (IsPackedString(string))
	{
		if (IsPackedString(chars))
		{
			while (i_string-- != 0)
			{
				chr = string{i_string};
				while (j_chars <= chars_len)
				{
					if (chars{j_chars++} == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
		else
		{
			while (i_string-- != 0)
			{
				chr = string{i_string};
				while (j_chars <= chars_len)
				{
					if (chars[j_chars++] == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
	}
	else
	{
		if (IsPackedString(chars))
		{
			while (i_string-- != 0)
			{
				chr = string[i_string];
				while (j_chars <= chars_len)
				{
					if (chars{j_chars++} == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
		else
		{
			while (i_string-- != 0)
			{
				chr = string[i_string];
				while (j_chars <= chars_len)
				{
					if (chars[j_chars++] == chr)
					{
						j_chars = 0;
						break;
					}
				}
				if (j_chars != 0)
					return i_string;
			}
		}
	}
	return 0;
}


stock
	strreverse(string[])
{
	new i, len = strlen(string), j = len - 1, chr;
	if (IsPackedString(string))
	{
		do
		{
			chr = string{i};
			string{i++} = string{j};
			string{j--} = chr;
		}
		while (i < j);
	}
	else
	{
		do
		{
			chr = string[i];
			string[i++] = string[j];
			string[j--] = chr;
		}
		while (i < j);
	}
	return 0;
}