/*
 * 2mat/datenum.hpp -- Datenum utilities for writing to MATLAB files
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

namespace mat
{
    double datenum(int year, int month, int day, int hour = 0, int minute = 0, double second = 0.0);
    double unix2dn(double s);
    double j19002dn(double j);
    double j20002dn(double j);
    double tt20002dn(double tt);
}