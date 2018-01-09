//Azamat
#ifndef NGREST_STRUTILS_H
#define NGREST_STRUTILS_H

#include <string.h>

/**
 * @brief C-string utility module
 */

namespace ngrest {

/**
 * @brief find substring in string
 * @param s source string
 * @param find substring to select
 * @param slen source string length
 * @param flen find string length
 * @return pointer to first match or nullptr if no substring found
 */
inline const char* strnstrn(const char *s, const char *find, size_t slen, size_t flen)
{
    char c;
    char sc;

    if ((c = *find++) != '\0') {
        --flen;
        do {
            do {
                if ((sc = *s++) == '\0' || slen-- < 1)
                    return nullptr;
            } while (sc != c);
            if (flen > slen)
                return nullptr;
        } while (strncmp(s, find, flen) != 0);
        s--;
    }
    return s;
}

/**
 * @brief get next token in mutable string
 *   tokens are delimited with whitespace chars
 * @param curr current string to search and modify
 * @return token
 */
inline char* token(char*& curr) {
    char* start = curr;
    while (*curr != ' ' && *curr != '\t' && *curr != '\n' && *curr != '\r' && *curr != '\0')
        ++curr;
    *curr = '\0';
    ++curr;
    return start;
}

/**
 * @brief get next token in mutable string
 * @param curr current string to search and modify
 * @param delimiter delimiter to use
 * @return token
 */
inline char* token(char*& curr, char delimiter) {
    char* start = curr;
    while (*curr != delimiter && *curr != '\0')
        ++curr;
    *curr = '\0';
    ++curr;
    return start;
}

/**
 * @brief skip whitespace chars
 * @param curr mutable reference to string
 */
inline void skipWs(char*& curr)
{
    while (*curr == ' ' || *curr == '\t' || *curr == '\n' || *curr == '\r')
        ++curr;
}

/**
 * @brief skip data until given char
 * @param curr mutable reference to string
 * @param ch char to find
 * @return true if seek was successful
 */
inline bool seekTo(char*& curr, char ch)
{
    for (; *curr != '\0'; ++curr)
        if (*curr == ch)
            return true;
    return false;
}

/**
 * @brief trim right whitespace chars
 * @param start string start
 * @param end string end
 */
inline void trimRight(char* start, char* end)
{
    char* found = nullptr;
    while ((end > start) && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        found = end;
        --end;
    }

    if (found)
        *found = '\0';
}

/**
 * @brief converts string to lower case
 * @param str mutable string to convert to lower case
 */
inline void toLowerCase(char* str)
{
    for (; *str; ++str)
        *str = tolower(*str);
}

}

#endif // NGREST_STRUTILS_H

