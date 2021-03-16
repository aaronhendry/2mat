/*
 * 2mat/element.cpp -- class implementation for element.hpp
 * 
 * Version: 1.0
 * Date created: 2021 March 16
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

#include "element.hpp"

namespace mat
{

    element::element(const std::string &name)
    :
        _name(name),
        _type(miDOUBLE),
        _data()
    {}

    element::element(const std::string &name, const std::string &str)
    :
        _name(name)
    {
        // MATLAB stores strings in a slightly strange way. In theory, it saves strings in UTF-8
        // format. However in practise, it converts the string to a series of UINT16_T values based
        // on the UTF-8 code points. This means that, for instance, the character 'ん' cannot be
        // saved in a "normal" MATLAB single-quote string. This is because the unicode code point
        // for the 'ん' character is 0xE38293, which is 3-bytes long. This means that when we 
        // receive a string intended to be written to a MATLAB file, we have to check to see if 
        // there are any 3- or 4-byte characters in the string. In practise, this means checking to
        // see if there are any bytes in the string with a value over 0xE0, which is the indicator
        // of a three-byte code point. This will catch both 3- and 4-byte code points.
        uint8_t max = *std::max_element(str.begin(),str.end());
        if (max > 0xE0)
        {
            // The easy work-around is to treat non-conforming strings as UTF-16 strings. This will
            // not work if we are saving to V6 format. This is actually not _strictly_ true, as 
            // MATLAB will still load these files, however it is likely that this would break on
            // older version of MATLAB.
            _type = miUTF16;
            std::memcpy(&_data[0],&str[0],str.size());
        } else {
            // Because a C++ string might have UTF code-points, for default MATLAB type strings we
            // can't do a simple memcpy to copy the data, as we need to convert _every_ character to
            // a UINT16_T value (even those that fit within a single byte).
            uint16_t *ptr = (uint16_t *)&_data[0];
            for (char c : str) *ptr++ = (uint16_t) c;
        }
    }

    element::element(const std::string &name, const std::u16string &str)
    :
        _name(name),
        _type(miUTF16)
    {
        // For explicitly UTF-16 strings, we can simply copy them as is -- the MATLAB UTF-16 type 
        // will deal with them properly.
        std::memcpy(&_data[0],&str[0],str.size());
    }
    

    element::element(const std::string &name, const std::u32string &str)
    :
        _name(name),
        _type(miUTF32)
    {
        // For explicitly UTF-32 strings, we can simply copy them as is -- the MATLAB UTF-32 type 
        // will deal with them properly.
        std::memcpy(&_data[0],&str[0],str.size());
    }

    const std::string &element::name() const
    {
        return _name;
    }

    datatype element::type() const
    {
        return _type;
    }

}