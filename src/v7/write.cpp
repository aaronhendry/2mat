/*
 * 2mat/v7/write.cpp -- implementation for writing routines for v7 MAT files
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
    void file<V7>::close()
    {
        if (_children.empty()) return;
        fwriter fw(_name);
        fw.write(create_header(head));
        fw.write<uint64_t>(0); // subsys offset
        fw.write<uint16_t>(VERSION);
        fw.write<uint16_t>(ENDIAN);

        for (auto const &child : _children)
        {
            fw.write<uint32_t>(miCOMPRESSED);
            fw.write<uint32_t>(0);
            auto sloc = fw.tellp();
            fw.addfilter<zfilter>();
            child->write(fw,V6);
            fw.rmfilter();
            auto eloc = fw.tellp();
            fw.seekp(sloc-4);
            fw.write<uint32_t>(eloc-sloc);
            fw.seekp(eloc);
        }
        fw.close();
        open = false;
    }

}