/*
 * 2mat/container.cpp -- class implementation for container.hpp
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

#include "container.hpp"

namespace mat
{

    container::container(const std::string &name)
    :
        element(name)
    {}

    container &container::add(const std::string &name, const std::string &str)
    {
        _children.push_back(std::unique_ptr<element>(new matrix(name,str)));
        return *this;
    }

    container &container::add(const std::string &name, const std::u16string &str)
    {
        _children.push_back(std::unique_ptr<element>(new matrix(name,str)));
        return *this;
    }

    container &container::add(const std::string &name, const std::u32string &str)
    {
        _children.push_back(std::unique_ptr<element>(new matrix(name,str)));
        return *this;
    }

}