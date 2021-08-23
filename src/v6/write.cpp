/*
 * 2mat/v6/write.cpp -- implementation for writing routines for v6 MAT files
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

#include "io/fwriter.hpp"
#include "file.hpp"
#include "matrix.hpp"
#include "mstruct.hpp"
#include "util.hpp"

#include <fstream>
#include <sstream>
#include <ctime>

namespace mat
{

    static const uint16_t VERSION = 0x0100, ENDIAN = 0x4d49;

    static std::string create_header(const std::string &head)
    {
        // Write the creation time to the header. We don't need to do this, but it's sometimes 
        // useful to have this information
        time_t rawtime;
        time(&rawtime);

        std::stringstream ss;
        ss << "MATLAB 5.0 MAT-file, Created on: ";
        ss << ctime(&rawtime) << " " << head;

        std::string str = ss.str();
        // truncate the header string if it is too long, otherwise pad it with spaces (we could use
        // null characters, but MATLAB by default uses spaces, so we just mimic that).
        str.resize(116,0x20);
        return str;
    }

    template <>
    void matrix::write<V6>(fwriter &fw, bool write_name)
    {
        unsigned int n;
        fw.write<uint32_t>(miMATRIX);
        fw.write<uint32_t>(size());
        fw.write<uint32_t>(miUINT32);
        fw.write<uint32_t>(8);
        fw.write<uint32_t>(((_logical*0x02+_complex*0x08)<<8) + _class);
        fw.write<uint32_t>(0);

        n = _dims.size();
        fw.write<uint32_t>(miINT32);
        fw.write<uint32_t>(n*4);
        fw.write<dim_t,uint32_t>(&_dims[0],n);
        n *= 4;
        fw.write_n<char>(0,ceil8(n)-n);

        if (write_name)
        {
            n = _name.size();
            if (n <= 4)
            {
                fw.write<uint16_t>(miINT8);
                fw.write<uint16_t>(n);
                fw.write<char>(&_name[0],n);
                fw.write_n<char>(0,4-n);
            } else {
                fw.write<uint32_t>(miINT8);
                fw.write<uint32_t>(n);
                fw.write<char>(&_name[0],n);
                fw.write_n<char>(0,ceil8(n)-n);
            }
        } else {
            fw.write<uint32_t>(miINT8);
            fw.write<uint32_t>(0);
        }

        n = _data->size();
        if (n <= 4)
        {
            fw.write<uint16_t>(_type);
            fw.write<uint16_t>(n);
            fw.write<unsigned char>(ptr(),n);
            fw.write_n<char>(0,4-n);
        } else {
            fw.write<uint32_t>(_type);
            fw.write<uint32_t>(n);
            fw.write<unsigned char>(ptr(),n);
            fw.write_n<char>(0,ceil8(n)-n);
        }
    }

    template <>
    void mstruct::write<V6>(fwriter &fw, bool write_name)
    {
        unsigned int n;
        // Write header

        fw.write<uint32_t>(miMATRIX);
        fw.write<uint32_t>(size());
        fw.write<uint32_t>(miUINT32);
        fw.write<uint32_t>(8);
        fw.write<uint32_t>(mxSTRUCT_CLASS);
        fw.write<uint32_t>(0);

        // Dimensions
        fw.write<uint32_t>(miUINT32);
        fw.write<uint32_t>(8);
        fw.write<uint32_t>(1);
        fw.write<uint32_t>(1);

        // Name
        if (write_name)
        {
            n = _name.size();
            if (n <= 4)
            {
                fw.write<uint16_t>(n);
                fw.write<uint16_t>(miINT8);
                fw.write<char>(&_name[0],n);
                fw.write_n<char>(0,4-n);
            } else {
                fw.write<uint32_t>(miINT8);
                fw.write<uint32_t>(n);
                fw.write<char>(&_name[0],n);
                fw.write_n<char>(0,ceil8(n)-n);
            }
        } else {
            fw.write<uint32_t>(miINT8);
            fw.write<uint32_t>(0);
        }


        // Field names;
        dim_t namesz = 0;
        for (auto &elem : _children) namesz = std::max((size_t) namesz, elem->name().size() + 1);
        namesz = std::min(namesz, 63ull);

        fw.write<uint16_t>(4);
        fw.write<uint16_t>(miINT32);
        fw.write<int32_t>((int32_t)namesz);
        fw.write<uint32_t>(miINT8);
        fw.write<uint32_t>(_children.size()*namesz);

        for (auto &elem : _children)
        {
            auto name = elem->name().substr(0,namesz);
            n = name.size();
            fw.write<char>(&name[0],n);
            fw.write_n<char>(0,namesz-n);
        }
        fw.write_n<char>(0, ceil8(_children.size()*namesz) - _children.size()*namesz);

        for (auto &elem : _children)
        {
            elem->write(fw, V6, false);
        }
    }

    template <>
    void file<V6>::close()
    {
        if (_children.empty()) return;
        fwriter fw(_name);
        fw.write(create_header(head));
        fw.write<uint64_t>(0); // subsys offset
        fw.write<uint16_t>(VERSION);
        fw.write<uint16_t>(ENDIAN);

        for (auto const &child : _children)
        {
            child->write(fw,V6);
        }
        fw.close();
        open = false;
    }

}