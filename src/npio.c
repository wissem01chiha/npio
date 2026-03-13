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

#include "npio.h"

static const struct
{
    npio_status_t code;
    const char   *msg;
} gaErrorList[] = {
    {NPIO_OK, "Sucess"},
    {NPIO_EOF, "End of the file encountered"},
    {NPIO_EBUF, "Buffer overflow"},
    {NPIO_EDIM, "Array dimensions exceed limits"},
    {NPIO_EFREAD, "Failed to read the file"},
    {NPIO_EFWRITE, "Failed to write the file"},
    {NPIO_EBUF_NULL, "Buffer pointer is NULL"},
    {NPIO_EBUF_SIZE_ZERO, "Buffer size is zero"},
    {NPIO_EBUF_TRUNCATED, "Buffer truncated"},
    {NPIO_EARR_NULL, "Null pointer to array"},
    {NPIO_EARR_DIM, "Dimension exceed allowed"},
    {NPIO_EFOPEN, "Failed to open the file"},
    {NPIO_EUNKNOWN, "Unknown error"},
};

int npio_strerror(npio_status_t statcode, char *buf, npio_size_t bufsize)
{
    if (buf == NULL)
    {
        return NPIO_EBUF_NULL;
    }
    if (bufsize == 0)
    {
        return NPIO_EBUF_SIZE_ZERO;
    }

    npio_size_t i;
    for (i = 0; gaErrorList[i].msg; i++)
    {
        if (statcode == gaErrorList[i].code)
        {
            int s = snprintf(buf, bufsize, "%s", gaErrorList[i].msg);
            if ((npio_size_t) s > bufsize)
            {
                return NPIO_EBUF_TRUNCATED;
            }
            return s;
        }
    }

    return NPIO_EUNKNOWN;
}

const char *npio_error_string(npio_status_t statcode)
{
    npio_size_t i;
    for (i = 0; gaErrorList[i].msg; i++)
    {
        if (statcode == gaErrorList[i].code)
        {
            return gaErrorList[i].msg;
        }
    }
    return NULL;
}

npy_array_t *npy_array_create(const npio_size_t *dims,
                              npio_size_t        ndim,
                              npio_size_t        word_size,
                              npio_bool_t        fortran_order)
{
    if (ndim == (npio_size_t) 0)
    {
        return NULL;
    }

    npy_array_t *arr = malloc(sizeof(npy_array_t));

    if (arr == NULL)
    {
        return NULL;
    }

    arr->shape.ndim = ndim;
    for (npio_size_t i = 0; i < ndim; i++)
    {
        if (dims[i] == (npio_size_t) 0)
        {
            return NULL;
        }
        arr->shape.shape[i] = dims[i];
    }

    npio_size_t num_vals = 1;
    for (npio_size_t i = 0; i < ndim; i++)
    {
        num_vals *= dims[i];
    }

    arr->word_size     = word_size;
    arr->fortran_order = fortran_order;
    arr->num_vals      = num_vals;
    arr->data          = malloc(num_vals * word_size);

    if (arr->data == NULL)
    {
        free(arr);
        return NULL;
    }

    return arr;
}

void npy_array_destroy(npy_array_t *arr)
{
    if (!arr)
        return;

    free(arr->data);
    free(arr);
}

npio_status_t npy_load(const char *pfname, npy_array_t *parray)
{
    FILE *fp = fopen(pfname, "rb");
    if (!fp)
    {
        return NPIO_EFOPEN;
    }
    if (parray == NULL)
    {
        return NPIO_EARR_NULL;
    }
    char        buffer[NPIO_BUF_SIZE];
    npio_size_t res = fread(buffer, sizeof(char), 11, fp);
    if (res != 11)
    {
        if (feof(fp) == EOF)
        {
            return NPIO_EOF;
        }
        return NPIO_EFREAD;
    }
    char *pheader = fgets(buffer, NPIO_BUF_SIZE, fp);
    if (pheader == NULL)
    {
        return NPIO_EUNKNOWN;
    }

    printf("%s", pheader);
    npio_size_t loc1, loc2;

    return NPIO_OK;
}

npio_status_t npy_read(unsigned char     *buffer,
                       npio_size_t       *word_size,
                       const npy_shape_t *pshape,
                       npio_bool_t       *fortran_order)
{
    if (buffer == NULL)
    {
        return NPIO_EBUF_NULL;
    }

    return NPIO_OK;
}

npio_status_t npy_save(npy_array_t *parray, const char *pfname)
{
    if (parray == NULL)
    {
        return NPIO_EARR_NULL;
    }

    return NPIO_OK;
}

npio_status_t
npy_fs_read(FILE *fp, npio_size_t word_size, const npy_shape_t *pshape, npio_bool_t fortran_order)
{
    return NPIO_OK;
}

npio_status_t npz_load(const char *pfname, npz_t *pnpz, npy_array_t *parray)
{
    FILE *fp = fopen(pfname, "rb");
    if (!fp)
    {
        return NPIO_EFREAD;
    }
    fclose(fp);
    return NPIO_OK;
}

npio_status_t npz_array_load(const char *pfname, const char *pvarname, npy_array_t *parray)
{
    return NPIO_OK;
}

npio_status_t npz_save(const char        *pzipname,
                       const char        *pfname,
                       const char        *data,
                       const npy_shape_t *pshape,
                       const char        *pmode)
{
    return NPIO_OK;
}

npio_status_t npio_zip_read(FILE         *fp,
                            npio_uint16_t nrecs,
                            npio_size_t   global_header_size,
                            npio_size_t   global_header_offset)
{
    return NPIO_OK;
}

// char BigEndianTest() {
//     int x = 1;
//     return (((char *)&x)[0]) ? '<' : '>';
// }

// char map_type(const std::type_info& t)
// {
//     if(t == typeid(float) ) return 'f';
//     if(t == typeid(double) ) return 'f';
//     if(t == typeid(long double) ) return 'f';

//     if(t == typeid(int) ) return 'i';
//     if(t == typeid(char) ) return 'i';
//     if(t == typeid(short) ) return 'i';
//     if(t == typeid(long) ) return 'i';
//     if(t == typeid(long long) ) return 'i';

//     if(t == typeid(unsigned char) ) return 'u';
//     if(t == typeid(unsigned short) ) return 'u';
//     if(t == typeid(unsigned long) ) return 'u';
//     if(t == typeid(unsigned long long) ) return 'u';
//     if(t == typeid(unsigned int) ) return 'u';

//     if(t == typeid(bool) ) return 'b';

//     if(t == typeid(std::complex<float>) ) return 'c';
//     if(t == typeid(std::complex<double>) ) return 'c';
//     if(t == typeid(std::complex<long double>) ) return 'c';

//     else return '?';
// }

// template<> std::vector<char>& operator+=(std::vector<char>& lhs, const std::string rhs) {
//     lhs.insert(lhs.end(),rhs.begin(),rhs.end());
//     return lhs;
// }

// template<> std::vector<char>& operator+=(std::vector<char>& lhs, const char* rhs) {
//     //write in little endian
//     size_t len = strlen(rhs);
//     lhs.reserve(len);
//     for(size_t byte = 0; byte < len; byte++) {
//         lhs.push_back(rhs[byte]);
//     }
//     return lhs;
// }

// void parse_npy_header(unsigned char* buffer,size_t& word_size, std::vector<size_t>& shape, bool&
// fortran_order) {
//     //std::string magic_string(buffer,6);
//     uint8_t major_version = *reinterpret_cast<uint8_t*>(buffer+6);
//     uint8_t minor_version = *reinterpret_cast<uint8_t*>(buffer+7);
//     uint16_t header_len = *reinterpret_cast<uint16_t*>(buffer+8);
//     std::string header(reinterpret_cast<char*>(buffer+9),header_len);

//     size_t loc1, loc2;

//     //fortran order
//     loc1 = header.find("fortran_order")+16;
//     fortran_order = (header.substr(loc1,4) == "True" ? true : false);

//     //shape
//     loc1 = header.find("(");
//     loc2 = header.find(")");

//     std::regex num_regex("[0-9][0-9]*");
//     std::smatch sm;
//     shape.clear();

//     std::string str_shape = header.substr(loc1+1,loc2-loc1-1);
//     while(std::regex_search(str_shape, sm, num_regex)) {
//         shape.push_back(std::stoi(sm[0].str()));
//         str_shape = sm.suffix().str();
//     }

//     //endian, word size, data type
//     //byte order code | stands for not applicable.
//     //not sure when this applies except for byte array
//     loc1 = header.find("descr")+9;
//     bool littleEndian = (header[loc1] == '<' || header[loc1] == '|' ? true : false);
//     assert(littleEndian);

//     //char type = header[loc1+1];
//     //assert(type == map_type(T));

//     std::string str_ws = header.substr(loc1+2);
//     loc2 = str_ws.find("'");
//     word_size = atoi(str_ws.substr(0,loc2).c_str());
// }

// void parse_npy_header(FILE* fp, size_t& word_size, std::vector<size_t>& shape, bool&
// fortran_order) {
//     char buffer[256];
//     size_t res = fread(buffer,sizeof(char),11,fp);
//     if(res != 11)
//         throw std::runtime_error("parse_npy_header: failed fread");
//     std::string header = fgets(buffer,256,fp);
//     assert(header[header.size()-1] == '\n');

//     size_t loc1, loc2;

//     //fortran order
//     loc1 = header.find("fortran_order");
//     if (loc1 == std::string::npos)
//         throw std::runtime_error("parse_npy_header: failed to find header keyword:
//         'fortran_order'");
//     loc1 += 16;
//     fortran_order = (header.substr(loc1,4) == "True" ? true : false);

//     //shape
//     loc1 = header.find("(");
//     loc2 = header.find(")");
//     if (loc1 == std::string::npos || loc2 == std::string::npos)
//         throw std::runtime_error("parse_npy_header: failed to find header keyword: '(' or ')'");

//     std::regex num_regex("[0-9][0-9]*");
//     std::smatch sm;
//     shape.clear();

//     std::string str_shape = header.substr(loc1+1,loc2-loc1-1);
//     while(std::regex_search(str_shape, sm, num_regex)) {
//         shape.push_back(std::stoi(sm[0].str()));
//         str_shape = sm.suffix().str();
//     }

//     //endian, word size, data type
//     //byte order code | stands for not applicable.
//     //not sure when this applies except for byte array
//     loc1 = header.find("descr");
//     if (loc1 == std::string::npos)
//         throw std::runtime_error("parse_npy_header: failed to find header keyword: 'descr'");
//     loc1 += 9;
//     bool littleEndian = (header[loc1] == '<' || header[loc1] == '|' ? true : false);
//     assert(littleEndian);

//     //char type = header[loc1+1];
//     //assert(type == map_type(T));

//     std::string str_ws = header.substr(loc1+2);
//     loc2 = str_ws.find("'");
//     word_size = atoi(str_ws.substr(0,loc2).c_str());
// }

// void parse_zip_footer(FILE* fp, uint16_t& nrecs, size_t& global_header_size, size_t&
// global_header_offset)
// {
//     std::vector<char> footer(22);
//     fseek(fp,-22,SEEK_END);
//     size_t res = fread(&footer[0],sizeof(char),22,fp);
//     if(res != 22)
//         throw std::runtime_error("parse_zip_footer: failed fread");

//     uint16_t disk_no, disk_start, nrecs_on_disk, comment_len;
//     disk_no = *(uint16_t*) &footer[4];
//     disk_start = *(uint16_t*) &footer[6];
//     nrecs_on_disk = *(uint16_t*) &footer[8];
//     nrecs = *(uint16_t*) &footer[10];
//     global_header_size = *(uint32_t*) &footer[12];
//     global_header_offset = *(uint32_t*) &footer[16];
//     comment_len = *(uint16_t*) &footer[20];

//     assert(disk_no == 0);
//     assert(disk_start == 0);
//     assert(nrecs_on_disk == nrecs);
//     assert(comment_len == 0);
// }

// NpyArray load_the_npy_file(FILE* fp) {
//     std::vector<size_t> shape;
//     size_t word_size;
//     bool fortran_order;
//     parse_npy_header(fp,word_size,shape,fortran_order);

//     NpyArray arr(shape, word_size, fortran_order);
//     size_t nread = fread(arr.data<char>(),1,arr.num_bytes(),fp);
//     if(nread != arr.num_bytes())
//         throw std::runtime_error("load_the_npy_file: failed fread");
//     return arr;
// }

// NpyArray load_the_npz_array(FILE* fp, uint32_t compr_bytes, uint32_t uncompr_bytes) {

//     std::vector<unsigned char> buffer_compr(compr_bytes);
//     std::vector<unsigned char> buffer_uncompr(uncompr_bytes);
//     size_t nread = fread(&buffer_compr[0],1,compr_bytes,fp);
//     if(nread != compr_bytes)
//         throw std::runtime_error("load_the_npy_file: failed fread");

//     int err;
//     z_stream d_stream;

//     d_stream.zalloc = Z_NULL;
//     d_stream.zfree = Z_NULL;
//     d_stream.opaque = Z_NULL;
//     d_stream.avail_in = 0;
//     d_stream.next_in = Z_NULL;
//     err = inflateInit2(&d_stream, -MAX_WBITS);

//     d_stream.avail_in = compr_bytes;
//     d_stream.next_in = &buffer_compr[0];
//     d_stream.avail_out = uncompr_bytes;
//     d_stream.next_out = &buffer_uncompr[0];

//     err = inflate(&d_stream, Z_FINISH);
//     err = inflateEnd(&d_stream);

//     std::vector<size_t> shape;
//     size_t word_size;
//     bool fortran_order;
//     parse_npy_header(&buffer_uncompr[0],word_size,shape,fortran_order);

//     NpyArray array(shape, word_size, fortran_order);

//     size_t offset = uncompr_bytes - array.num_bytes();
//     memcpy(array.data<unsigned char>(),&buffer_uncompr[0]+offset,array.num_bytes());

//     return array;
// }

// npz_t npz_load(std::string fname) {
//     FILE* fp = fopen(fname.c_str(),"rb");

//     if(!fp) {
//         throw std::runtime_error("npz_load: Error! Unable to open file "+fname+"!");
//     }

//     npz_t arrays;

//     while(1) {
//         std::vector<char> local_header(30);
//         size_t headerres = fread(&local_header[0],sizeof(char),30,fp);
//         if(headerres != 30)
//             throw std::runtime_error("npz_load: failed fread");

//         //if we've reached the global header, stop reading
//         if(local_header[2] != 0x03 || local_header[3] != 0x04) break;

//         //read in the variable name
//         uint16_t name_len = *(uint16_t*) &local_header[26];
//         std::string varname(name_len,' ');
//         size_t vname_res = fread(&varname[0],sizeof(char),name_len,fp);
//         if(vname_res != name_len)
//             throw std::runtime_error("npz_load: failed fread");

//         //erase the lagging .npy
//         varname.erase(varname.end()-4,varname.end());

//         //read in the extra field
//         uint16_t extra_field_len = *(uint16_t*) &local_header[28];
//         if(extra_field_len > 0) {
//             std::vector<char> buff(extra_field_len);
//             size_t efield_res = fread(&buff[0],sizeof(char),extra_field_len,fp);
//             if(efield_res != extra_field_len)
//                 throw std::runtime_error("npz_load: failed fread");
//         }

//         uint16_t compr_method = *reinterpret_cast<uint16_t*>(&local_header[0]+8);
//         uint32_t compr_bytes = *reinterpret_cast<uint32_t*>(&local_header[0]+18);
//         uint32_t uncompr_bytes = *reinterpret_cast<uint32_t*>(&local_header[0]+22);

//         if(compr_method == 0) {arrays[varname] = load_the_npy_file(fp);}
//         else {arrays[varname] = load_the_npz_array(fp,compr_bytes,uncompr_bytes);}
//     }

//     fclose(fp);
//     return arrays;
// }

// NpyArray npz_load(std::string fname, std::string varname) {
//     FILE* fp = fopen(fname.c_str(),"rb");

//     if(!fp) throw std::runtime_error("npz_load: Unable to open file "+fname);

//     while(1) {
//         std::vector<char> local_header(30);
//         size_t header_res = fread(&local_header[0],sizeof(char),30,fp);
//         if(header_res != 30)
//             throw std::runtime_error("npz_load: failed fread");

//         //if we've reached the global header, stop reading
//         if(local_header[2] != 0x03 || local_header[3] != 0x04) break;

//         //read in the variable name
//         uint16_t name_len = *(uint16_t*) &local_header[26];
//         std::string vname(name_len,' ');
//         size_t vname_res = fread(&vname[0],sizeof(char),name_len,fp);
//         if(vname_res != name_len)
//             throw std::runtime_error("npz_load: failed fread");
//         vname.erase(vname.end()-4,vname.end()); //erase the lagging .npy

//         //read in the extra field
//         uint16_t extra_field_len = *(uint16_t*) &local_header[28];
//         fseek(fp,extra_field_len,SEEK_CUR); //skip past the extra field

//         uint16_t compr_method = *reinterpret_cast<uint16_t*>(&local_header[0]+8);
//         uint32_t compr_bytes = *reinterpret_cast<uint32_t*>(&local_header[0]+18);
//         uint32_t uncompr_bytes = *reinterpret_cast<uint32_t*>(&local_header[0]+22);

//         if(vname == varname) {
//             NpyArray array  = (compr_method == 0) ? load_the_npy_file(fp) :
//             load_the_npz_array(fp,compr_bytes,uncompr_bytes); fclose(fp); return array;
//         }
//         else {
//             //skip past the data
//             uint32_t size = *(uint32_t*) &local_header[22];
//             fseek(fp,size,SEEK_CUR);
//         }
//     }

//     fclose(fp);

//     //if we get here, we haven't found the variable in the file
//     throw std::runtime_error("npz_load: Variable name "+varname+" not found in "+fname);
// }

// NpyArray npy_load(std::string fname) {

//     FILE* fp = fopen(fname.c_str(), "rb");

//     if(!fp) throw std::runtime_error("npy_load: Unable to open file "+fname);

//     NpyArray arr = load_the_npy_file(fp);

//     fclose(fp);
//     return arr;
// }
