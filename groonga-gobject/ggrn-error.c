/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * Copyright (C) 2013  Kouhei Sutou <kou@clear-code.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <groonga.h>

#include "ggrn-error.h"

GQuark
ggrn_error_quark(void)
{
    return g_quark_from_static_string("ggrn-error-quark");
}

const gchar *
ggrn_error_to_string(GGrnError error)
{
    const gchar *message = "unknown";

    switch (error) {
    case 0:
        message = "succeess";
        break;
    case GGRN_ERROR_END_OF_DATA:
        message = "end of data";
        break;
    case GGRN_ERROR_UNKNOWN_ERROR:
        message = "unknown error";
        break;
    case GGRN_ERROR_OPERATION_NOT_PERMITTED:
        message = "operation not permitted";
        break;
    case GGRN_ERROR_NO_SUCH_FILE_OR_DIRECTORY:
        message = "no such file or directory";
        break;
    case GGRN_ERROR_NO_SUCH_PROCESS:
        message = "no such process";
        break;
    case GGRN_ERROR_INTERRUPTED_FUNCTION_CALL:
        message = "interrupted function call";
        break;
    case GGRN_ERROR_INPUT_OUTPUT_ERROR:
        message = "input output error";
        break;
    case GGRN_ERROR_NO_SUCH_DEVICE_OR_ADDRESS:
        message = "no such device or address";
        break;
    case GGRN_ERROR_ARG_LIST_TOO_LONG:
        message = "arg list too long";
        break;
    case GGRN_ERROR_EXEC_FORMAT_ERROR:
        message = "exec format error";
        break;
    case GGRN_ERROR_BAD_FILE_DESCRIPTOR:
        message = "bad file descriptor";
        break;
    case GGRN_ERROR_NO_CHILD_PROCESSES:
        message = "no child processes";
        break;
    case GGRN_ERROR_RESOURCE_TEMPORARILY_UNAVAILABLE:
        message = "resource temporarily unavailable";
        break;
    case GGRN_ERROR_NOT_ENOUGH_SPACE:
        message = "not enough space";
        break;
    case GGRN_ERROR_PERMISSION_DENIED:
        message = "permission denied";
        break;
    case GGRN_ERROR_BAD_ADDRESS:
        message = "bad address";
        break;
    case GGRN_ERROR_RESOURCE_BUSY:
        message = "resource busy";
        break;
    case GGRN_ERROR_FILE_EXISTS:
        message = "file exists";
        break;
    case GGRN_ERROR_IMPROPER_LINK:
        message = "improper link";
        break;
    case GGRN_ERROR_NO_SUCH_DEVICE:
        message = "no such device";
        break;
    case GGRN_ERROR_NOT_A_DIRECTORY:
        message = "not a directory";
        break;
    case GGRN_ERROR_IS_A_DIRECTORY:
        message = "is a directory";
        break;
    case GGRN_ERROR_INVALID_ARGUMENT:
        message = "invalid argument";
        break;
    case GGRN_ERROR_TOO_MANY_OPEN_FILES_IN_SYSTEM:
        message = "too many open files in system";
        break;
    case GGRN_ERROR_TOO_MANY_OPEN_FILES:
        message = "too many open files";
        break;
    case GGRN_ERROR_INAPPROPRIATE_IO_CONTROL_OPERATION:
        message = "inappropriate IO control operation";
        break;
    case GGRN_ERROR_FILE_TOO_LARGE:
        message = "file too large";
        break;
    case GGRN_ERROR_NO_SPACE_LEFT_ON_DEVICE:
        message = "no space left on device";
        break;
    case GGRN_ERROR_INVALID_SEEK:
        message = "invalid seek";
        break;
    case GGRN_ERROR_READ_ONLY_FILE_SYSTEM:
        message = "read only file system";
        break;
    case GGRN_ERROR_TOO_MANY_LINKS:
        message = "too many links";
        break;
    case GGRN_ERROR_BROKEN_PIPE:
        message = "broken pipe";
        break;
    case GGRN_ERROR_DOMAIN_ERROR:
        message = "domain error";
        break;
    case GGRN_ERROR_RESULT_TOO_LARGE:
        message = "result too large";
        break;
    case GGRN_ERROR_RESOURCE_DEADLOCK_AVOIDED:
        message = "resource deadlock avoided";
        break;
    case GGRN_ERROR_NO_MEMORY_AVAILABLE:
        message = "no memory available";
        break;
    case GGRN_ERROR_FILENAME_TOO_LONG:
        message = "filename too long";
        break;
    case GGRN_ERROR_NO_LOCKS_AVAILABLE:
        message = "no locks available";
        break;
    case GGRN_ERROR_FUNCTION_NOT_IMPLEMENTED:
        message = "function not implemented";
        break;
    case GGRN_ERROR_DIRECTORY_NOT_EMPTY:
        message = "directory not empty";
        break;
    case GGRN_ERROR_ILLEGAL_BYTE_SEQUENCE:
        message = "illegal byte sequence";
        break;
    case GGRN_ERROR_SOCKET_NOT_INITIALIZED:
        message = "socket not initialized";
        break;
    case GGRN_ERROR_OPERATION_WOULD_BLOCK:
        message = "operation would block";
        break;
    case GGRN_ERROR_ADDRESS_IS_NOT_AVAILABLE:
        message = "address is not available";
        break;
    case GGRN_ERROR_NETWORK_IS_DOWN:
        message = "network is down";
        break;
    case GGRN_ERROR_NO_BUFFER:
        message = "no buffer";
        break;
    case GGRN_ERROR_SOCKET_IS_ALREADY_CONNECTED:
        message = "socket is already connected";
        break;
    case GGRN_ERROR_SOCKET_IS_NOT_CONNECTED:
        message = "socket is not connected";
        break;
    case GGRN_ERROR_SOCKET_IS_ALREADY_SHUTDOWNED:
        message = "socket is already shutdowned";
        break;
    case GGRN_ERROR_OPERATION_TIMEOUT:
        message = "operation timeout";
        break;
    case GGRN_ERROR_CONNECTION_REFUSED:
        message = "connection refused";
        break;
    case GGRN_ERROR_RANGE_ERROR:
        message = "range error";
        break;
    case GGRN_ERROR_TOKENIZER_ERROR:
        message = "tokenizer error";
        break;
    case GGRN_ERROR_FILE_CORRUPT:
        message = "file corrupt";
        break;
    case GGRN_ERROR_INVALID_FORMAT:
        message = "invalid format";
        break;
    case GGRN_ERROR_OBJECT_CORRUPT:
        message = "object corrupt";
        break;
    case GGRN_ERROR_TOO_MANY_SYMBOLIC_LINKS:
        message = "too many symbolic links";
        break;
    case GGRN_ERROR_NOT_SOCKET:
        message = "not socket";
        break;
    case GGRN_ERROR_OPERATION_NOT_SUPPORTED:
        message = "operation not supported";
        break;
    case GGRN_ERROR_ADDRESS_IS_IN_USE:
        message = "address is in use";
        break;
    case GGRN_ERROR_ZLIB_ERROR:
        message = "zlib error";
        break;
    case GGRN_ERROR_LZO_ERROR:
        message = "lzo error";
        break;
    case GGRN_ERROR_STACK_OVER_FLOW:
        message = "stack over flow";
        break;
    case GGRN_ERROR_SYNTAX_ERROR:
        message = "syntax error";
        break;
    case GGRN_ERROR_RETRY_MAX:
        message = "retry max";
        break;
    case GGRN_ERROR_INCOMPATIBLE_FILE_FORMAT:
        message = "incompatible file format";
        break;
    case GGRN_ERROR_UPDATE_NOT_ALLOWED:
        message = "update not allowed";
        break;
    case GGRN_ERROR_TOO_SMALL_OFFSET:
        message = "too small offset";
        break;
    case GGRN_ERROR_TOO_LARGE_OFFSET:
        message = "too large offset";
        break;
    case GGRN_ERROR_TOO_SMALL_LIMIT:
        message = "too small limit";
        break;
    case GGRN_ERROR_CAS_ERROR:
        message = "cas error";
        break;
    case GGRN_ERROR_UNSUPPORTED_COMMAND_VERSION:
        message = "unsupported command version";
        break;
    case GGRN_ERROR_NORMALIZER_ERROR:
        message = "normalizer error";
        break;
    default:
        message = "unknown";
        break;
    }

    return message;
}
