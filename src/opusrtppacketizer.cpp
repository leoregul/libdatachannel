/**
 * Copyright (c) 2020 Filip Klembara (in2core)
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#if RTC_ENABLE_MEDIA

#include "opusrtppacketizer.hpp"

#include <cassert>

namespace rtc {

OpusRtpPacketizer::OpusRtpPacketizer(shared_ptr<RtpPacketizationConfig> rtpConfig)
    : RtpPacketizer(std::move(rtpConfig)) {}

void OpusRtpPacketizer::incoming([[maybe_unused]] message_vector &messages, [[maybe_unused]] const message_callback &send) {}

void OpusRtpPacketizer::outgoing(message_vector &messages, [[maybe_unused]] const message_callback &send) {
	for(auto &message : messages)
		message = packetize(message, false);
}

} // namespace rtc

#endif /* RTC_ENABLE_MEDIA */
