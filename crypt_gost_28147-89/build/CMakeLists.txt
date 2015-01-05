cmake_minimum_required (VERSION 2.6) 

project (crypt_gost_28147_89_API)

set (SOURSE_LIBS ../crypt_gost_28147_89_API.c)
set (HEDERS ../crypt_gost_types.h ../crypt_gost_28147_89_API.h)

add_library( ${project} STATIC ${HEDERS} ${SOURSE_LIBS}) #статическая библиотека crypt_gost_28147_89_API
