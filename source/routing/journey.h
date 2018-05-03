/* Copyright © 2001-2018, Canal TP and/or its affiliates. All rights reserved.

This file is part of Navitia,
    the software to build cool stuff with public transport.

Hope you'll enjoy and contribute to this project,
    powered by Canal TP (www.canaltp.fr).
Help us simplify mobility and open public transport:
    a non ending quest to the responsive locomotion way of traveling!

LICENCE: This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Stay tuned using
twitter @navitia
IRC #navitia on freenode
https://groups.google.com/d/forum/navitia
www.navitia.io
*/

#pragma once

#include "type/type.h"
#include <unordered_set>

namespace navitia {
namespace routing {

struct Journey {
    struct Section {
        Section() = default;
        Section(const type::StopTime& in,
                const DateTime in_dt,
                const type::StopTime& out,
                const DateTime out_dt);
        const type::StopTime* get_in_st = nullptr;
        DateTime get_in_dt = 0;
        const type::StopTime* get_out_st = nullptr;
        DateTime get_out_dt = 0;
        bool operator==(const Section & rhs) const;
    };

    bool better_on_dt(const Journey& that, bool request_clockwise) const;
    bool better_on_transfer(const Journey& that, bool) const;
    bool better_on_sn(const Journey& that, bool) const;
    bool operator==(const Journey & rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Journey& j);

    std::vector<Section> sections;// the pt sections, with transfer between them
    navitia::time_duration sn_dur = 0_s;// street network duration
    navitia::time_duration transfer_dur = 0_s;// walking duration during transfer
    navitia::time_duration min_waiting_dur = 0_s;// minimal waiting duration on every transfers
    DateTime departure_dt = 0;// the departure dt of the journey, including sn
    DateTime arrival_dt = 0;// the arrival dt of the journey, including sn
    uint8_t nb_vj_extentions = 0;// number of vehicle journey extentions (I love useless comments!)
};

struct JourneyHash {
    size_t operator()(const Journey& j) const;
};

struct SectionHash {
    size_t operator()(const Journey::Section& s, size_t seed) const;
};

typedef std::unordered_set<Journey, JourneyHash> JourneySet;

} // namespace routing
} // namespace navitia
