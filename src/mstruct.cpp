/*
 * 2mat/mstruct.hpp -- class definition for matlab struct types
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

#include "mstruct.hpp"

namespace mat
{


    mstruct::mstruct(const std::string& name)
    :
        container(name)
    {}

    [[nodiscard]] dim_t mstruct::size(bool with_name) const
    {
        dim_t size = 56;
        if (with_name) size += _name.size()> 4 ? ceil8(_name.size()) : 0;

        // Calculate field name size
        dim_t namesz = 0;
        for (auto &elem : _children) namesz = std::max((size_t) namesz, elem->name().size() + 1);
        size += ceil8(std::min(namesz, 63ull) * _children.size());

        for (auto &elem : _children) size += elem->size(false)+8; // Plus 8 for the element headers
        return size;
    }

    void mstruct::write(fwriter& fw, file_version v, bool write_name)
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

    mstruct &mstruct::add(const std::string &name, const std::string &str)
    {
        container::add(name,str);
        return *this;
    }
    mstruct &mstruct::add(const std::string &name, const std::u16string &str)
    {
        container::add(name,str);
        return *this;
    }
    mstruct &mstruct::add(const std::string &name, const std::u32string &str)
    {
        container::add(name,str);
        return *this;
    }

}