/**
 * Copyright (c) 2023 Zita Liao (Dolby)
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#ifndef RTC_H265_RTP_PACKETIZER_H
#define RTC_H265_RTP_PACKETIZER_H

#if RTC_ENABLE_MEDIA

#include "h265nalunit.hpp"
#include "rtppacketizer.hpp"

namespace rtc {

// RTP packetization for H265
class RTC_CPP_EXPORT H265RtpPacketizer final : public RtpPacketizer {
public:
	using Separator = NalUnit::Separator;

	// Default clock rate for H265 in RTP
	inline static const uint32_t defaultClockRate = 90 * 1000;

	// Constructs h265 payload packetizer with given RTP configuration.
	// @note RTP configuration is used in packetization process which may change some configuration
	// properties such as sequence number.
	// @param separator NAL unit separator
	// @param rtpConfig  RTP configuration
	// @param maximumFragmentSize maximum size of one NALU fragment
	H265RtpPacketizer(Separator separator, shared_ptr<RtpPacketizationConfig> rtpConfig,
	                  uint16_t maximumFragmentSize = H265NalUnits::defaultMaximumFragmentSize);

	// TODO: deprecate
	H265RtpPacketizer(shared_ptr<RtpPacketizationConfig> rtpConfig,
	                  uint16_t maximumFragmentSize = H265NalUnits::defaultMaximumFragmentSize);

	void incoming(message_vector &messages, const message_callback &send) override;
	void outgoing(message_vector &messages, const message_callback &send) override;

private:
	shared_ptr<H265NalUnits> splitMessage(binary_ptr message);

	const uint16_t maximumFragmentSize;
	const NalUnit::Separator separator;
};

// Dummy wrapper for backward compatibility
class RTC_CPP_EXPORT H265PacketizationHandler final : public MediaHandler {
public:
	H265PacketizationHandler(shared_ptr<H265RtpPacketizer> packetizer)
	    : mPacketizer(std::move(packetizer)) {}

	inline void incoming(message_vector &messages, const message_callback &send) {
		return mPacketizer->incoming(messages, send);
	}
	inline void outgoing(message_vector &messages, const message_callback &send) {
		return mPacketizer->outgoing(messages, send);
	}

private:
	shared_ptr<H265RtpPacketizer> mPacketizer;
};

} // namespace rtc

#endif /* RTC_ENABLE_MEDIA */

#endif /* RTC_H265_RTP_PACKETIZER_H */
