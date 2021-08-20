/*
 * 2mat/util.hpp -- implementation of util functions
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

#include "util.hpp"

namespace mat
{

    mfile_error::mfile_error(const std::string &m)
    :
        runtime_error(m)
    {}

    mfile_error::~mfile_error() noexcept= default;
}
