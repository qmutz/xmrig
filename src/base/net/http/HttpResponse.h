/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2014-2019 heapwolf    <https://github.com/heapwolf>
 * Copyright 2018-2019 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2019 XMRig       <https://github.com/xmrig>, <support@xmrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef XMRIG_HTTPRESPONSE_H
#define XMRIG_HTTPRESPONSE_H


#include <map>
#include <sstream>
#include <string>


namespace xmrig {


class HttpResponse
{
public:
    HttpResponse(uint64_t id);

    inline void end()                                                       { writeOrEnd("", true); }
    inline void end(const std::string &str)                                 { writeOrEnd(str, true); }
    inline void setHeader(const std::string &key, const std::string &value) { headers.insert({ key, value }); }
    inline void setStatus(int code)                                         { statusCode = code; }
    inline void write(const std::string &str)                               { writeOrEnd(str, false); }

    int statusCode;
    std::map<const std::string, const std::string> headers;
    std::string body;
    std::string statusAdjective; // FIXME

private:
    void writeOrEnd(const std::string &str, bool end);

    bool m_writtenOrEnded = false;
    const uint64_t m_id;
};


} // namespace xmrig


#endif // XMRIG_HTTPRESPONSE_H
