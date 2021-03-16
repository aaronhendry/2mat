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
        std::vector<dim_t> dims;

        template <file_version V>
        void write(std::ostream& out);
    public:        
        /*
         * mat::matrix::matrix(const std::string &)
         * 
         * Constructs an empty data element with the specified name. This is typically used if the
         * parent object is managing the data itself (or if an empty element is needed for some
         * reason. For these empty elements, the datatype is set to DOUBLE, but this can be
         * overridden by the parent class.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         */
		matrix(const std::string &name);

        /*
         * mat::matrix::matrix(const std::string &, NT, NT)
         * 
         * Constructs a data element using the passed pointer-like arguments. Data is deep-copied 
         * from the passed pointers. The dimensions of this matrix can be explicity specified, but
         * the elements of the dims vector must be commensurate with the number of elements in the
         * matrix. If dims is not specified, the matrix will be a 1D row vector.
         * 
         * TEMPLATE
         *  T   The type of the value obtained when dereferencing an argument of type NT
         *  NT  A pointer-like value (e.g., a pointer or iterator)
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (NT) a pointer to the start of the data to copy
         *  end (NT) a pointer to the end of the data to copy
         */
        template <typename T, typename NT>
		matrix(const std::string &name, NT start, NT end, const std::vector<dim_t> dims = {});

        /*
         * mat::matrix::matrix(const std::string &, T *, dim_t)
         * 
         * Constructs a data element from the passed point. Data is deep-copied -- the total number
         * of bytes copied will be sizeof(T)*numel. The dimensions of this matrix can be explicity
         * specified, but the elements of the dims vector must be commensurate with the number of
         * elements in the matrix. If dims is not specified, the matrix will be a 1D row vector.
         * 
         * TEMPLATE
         *  T   The type of the data to copy
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  data (T *) a pointer to the start of the data to copy
         *  numel (dim_t) the number of elements to copy
         */
        template <typename T>
		matrix(const std::string &name, T *data, dim_t numel, const std::vector<dim_t> dims = {});

        /*
         * mat::matrix::matrix(const std::string &, const std::string &)
         * 
         * Constructs a data element from the passed string. In keeping with MATLAB format, the data
         * will be stored as an unsigned 16-bit integer. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  str (const std::string &) the string to construct the element from
         */
        matrix(const std::string &name, const std::string &str);

        /*
         * mat::matrix::matrix(const std::string &, const std::u16string &)
         * 
         * Constructs a data element from the passed UTF-16 string. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (const std::u16string &) the string to construct the element from
         */
        matrix(const std::string &name, const std::u16string &str);

        /*
         * mat::matrix::matrix(const std::string &, const std::u32string &)
         * 
         * Constructs a data element from the passed UTF-32 string. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (const std::u32string &) the string to construct the element from
         */
        matrix(const std::string &name, const std::u32string &str);
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