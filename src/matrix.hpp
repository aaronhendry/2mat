/*
 * 2mat/matrix.hpp -- class definition for a MATLAB matrix class for storing data
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

#ifndef TOO_MAT_MATRIX_H
#define TOO_MAT_MATRIX_H

#include "element.hpp"

#include <vector>
#include <string>
#include <algorithm>

namespace mat
{

    /*
     *  mat::matrix
     * 
     * A class for constructing a MATLAB matrix, used for storing most kinds of data in MATLAB. 
     * These are typically written directly to a MATLAB .mat file, or stored in a container type 
     * (for instance a struct or cell-array).
     * 
     */
    class matrix : public element
    {
    private:

        template <file_version V>
        void write(std::ostream& out);
    public:
        // The matrix is basically a thin wrapper around a data-element, so we just re-use the 
        // constructors from element
        using element::element;
        ~matrix() = default;

        /*
         * void mat::matrix::write(std::ostream& out, file_version v)
         * 
         * Writes the data in this matrix to the given output stream, in accordance with the file
         * version specified.
         * 
         * INPUT:
         *  out (std::ostream &) the stream to output the binary data to
         *  v (file_version) the file format to use
         */
        virtual inline void write(std::ostream& out, file_version v)
        {
            switch(v)
            {
                case V4:
                    write<V4>(out);
                    return;
                case V6:
                    write<V6>(out);
                    return;
                case V7:
                    write<V7>(out);
                    return;
                case V7_3:
                    write<V7_3>(out);
                    return;
            }
        }

    };

}

#endif