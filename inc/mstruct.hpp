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

#ifndef TOO_MAT_MSTRUCT_H
#define TOO_MAT_MSTRUCT_H

#include "container.hpp"

namespace mat
{

    class mstruct : public container
    {

        template <file_version V>
        void write(fwriter& fw, bool write_name);
    public:
		explicit mstruct(const std::string& name);
		~mstruct() override = default;

        [[nodiscard]] dim_t size(bool with_name = true) const override;

        template <typename T>
        mstruct &add(const T &c);

        template <typename NT, typename dimtype=dim_t>
		mstruct &add(const std::string &name, NT start, NT end,
            const std::vector<dimtype> &dims = {});

        template <typename T, typename dimtype=dim_t>
		mstruct &add(const std::string &name, T *data, dim_t numel,
            const std::vector<dimtype> &dims = {});

        template <typename T, typename dimtype=dim_t>
		mstruct &add(const std::string &name, std::initializer_list<T> data,
            const std::vector<dimtype> &dims = {});

        mstruct &add(const std::string &name, const std::string &str) override;
        mstruct &add(const std::string &name, const std::u16string &str) override;
        mstruct &add(const std::string &name, const std::u32string &str) override;

        /*
         * void mat::mstruct::write(std::ostream& out, file_version v)
         *
         * Writes the data in this mstruct to the given output stream, in accordance with the file
         * version specified.
         *
         * INPUT:
         *  out (std::ostream &) the stream to output the binary data to
         *  v (file_version) the file format to use
         */
        void write(fwriter &fw, file_version v, bool write_name = true) override;
    };

    template<typename T>
    mstruct &mstruct::add(const T &c) {
        container::add<T>(c);
        return *this;
    }

    template<typename NT, typename dimtype>
    mstruct &mstruct::add(const std::string &name, NT start, NT end, const std::vector<dimtype> &dims) {
        container::add<NT,dimtype>(name,start,end,dims);
        return *this;
    }

    template<typename T, typename dimtype>
    mstruct &mstruct::add(const std::string &name, T *data, dim_t numel, const std::vector<dimtype> &dims) {
        container::add<T,dimtype>(name,data,numel,dims);
        return *this;
    }

    template<typename T, typename dimtype>
    mstruct &mstruct::add(const std::string &name, std::initializer_list<T> data, const std::vector<dimtype> &dims) {
        container::add<T,dimtype>(name,data,dims);
        return *this;
    }

}

#endif