/*
 * 2mat/v7_3/write.cpp -- implementation for writing routines for v7.3 MAT files
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

#include "file.hpp"
#include "matrix.hpp"
#include "mstruct.hpp"
#include "util.hpp"

#include <cmath>
#include <fstream>
#include <sstream>
#include <ctime>

namespace mat
{

    template <>
    void matrix::write<V7_3>(fwriter &fw, bool write_name)
    {
    }

    template <>
    void mstruct::write<V7_3>(fwriter &fw, bool write_name)
    {
    }

    template <>
    void file<V7_3>::close()
    {
        open = false;
    }

}