/*
 * 2mat/2mat.hpp -- mat::file class definition for writing to .mat files
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


#ifndef TOO_MAT_H
#define TOO_MAT_H

#include "types.hpp"
#include "container.hpp"

#include <string>
#include <vector>
#include <cstdint>
#include <initializer_list>
#include <type_traits>
#include <stdexcept>

namespace mat
{

    template <file_version V=V7>
    class file : public container
    {
        bool open;
        std::string head;

        inline virtual void write(fwriter& fw, file_version v)
        {
            throw mfile_error("Cannot write file object");
        };

    public:
		file(std::string fname, const std::string &head="Created using 2mat");
		~file();

        /*
         * mat::file::header(std::string)
         *
         * Writes the specified string to the header of this file. For V7 and lower files, if this
         * string is longer than 116 bytes, it will be truncated. For V7.3 files, this string will
         * be written as a comment in the root group of the resulting hdf5 file.
         *
         * INPUT:
         *  head (std::string &) the string to write to the head
         */
		void header(const std::string &head);

        /*
         * const std::string &mat::file::header() const
         *
         * Returns the string currently stored in the header of this file.
         *
         * RETURNS:
         *  The header of this file
         */
		const std::string &header() const;

        /*
         * void mat::file::close() const
         *
         * Write all data to disk and close the file. After this, the file cannot be written to
         * anymore.
         *
         * RETURNS:
         *  The header of this file
         */
        void close();
    };

    template <file_version V>
    file<V>::~file()
    {
        close();
    }

    template <file_version V>
    file<V>::file(std::string fname, const std::string &head)
    :
        container(fname),
        open(true),
        head(head)
    {}

    template <file_version V>
    void file<V>::header(const std::string &head)
    {
        this->head = head;
    }
    
    template <file_version V>
    const std::string &file<V>::header() const
    {
        return head;
    }

}

#endif