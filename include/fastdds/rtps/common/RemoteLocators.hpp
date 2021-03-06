// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file RemoteLocators.hpp
 */

#ifndef _FASTDDS_RTPS_COMMON_REMOTELOCATORS_HPP_
#define _FASTDDS_RTPS_COMMON_REMOTELOCATORS_HPP_

#include <fastdds/rtps/common/Locator.h>
#include <fastrtps/utils/collections/ResourceLimitedVector.hpp>

namespace eprosima {
namespace fastrtps {
namespace rtps {

/**
 * Holds information about the locators of a remote entity.
 */
struct RemoteLocatorList
{
    /**
     * Construct a RemoteLocatorList.
     *
     * @param max_unicast_locators Maximum number of unicast locators to hold.
     * @param max_multicast_locators Maximum number of multicast locators to hold.
     */
    RemoteLocatorList(
            size_t max_unicast_locators,
            size_t max_multicast_locators)
        : unicast(ResourceLimitedContainerConfig::fixed_size_configuration(max_unicast_locators))
        , multicast(ResourceLimitedContainerConfig::fixed_size_configuration(max_multicast_locators))
    {
    }

    /**
     * Copy-construct a RemoteLocatorList.
     *
     * @param other RemoteLocatorList to copy data from.
     */
    RemoteLocatorList(const RemoteLocatorList& other)
        : unicast(ResourceLimitedContainerConfig::fixed_size_configuration(other.unicast.max_size()))
        , multicast(ResourceLimitedContainerConfig::fixed_size_configuration(other.multicast.max_size()))
    {
        *this = other;
    }

    /**
     * Assign locator values from other RemoteLocatorList.
     *
     * @param other RemoteLocatorList to copy data from.
     *
     * @remarks Using the assignment operator is different from copy-constructing as in the first case the
     * configuration with the maximum number of locators is not copied. This means that, for two lists with
     * different maximum number of locators, the expression `(a = b) == b` may not be true.
     */
    RemoteLocatorList& operator = (const RemoteLocatorList& other)
    {
        unicast = other.unicast;
        multicast = other.multicast;
        return *this;
    }

    /**
     * Adds a locator to the unicast list.
     *
     * If the locator already exists in the unicast list, or the maximum number of unicast locators has been reached,
     * the new locator is silently discarded.
     *
     * @param locator Unicast locator to be added.
     */
    void add_unicast_locator(const Locator_t& locator)
    {
        for (const Locator_t& loc : unicast)
        {
            if (loc == locator)
            {
                return;
            }
        }

        unicast.push_back(locator);
    }

    /**
     * Adds a locator to the multicast list.
     *
     * If the locator already exists in the multicast list, or the maximum number of multicast locators has been reached,
     * the new locator is silently discarded.
     *
     * @param locator Multicast locator to be added.
     */
    void add_multicast_locator(const Locator_t& locator)
    {
        for (const Locator_t& loc : multicast)
        {
            if (loc == locator)
            {
                return;
            }
        }

        multicast.push_back(locator);
    }

    //! List of unicast locators
    ResourceLimitedVector<Locator_t> unicast;
    //! List of multicast locators
    ResourceLimitedVector<Locator_t> multicast;
};

} /* namespace rtps */
} /* namespace fastrtps */
} /* namespace eprosima */

#endif /* _FASTDDS_RTPS_COMMON_REMOTELOCATORS_HPP_ */
