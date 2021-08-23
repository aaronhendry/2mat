/*
 * 2mat/matrix.cpp -- partial class implementation for matrix.hpp
 * 
 * Version: 1.0
 * Date created: 2021 March 17
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

#include "matrix.hpp"

namespace mat
{

    matrix::matrix(const std::string &name)
    :
        element(name),
        _class(mxDOUBLE_CLASS),
        _dims({0,0}),
        _logical(false),
        _complex(false)
    {}

    template <>
    matrix::matrix(const std::string &name, std::initializer_list<char> data,
        const std::vector<dim_t> &dims)
    :
        matrix(name,data.begin(),data.end(),dims)
    {}

    dim_t utflen(const std::string &str)
    {
        int len = 0;
        const char *s = &str[0];
        while (*s) len += (*s++ & 0xc0) != 0x80;
        return len;
    }

    matrix::matrix(const std::string &name, const std::string &str)
    :
        element(name,str),
        _class(mxCHAR_CLASS),
        _dims(std::vector<dim_t>{1ull,(dim_t)(utflen(str))}),
        _logical(false),
        _complex(false)
    {}
    matrix::matrix(const std::string &name, const std::u16string &str)
    :
        element(name,str),
        _class(mxCHAR_CLASS),
        _dims(std::vector<dim_t>{1ull,(dim_t)(str.size())}),
        _logical(false),
        _complex(false)
    {}
    matrix::matrix(const std::string &name, const std::u32string &str)
    :
        element(name,str),
        _class(mxCHAR_CLASS),
        _dims(std::vector<dim_t>{1ull,(dim_t)(str.size())}),
        _logical(false),
        _complex(false)
    {}

    dim_t matrix::size(bool with_name) const {
        dim_t size = 32 + ceil8(_dims.size()*4) + (_data->size()<=4? 0 : ceil8(_data->size()));
        if (with_name) size += 8 + _name.size() > 4 ? ceil8(_name.size()) : 0;
        return size;
    }

    void matrix::write(fwriter& fw, file_version v, bool write_name)
    {
        switch(v)
        {
            // Writing for V6 and V7 is the same -- only the compression at the end differs
            case V6:
            case V7:
                write<V6>(fw, write_name);
                return;
            case V7_3:
                write<V7_3>(fw, write_name);
                return;
        }
    }

}