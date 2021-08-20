/*
 * 2mat/util.hpp -- useful functions for converting to MATLAB format
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

#ifndef TOO_MAT_UTIL_H
#define TOO_MAT_UTIL_H

#include <stdexcept>

namespace mat
{

    /*
     * uint mat::ceil8(uint)
     * 
     * Rounds an unsigned integer up to the nearest 8
     * 
     * EXAMPLE:
     * 
     * uint n = ceil8(15); // Returns 16u
     * 
     * INPUT:
     *  n   (uint)  the unsigned integer to round up
     * RETURNS:
     *  the integer n rounded up to the nearest 8
     */
    inline unsigned int ceil8 (unsigned int n)
    {
        return (n+7)&~7;
    }

    /*
     * mat::mfile_error
     * 
     * Error class for exceptions that occur during creating MATLAB .mat files
     */
    class mfile_error : public std::runtime_error
    {
    public:
        explicit mfile_error(const std::string &m);
        ~mfile_error() noexcept override;
    };
}

#endif