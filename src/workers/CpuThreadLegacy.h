/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
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

#ifndef XMRIG_CPUTHREADLEGACY_H
#define XMRIG_CPUTHREADLEGACY_H


#include "backend/common/interfaces/IThread.h"
#include "crypto/cn/CnHash.h"


struct cryptonight_ctx;


namespace xmrig {


class CpuThreadLegacy : public IThread
{
public:
    struct Data
    {
        inline Data() : valid(false), affinity(-1L), multiway(SingleWay) {}

        inline void setMultiway(int value)
        {
            if (value >= SingleWay && value <= PentaWay) {
                multiway = static_cast<Multiway>(value);
                valid    = true;
            }
        }

        Assembly assembly;
        bool valid;
        int64_t affinity;
        Multiway multiway;
    };


    CpuThreadLegacy(size_t index, Algorithm algorithm, CnHash::AlgoVariant av, Multiway multiway, int64_t affinity, int priority, bool softAES, bool prefetch, Assembly assembly);

    cn_hash_fun fn(const Algorithm &algorithm) const;

    static bool isSoftAES(CnHash::AlgoVariant av);
    static CpuThreadLegacy *createFromAV(size_t index, const Algorithm &algorithm, CnHash::AlgoVariant av, int64_t affinity, int priority, Assembly assembly);
    static CpuThreadLegacy *createFromData(size_t index, const Algorithm &algorithm, const CpuThreadLegacy::Data &data, int priority, bool softAES);
    static Data parse(const rapidjson::Value &object);
    static Multiway multiway(CnHash::AlgoVariant av);

    inline bool isPrefetch() const               { return m_prefetch; }
    inline bool isSoftAES() const                { return m_softAES; }

    inline Algorithm algorithm() const override  { return m_algorithm; }
    inline int priority() const override         { return m_priority; }
    inline int64_t affinity() const override     { return m_affinity; }
    inline Multiway multiway() const override    { return m_multiway; }
    inline size_t index() const override         { return m_index; }
    inline Type type() const override            { return CPU; }

protected:
#   ifdef APP_DEBUG
    void print() const override;
#   endif

#   ifdef XMRIG_FEATURE_API
    rapidjson::Value toAPI(rapidjson::Document &doc) const override;
#   endif

    rapidjson::Value toConfig(rapidjson::Document &doc) const override;

private:
    const Algorithm m_algorithm;
    const CnHash::AlgoVariant m_av;
    const Assembly m_assembly;
    const bool m_prefetch;
    const bool m_softAES;
    const int m_priority;
    const int64_t m_affinity;
    const Multiway m_multiway;
    const size_t m_index;
};


} /* namespace xmrig */


#endif /* XMRIG_CPUTHREADLEGACY_H */