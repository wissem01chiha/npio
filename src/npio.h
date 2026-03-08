/**
    Copyright (c) Wissem Chiha, 2026

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

    Copyright (c) Carl Rogers, 2011

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef NPIO_H
#define NPIO_H

#include <zlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#define NPIO_VERSION_MAJOR 0
#define NPIO_VERSION_MINOR 1
#define NPIO_VERSION_PATCH 0

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** no error. */
#define NPIO_OK 0x00

/** has encountered the end of the file. */
#define NPIO_EOF 0x01

/** detected a buffer overflow  */
#define NPIO_EBUF 0x02

/** array dimensions exceed allowed limits. */
#define NPIO_EDIM 0x03

/** failed to read the file */
#define NPIO_EFREAD 0x04

/** failed to open the file */
#define NPIO_EFOPEN 0x05

/** failed to write the file */
#define NPIO_EFWRITE 0x06

/** buffer size is zero */
#define NPIO_EBUF_SIZE_ZERO 0x07

/** null pointer to a buffer  */
#define NPIO_EBUF_NULL 0x08

/** buffer truncated */
#define NPIO_EBUF_TRUNCATED 0x09

/** null pointer to an npio array  */
#define NPIO_EARR_NULL 0x000A

/** dimension exceed allowed npio default */
#define NPIO_EARR_DIM 0x000A

/** unknown error */
#define NPIO_EUNKNOWN 0x0064

/** maximum number of npy array dimensions */
#define NPY_ARRAY_DIM 8

/** default buffer size for I/O  */
#define NPIO_BUF_SIZE 256

    /**
     * @brief
     */
    typedef size_t npio_size_t;

    /**
     * @brief
     */
    typedef uint8_t npio_bool_t;

    /**
     * @brief
     */
    typedef uint16_t npio_uint16_t;

    /**
     * @brief
     */
    typedef int npio_int_t;

    /**
     * @brief Type for specifying an error or status code.
     */
    typedef int npio_status_t;

    /** NPY array shape type */
    typedef struct
    {
        size_t shape[NPY_ARRAY_DIM];
        size_t ndim;
    } npy_shape_t;

    /**
     * @brief data type for numpy array object
     */
    typedef struct
    {
        char       *data;
        npy_shape_t shape;
        npio_size_t word_size;
        npio_bool_t fortran_order;
        npio_size_t num_vals;
    } npy_array_t;

    typedef struct
    {
        char       *key;
        npy_array_t value;
    } npz_entry_t;

    typedef struct
    {
        npz_entry_t *entries;
        npio_size_t  count;
    } npz_t;

    /**
     * @brief Return a human readable string describing the specified error.
     * @param statcode The error code to get a string for.
     * @param buf A buffer to hold the error string.
     * @param bufsize Size of the buffer to hold the string.
     * @return The number of characters that would have been written on the buffer, if buffsize had
     * been sufficiently large. If an encoding error occurs, a negative number is returned.
     */
    int npio_strerror(npio_status_t statcode, char *buf, npio_size_t bufsize);

    /**
     * @brief convert a npio_status_t error code into a human readble string
     * @return null pointer if the stacode not supported in npio error list
     */
    const char *npio_error_string(npio_status_t statcode);

    /**
     * @brief
     * @param pfname
     * @param parray pointer to npy_array_t object
     *
     */
    npio_status_t npy_load(const char *pfname, npy_array_t *parray);

    /**
     * @brief read the array this function is mainly used by npy_load
     * @param buffer
     */
    npio_status_t npy_read(unsigned char     *buffer,
                           npio_size_t       *word_size,
                           const npy_shape_t *pshape,
                           npio_bool_t       *fortran_order);

    /**
     * @brief
     */
    npio_status_t
    npy_save(const char *pfname, const char *pdata, const npy_shape_t *pshape, const char *pmode);

    /**
     * @brief
     */
    npio_status_t npy_init(const npy_shape_t *pshape, char *pheader);

    /**
     * @brief read an npy array from filesystem
     */
    npio_status_t npy_fs_read(FILE              *fp,
                              npio_size_t        word_size,
                              const npy_shape_t *pshape,
                              npio_bool_t        fortran_order);

    /**
     * @brief load an .npz file into memmory, .npz file format is a zipped archive of files named
     * after the variables they contain. this typcillay require zlib librray to read archive npy
     * entries for more information about npz file format look into :
     * https://numpy.org/doc/stable/reference/generated/numpy.savez_compressed.html
     * @param pfname npz filename
     * @param pnpz
     * @param parray
     */
    npio_status_t npz_load(const char *pfname, npz_t *pnpz, npy_array_t *parray);

    /**
     * @brief load only a given encoded array from the npz file
     */
    npio_status_t npz_array_load(const char *pfname, const char *pvarname, npy_array_t *parray);

    /**
     * @brief
     */
    npio_status_t npz_save(const char        *pzipname,
                           const char        *pfname,
                           const char        *data,
                           const npy_shape_t *pshape,
                           const char        *pmode);

    /**
     * @brief
     */
    npio_status_t npio_zip_read(FILE         *fp,
                                npio_uint16_t nrecs,
                                npio_size_t   global_header_size,
                                npio_size_t   global_header_offset);

    // char BigEndianTest();
    // char map_type(const std::type_info& t);
    // template<typename T> std::vector<char> create_npy_header(const std::vector<size_t>& shape);
    // void parse_npy_header(FILE* fp,size_t& word_size, std::vector<size_t>& shape, bool&
    // fortran_order); void parse_npy_header(unsigned char* buffer,size_t& word_size,
    // std::vector<size_t>& shape, bool& fortran_order); void parse_zip_footer(FILE* fp, uint16_t&
    // nrecs, size_t& global_header_size, size_t& global_header_offset);

    // template<typename T> std::vector<char>& operator+=(std::vector<char>& lhs, const T rhs) {
    //     //write in little endian
    //     for(size_t byte = 0; byte < sizeof(T); byte++) {
    //         char val = *((char*)&rhs+byte);
    //         lhs.push_back(val);
    //     }
    //     return lhs;
    // }

    // template<> std::vector<char>& operator+=(std::vector<char>& lhs, const std::string rhs);
    // template<> std::vector<char>& operator+=(std::vector<char>& lhs, const char* rhs);

    // template<typename T> void npy_save(std::string fname, const T* data, const
    // std::vector<size_t> shape, std::string mode = "w") {
    //     FILE* fp = NULL;
    //     std::vector<size_t> true_data_shape; //if appending, the shape of existing + new data

    //     if(mode == "a") fp = fopen(fname.c_str(),"r+b");

    //     if(fp) {
    //         //file exists. we need to append to it. read the header, modify the array size
    //         size_t word_size;
    //         bool fortran_order;
    //         parse_npy_header(fp,word_size,true_data_shape,fortran_order);
    //         assert(!fortran_order);

    //         if(word_size != sizeof(T)) {
    //             std::cout<<"libnpy error: "<<fname<<" has word size "<<word_size<<" but npy_save
    //             appending data sized "<<sizeof(T)<<"\n"; assert( word_size == sizeof(T) );
    //         }
    //         if(true_data_shape.size() != shape.size()) {
    //             std::cout<<"libnpy error: npy_save attempting to append misdimensioned data to
    //             "<<fname<<"\n"; assert(true_data_shape.size() != shape.size());
    //         }

    //         for(size_t i = 1; i < shape.size(); i++) {
    //             if(shape[i] != true_data_shape[i]) {
    //                 std::cout<<"libnpy error: npy_save attempting to append misshaped data to
    //                 "<<fname<<"\n"; assert(shape[i] == true_data_shape[i]);
    //             }
    //         }
    //         true_data_shape[0] += shape[0];
    //     }
    //     else {
    //         fp = fopen(fname.c_str(),"wb");
    //         true_data_shape = shape;
    //     }

    //     std::vector<char> header = create_npy_header<T>(true_data_shape);
    //     size_t nels = std::accumulate(shape.begin(),shape.end(),1,std::multiplies<size_t>());

    //     fseek(fp,0,SEEK_SET);
    //     fwrite(&header[0],sizeof(char),header.size(),fp);
    //     fseek(fp,0,SEEK_END);
    //     fwrite(data,sizeof(T),nels,fp);
    //     fclose(fp);
    // }

    // template<typename T> void npz_save(std::string zipname, std::string fname, const T* data,
    // const std::vector<size_t>& shape, std::string mode = "w")
    // {
    //     //first, append a .npy to the fname
    //     fname += ".npy";

    //     //now, on with the show
    //     FILE* fp = NULL;
    //     uint16_t nrecs = 0;
    //     size_t global_header_offset = 0;
    //     std::vector<char> global_header;

    //     if(mode == "a") fp = fopen(zipname.c_str(),"r+b");

    //     if(fp) {
    //         //zip file exists. we need to add a new npy file to it.
    //         //first read the footer. this gives us the offset and size of the global header
    //         //then read and store the global header.
    //         //below, we will write the the new data at the start of the global header then append
    //         the global header and footer below it size_t global_header_size;
    //         parse_zip_footer(fp,nrecs,global_header_size,global_header_offset);
    //         fseek(fp,global_header_offset,SEEK_SET);
    //         global_header.resize(global_header_size);
    //         size_t res = fread(&global_header[0],sizeof(char),global_header_size,fp);
    //         if(res != global_header_size){
    //             throw std::runtime_error("npz_save: header read error while adding to existing
    //             zip");
    //         }
    //         fseek(fp,global_header_offset,SEEK_SET);
    //     }
    //     else {
    //         fp = fopen(zipname.c_str(),"wb");
    //     }

    //     std::vector<char> npy_header = create_npy_header<T>(shape);

    //     size_t nels = std::accumulate(shape.begin(),shape.end(),1,std::multiplies<size_t>());
    //     size_t nbytes = nels*sizeof(T) + npy_header.size();

    //     //get the CRC of the data to be added
    //     uint32_t crc = crc32(0L,(uint8_t*)&npy_header[0],npy_header.size());
    //     crc = crc32(crc,(uint8_t*)data,nels*sizeof(T));

    //     //build the local header
    //     std::vector<char> local_header;
    //     local_header += "PK"; //first part of sig
    //     local_header += (uint16_t) 0x0403; //second part of sig
    //     local_header += (uint16_t) 20; //min version to extract
    //     local_header += (uint16_t) 0; //general purpose bit flag
    //     local_header += (uint16_t) 0; //compression method
    //     local_header += (uint16_t) 0; //file last mod time
    //     local_header += (uint16_t) 0;     //file last mod date
    //     local_header += (uint32_t) crc; //crc
    //     local_header += (uint32_t) nbytes; //compressed size
    //     local_header += (uint32_t) nbytes; //uncompressed size
    //     local_header += (uint16_t) fname.size(); //fname length
    //     local_header += (uint16_t) 0; //extra field length
    //     local_header += fname;

    //     //build global header
    //     global_header += "PK"; //first part of sig
    //     global_header += (uint16_t) 0x0201; //second part of sig
    //     global_header += (uint16_t) 20; //version made by
    //     global_header.insert(global_header.end(),local_header.begin()+4,local_header.begin()+30);
    //     global_header += (uint16_t) 0; //file comment length
    //     global_header += (uint16_t) 0; //disk number where file starts
    //     global_header += (uint16_t) 0; //internal file attributes
    //     global_header += (uint32_t) 0; //external file attributes
    //     global_header += (uint32_t) global_header_offset; //relative offset of local file header,
    //     since it begins where the global header used to begin global_header += fname;

    //     //build footer
    //     std::vector<char> footer;
    //     footer += "PK"; //first part of sig
    //     footer += (uint16_t) 0x0605; //second part of sig
    //     footer += (uint16_t) 0; //number of this disk
    //     footer += (uint16_t) 0; //disk where footer starts
    //     footer += (uint16_t) (nrecs+1); //number of records on this disk
    //     footer += (uint16_t) (nrecs+1); //total number of records
    //     footer += (uint32_t) global_header.size(); //nbytes of global headers
    //     footer += (uint32_t) (global_header_offset + nbytes + local_header.size()); //offset of
    //     start of global headers, since global header now starts after newly written array footer
    //     += (uint16_t) 0; //zip file comment length

    //     //write everything
    //     fwrite(&local_header[0],sizeof(char),local_header.size(),fp);
    //     fwrite(&npy_header[0],sizeof(char),npy_header.size(),fp);
    //     fwrite(data,sizeof(T),nels,fp);
    //     fwrite(&global_header[0],sizeof(char),global_header.size(),fp);
    //     fwrite(&footer[0],sizeof(char),footer.size(),fp);
    //     fclose(fp);
    // }

    // template<typename T> void npy_save(std::string fname, const std::vector<T> data, std::string
    // mode = "w") {
    //     std::vector<size_t> shape;
    //     shape.push_back(data.size());
    //     npy_save(fname, &data[0], shape, mode);
    // }

    // template<typename T> void npz_save(std::string zipname, std::string fname, const
    // std::vector<T> data, std::string mode = "w") {
    //     std::vector<size_t> shape;
    //     shape.push_back(data.size());
    //     npz_save(zipname, fname, &data[0], shape, mode);
    // }

    // template<typename T> std::vector<char> create_npy_header(const std::vector<size_t>& shape) {

    //     std::vector<char> dict;
    //     dict += "{'descr': '";
    //     dict += BigEndianTest();
    //     dict += map_type(typeid(T));
    //     dict += std::to_string(sizeof(T));
    //     dict += "', 'fortran_order': False, 'shape': (";
    //     dict += std::to_string(shape[0]);
    //     for(size_t i = 1;i < shape.size();i++) {
    //         dict += ", ";
    //         dict += std::to_string(shape[i]);
    //     }
    //     if(shape.size() == 1) dict += ",";
    //     dict += "), }";
    //     //pad with spaces so that preamble+dict is modulo 16 bytes. preamble is 10 bytes. dict
    //     needs to end with \n int remainder = 16 - (10 + dict.size()) % 16;
    //     dict.insert(dict.end(),remainder,' ');
    //     dict.back() = '\n';

    //     std::vector<char> header;
    //     header += (char) 0x93;
    //     header += "NUMPY";
    //     header += (char) 0x01; //major version of numpy format
    //     header += (char) 0x00; //minor version of numpy format
    //     header += (uint16_t) dict.size();
    //     header.insert(header.end(),dict.begin(),dict.end());

    //     return header;
    // }

#ifdef __cplusplus
}
#endif

#endif // NPIO_H
