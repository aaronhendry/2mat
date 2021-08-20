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

    element::element(std::string name)
    :
        _type(miDOUBLE),
        _name(std::move(name)),
        _data()
    {}

    element::element(std::string name, const std::string &str)
    :
        _type(miUTF8),
        _name(std::move(name))
    {

        // MATLAB stores strings in a slightly strange way. In theory, it saves strings in UTF-8
        // format. However in practise, it converts the string to a series of UINT16_T values based
        // on the UTF-8 code points. This means that, for instance, the character 'ん' cannot be
        // saved in a "normal" MATLAB single-quote string. This is because the unicode code point
        // for the 'ん' character is 0xE38293, which is 3-bytes long.
        
        // In practise, it is simply easier to treat *all* strings as UTF-8. MATLAB has no trouble
        // reading these on any version newer than 2004, and it greatly simplifies this process.
        // I have made the decision to not support 17-year old version of MATLAB for my own sanity.
        _data = std::make_shared<std::vector<unsigned char>>(str.size());
        std::memcpy(ptr(),&str[0],str.size());
    }

    element::element(std::string name, const std::u16string &str)
    :
        _type(miUTF16),
        _name(std::move(name))
    {
        _data = std::make_shared<std::vector<unsigned char>>(str.size()*2);
        // For explicitly UTF-16 strings, we can simply copy them as is -- the MATLAB UTF-16 type 
        // will deal with them properly.
        std::memcpy(ptr(),&str[0],str.size());
    }
    

    element::element(std::string name, const std::u32string &str)
    :
        _type(miUTF32),
        _name(std::move(name))
    {
        _data = std::make_shared<std::vector<unsigned char>>(str.size()*4);
        // For explicitly UTF-32 strings, we can simply copy them as is -- the MATLAB UTF-32 type 
        // will deal with them properly.
        std::memcpy(ptr(),&str[0],str.size());
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