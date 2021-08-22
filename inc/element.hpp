/*
 * 2mat/element.hpp -- class definition for the base element for storing data
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

#ifndef TOO_MAT_ELEMENT_H
#define TOO_MAT_ELEMENT_H

#include "types.hpp"

#include <cstring>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

namespace mat
{

    class fwriter;

    class element
    {
    protected:
        datatype _type = miUNKNOWN;
        std::string _name;
        std::shared_ptr<std::vector<unsigned char>> _data;

        template <typename T=unsigned char>
        T *ptr();

    public:
        /*
         * mat::element::element(const std::string &)
         * 
         * Constructs an empty data element with the specified name. This is typically used if the
         * parent object is managing the data itself (or if an empty element is needed for some
         * reason. For these empty elements, the datatype is set to DOUBLE, but this can be
         * overridden by the parent class.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         */
		explicit element(std::string name);

        /*
         * mat::element::element(const std::string &, NT, NT)
         * 
         * Constructs a data element using the passed pointer-like arguments. Data is deep-copied 
         * from the passed pointers.
         * 
         * TEMPLATE
         *  T   The type of the value obtained when dereferencing an argument of type NT
         *  NT  A pointer-like value (e.g., a pointer or iterator)
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (NT) a pointer to the start of the data to copy
         *  end (NT) a pointer to the end of the data to copy
         */
        template <typename NT>
		element(std::string name, NT start, NT end);

        /*
         * mat::element::element(const std::string &, T *, dim_t)
         * 
         * Constructs a data element from the passed point. Data is deep-copied -- the total number
         * of bytes copied will be sizeof(T)*numel.
         * 
         * TEMPLATE
         *  T   The type of the data to copy
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  data (T *) a pointer to the start of the data to copy
         *  numel (dim_t) the number of elements to copy
         */
        template <typename T>
		element(std::string name, T *data, dim_t numel);

        /*
         * mat::element::element(const std::string &, const std::string &)
         * 
         * Constructs a data element from the passed string. In keeping with MATLAB format, the data
         * will be stored as an unsigned 16-bit integer. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  str (const std::string &) the string to construct the element from
         */
        element(std::string name, const std::string &str);

        /*
         * mat::element::element(const std::string &, const std::u16string &)
         * 
         * Constructs a data element from the passed UTF-16 string. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (const std::u16string &) the string to construct the element from
         */
        element(std::string name, const std::u16string &str);

        /*
         * mat::element::element(const std::string &, const std::u32string &)
         * 
         * Constructs a data element from the passed UTF-32 string. 
         * 
         * INPUT:
         *  name (const str::string &) the name of the new element
         *  start (const std::u32string &) the string to construct the element from
         */
        element(std::string name, const std::u32string &str);
		virtual ~element() = default;

        /*
         * const std::string &mat::element::name() const
         * 
         * Returns the name of the element
         * 
         * RETURN:
         *  The name of this element
         */
        [[nodiscard]] const std::string &name() const;

        /*
         * datatype mat::element::type() const
         * 
         * Returns the MATLAB datatype contained in this element
         * 
         * RETURN:
         *  The name of this element
         */
        [[nodiscard]] datatype type() const;

        /*
         * void mat::element::write(std::ostream& out, file_version v)
         * 
         * Writes the data in this element to the given output stream, in accordance with the file
         * version specified.
         * 
         * INPUT:
         *  out (std::ostream &) the stream to output the binary data to
         *  v (file_version) the file format to use
         */
        virtual void write(fwriter &fw, file_version v) = 0;

    };

    template <typename T>
    T *element::ptr()
    {
        return !_data ? NULL : (T *)&_data->at(0);
    }

    template <typename NT>
    element::element(std::string name, NT start, NT end)
    :
        _type(get_datatype(*start)),
        _name(std::move(name))
    {
        dim_t n = (end-start)*sizeof(*start);
        _data = std::make_shared<std::vector<unsigned char>>(n);
        std::memcpy(ptr(),&(*start),n);
    }

    template <typename T>
    element::element(std::string name, T *data, dim_t numel)
    :
        element(name,data,data+numel)
    {}


}

#endif