/*
 * 2mat/types.hpp -- Type definitions used in MATLAB .MAT files as well as utility functions therein
 * 
 * Version: 1.0
 * Date created: 2021 March 12
 * Copyright (c) 2021 Aaron Hendry
 * 
 * This program is free software: you can redistribute it and/or modify it under the terms of the
 * GNU Lesser General Public License as published by the Free Software Foundation, either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with this program.
 * If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TOO_MAT_TYPES_H
#define TOO_MAT_TYPES_H

#include <cstdint>
#include <string>
#include <typeindex>
#include <unordered_map>

namespace mat
{

    /*
     * mat::datatype
     * 
     * enumerated list of the MATLAB file versions
     * 
     */
    enum file_version
    {
        V6 = 6,
        V7 = 7,
        V7_3 = 73
    };

    typedef unsigned long long dim_t;

	/*
	 * mat::datatype
	 * 
	 * enumerated list of MATLAB datatypes used in .mat binary files.
	 * 
	 */
	enum datatype
	{
		miUNKNOWN=0,
		miINT8 = 1,
		miUINT8 = 2,
		miINT16 = 3,
		miUINT16 = 4,
		miINT32 = 5,
		miUINT32 = 6,
		miSINGLE = 7,
		miDOUBLE = 9,
		miINT64 = 12,
		miUINT64 = 13,
		miMATRIX = 14,
		miCOMPRESSED = 15,
		miUTF8 = 16,
		miUTF16 = 17,
		miUTF32 = 18
		// TODO: Add missing datatypes
	};

	/*
	 * uint32_t mat::datasize(mat::datatype)
	 * 
	 * Returns the size of a variable of the specified MATLAB datatype, in bits.
	 * 
	 * EXAMPLE:
	 *
	 * uint32_t size = datasize(miDOUBLE); // returns 64
	 * 
	 * INPUT:
	 * 	dt	(uint32_t)	the datatype to get the size of
	 * RETURNS:
	 * 	the size of the datatype in bits
	 */
	inline uint32_t datasize(datatype dt)
	{
		switch(dt)
		{
			case miINT8:
			case miUINT8:
			case miUTF8:
				return 8;
			case miINT16:
			case miUINT16:
			case miUTF16:
				return 16;
			case miINT32:
			case miUINT32:
			case miUTF32:
			case miSINGLE:
				return 32;
			case miINT64:
			case miUINT64:
			case miDOUBLE:
				return 64;
			case miUNKNOWN:
			case miMATRIX:
			case miCOMPRESSED:
			default:
				return 0;
		}
	}
		
	/*
	 * mat::datatype
	 * 
	 * enumerated list of MATLAB class types used in .mat binary files. There are two "mystery" 
	 * types that appear to be used in .mat binary files, which, based on searches on the internet,
	 * people seem to refer to as "FUNCTION" and "OPAQUE" classes. I've borrowed this terminology
	 * until I can look into this more and better understand what is actually going on.
	 * 
	 */
	enum array_class
	{
		mxUNKNOWN_CLASS=0,
		mxCELL_CLASS = 1,
		mxSTRUCT_CLASS = 2,
		mxOBJECT_CLASS = 3,
		mxCHAR_CLASS = 4,
		mxSPARSE_CLASS = 5,
		mxDOUBLE_CLASS = 6,
		mxSINGLE_CLASS = 7,
		mxINT8_CLASS = 8,
		mxUINT8_CLASS = 9,
		mxINT16_CLASS = 10,
		mxUINT16_CLASS = 11,
		mxINT32_CLASS = 12,
		mxUINT32_CLASS = 13,
		mxINT64_CLASS = 14,
		mxUINT64_CLASS = 15,
		mxFUNCTION_CLASS = 16,
		mxOPAQUE_CLASS = 17
		// TODO: Sort out FUNCTION and OPAQUE classes
	};

    // Map from type to datatype
    static std::unordered_map<std::type_index,datatype> type2datatype
    {
        {std::type_index(typeid(int8_t)), miINT8},
        {std::type_index(typeid(uint8_t)), miUINT8},
        {std::type_index(typeid(int16_t)), miINT16},
        {std::type_index(typeid(uint16_t)), miUINT16},
        {std::type_index(typeid(int32_t)), miINT32},
        {std::type_index(typeid(uint32_t)), miUINT32},
        {std::type_index(typeid(float)), miSINGLE},
        {std::type_index(typeid(double)), miDOUBLE},
        {std::type_index(typeid(int64_t)), miINT64},
        {std::type_index(typeid(uint64_t)), miUINT64},
        {std::type_index(typeid(char)), miINT8},
        {std::type_index(typeid(char16_t)), miUTF16},
        {std::type_index(typeid(char32_t)), miUTF32},
        {std::type_index(typeid(std::string)), miUINT8}
    };

    // Map from type to datatype
    static std::unordered_map<std::type_index,array_class> type2class
    {
        {std::type_index(typeid(int8_t)), mxINT8_CLASS},
        {std::type_index(typeid(uint8_t)), mxUINT8_CLASS},
        {std::type_index(typeid(int16_t)), mxINT16_CLASS},
        {std::type_index(typeid(uint16_t)), mxUINT16_CLASS},
        {std::type_index(typeid(int32_t)), mxINT32_CLASS},
        {std::type_index(typeid(uint32_t)), mxUINT32_CLASS},
        {std::type_index(typeid(float)), mxSINGLE_CLASS},
        {std::type_index(typeid(double)), mxDOUBLE_CLASS},
        {std::type_index(typeid(int64_t)), mxINT64_CLASS},
        {std::type_index(typeid(uint64_t)), mxUINT64_CLASS},
        {std::type_index(typeid(char)), mxCHAR_CLASS},
        {std::type_index(typeid(std::string)), mxCHAR_CLASS},
        {std::type_index(typeid(std::wstring)), mxCHAR_CLASS}
    };

	/*
	 * mat::datatype mat::get_datatype<T>()
	 * 
	 * Template function to return the MATLAB datatype of a variable with the templated type
	 * 
	 * TEMPLATE:
	 * 	The type of the variable to get the datatype for
	 * RETURNS:
	 * 	The datatype of the template type
	 */
	template <typename T>
	datatype get_datatype(T)
    {
        return type2datatype[std::type_index(typeid(T))];
    }

	/*
	 * mat::datatype mat::get_datatype<T>()
	 * 
	 * Template function to return the MATLAB datatype of a variable with the templated type
	 * 
	 * TEMPLATE:
	 * 	The type of the variable to get the datatype for
	 * RETURNS:
	 * 	The datatype of the template type
	 */
	template <typename T>
	array_class get_class(T)
    {
        return type2class[std::type_index(typeid(T))];
    }
}

#endif