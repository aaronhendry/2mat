/*
 * 2mat/container.hpp -- class definition for a generic container class for storing data elements
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

#ifndef TOO_MAT_CONTAINER_H
#define TOO_MAT_CONTAINER_H

#include "element.hpp"
#include "matrix.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <memory>

namespace mat
{

    class container : public element
    {
    protected:
        std::vector<std::unique_ptr<element>> _children;
    public:
        /*
         * mat::container::container(const std::string &)
         * 
         * Constructs an empty container element with the specified name. It is assumed that further
         * elements will be added to the container before writing (although this is not strictly
         * necessary).
         * 
         * INPUT:
         *  name (const str::string &) the name of the new container
         */
        container(const std::string &name);
        virtual ~container() = 0;

        /*
         * mat::container::add(const T &)
         * 
         * Adds the passed object (which must be a derived type of element) to this container.
         * 
         * TEMPLATE:
         *  T   the type of the object to add, which must be a derived type of element
         * INPUT:
         *  elem (const T &) the element to add
         */
        template <typename T>
        container &add(const T &);

        //------------- helper methods for adding matrices to the container directly -------------//

        /*
         * mat::container::add(const std::string &, NT, NT, const std::vector<dim_t>)
         * 
         * Creates a matrix with the specified name from the passed iterators and adds it to this
         * container. The dimensions of this matrix can be explicity specified, but the elements of
         * the dims vector must be commensurate with the number of elements in the matrix. If dims 
         * is not specified, the matrix will be a 1D row vector.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new matrix
         *  start (NT) the pointer to the start of the range to add
         *  end (NT) the pointer to the end of the range to add
         *  dims (const std::vector<dim_t> &) the dimensions of the matrix
         */
        template <typename NT>
		container &add(const std::string &name, NT start, NT end, 
            const std::vector<dim_t> &dims = {});

        /*
         * mat::container::add(const std::string &, T *, dim_t, const std::vector<dim_t>)
         * 
         * Creates a matrix with the specified name from the passed array and adds it to this
         * container. The dimensions of this matrix can be explicity specified, but the elements of
         * the dims vector must be commensurate with the number of elements in the matrix. If dims
         * is not specified, the matrix will be a 1D row vector.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new matrix
         *  data (NT) the pointer to the start of the data to add
         *  numel (NT) the number of elements to add from the pass array
         *  dims (const std::vector<dim_t> &) the dimensions of the matrix
         */
        template <typename T>
		container &add(const std::string &name, T *data, dim_t numel, 
            const std::vector<dim_t> &dims = {});

        template <typename T>
		container &add(const std::string &name, std::initializer_list<T> data, 
            const std::vector<dim_t> dims = {});

        /*
         * mat::container::add(const std::string &, T *, dim_t, const std::vector<dim_t>)
         * 
         * Creates a matrix with the specified name from the passed string and adds it to this
         * container.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new matrix
         *  str (const std::string &) the string to add
         */
        container &add(const std::string &name, const std::string &str);

        /*
         * mat::container::add(const std::string &, T *, dim_t, const std::vector<dim_t>)
         * 
         * Creates a matrix with the specified name from the passed UTF-16 string and adds it to
         * this container.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new matrix
         *  str (const std::string &) the UTF-16 string to add
         */
        container &add(const std::string &name, const std::u16string &str);

        /*
         * mat::container::add(const std::string &, T *, dim_t, const std::vector<dim_t>)
         * 
         * Creates a matrix with the specified name from the passed UTF-32 string and adds it to
         * this container.
         * 
         * INPUT:
         *  name (const str::string &) the name of the new matrix
         *  str (const std::string &) the UTF-32 string to add
         */
        container &add(const std::string &name, const std::u32string &str);

        virtual void write(fwriter& fw, file_version v) = 0;
    };

    inline container::~container() = default;

    template <typename T>
    container &container::add(const T &child)
    {
        _children.push_back(std::unique_ptr<element>(new T(child)));
        return *this;
    }

    template <typename NT>
    container &container::add(const std::string &name, NT start, NT end, 
            const std::vector<dim_t> &dims)
    {
        add(matrix(name,start,end,dims));
        return *this;
    }

    template <typename T>
    container &container::add(const std::string &name, T *data, dim_t numel, 
            const std::vector<dim_t> &dims)
    {
        add(matrix(name,data,numel,dims));
        return *this;
    }

    template <typename T>
    container &container::add(const std::string &name, std::initializer_list<T> data, 
        const std::vector<dim_t> dims)
    {
        add(matrix(name,data,dims));
        return *this;
    }

}

#endif