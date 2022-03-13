/*
 * Copyright 2001-2010 Georges Menie (www.menie.org)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University of California, Berkeley nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author:  Lammert Bies
 *
 * This file is licensed under the MIT License as stated below
 *
 * Copyright (c) 1999-2016 Lammert Bies
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UTILS_CRC_H_
#define UTILS_CRC_H_

// System headers
#include <cstdint>

// Other libraries headers

// Own components headers

// Forward declarations

/** @brief used to calculate 16bit CRC using CCITT standards
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint32_t - size of the buffer
 *
 *  @return uint16_t      - calculated 16bit CRC
 * */
uint16_t crc16_ccitt(uint8_t* buf, const uint32_t size);

/** @brief used to calculate 16bit CRC using CCITT standards
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint64_t - size of the buffer
 *
 *  @return uint16_t      - calculated 16bit CRC
 * */
uint16_t crc16_ccitt(uint8_t* buf, const uint64_t size);

/** @brief used to calculate 16bit CRC using CCITT standards
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint64_t - size of the buffer
 *  @param uint16_t       - the crc from the last iteration
 *
 *  @note this function is supposed to be used when a single checksum needs
 *      to be calculated over raw data, that is split into different parts of
 *      the memory
 *
 *  @return uint16_t      - calculated 16bit CRC
 * */
uint16_t crc16_ccitt(uint8_t* buf, const uint64_t size, const uint16_t oldCrc);

/** @brief calculates the 16 bits Kermit CRC in one pass for a byte string
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint32_t - size of the buffer
 */
uint16_t crc16_kermit(uint8_t* buf, const uint32_t size);

/** @brief calculates the 16 bits Kermit CRC in one pass for a byte string
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint64_t - size of the buffer
 *
 *  @return uint16_t      - calculated 16bit CRC Kermit
 */
uint16_t crc16_kermit(uint8_t* buf, const uint64_t size);

/** @brief calculates a new CRC Kermit value based on the previous value
 *         of the CRC and the next byte of data to be checked
 *
 *  @param uint16_t      - previous CRC
 *  @param const uint8_t - new byte for the update
 *
 *  @return uint16_t      - calculated 16bit CRC Kermit
 */
uint16_t update_crc16_kermit(uint16_t crc, const uint8_t byte);

/** @brief used to calculate 8bit CRC using cctalk standards
 *                                          (sum of all bytes % UINT8_MAX(255)
 *
 *  @param uint8_t *      - buffer for CRC calculation
 *  @param const uint32_t - size of the buffer
 *
 *  @return uint8_t       - calculated 8bit CRC
 * */
uint8_t crc8_cctalk(uint8_t* buf, const uint32_t size);

inline uint16_t byteSwap(const uint16_t input) {
  return static_cast<uint16_t>(((input & 0xFF) << 8) | ((input & 0xFF00) >> 8));
}

#endif /* UTILS_CRC_H_ */
