/*
 * 2mat/date/leap.cpp -- implementation of leap seconds
 * 
 * Version: 1.0
 * Date created: 2021 August 20
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
     const double LEAP_JD[27] =
    {
        2457753.5,
        2457203.5,
        2456108.5,
        2454831.5,
        2453735.5,
        2451178.5,
        2450629.5,
        2450082.5,
        2449533.5,
        2449168.5,
        2448803.5,
        2448256.5,
        2447891.5,
        2447160.5,
        2446246.5,
        2445515.5,
        2445150.5,
        2444785.5,
        2444238.5,
        2443873.5,
        2443508.5,
        2443143.5,
        2442777.5,
        2442412.5,
        2442047.5,
        2441682.5,
        2441498.5
    };
}